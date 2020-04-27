#include "PictureProcessingUnit.h"

PictureProcessingUnit::PictureProcessingUnit()
{

}

PictureProcessingUnit::~PictureProcessingUnit()
{

}

void PictureProcessingUnit::step()
{
}

void PictureProcessingUnit::dmaCopyToOam(uint8_t oam[256])
{
	int a = oam[0];
}

void PictureProcessingUnit::write(uint16_t /*address*/, uint8_t /*data*/)
{
}

uint8_t PictureProcessingUnit::read(uint16_t /*address*/)
{
	return 0;
}
