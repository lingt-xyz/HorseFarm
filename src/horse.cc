#include "helper.h"

#include "horse.h"
#include "controller.h"


const GLfloat vertices[] =
{
    -0.5,  0.5,  0.5, -0, 0, 1.0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5, -0.5,  0.5, -0, 0, 1.0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 1.0,
    0.5, -0.5,  0.5, -0, 0, 1.0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    -0.5,  0.5,  0.5, -0, 0, 1.0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    0.5, -0.5,  0.5, -0, 0, 1.0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5,  0.5,  0.5, -0, 0, 1.0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 0,
    0.5,  0.5,  0.5, 1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    0.5, -0.5,  0.5, 1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 1.0,
    0.5, -0.5, -0.5, 1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5,  0.5,  0.5, 1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    0.5, -0.5, -0.5, 1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5,  0.5, -0.5, 1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 0,
    0.5, -0.5,  0.5, -0, -1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5, -0.5,  0.5, -0, -1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 1.0,
    -0.5, -0.5, -0.5, -0, -1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5, -0.5,  0.5, -0, -1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5, -0.5, -0.5, -0, -1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5, -0.5, -0.5, -0, -1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 0,
    0.5,  0.5, -0.5, 0, 1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5,  0.5, -0.5, 0, 1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 1.0,
    -0.5,  0.5,  0.5, 0, 1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5,  0.5, -0.5, 0, 1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5,  0.5,  0.5, 0, 1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5,  0.5,  0.5, 0, 1.0, -0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 0,
    -0.5, -0.5, -0.5, 0, 0, -1.0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5,  0.5, -0.5, 0, 0, -1.0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 1.0,
    0.5,  0.5, -0.5, 0, 0, -1.0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    -0.5, -0.5, -0.5, 0, 0, -1.0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    0.5,  0.5, -0.5, 0, 0, -1.0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    0.5, -0.5, -0.5, 0, 0, -1.0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 0,
    -0.5,  0.5, -0.5, -1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5, -0.5, -0.5, -1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 1.0,
    -0.5, -0.5,  0.5, -1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    -0.5,  0.5, -0.5, -1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 1.0, 0,
    -0.5, -0.5,  0.5, -1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 1.0,
    -0.5,  0.5,  0.5, -1.0, 0, 0, 0.7f, 1.0f, 0.7f, 1.0f, 0, 0,
};

Horse::Horse(Shader& shader)
{
    this->shader_ = shader;

    color = glm::vec4(getRandomFloat(), getRandomFloat(), getRandomFloat(), 1.0f);

    GLuint VBO;

    glGenVertexArrays(1.0, &this->quadVAO_);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));

    glBindVertexArray(0);
}

Horse::~Horse()
{
}

void Horse::Draw()
{
    this->shader_.Use();

    this->shader_.SetVector4f("aColor", color);
    this->shader_.SetMatrix4("projection", Controller::projection);
    this->shader_.SetMatrix4("view", Controller::view);
    glm::mat4 model = glm::mat4(1.0f);

    this->shader_.SetMatrix4("model", model);

    glBindVertexArray(this->quadVAO_);

    if(run_on) // let's run
    {
        run();
        ++tmp_time;
        tmp_time %= (speedDivision+1);
        tmp_step += (tmp_time / speedDivision);
        if(tmp_step > 6)
        {
            tmp_step = 1;
        }
    }

    this->BuildModel();

    glBindVertexArray(0);
}
