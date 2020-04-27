#include "Emulator.h"

#include <string>

#include "Window.h"

Emulator::Emulator(const char* filename)
{
	window = new Window();
}

Emulator::~Emulator()
{
	if (window)
		delete window;
}

void Emulator::run()
{
	while (!window->shouldClose())
	{
		update();
		render();
	}
}

void Emulator::update()
{
	window->update();
}

void Emulator::render()
{
	window->setWindowResized(false);
}
