#pragma once

// This class wraps iNES and NES 2.0 ROM file formats into
// nicelly accessible class that is initialized with filename
// and doesn't care what you do with the data.

#include <stdint.h>
#include <string>
#include <vector>

enum class ConsoleType;
enum class TimingMode;

class NesRomFile
{
	public:
		// Construct from file
		NesRomFile(std::string filename);

		// Queries to flags
		bool getBitFlag(uint8_t flag, uint8_t bit) const;
		// Returns true if specified bit of specified flag is set
		// Uses common byte numbering, so flags start at 6

		// Exact information queries
		bool hasCorrectFormatString() const;
		bool hasVerticalMirroring() const;
		bool hasPersistentMemory() const; // True indicates presense of battery backed memory or other non-volatile memory, must be stored separately
		bool hasTrainer() const;
		bool hasIgnoreMirroring() const; // Usually means four-screen VRAM
		uint16_t getMapperNumber() const;
		uint8_t getSubmapperNumber() const;
		bool isNesVersionTwo() const;
		ConsoleType getConsoleType() const;
		bool hasInstRom() const;
		TimingMode getTimingMode() const;
		uint8_t getMiscRomCount() const;
		uint8_t getDefaultExpansionDevice() const;
		// These return actual size in byte, zero if the part doesn't exist
		uint64_t getPrgRomSize() const;
		uint64_t getChrRomSize() const;
		uint64_t getPrgRamSize() const;
		uint64_t getPrgNvramSize() const;
		uint64_t getEepromSize() const;
		uint64_t getChrRamSize() const;
		uint64_t getChrNvramSize() const;

	private:
		// 16 byte header
		uint8_t header[16];
		// Bytes 0-3, Identification, must be 0x4E 0x45 0x53 0x1A, for "NES" + MS-DOS end-of-file;
		// Byte 4, prgSize, size of PRG ROM in 16 KB units, LSB in v2.0
		// Byte 5, chrSize; size of CHR ROM in 8 KB units, 0 means CHR RAM is used instead, LSB in v2.0
		// Starting from byte 6, flags, with numbers continuing with byte
		// Flags 6 NNNN FTBM
		// M Hard-wired nametable mirroring, 0 horisontal or mapper controlled, 1 vertical
		// B Battery or other non-volatile memory
		// T Trainer
		// F Hard-Wired four screen mode
		// NNNN mapper number bits 0-3
		// Flags 7 NNNN VVTT
		// TT Console Type, 0 NES or Famicom, 1 Vs. System, 2 PlayChoise 10, 3 Extended
		// VV ROM file format version, 10 for Nes 2.0
		// NNNN mapper number bits 4-7
		// Flags 8 SSSS NNNN
		// NNNN Mapper number bits 8-11
		// SSSS Submapper number
		// Flags 9 CCCC PPPP
		// PPPP PRG-ROM size, MSB
		// CCCC CHR-ROM size, MSB
		// Flags 10 pppp PPPP
		// PPPP PRG-RAM volatile shift count, 0 = no prg-ram, 64 << PPPP for size of prg-ram
		// pppp PRG-NVRAM/EEPROM shift count
		// Flags 11 cccc CCCC
		// CCCC CHR-RAM shift count
		// cccc CHR-NVRAM shift count
		// Flags 12 .... ..VV
		// VV CPU/PPU timing mode, 0 RP2CO2 NTSC NES, 1 RP2CO7 Licensed PAL NES, 2 Multple-region, 3 UMC 6527P Dendy
		// Flags 13 if (flags 7 & EOF) = 1: MMMM PPPP, if (flags 7 & EOF) = 3: .... CCCC
		// PPPP Vs. PPU Type
		// MMMM Vs. Hardware Type
		// CCCC Extended Console Type
		// Flags 14 .... ..RR
		// RR number of misc ROMs present
		// Flags 15 ..DD DDDD
		// DDDDDD Default Expansion Device

		// optional 512 bytes of trainer
		std::vector<uint8_t> trainer;
		// prgSize * 16384 bytes of PRG ROM
		std::vector<uint8_t> prgRom;
		// chrSize * 8194 bytes of CHR ROM if present
		std::vector<uint8_t> chrRom;

		// Set to true if there are no problems during reading of the file
		bool functional = false;
};
