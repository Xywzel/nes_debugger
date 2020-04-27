#pragma once


struct GLFWwindow;

class Window
{
	public:
		Window();
		~Window();

		// Public interface
		void update();
		bool shouldClose();
		void setWindowResized(bool state);
		bool getWindowResized() const;

	private:
		// Data presentation
		GLFWwindow* window = nullptr;
		bool resized = false;

		// Helpers
		void poolEvents();
};
