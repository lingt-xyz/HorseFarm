#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "axis.h"
#include "controller.h"

const GLfloat vertices[] =
{
    0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    5.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    5.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    4.5f, 0.0f,  0.2f, 1.0f, 0.0f, 0.0f, 1.0f,
    5.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    4.5f, 0.0f, -0.2f, 1.0f, 0.0f, 0.0f, 1.0f,

    0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 5.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 5.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.2f, 4.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 5.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.2f, 4.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f,  5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f,  5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.2f, 0.0f,  4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f,  5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.2f, 0.0f,  4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
};

Axis::Axis()
{
    GLuint VBO;

    glGenVertexArrays(1, &this->quadVAO_);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));

    glBindVertexArray(0);
}

Axis::~Axis()
{
}

void Axis::Draw(Shader& shader)
{
    this->shader_ = shader;
    this->shader_.Use();
    this->shader_.SetMatrix4("projection", Controller::projection);
    this->shader_.SetMatrix4("view", Controller::view);
    this->shader_.SetMatrix4("model", glm::mat4(1.0f));

    glBindVertexArray(this->quadVAO_);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(5.0f);
    glDrawArrays(GL_LINES, 0, 3*2);
    glDrawArrays(GL_LINES, 6, 3*2);
    glDrawArrays(GL_LINES, 12, 3*2);
    glLineWidth(0.5f);

    glBindVertexArray(0);
}
