#pragma once

#include "WindowOptions.h"

struct Options
{
	WindowOptions window;
	bool initialized = false;
};

const Options& getOptions();
