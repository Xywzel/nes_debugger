#include "CentralProcessingUnit.h"

#include "PictureProcessingUnit.h"
#include "AudioProcessingUnit.h"
#include "Cartridge.h"

CentralProcessingUnit::CentralProcessingUnit()
{
}

CentralProcessingUnit::~CentralProcessingUnit()
{
}

void CentralProcessingUnit::step()
{
	//Read operation cose from memory, as pointed by program counter
	opCode = readMemory(pc);

	switch (opCode)
	{
		case 0:
			break;
		default:
			break;
	}
}

// Hardware bug, indirrect JMP (addr) with addres 0xXXFF will read
// the the second byte of the jump target position
// from 0xXX00 instead of 0xXY00, where Y = X+1

void CentralProcessingUnit::writeMemory(uint16_t address, uint8_t value)
{
	if (address < 0x0800) // 2KB internal RAM, note zero page and stack areas
	{
		ram[address] = value;
		return;
	}
	if (address < 0x2000) // RAM mirrored 3 times
	{
		ram[address % 0x0800] = value;
		return;
	}
	if (address < 0x2008) // PPU registers
	{
		uint16_t ppuAddress = address - 0x2000;
		if (ppu)
			ppu->write(ppuAddress, value);
		return;
	}
	if (address < 0x4000) // PPU registers mirrored every 8 bytes
	{
		uint16_t ppuAddress = (address - 0x2000) % 0x0008;
		if (ppu)
			ppu->write(ppuAddress, value);
		return;
	}
	if (address < 0x4018) // APU and IO registers
		return;
	if (address < 0x4020) // Normally disabled APU and IO functionality, test mode
		return;
	// Cartridge space PRG ROM, PRG RAM, mapper registers
	if (cart)
		cart->write(address, value);
}

uint8_t CentralProcessingUnit::readMemory(uint16_t address)
{
	if (address < 0x0800) // 2KB internal RAM, note zero page and stack areas
		return ram[address];
	if (address < 0x2000) // RAM mirrored 3 times
		return ram[address % 0x0800];
	if (address < 0x2008) // PPU registers
	{
		int ppuAddress = address - 0x2000;
		if (ppu)
			return ppu->read(ppuAddress);
		return 0;
	}
	if (address < 0x4000) // PPU registers mirrored every 8 bytes
	{
		int ppuAddress = (address - 0x2000) % 0x0008;
		if (ppu)
			return ppu->read(ppuAddress);
		return 0;
	}
	if (address < 0x4018) // APU and IO registers
		return 0;
	if (address < 0x4020) // Normally disabled APU and IO functionality, test mode
		return 0;
	// Cartridge space PRG ROM, PRG RAM, mapper registers
	return cart->read(address);
}
