#include "NesRomFile.h"
#include "files/InputFile.h"
#include "hardware/ConsoleType.h"
#include "hardware/TimingMode.h"

#include <fstream>
#include <iostream>

NesRomFile::NesRomFile(std::string filename)
{
	InputFile input(filename);
	if(!input.isGood())
		return;

	input.read(header, 16);
	std::cout << "Header read" << std::endl;
	if (!hasCorrectFormatString())
	{
		std::cout << "Format String not correct" << std::endl;
		return;
	}

	if(hasTrainer())
	{
		std::cout << "Reading trainer" << std::endl;
		trainer.resize(512);
		input.read(trainer);
	}

	{
		prgRom.resize(getPrgRomSize());
		input.read(prgRom);
	}

	{
		chrRom.resize(getChrRomSize());
		input.read(chrRom);
	}

	// Rest is misc ROMs until end of the file
	// Currently they are used in 3 cases
	// 1 ConsoleType = PlayChoise 10, 8 KiB of INST-ROM, 16 bytes of PROM and 16 bytes PROM Counter Out
	if (getConsoleType() == ConsoleType::NintendoPlaychoice10)
	{

	}
	// 2 INES Mapper 086 Submapper 1, a single misc ROM with speech data
	else if (getMapperNumber() == 86 && getSubmapperNumber() == 1)
	{

	}
	// 3 NES 2.0 Mapper 355, empeded ROM of the PIC16C54 microcontroller, used for protection
	else if (getMapperNumber() == 355)
	{

	}

	functional = true;
}

bool NesRomFile::getBitFlag(uint8_t flag, uint8_t bit) const
{
	uint8_t data = header[flag];
	return (data & (1u << bit));
}

bool NesRomFile::hasCorrectFormatString() const
{
	// Format identification string is first 4 bytes of header, and should always be "NES<EOF>"
	return header[0] == 0x4E && header[1] == 0x45 && header[2] == 0x53 && header[3] == 0x1A;
}

bool NesRomFile::hasVerticalMirroring() const
{
	return getBitFlag(6, 0);
}

bool NesRomFile::hasPersistentMemory() const
{
	return getBitFlag(6, 1);
}

bool NesRomFile::hasTrainer() const
{
	return getBitFlag(6, 2);
}

bool NesRomFile::hasIgnoreMirroring() const
{
	return getBitFlag(6, 3);
}

uint16_t NesRomFile::getMapperNumber() const
{
	uint8_t low = (0b11110000 & header[6]) >> 4;
	uint8_t high = (0b11110000 & header[7]);
	uint8_t extra = (0b00001111 & header[8]);
	uint8_t low_byte = low | high;
	uint16_t whole = (extra << 8) | uint16_t(low_byte);
	return whole;
}

uint8_t NesRomFile::getSubmapperNumber() const
{
	uint8_t number = (0b11110000 & header[8]) >> 4;
	return number;
}

bool NesRomFile::isNesVersionTwo() const
{
	return getBitFlag(7, 3) && !getBitFlag(7, 2);
}

ConsoleType NesRomFile::getConsoleType() const
{
	uint8_t consoleType = (header[7] & 0b00000011);
	switch (consoleType)
	{
		case 0:
			return ConsoleType::NintendoEntertainmentSystem;
		case 1:
			return ConsoleType::NintendoVsSystem;
		case 2:
			return ConsoleType::NintendoPlaychoice10;
		case 3:
			{
				// Extended Console Type handling here
				return ConsoleType::Unsupported;
			}
		default:
			return ConsoleType::Unsupported;
	}
}

bool NesRomFile::hasInstRom() const
{
	return false;
}

uint8_t NesRomFile::getMiscRomCount() const
{
	uint8_t count = (header[14] & 0b00000011);
	return count;
}

uint8_t NesRomFile::getDefaultExpansionDevice() const
{
	return header[15];
}

uint64_t NesRomFile::getPrgRomSize() const
{
	uint8_t low = header[4];
	uint8_t high = (0b00001111 & header[9]);
	uint64_t total = (uint64_t(high) << 8) | (uint64_t(low)) * 16384;

	if (high == 0xF)
	{
		uint64_t multiplier = uint64_t(low & 0b00000011) * 2 + 1;
		uint64_t exponent = uint64_t(low & 0b11111100);
		// 2^exponent * multiplier
		total = (1 << exponent) * multiplier;
	}

	return total;
}

uint64_t NesRomFile::getChrRomSize() const
{
	uint8_t low = header[4];
	uint8_t high = (0b00001111 & header[9]);
	uint64_t total = (uint64_t(high) << 8) | (uint64_t(low)) * 8194;

	if (high == 0xF)
	{
		uint64_t multiplier = uint64_t(low & 0b00000011) * 2 + 1;
		uint64_t exponent = uint64_t(low & 0b11111100);
		// 2^exponent * multiplier
		total = (1 << exponent) * multiplier;
	}
	return total;
}

uint64_t NesRomFile::getPrgRamSize() const
{
	uint64_t shift = uint64_t(0b00001111 & header[10]);
	return 64u << shift;
}

uint64_t NesRomFile::getPrgNvramSize() const
{
	uint64_t shift = uint64_t((0b11110000 & header[10]) >> 4);
	return 64u << shift;
}

uint64_t NesRomFile::getChrRamSize() const
{
	uint64_t shift = uint64_t(0b00001111 & header[11]);
	return 64u << shift;
}

uint64_t NesRomFile::getChrNvramSize() const
{
	uint64_t shift = uint64_t((0b11110000 & header[11]) >> 4);
	return 64u << shift;
}
