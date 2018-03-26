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

void SpriteRenderer::DrawLineLoop()
{
    this->shader_.Use();
    this->shader_.SetMatrix4("model", glm::mat4(1.0f));

    glBindVertexArray(this->quadVAO_);
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(glm::mat4 model)
{
    this->shader_.Use();
    this->shader_.SetMatrix4("model", model);


    glBindVertexArray(this->quadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::mat4 model)
{

    this->shader_.Use();
    this->shader_.SetMatrix4("model", model);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData()
{

}
