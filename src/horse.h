#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    Neck = 10
};

struct HorseDimension
{
    const double kTorsoHeight = 1.0;
    const double kTorsoWidth = 3.0;
    const double kTorsoDepth = 1.0;

    const double kNeckHeight = 1.5;
    const double kNeckWidth = 0.6;
    const double kNeckDepth = 0.6;

    const double kHeadHeight = 1.0;
    const double kHeadWidth = 0.5;
    const double kHeadDepth = 0.5;

    const double kUpperArmHeight = 1.0;
    const double kLowerArmHeight = 1.0;
    const double kUpperArmWidth  = 0.3;
    const double kLowerArmWidth  = 0.3;

    const double kUpperLegHeight = 1.0;
    const double kLowerLegHeight = 1.0;
    const double kUpperLegWidth  = 0.3;
    const double kLowerLegWidth = 0.3;
};

class Horse
{
public:

    bool run_on = false;

    int tmp_step = 1;
    // to waste some frames to keep the horse run slowly
    int tmp_time = 0;
    int speedDivision = 10;

    double base_scale = 1.0f;

    float base_x = 0.0;
    float base_y = 0.0;
    float base_z = 0.0;

    double rotateX = 0.0;
    double rotateY = 0.0;
    double rotateZ = 0.0;

    GLfloat theta[11] =
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

    Horse();
    ~Horse();

    void Draw(Shader& shader);

    void run()
    {
        switch(tmp_step)
        {
        case 1 :
            theta[RightUpperLeg] = 150;
            theta[RightLowerLeg] = 90;
            theta[LeftUpperLeg] = 110;
            theta[LeftLowerLeg] = 90;
            theta[RightUpperArm] = 130;
            theta[RightLowerArm] = -10;
            theta[LeftUpperArm] = 150;
            theta[LeftLowerArm] = -20;
            theta[Neck] = 55;
            theta[Torso] = 0;
            break;
        case 2 :
            theta[RightUpperLeg] = 110;
            theta[RightLowerLeg] = 90;
            theta[LeftUpperLeg] = 110;
            theta[LeftLowerLeg] = 50;
            theta[RightUpperArm] = 170;
            theta[RightLowerArm] = -10;
            theta[LeftUpperArm] = 220;
            theta[LeftLowerArm] = -20;
            theta[Neck] = 45;
            theta[Torso] = -5;
            break;
        case 3 :
            theta[RightUpperLeg] = 120;
            theta[RightLowerLeg] = 70;
            theta[LeftUpperLeg] = 160;
            theta[LeftLowerLeg] = 0;
            theta[RightUpperArm] = 200;
            theta[RightLowerArm] = -30;
            theta[LeftUpperArm] = 250;
            theta[LeftLowerArm] = -10;
            theta[Neck] = 55;
            theta[Torso] = -2;
            break;
        case 4 :
            theta[RightUpperLeg] = 160;
            theta[RightLowerLeg] = 0;
            theta[LeftUpperLeg] = 190;
            theta[LeftLowerLeg] = 0;
            theta[RightUpperArm] = 220;
            theta[RightLowerArm] = -20;
            theta[LeftUpperArm] = 250;
            theta[LeftLowerArm] = -70;
            theta[Neck] = 45;
            theta[Torso] = 2;
            break;
        case 5 :
            theta[RightUpperLeg] = 190;
            theta[RightLowerLeg] = 0;
            theta[LeftUpperLeg] = 200;
            theta[LeftLowerLeg] = 10;
            theta[RightUpperArm] = 250;
            theta[RightLowerArm] = -90;
            theta[LeftUpperArm] = 230;
            theta[LeftLowerArm] = -90;
            theta[Neck] = 55;
            theta[Torso] = 5;
            break;
        case 6 :
            theta[RightUpperLeg] = 200;
            theta[RightLowerLeg] = 20;
            theta[LeftUpperLeg] = 170;
            theta[LeftLowerLeg] = 80;
            theta[RightUpperArm] = 210;
            theta[RightLowerArm] = -90;
            theta[LeftUpperArm] = 190;
            theta[LeftLowerArm] = -80;
            theta[Neck] = 55;
            theta[Torso] = 2;
            break;
        }
    }

    void ResetModel()
    {
        base_scale = 1.0f;

        base_x = 0.0;
        base_y = 0.0;
        base_z = 0.0;

        rotateX = 0.0;
        rotateY = 0.0;
        rotateZ = 0.0;

        tmp_step = 1;
        tmp_time = 0;
        speedDivision = 10;
        run_on = false;

        theta[Torso] = 0.0f;
        theta[Head] = 80.0f;
        theta[LeftUpperArm] = 190.0f;
        theta[LeftLowerArm] = -10.0f;
        theta[RightUpperArm] = 190.0f;
        theta[RightLowerArm] = -10.0f;
        theta[LeftUpperLeg] = 180.0f;
        theta[LeftLowerLeg] = 0.0f;
        theta[RightUpperLeg] = 180.0f;
        theta[RightLowerLeg] = 0.0f;
        theta[Neck] = 45.0f;
    }

private:
    glm::vec4 color;
    unsigned int NumVertices = 36;

    GLuint quadVAO_;
    Shader shader_;

    HorseDimension horse_dimension_;

    void BuildModel()
    {
        glm::mat4 baseScale = glm::scale(glm::mat4(1.0), glm::vec3(base_scale, base_scale, base_scale));

        glm::mat4 torsoModel = glm::translate(glm::mat4(1.0), glm::vec3(base_x, base_y + 1.9*horse_dimension_.kTorsoHeight, base_z)) * RotateX(rotateX) * RotateY(rotateY) * RotateZ(rotateZ + theta[Torso]);
        //nodes[Torso] = Node(m, torso, NULL, &nodes[Neck]);
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f * horse_dimension_.kTorsoHeight, 0.0f));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kTorsoWidth, horse_dimension_.kTorsoHeight, horse_dimension_.kTorsoDepth));
        //glUniformMatrix4fv(glGetUniformLocation(shader_, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));

        torsoModel = baseScale * torsoModel;
        shader_.SetMatrix4("model", torsoModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 neckModel = glm::translate(glm::mat4(1.0), glm::vec3(-(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kNeckWidth / 2), horse_dimension_.kTorsoHeight, 0.0)) * RotateZ(theta[Neck]);
        //nodes[Neck] = Node(m, neck, &nodes[LeftUpperArm], &nodes[Head]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kNeckHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kNeckWidth, horse_dimension_.kNeckHeight, horse_dimension_.kNeckDepth));
        shader_.SetMatrix4("model", torsoModel * neckModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 headModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kNeckHeight, 0.0)) * RotateZ(theta[Head]);
        //nodes[Head] = Node(m, head, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kHeadHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kHeadWidth, horse_dimension_.kHeadHeight, horse_dimension_.kHeadDepth));
        shader_.SetMatrix4("model", torsoModel * neckModel * headModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 leftUpperArmModel = glm::translate(glm::mat4(1.0), glm::vec3(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperLegWidth / 2, 0.1*horse_dimension_.kUpperLegHeight, -horse_dimension_.kTorsoDepth/2 + horse_dimension_.kUpperLegWidth / 2)) * RotateZ(theta[LeftUpperArm]);
        //nodes[LeftUpperArm] = Node(m, left_upper_arm, &nodes[RightUpperArm], &nodes[LeftLowerArm]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperArmWidth, horse_dimension_.kUpperArmHeight, horse_dimension_.kUpperArmWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperArmModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 rightUpperArmModel = glm::translate(glm::mat4(1.0), glm::vec3(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperLegWidth / 2, 0.1*horse_dimension_.kUpperArmHeight, horse_dimension_.kTorsoDepth/2 - horse_dimension_.kUpperArmWidth / 2)) * RotateZ(theta[RightUpperArm]);
        //nodes[RightUpperArm] = Node(m, right_upper_arm, &nodes[LeftUpperLeg], &nodes[RightLowerArm]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperArmWidth, horse_dimension_.kUpperArmHeight, horse_dimension_.kUpperArmWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperArmModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 leftUpperLegModel = glm::translate(glm::mat4(1.0), glm::vec3(-(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperArmWidth / 2), 0.1*horse_dimension_.kUpperArmHeight, -horse_dimension_.kTorsoDepth/2 + horse_dimension_.kUpperArmWidth / 2)) * RotateZ(theta[LeftUpperLeg]);
        //nodes[LeftUpperLeg] = Node(m, left_upper_leg, &nodes[RightUpperLeg], &nodes[LeftLowerLeg]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperLegWidth, horse_dimension_.kUpperLegHeight, horse_dimension_.kUpperLegWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperLegModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 rightUpperLegModel = glm::translate(glm::mat4(1.0), glm::vec3(-(horse_dimension_.kTorsoWidth / 2 - horse_dimension_.kUpperLegWidth / 2), 0.1*horse_dimension_.kUpperLegHeight, horse_dimension_.kTorsoDepth/2 - horse_dimension_.kUpperLegWidth / 2)) * RotateZ(theta[RightUpperLeg]);
        //nodes[RightUpperLeg] = Node(m, right_upper_leg, NULL, &nodes[RightLowerLeg]);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kUpperLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kUpperLegWidth, horse_dimension_.kUpperLegHeight, horse_dimension_.kUpperLegWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperLegModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);


        glm::mat4 leftLowerArmModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperArmHeight, 0.0)) * RotateZ(theta[LeftLowerArm]);
        //nodes[LeftLowerArm] = Node(m, left_lower_arm, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerArmWidth, horse_dimension_.kLowerArmHeight, horse_dimension_.kLowerArmWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperArmModel * leftLowerArmModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 rightLowerArmModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperArmHeight, 0.0)) * RotateZ(theta[RightLowerArm]);
        //nodes[RightLowerArm] = Node(m, right_lower_arm, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerArmHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerArmWidth, horse_dimension_.kLowerArmHeight, horse_dimension_.kLowerArmWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperArmModel * rightLowerArmModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 leftLowerLegModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperLegHeight, 0.0)) * RotateZ(theta[LeftLowerLeg]);
        //nodes[LeftLowerLeg] = Node(m, left_lower_leg, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerLegWidth, horse_dimension_.kLowerLegHeight, horse_dimension_.kLowerLegWidth));
        shader_.SetMatrix4("model", torsoModel * leftUpperLegModel* leftLowerLegModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glm::mat4 rightLowerLegModel = glm::translate(glm::mat4(1.0), glm::vec3(0.0, horse_dimension_.kUpperLegHeight, 0.0))* RotateZ(theta[RightLowerLeg]);
        //nodes[RightLowerLeg] = Node(m, right_lower_leg, NULL, NULL);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * horse_dimension_.kLowerLegHeight, 0.0));
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(horse_dimension_.kLowerLegWidth, horse_dimension_.kLowerLegHeight, horse_dimension_.kLowerLegWidth));
        shader_.SetMatrix4("model", torsoModel * rightUpperLegModel * rightLowerLegModel * translate * scale);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    }


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

};
