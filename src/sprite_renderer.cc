#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader_ = shader;
    this->InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO_);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::mat4 model, glm::vec4 color)
{
    // Prepare transformations
    this->shader_.Use();
    this->shader_.SetMatrix4("model", model);

    //this->shader_.SetVector4f("spriteColor", color);

    //glActiveTexture(GL_TEXTURE0);
    //texture.Bind();

    glBindVertexArray(this->quadVAO_);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawArrays(GL_LINE_LOOP, 0, 4*2);
    glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData()
{
    GLuint VBO;
    GLuint EBO;
    const GLfloat vertices[] =
    {
        // position    // color          // texture
        0.f, 0.f, 0.f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        1.f, 0.f, 0.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.f, 0.f, 1.f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.f, 0.f, 1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &this->quadVAO_);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(this->quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
}
