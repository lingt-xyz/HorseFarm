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
	static void InitWindow();
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void SizeCallback(GLFWwindow* window, int width, int height);

	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};
