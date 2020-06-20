#include "TimingMode.h"

#include <string>

std::string enumToString(TimingMode type)
{
	switch(type)
	{
		case TimingMode::RP2CO2:
			return "RP2CO2 (NTSC NES)";
		case TimingMode::RP2CO7:
			return "RP2CO7 (Licensed PAL NES)";
		case TimingMode::MultipleRegion:
			return "Multiple-region";
		case TimingMode::UMC6527P:
			return "UMC 6527P (Dendy)";
		default:
			return "Unsupported";
	}
}
