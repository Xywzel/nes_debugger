#include "ConsoleType.h"

#include <string>

std::string enumToString(ConsoleType type)
{
	switch(type)
	{
		case ConsoleType::NintendoEntertainmentSystem:
			return "NintendoEntertainmentSystem";
		case ConsoleType::NintendoVsSystem:
			return "NintendoVsSystem";
		case ConsoleType::NintendoPlaychoice10:
			return "NintendoPlaychoice10";
		case ConsoleType::ExtendedConsoleType:
			return "ExtendedConsoleType";
		default:
			return "Unsupported";
	}
}
