#include "NesRomFile.h"
#include "files/InputFile.h"
#include "hardware/ConsoleType.h"

#include <fstream>
#include <iostream>

NesRomFile::NesRomFile(std::string filename)
{
	InputFile input(filename);
	if(!input.isGood())
		return;

	input.read(formatString, 4);
	if (!hasCorrectFormatString())
		return;

	std::cout << "Format String correct" << std::endl;
	input >> prgSize;
	input >> chrSize;
	input.read(flags, 5);
	input.read(padding, 5);
	std::cout << "Header read" << std::endl;

	if(hasTrainer())
	{
		std::cout << "Header read" << std::endl;
		trainer.resize(512);
		input.read(trainer);
	}

	
	functional = true;
}

bool NesRomFile::getFlag(uint8_t flag, uint8_t bit)
{
	uint8_t data = flags[flag-6];
	return (data & (1u << bit));
}


bool NesRomFile::hasCorrectFormatString()
{
	return formatString[0] == 0x4E && formatString[1] == 0x45 && formatString[2] == 0x53 && formatString[3] == 0x1A;
}

bool NesRomFile::hasVerticalMirroring()
{
	return getFlag(6, 0);
}

bool NesRomFile::hasPersistentMemory()
{
	return getFlag(6, 1);
}

bool NesRomFile::hasTrainer()
{
	return getFlag(6, 2);
}

bool NesRomFile::hasIgnoreMirroring()
{
	return getFlag(6, 3);
}

uint8_t NesRomFile::mapperNumber()
{
	uint8_t low = (0b11110000 & flags[0]) >> 4;
	uint8_t high = (0b00001111 & flags[1]) << 4;
	return low | high;
}

bool NesRomFile::isNesVersionTwo()
{
	return getFlag(7u, 3) && !getFlag(7, 2);
}

ConsoleType NesRomFile::getConsoleType()
{
	if(!getFlag(7, 0) && getFlag(7, 1))
		return ConsoleType::NintendoEntertainmentSystem;
	return ConsoleType::Unsupported;
}
