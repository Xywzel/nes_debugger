#pragma once

// Runs 3 cycles for each CPU cycle
// Each cycle outputs a single pixel
// Can render a background layer and up to 64 sprites
// Eigth sprites can be visible on same scanline
// Overflow flag for two many sprites,
// hardware bug that might cause it not to be set
// Sprites 8x8 or 8x16 (width X height)
// Background can be scrolled in both X and Y direction
// One pixel step possible
// Background and sprites composed from 8x8 tiles
// Pattern table at ROM defines tiles
// Two bits of color from pattern, two from attribute table
// Nametable specifies background tile composition
// Background layer 32x30 tiles (960)
// Scrolling requires rendering multiple offset backgrounds
// Only two can be used at time, scrolling in multiple axises requires mirroring
// Primitive collision check between sprites and background
// Sets a flag, but only works once per frame
// 
//

#include "math/Color.h"

class PictureProcessingUnit
{
	public:
		PictureProcessingUnit();
		~PictureProcessingUnit();
		void step();

		void dmaCopyToOam(uint8_t oam[256]);
	private:
		uint8_t oam[256];
		// 256 Bytes of ObjectAttributeMemory
		// Storing each sprites x and y coordinates,
		// Tile number and flags (color 2 bits, layer 2 bits, vertical or horisontal flipping)
		// Supports dirrect copying from CPU as single chunck

		Color pallette[64];
		// Color palette with colors from 0x00 to 0x3F (64 colors)
		// Contains 54 unique colors and multiple blacks
		// Chorma and luminance signals format for output in practise
};
