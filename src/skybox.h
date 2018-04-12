#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Skybox
{
public:

    Skybox();
    ~Skybox();

    void Draw(Shader& shader);

private:
    GLuint quadVAO_;
    Shader shader_;
    unsigned int cubemapTexture;
    unsigned int LoadCubemap(std::vector<std::string> faces);
};
