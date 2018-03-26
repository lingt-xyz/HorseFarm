#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Axis
{
public:

    Axis(Shader& shader);
    ~Axis();

    void Draw();

private:
    GLuint quadVAO_;
    Shader shader_;
};
