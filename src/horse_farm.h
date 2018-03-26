#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "drawable.h"

class HorseFarm : public Drawable
{
public:

    // Constructor/Destructor
    HorseFarm(GLuint width, GLuint height);
    ~HorseFarm();
    // Initialize game state (load all shaders/textures/levels)
    void Init();

    void Render();
};
