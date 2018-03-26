#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "drawable.h"

class Farm : public Drawable
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
