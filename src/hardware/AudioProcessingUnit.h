#pragma once

#include <stdint.h>

class AudioProcessingUnit
{
	public:
		AudioProcessingUnit();
		~AudioProcessingUnit();
		void step();

		void write(uint16_t address, uint8_t data);

	private:
		uint64_t sampleSquareWaveOne(); // Frequency and duration control
		uint64_t sampleSquareWaveTwo(); // Refquency sweeos and volume envelopes
		uint64_t sampleTriangleWave();
		uint64_t sampleNoice(); // Linear feedback shift register, pseudo random
		uint64_t sampleDeltaModulation(); // Samples from memory
};
