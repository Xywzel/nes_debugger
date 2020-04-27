#include "PictureProcessingUnit.h"

#include <cstring>

PictureProcessingUnit::PictureProcessingUnit()
{

}

PictureProcessingUnit::~PictureProcessingUnit()
{

}

void PictureProcessingUnit::step()
{
}

void PictureProcessingUnit::dmaCopyToOam(uint8_t oam_[256])
{
	std::memcpy(oam, oam_, 256 * sizeof(uint8_t));
}

void PictureProcessingUnit::write(uint16_t /*address*/, uint8_t /*data*/)
{
}

uint8_t PictureProcessingUnit::read(uint16_t address)
{
	if (address < 0x1000)
		// Pattern table 0
		return 0;

	else if (address < 0x2000)
		// Pattern table 1
		return 0;

	else if (address < 0x23C0)
		// Name Table 0
		return 0;

	else if (address < 0x2400)
		// Attribute table 0
		return 0;

	else if (address < 0x27C0)
		// Name Table 1
		return 0;

	else if (address < 0x2800)
		// Attribute table 1
		return 0;

	else if (address < 0x2BC0)
		// Name Table 2
		return 0;

	else if (address < 0x2C00)
		// Attribute table 2
		return 0;

	else if (address < 0x2FC0)
		// Name Table 3
		return 0;

	else if (address < 0x3400)
		// Attribute table 3
		return 0;

	else if (address < 0x3F00)
		// Mirrors range 0x2000 - 0x2EFF
		return read(address - 0x1000);

	else if (address < 0x3F10)
		// Image palette
		return 0;

	else if (address < 0x3F20)
		// Sprite palette
		return 0;

	else if (address < 0x4000)
	{
		// Mirrors range 0x3F00 - 0x3F1F
		uint16_t newAddress = ((address - 0x3F00) % 0x0020) + 0x3F00;
		return read(newAddress);
	}

	else // Address < 0x1 0000
		// Mirrors range 0x0000 - 0x3FFF
		return read(address % 0x4000);
}
