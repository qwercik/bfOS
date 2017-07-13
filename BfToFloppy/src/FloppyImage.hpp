#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace btf
{
	class FloppyImage
	{
	public:
		FloppyImage(const std::string& codeFilename, const std::string& loaderFilename);

		void writeToFile(const std::string& floppyImageFilename);

	private:
		void writeLoader(const std::string& loaderFilename);
		int assignCode(const std::string& codeFilename);
		void replaceFlagWithMachineCode(int brainfuckCodeSize);

		std::vector<uint8_t> imageFileContent;

		const int FLOPPY_SIZE = 1474560;
	};
}
