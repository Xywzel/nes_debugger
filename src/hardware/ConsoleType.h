#pragma once

#include <string>

enum class ConsoleType
{
	NintendoEntertainmentSystem,
	NintendoVsSystem,
	NintendoPlaychoice10,
	ExtendedConsoleType,
	Unsupported
};

std::string enumToString(ConsoleType type);
