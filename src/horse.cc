#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "node.h"
#include "matrix_stack.h"
#include "horse.h"
#include "controller.h"

inline glm::mat4 RotateX(float f)
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(1, 0, 0));
}

inline glm::mat4 RotateY(float f)
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(0, 1, 0));
}

inline glm::mat4 RotateZ(float f)
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(0, 0, 1));
}

double TORSO_HEIGHT = 1.0;
double TORSO_WIDTH = 3.0;
double TORSO_DEPTH = 1.0;

double NECK_HEIGHT = 1.5;
double NECK_WIDTH = 0.6;
double NECK_DEPTH = 0.6;

double HEAD_HEIGHT = 1.0;
double HEAD_WIDTH = 0.5;
double HEAD_DEPTH = 0.5;

double UPPER_ARM_HEIGHT = 1.0;
double LOWER_ARM_HEIGHT = 1.0;
double UPPER_ARM_WIDTH  = 0.3;
double LOWER_ARM_WIDTH  = 0.3;

double UPPER_LEG_HEIGHT = 1.0;
double LOWER_LEG_HEIGHT = 1.0;
double UPPER_LEG_WIDTH  = 0.3;
double LOWER_LEG_WIDTH = 0.3;

double base_scale = 1.0f;

float base_x = 0.0;
float base_y = 0.0;
float base_z = 0.0;

double rotateX = 0.0;
double rotateY = 0.0;
double rotateZ = 0.0;

unsigned int NumVertices = 36;

Node nodes[NumNodes];
MatrixStack mvstack;
glm::mat4 base_model;

GLuint shader_current;//TODO

void torso()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,1.0f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f * TORSO_HEIGHT, 0.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void neck()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.8f,0.9f,0.75f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * NECK_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(NECK_WIDTH, NECK_HEIGHT, NECK_DEPTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void head()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.6f,0.65f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * HEAD_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(HEAD_WIDTH, HEAD_HEIGHT, HEAD_DEPTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_upper_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_lower_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_upper_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_lower_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_upper_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_lower_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_upper_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_lower_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void traverse(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    mvstack.push(base_model);

    base_model *= node->transform;
    node->render();

    if (node->child)
    {
        traverse(node->child);
    }

    base_model = mvstack.pop();

    if (node->sibling)
    {
        traverse(node->sibling);
    }
}


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
    this->shader_.SetMatrix4("projection", Controller::projection);
    this->shader_.SetMatrix4("view", Controller::view);
    glm::mat4 model = glm::mat4(1.0f);

    this->shader_.SetMatrix4("model", model);

    glBindVertexArray(this->quadVAO_);

    //glDrawArrays(GL_TRIANGLES, 0, 36);
    this->BuildModel();
    traverse(&nodes[Torso]);

    glBindVertexArray(0);
}


void Horse::BuildModel()
{
    glm::mat4  m;

    m = glm::translate(glm::mat4(1.0), glm::vec3(base_x, base_y + 1.9*TORSO_HEIGHT, base_z)) * RotateX(rotateX) * RotateY(rotateY) * RotateZ(rotateZ + theta[Torso]);
    nodes[Torso] = Node(m, torso, NULL, &nodes[Neck]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(-(TORSO_WIDTH / 2 - NECK_WIDTH / 2), TORSO_HEIGHT, 0.0)) * RotateZ(theta[Neck]);
    nodes[Neck] = Node(m, neck, &nodes[LeftUpperArm], &nodes[Head]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, NECK_HEIGHT, 0.0)) * RotateZ(theta[Head]);
    nodes[Head] = Node(m, head, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(TORSO_WIDTH / 2 - UPPER_LEG_WIDTH / 2, 0.1*UPPER_LEG_HEIGHT, -TORSO_DEPTH/2 + UPPER_LEG_WIDTH / 2)) * RotateZ(theta[LeftUpperArm]);
    nodes[LeftUpperArm] = Node(m, left_upper_arm, &nodes[RightUpperArm], &nodes[LeftLowerArm]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(TORSO_WIDTH / 2 - UPPER_LEG_WIDTH / 2, 0.1*UPPER_ARM_HEIGHT, TORSO_DEPTH/2 - UPPER_ARM_WIDTH / 2)) * RotateZ(theta[RightUpperArm]);
    nodes[RightUpperArm] = Node(m, right_upper_arm, &nodes[LeftUpperLeg], &nodes[RightLowerArm]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(-(TORSO_WIDTH / 2 - UPPER_ARM_WIDTH / 2), 0.1*UPPER_ARM_HEIGHT, -TORSO_DEPTH/2 + UPPER_ARM_WIDTH / 2)) * RotateZ(theta[LeftUpperLeg]);
    nodes[LeftUpperLeg] = Node(m, left_upper_leg, &nodes[RightUpperLeg], &nodes[LeftLowerLeg]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(-(TORSO_WIDTH / 2 - UPPER_LEG_WIDTH / 2), 0.1*UPPER_LEG_HEIGHT, TORSO_DEPTH/2 - UPPER_LEG_WIDTH / 2)) * RotateZ(theta[RightUpperLeg]);
    nodes[RightUpperLeg] = Node(m, right_upper_leg, NULL, &nodes[RightLowerLeg]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_ARM_HEIGHT, 0.0)) * RotateZ(theta[LeftLowerArm]);
    nodes[LeftLowerArm] = Node(m, left_lower_arm, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_ARM_HEIGHT, 0.0)) * RotateZ(theta[RightLowerArm]);
    nodes[RightLowerArm] = Node(m, right_lower_arm, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_LEG_HEIGHT, 0.0)) * RotateZ(theta[LeftLowerLeg]);
    nodes[LeftLowerLeg] = Node(m, left_lower_leg, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_LEG_HEIGHT, 0.0))* RotateZ(theta[RightLowerLeg]);
    nodes[RightLowerLeg] = Node(m, right_lower_leg, NULL, NULL);
}
