#include <iostream>
#include <fstream>
#include <string>

#include "FloppyImage.hpp"
#include "Error.hpp"

void displayHelp(std::ostream& ostream);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Incorrect usage.\n";
		displayHelp(std::cerr);
		return EXIT_FAILURE;
	}
	else if (std::string(argv[1]) == "--help")
	{
		displayHelp(std::cout);
	}

	std::string floppyImageFilename = argv[1];
	std::string codeFilename = argv[2];
	std::string loaderFilename = "loader.bin";

	try
	{
		btf::FloppyImage floppyImage(floppyImageFilename);
		floppyImage.create(codeFilename, loaderFilename);
	}
	catch (btf::Error& error)
	{
		std::cerr << "An error has ocurred\n";
		std::cerr << "Message: " << error.what() << "\n";
		return EXIT_FAILURE;
	}

	std::cout << "Floppy image " << floppyImageFilename << " has been created.\n";
}

void displayHelp(std::ostream& ostream)
{
	ostream << "Use: ./BfToFloppy <floppy_image> <code>\n";
	ostream << "Where:\n";
	ostream << "<floppy_image> is file you want to generate\n";
	ostream << "<code> is file with brainfuck source code\n";
}
