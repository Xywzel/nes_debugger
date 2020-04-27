#pragma once

#include <stdint.h>

class AudioProcessingUnit;
class PictureProcessingUnit;
class Cartridge;


class CentralProcessingUnit
{
	public:
		CentralProcessingUnit();
		CentralProcessingUnit(AudioProcessingUnit* apu, PictureProcessingUnit* ppu, Cartridge* cart);
		~CentralProcessingUnit();

		// Compute next tick of current program
		void step();

	private:
		uint64_t cycly = 0;
		uint8_t opCode = 0;
		uint8_t lowByte = 0;
		uint8_t hiByte = 0;

		enum CycleState
		{
			OpCode,
			LowByte,
			HiByte,
			Idle,
		};
		CycleState nextState = OpCode;

		// Registers
		uint16_t pc = 0u; // Program counter
		uint8_t ac = 0u; // Accumulator
		uint8_t x = 0u; // Index register X
		uint8_t y = 0u; // Index register Y
		uint8_t sr = 0u; // Status register [NV-BDIZC]
		uint8_t sp = 0u; // Stack pointer
/*
 *SR Flags (bit 7 to bit 0):
 *N	....	Negative
 *V	....	Overflow
 *-	....	ignored
 *B	....	Break
 *D	....	Decimal (use BCD for arithmetics)
 *I	....	Interrupt (IRQ disable)
 *Z	....	Zero
 *C	....	Carry
 */

		// Memory 16-bit addressable memory space
		uint8_t ram[2048]; // 2KB of RAM, rest is mapped to IO or catridge
		// Split into 8 256 byte pages
		// First is zero page, has special uses in certain addressing modes
		// Second page, contains stack, but can also be used for other things

		// Connections to other parts of the hardware
		AudioProcessingUnit* apu = nullptr;
		PictureProcessingUnit* ppu = nullptr;
		Cartridge* cart = nullptr;

		// Helpers for memory
		void writeMemory(uint16_t address, uint8_t value);
		uint8_t readMemory(uint16_t address);
};
