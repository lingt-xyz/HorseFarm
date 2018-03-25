#include "window.h"

#include <iostream>

#include "input.h"
#include "resource_manager.h"

int Window::width = 800;
int Window::height = 600;
std::string Window::title = "GLFW";
GLFWwindow* Window::window;

Window::Window()
{
	initWindow();

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, Window::keyCallback);
}

Window::Window(int width, int height, std::string title)
{
	Window::width = width;
	Window::height = height;
	Window::title = title;

	initWindow();

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, Window::keyCallback);
}

Window::~Window()
{
	ResourceManager::Clear();
	glfwDestroyWindow(this->window);
}

void Window::makeContextCurrent()
{
	glfwMakeContextCurrent(Window::window);
}

GLboolean Window::getWindowShouldClose()
{
	return glfwWindowShouldClose(Window::window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(Window::window);
}

void Window::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	Window::window = glfwCreateWindow(Window::width, Window::height, Window::title.c_str(),
		nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// init glew
	glewExperimental = GL_TRUE;
	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW: " << glewGetErrorString(glewInitStatus) << std::endl;
	}
	glGetError();

	int width, height;
	glfwGetFramebufferSize(Window::window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
            Input::Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            Input::Keys[key] = GL_FALSE;
	}
}
