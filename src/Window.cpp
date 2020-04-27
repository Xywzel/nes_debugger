#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Options.h"

// Callbacks
static void framebufferResizeCallback(GLFWwindow* window, int /*width*/, int /*height*/)
{
	Window* self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	self->setWindowResized(true);
}

Window::Window()
{
	const WindowOptions& options = getOptions().window;
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, options.resizable ? GLFW_TRUE : GLFW_FALSE);
	window = glfwCreateWindow(options.width, options.height, options.title.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::update()
{
	poolEvents();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::setWindowResized(bool state)
{
	resized = state;
}

bool Window::getWindowResized() const
{
	return resized;
}

void Window::poolEvents()
{
	glfwPollEvents();
}

