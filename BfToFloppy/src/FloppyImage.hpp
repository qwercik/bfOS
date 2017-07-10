#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

namespace btf
{
	class FloppyImage
	{
	public:
		FloppyImage(const std::string& filename);
		
		void create(const std::string& codeFilename, const std::string& loaderFilename);

	private:
		void overwriteMbr(const std::string& mbrFilename);
		void assignCode(const std::string& codeFilename);

		std::ofstream imageFile;
		std::vector<uint8_t> imageFileContent;
	};
}
