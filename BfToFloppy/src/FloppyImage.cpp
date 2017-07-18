#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <cmath>

#include "FloppyImage.hpp"
#include "Error.hpp"

namespace btf
{
	FloppyImage::FloppyImage(const std::string& codeFilename, const std::string& loaderFilename)
	{
		imageFileContent.assign(FLOPPY_SIZE, 0);

		int loaderSize = writeLoader(loaderFilename);
		int codeSize = assignCode(codeFilename, loaderSize);
		replaceFlagWithMachineCode(codeSize);
	}

	void FloppyImage::writeToFile(const std::string& floppyImageFilename)	
	{
		std::ofstream imageFile(floppyImageFilename, std::ios::binary);

		if (!imageFile.is_open())
			throw Error("Couldn\'t open floppy image file (" + floppyImageFilename + ") to write");

		std::copy(imageFileContent.begin(), imageFileContent.end(), std::ostreambuf_iterator<char>(imageFile));
	}

	int FloppyImage::writeLoader(const std::string& loaderFilename)
	{
		std::ifstream loaderFile(loaderFilename, std::ios::binary);

		if (!loaderFile.is_open())
			throw Error("Couldn\'t find MBR file: " + loaderFilename);

		std::vector<char> loader((std::istreambuf_iterator<char>(loaderFile)), std::istreambuf_iterator<char>());
		std::copy(loader.begin(), loader.end(), imageFileContent.begin());

		return loader.size();
	}
	
	int FloppyImage::assignCode(const std::string& codeFilename, int offset)
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
		
		std::copy(code.begin(), code.end(), imageFileContent.begin() + offset); 

		return code.size();
	}

	void FloppyImage::replaceFlagWithMachineCode(int codeSize)
	{
		uint8_t sectorsAmount = std::ceil(codeSize / 512.0);
		
		std::vector<uint8_t> flag = {0xDE, 0xC0, 0xBF, 0x00};
		auto iterator = std::search(imageFileContent.begin(), imageFileContent.end(), flag.begin(), flag.end());

		if (iterator == imageFileContent.end())
			throw Error("Loader file doesn\'t contain 0xBFC0DE flag");

		/* Opcode as asm mnemonics:
		 * mov al, sectorsAmount
		 * nop
		 * nop
		 */
		
		std::vector<uint8_t> opcode = {0xB0, static_cast<uint8_t>(sectorsAmount & 0xFF), 0x90, 0x90};
		
		std::copy(opcode.begin(), opcode.end(), iterator);
	}
}
