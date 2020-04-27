#pragma once

#include <string>

struct WindowOptions
{
	int width = 800;
	int height = 600;
	bool resizable = false;
	std::string title = "nes_debugger";
};
