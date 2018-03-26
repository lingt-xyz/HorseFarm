#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Farm
{
public:

    Farm(GLuint width = 800, GLuint height = 800);
    ~Farm();
    // Initialize game state (load all shaders/textures/levels)
    void Init();

    void Render();

private:
    GLuint width_;
    GLuint height_;
};
