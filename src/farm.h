#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "api/shader.h"

class Farm
{
public:
    Farm();
    ~Farm();

    void Draw(Shader& shader);

private:
    GLuint quadVAO_;
    Shader shader_;
};
