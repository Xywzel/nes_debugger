#pragma once

#include <string>

enum class TimingMode
{
	RP2CO2, // NTSC NES
	RP2CO7, // PAL NES
	MultipleRegion,
	UMC6527P, // Dendy
	Unsupported
};

std::string enumToString(TimingMode type);
