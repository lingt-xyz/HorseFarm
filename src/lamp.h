#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Lamp
{
public:

    Lamp(Shader& shader);
    ~Lamp();

    void Draw();

private:
    GLuint quadVAO_;
    Shader shader_;
    glm::vec3 light_position_;
};
