#include "NesRomFile.h"

#include <fstream>

NesRomFile::NesRomFile(std::string filename)
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (! file.is_open())
		return;

	file >> formatString;
	if (!hasCorrectFormatString())
		return;
	
	
	functional = true;
}

bool NesRomFile::hasCorrectFormatString()
{
	return formatString[0] == 0x4E && formatString[1] == 0x45 && formatString[2] == 0x53 && formatString[3] == 0x1A;
}

bool NesRomFile::hasVerticalMirroring()
{
	return false;
}
