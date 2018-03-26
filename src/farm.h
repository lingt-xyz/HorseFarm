#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "drawable.h"

class Farm : public Drawable
{
public:

    Farm();
    ~Farm();
    // Initialize game state (load all shaders/textures/levels)
    void Init();

    void Render();

};
