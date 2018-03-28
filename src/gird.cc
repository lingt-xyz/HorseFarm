#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "grid.h"
#include "controller.h"

const GLfloat vertices[] =
{
     // position         // normal         // color                // texture
     0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
     0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
};

Grid::Grid(){

    gridX_ = 25;
    gridZ_ = 25;

    GLuint VBO;

    glGenVertexArrays(1, &this->quadVAO_);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));

    glBindVertexArray(0);
}

Grid::~Grid(){
}

void Grid::Draw(Shader& shader){
    this->shader_ = shader;
    this->shader_.Use();
    //this->shader_.SetMatrix4("projection", Controller::projection);
    //this->shader_.SetMatrix4("view", Controller::view);
    this->shader_.SetMatrix4("model", glm::mat4(1.0f));
    // for no texture only
    this->shader_.SetVector4f("shader_color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // for texture only
    this->shader_.SetInteger("material.diffuse", 0.3);
    this->shader_.SetVector3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    this->shader_.SetFloat("material.shininess", 64.0f);
    glBindVertexArray(this->quadVAO_);

    glm::mat4 base = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.0, 0.5));
    for(int i=1; i<=gridX_; ++i)
    {
        glm::mat4 anchor_x1 = glm::translate(glm::mat4(1.0f), glm::vec3(i-1, 0.f, 0.f));
        for(int j=1; j<=gridZ_; ++j)
        {
            glm::mat4 anchor_z1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, j-1));
            this->shader_.SetMatrix4("model", anchor_x1 * anchor_z1 * base);
            glDrawArrays(GL_LINE_LOOP, 0, 4);

            glm::mat4 anchor_z2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -j));
            this->shader_.SetMatrix4("model", (anchor_x1 * anchor_z2 * base));
            glDrawArrays(GL_LINE_LOOP, 0, 4);
        }

        glm::mat4 anchor_x2 = glm::translate(glm::mat4(1.0f), glm::vec3(-i, 0.f, 0.f));
        for(int j=1; j<=gridZ_; ++j)
        {
            glm::mat4 anchor_1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, j-1));
            this->shader_.SetMatrix4("model", (anchor_x2 * anchor_1 * base));
            glDrawArrays(GL_LINE_LOOP, 0, 4);

            glm::mat4 anchor_2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -j));
            this->shader_.SetMatrix4("model", (anchor_x2 * anchor_2 * base));
            glDrawArrays(GL_LINE_LOOP, 0, 4);
        }
    }

    glBindVertexArray(0);
}
