#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "api/texture.h"
#include "api/shader.h"


class SpriteRenderer
{
public:

    SpriteRenderer(Shader &shader);

    ~SpriteRenderer();
    void InitRenderData();
    void DrawLineLoop();

    void DrawSprite(glm::mat4 model = glm::mat4(1.0f));

    void DrawSprite(Texture2D &texture, glm::mat4 model = glm::mat4(1.0f));
private:

    Shader shader_;
    GLuint quadVAO_;

};
