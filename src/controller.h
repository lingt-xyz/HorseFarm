#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "horse.h"

class Controller
{
public:
    //float c_rotate_x = 0.0f;
    static float c_vertical;
    static float c_horizontal;
    static float c_dir_x;
    static float c_dir_y;
    static float c_dir_z;

    static float fov;//perspective angle

    static float c_radius;
    static glm::vec3 c_pos;
    static glm::vec3 c_dir; // camera direction
    static glm::vec3 c_up; // tell the camera which way is 'up'

    static glm::vec3 light_position_;

    static glm::mat4 view;
    static glm::mat4 projection;

    static bool light_on;
    static bool texture_on;
    static bool shadow_on;

    static bool final_on;
    static bool added;

    static Horse* horse_;

    Controller();
    ~Controller();

    static void UpdateController();

    static void ResetController();
private:
};

