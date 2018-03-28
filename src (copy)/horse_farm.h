#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "test.h"
#include "grid.h"
#include "axis.h"
#include "lamp.h"
#include "farm.h"
#include "horse.h"

class HorseFarm
{
public:
    Test* test_;
    Grid* grid_;
    Axis* axis_;
    Lamp* lamp_;
    Farm* farm_;
    Horse* horse_;

    //std::vector<Horse> vector_horse_;

    // Constructor/Destructor
    HorseFarm(GLuint width, GLuint height);
    ~HorseFarm();
    // Initialize game state (load all shaders/textures/levels)
    void Init();

    void Render();

private:
    GLuint width_;
    GLuint height_;
};