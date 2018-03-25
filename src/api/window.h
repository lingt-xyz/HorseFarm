#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	static int width, height;
	static std::string title;

	Window();
	Window(int width, int height, std::string title);
	~Window();

	static void makeContextCurrent();
	static GLboolean getWindowShouldClose();
	static void swapBuffers();

private:
	static GLFWwindow* window;
	static void initWindow();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};