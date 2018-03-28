#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Grid
{
public:

    Grid();
    ~Grid();

    void Draw(Shader& shader);

private:
    GLuint quadVAO_;
    Shader shader_;
    unsigned int gridX_;
    unsigned int gridZ_;
};
