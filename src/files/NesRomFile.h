#pragma once

// This class wraps iNES and NES 2.0 ROM file formats into
// nicelly accessible class that is initialized with filename
// and doesn't care what you do with the data.

#include <stdint.h>
#include <string>
#include <vector>

enum class ConsoleType;

class NesRomFile
{
	public:
		NesRomFile(std::string filename);

		bool getFlag(uint8_t flag, uint8_t bit);
		// Returns true if specified bit of specified flag is set
		// Uses common byte numbering, so flags start at 6

		bool hasCorrectFormatString();
		bool hasVerticalMirroring();
		bool hasPersistentMemory();
		bool hasTrainer();
		bool hasIgnoreMirroring(); // Usually means four-screen VRAM
		uint8_t mapperNumber();
		bool isNesVersionTwo();
		ConsoleType getConsoleType();

	private:
		// 16 byte header
		uint8_t formatString[4]; // Must be 0x4E 0x45 0x53 0x1A, for "NES" + MS-DOS end-of-file;
		uint8_t prgSize; // Size of PRG ROM in 16 KB units
		uint8_t chrSize; // Size of CHR ROM in 8 KB units, 0 means CHR RAM is used instead
		uint8_t flags[5];
		// Flags 6 NNNN FTBM
		// M Hard-wired nametable mirroring, 0 horisontal or mapper controlled, 1 vertical
		// B Battery or other non-volatile memory
		// T Trainer
		// F Hard-Wired four screen mode
		//
		uint8_t padding[5];
		// optional 512 bytes of trainer
		std::vector<uint8_t> trainer;
		// prgSize * 16384 bytes of PRG ROM
		std::vector<uint8_t> prgRom;
		// chrSize * 8194 bytes of CHR ROM if present
		std::vector<uint8_t> chrRom;
		// PlayChoice INST-ROM if present, 8192 bytes
		std::vector<uint8_t> instRom;
		// PlayChoice PROM if present, 16 bytes each
		std::vector<uint8_t> promData;
		std::vector<uint8_t> promCounterOut;

		bool functional = false;
};
