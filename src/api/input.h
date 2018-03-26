#pragma once

#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input
{
public:

    static bool Keys[1024];
    static bool KeysProcessed[1024];
    static bool KeysMode[1024];

    static void ProcessInput(GLfloat dt);

private:
	static std::map<int, bool> keyDown;
	static std::map<int, bool> keyUp;
	static std::map<int, bool> keyHeld;
};
