#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "farm.h"
#include "horse.h"

class HorseFarm
{
public:
    Farm* farm_;
    std::vector<Horse> vector_horse_;

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
