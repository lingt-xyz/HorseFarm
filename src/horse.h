#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

enum HorsePart
{
    Torso = 0,
    Head = 1,
    LeftUpperArm = 2,
    LeftLowerArm = 3,
    RightUpperArm = 4,
    RightLowerArm = 5,
    LeftUpperLeg = 6,
    LeftLowerLeg = 7,
    RightUpperLeg = 8,
    RightLowerLeg = 9,
    Neck = 10,
    NumNodes
};

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

    GLfloat theta[NumNodes] =
    {
        0.0,	// Torso
        80.0,	// Head
        190.0,	// LeftUpperArm
        -10.0,	// LeftLowerArm
        190.0,	// RightUpperArm
        -10.0,	// RightLowerArm
        180.0,	// LeftUpperLeg
        0.0,	// LeftLowerLeg
        180.0,	// RightUpperLeg
        0.0,	// RightLowerLeg
        45.0	// Neck
    };

    void BuildModel();

};
