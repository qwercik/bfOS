#include <string>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <cmath>

#include "FloppyImage.hpp"
#include "Error.hpp"

namespace btf
{
	FloppyImage::FloppyImage(const std::string& filename)
	{
		imageFile.open(filename, std::ios::binary);

		if (!imageFile.is_open())
			throw Error("Couldn\'t open floppy image file (" + filename + ") to write");
	}

	void FloppyImage::create(const std::string& codeFilename, const std::string& mbrFilename)
	{
		// Fills image with zeros to 1.44MB
		imageFileContent.assign(1474560, 0);
		
		overwriteMbr(mbrFilename);
		assignCode(codeFilename);		

		std::copy(imageFileContent.begin(), imageFileContent.end(), std::ostreambuf_iterator<char>(imageFile));
	}

	void FloppyImage::overwriteMbr(const std::string& mbrFilename)
	{
		std::ifstream mbrFile(mbrFilename, std::ios::binary);

		if (!mbrFile.is_open())
			throw Error("Couldn\'t find MBR file: " + mbrFilename);

		std::vector<char> mbr((std::istreambuf_iterator<char>(mbrFile)), std::istreambuf_iterator<char>());
		
		imageFileContent.erase(imageFileContent.begin(), imageFileContent.begin() + 512);
		imageFileContent.insert(imageFileContent.begin(), mbr.begin(), mbr.end());
	}
	
	void FloppyImage::assignCode(const std::string& codeFilename)
	{
		std::ifstream codeFile(codeFilename);

		if (!codeFile.is_open())
			throw Error("Couldn\'t open file (" + codeFilename + ") with brainfuck source code.");

		std::string code;
		std::getline(codeFile, code, '\0');
		
		if (code.size() == 0)
			throw Error("File(" + codeFilename + ") with brainfuck source code is empty");

		if (code.size() > 65536)
			throw Error("Accteptable brainfuck source code size is 64KiB");
		
		imageFileContent.erase(imageFileContent.begin() + 512, imageFileContent.begin() + 512 + code.size());
		imageFileContent.insert(imageFileContent.begin() + 512, code.begin(), code.end());

		uint8_t sectorsAmount = std::ceil(code.size() / 512.0);
		
		std::vector<uint8_t> flag = {0xDE, 0xC0, 0xBF, 0x00};
		auto iterator = std::search(imageFileContent.begin(), imageFileContent.end(), flag.begin(), flag.end()); 

		if (iterator == imageFileContent.end())
			throw Error("MBR file doesn\'t contain 0xBFC0DE flag");

		std::vector<uint8_t> opcode = {0xB0, static_cast<uint8_t>(sectorsAmount & 0xFF), 0x90, 0x90};
		imageFileContent.erase(iterator, iterator + 4);
		imageFileContent.insert(iterator, opcode.begin(), opcode.end());
	}
}
