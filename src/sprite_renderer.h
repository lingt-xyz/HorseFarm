#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "api/texture.h"
#include "api/shader.h"


class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(
        Texture2D &texture,
        glm::mat4 model = glm::mat4(1.0f),
        glm::vec4 color = glm::vec4(1.0f)
    );
private:
    // Render state
    Shader shader_;
    GLuint quadVAO_;
    // Initializes and configures the quad's buffer and vertex attributes
    void InitRenderData();
};
