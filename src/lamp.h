#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Lamp
{
public:

    Lamp();
    ~Lamp();

    void Draw(Shader& shader);

private:
    GLuint quadVAO_;
    Shader shader_;
    glm::vec3 light_position_;
};
