#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace btf
{
	class FloppyImage
	{
	public:
		FloppyImage(const std::string& filename);
		
		void create(const std::string& codeFilename, std::string mbrFilename = "bfOS.img");

	private:
		void overwriteMbr(const std::string& mbrFilename);
		void assignCode(const std::string& codeFilename);

		std::ofstream imageFile;
		std::vector<char> imageFileContent;
	};
}
