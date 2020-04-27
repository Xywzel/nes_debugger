#include <iostream>
#include <fstream>

#include "Emulator.h"

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " path/to/rom" << std::endl;
		return 1;
	}

	{
		std::ifstream f(argv[1]);
		if (!f.good())
		{
			std::cout << "File " << argv[1] << " can't be openned, check that it exists and you have permission to read it" << std::endl;
			return 1;
		}
	}

	Emulator emulator(argv[1]);
	emulator.run();
	return 0;
}
