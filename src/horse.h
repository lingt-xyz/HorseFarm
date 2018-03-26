#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "drawable.h"

class Horse : public Drawable
{
public:
    Horse();
    ~Horse();
    // Initialize game state (load all shaders/textures/levels)
    void Init();

    void Render();

};
