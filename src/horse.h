#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Horse
{
public:
    Horse(Shader& shader);
    ~Horse();
    // Initialize game state (load all shaders/textures/levels)
    void Draw();

private:
    GLuint quadVAO_;
    Shader shader_;
    glm::vec3 light_position_;

};
