#include <iostream>
#include <fstream>
#include <string>

#include "FloppyImage.hpp"
#include "Error.hpp"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Incorrect usage.\n";
		std::cerr << "Use: " << argv[0] << " floppy.img code.bf\n";
		return 1;
	}

	std::string floppyImageFilename = argv[1];
	std::string codeFilename = argv[2];
	
	try
	{
		btf::FloppyImage floppyImage(floppyImageFilename);
		floppyImage.create(codeFilename);
	}
	catch (btf::Error& error)
	{
		std::cerr << "An error has ocurred\n";
		std::cerr << "Message: " << error.what() << "\n";
		return 2;
	}

	std::cout << "Floppy image " << floppyImageFilename << " has been created.\n";
}
