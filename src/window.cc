#include "window.h"

#include <iostream>

#include "api/resource_manager.h"
#include "input.h"
#include "controller.h"

int Window::width = 800;
int Window::height = 800;
std::string Window::title = "GLFW";
GLFWwindow* Window::window;

Window::Window()
{
    InitWindow();

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, Window::SizeCallback);
    glfwSetKeyCallback(window, Window::KeyCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
}

Window::Window(int width, int height, std::string title)
{
    Window::width = width;
    Window::height = height;
    Window::title = title;

    InitWindow();

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, Window::SizeCallback);
    glfwSetKeyCallback(window, Window::KeyCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
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

void Window::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window::window = glfwCreateWindow(Window::width, Window::height, Window::title.c_str(), nullptr, nullptr);
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
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        Input::KeysMode[key] = mode;
        if (action == GLFW_PRESS)
        {
            Input::KeysProcessed[key] = GL_FALSE;
            Input::Keys[key] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE)
        {
            Input::Keys[key] = GL_FALSE;
        }
    }
}

void Window::SizeCallback(GLFWwindow* window, int width, int height)
{
    Window::width = width;
    Window::height = height;
    glViewport(0, 0, width, height);
}

float lastX;
float lastY;
bool leftMouseButton=false, middleMouseButton=false, rightMouseButton=false;//varibles for detecting the mouse button action
bool firstMouse=true;

void Window::CursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    if(firstMouse)
    {
        lastX=xPos;
        lastY=yPos;
        firstMouse=false;
        return;
    }

    float xOffset=xPos-lastX;
    float yOffset=yPos-lastY;
    lastX=xPos;
    lastY=yPos;

    //while right button is pressed → use mouse movement in x direction to pan
    if(rightMouseButton)//yaw
    {
        Controller::c_dir_x += 0.1 * xOffset;
    }
    //while middle button is pressed → use mouse movement in y direction to tilt.
    if(middleMouseButton)//pitch
    {
        Controller::c_dir_y -= 0.1*yOffset;
    }
    //while left button is pressed use mouse movement to move into/out of the scene
    if(leftMouseButton)//zoom in and out by adjusting the fov degree
    {
        if(Controller::fov >= 1.0f && Controller::fov <= 80.0f)
            Controller::fov += 0.1*yOffset;
        if(Controller::fov <= 1.0f)
            Controller::fov = 1.0f;
        if(Controller::fov >= 80.0f)
            Controller::fov = 80.0f;
    }
}

void Window::MouseButtonCallback(GLFWwindow* window, int key, int action, int mods)
{
    if(key==GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
        {
            rightMouseButton=true;
        }
        else if(action == GLFW_RELEASE)
        {
            rightMouseButton=false;
        }
    }
    else if(key==GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if(action == GLFW_PRESS)
        {
            middleMouseButton=true;
        }
        else if(action == GLFW_RELEASE)
        {
            middleMouseButton=false;
        }
    }
    else if(key==GLFW_MOUSE_BUTTON_LEFT)
    {
        if(action == GLFW_PRESS)
        {
            leftMouseButton=true;
        }
        else if(action == GLFW_RELEASE)
        {
            leftMouseButton=false;
        }
    }
}
