#pragma once

// 32KB of addressable program memory and
// 8KB character memory (pattern table)

// Custom Mappers to have more by switching banks
// Some Cartridges also have battery backed RAM


class Mapper;
class Bank;
class SaveRAM;

class Cartridge
{
	public:
		Cartridge();
		~Cartridge();

		void write(uint16_t address, uint8_t data);
		uint8_t read(uint16_t address);

		// Store to file contents of batter backed RAM
		void readBackedRam();
		void writeBAckedRam();
	private:
		Mapper* mapper = nullptr;
		Bank* currentBank = nullptr;

};
