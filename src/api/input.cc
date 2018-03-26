#include "helper.h"

#include "input.h"
#include "../controller.h"

bool Input::Keys[1024];
bool Input::KeysProcessed[1024];
bool Input::KeysMode[1024];

std::map<int, bool> Input::keyDown;
std::map<int, bool> Input::keyUp;
std::map<int, bool> Input::keyHeld;

void Input::ProcessInput(GLfloat dt)
{
    //Pressing the spacebar should re-position the horse at a random location on the grid
    if(Input::Keys[GLFW_KEY_SPACE] && !Input::KeysProcessed[GLFW_KEY_SPACE])
    {
        Input::KeysProcessed[GLFW_KEY_SPACE] = true;
        if(getRandomBool())
        {
            Controller::horse_->base_x = getRandomFromRange(25);
            Controller::horse_->base_z = getRandomFromRange(25);
        }
        else
        {
            Controller::horse_->base_x = -getRandomFromRange(25);
            Controller::horse_->base_z = -getRandomFromRange(25);
        }
    }
    //pressing ‘U’ for scale-up and ‘J’ for scale-down
    else if (Input::Keys[GLFW_KEY_U])
    {
        Controller::horse_->base_scale += 0.01f;

    }
    else if (Input::Keys[GLFW_KEY_J])
    {
        if(Controller::horse_->base_scale >= 0.01)
        {
            Controller::horse_->base_scale -= 0.01f;
        }
    }

    //A ​ → move left 1 grid unit,
    //D → move right 1 grid unit,
    //W → move up 1 grid unit,
    //S → move down 1 grid unit
    //a ​ → rotate left 5 degrees about Y axis,
    //d → rotate right 5 degrees about Y axis,
    //w → rotate upwards 5 degrees raising the front legs,
    //s → rotate downwards 5 degrees raising the hind legs.
    else if(Input::Keys[GLFW_KEY_A] && !Input::KeysProcessed[GLFW_KEY_A])
    {
        Input::KeysProcessed[GLFW_KEY_A] = true;
        if(Input::KeysMode[GLFW_KEY_A] == GLFW_MOD_SHIFT)
        {
            --(Controller::horse_->base_x);
        }
        else
        {
            Controller::horse_->rotateY +=5;
        }
    }
    else if(Input::Keys[GLFW_KEY_D] && !Input::KeysProcessed[GLFW_KEY_D])
    {
        Input::KeysProcessed[GLFW_KEY_D] = true;
        if(Input::KeysMode[GLFW_KEY_D] == GLFW_MOD_SHIFT)
        {
            ++(Controller::horse_->base_x);
        }
        else
        {
            Controller::horse_->rotateY -=5;
        }
    }
    else if(Input::Keys[GLFW_KEY_W] && !Input::KeysProcessed[GLFW_KEY_W])
    {
        Input::KeysProcessed[GLFW_KEY_W] = true;
        if(Input::KeysMode[GLFW_KEY_W] == GLFW_MOD_SHIFT)
        {
            ++(Controller::horse_->base_y);
        }
        else
        {
            Controller::horse_->rotateZ +=5;
        }
    }
    else if(Input::Keys[GLFW_KEY_S] && !Input::KeysProcessed[GLFW_KEY_S])
    {
        Input::KeysProcessed[GLFW_KEY_S] = true;
        if(Input::KeysMode[GLFW_KEY_S] == GLFW_MOD_SHIFT)
        {
            if(Controller::horse_->base_y >= 1.0f)
            {
                --(Controller::horse_->base_y);
            }
        }
        else
        {
            Controller::horse_->rotateZ -=5;
        }
    }
    else if(Input::Keys[GLFW_KEY_Q] && !Input::KeysProcessed[GLFW_KEY_Q])
    {
        Input::KeysProcessed[GLFW_KEY_Q] = true;
        if(Input::KeysMode[GLFW_KEY_Q] == GLFW_MOD_SHIFT)
        {
            ++(Controller::horse_->base_z);
        }
        else
        {
            Controller::horse_->rotateX +=5;
        }
    }
    else if(Input::Keys[GLFW_KEY_E] && !Input::KeysProcessed[GLFW_KEY_E])
    {
        Input::KeysProcessed[GLFW_KEY_E] = true;
        if(Input::KeysMode[GLFW_KEY_E] == GLFW_MOD_SHIFT)
        {
            --(Controller::horse_->base_z);
        }
        else
        {
            Controller::horse_->rotateX -=5;
        }
    }

    //The world orientation
    else if(Input::Keys[GLFW_KEY_LEFT])
    {
        Controller::c_horizontal += 1.0f;
    }
    else if (Input::Keys[GLFW_KEY_RIGHT])
    {
        Controller::c_horizontal -= 1.0f;
    }
    else if(Input::Keys[GLFW_KEY_UP])
    {
        Controller::c_vertical += 1.0f;
        if(Controller::c_vertical >= 90.0)
        {
            Controller::c_vertical = 89.0f;
        }
    }
    else if(Input::Keys[GLFW_KEY_DOWN])
    {
        Controller::c_vertical -= 1.0f;
        if(Controller::c_vertical < 0)
        {
            Controller::c_vertical = 0.0f;
        }
    }

    //Pressing the “Home” button should reset to the initial world position and orientation
    else if(Input::Keys[GLFW_KEY_HOME])
    {
        Controller::ResetController();
    }
    //rendering mode
    //‘P’ for points, key ‘L’ for lines, key ‘T’ for triangles
    else if(Input::Keys[GLFW_KEY_P])
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if(Input::Keys[GLFW_KEY_L])
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if(Input::Keys[GLFW_KEY_T])
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //Rotate joint 0 by 5 degrees (Key_0 clockwise and the corresponding Shift + Key_0 for counterclockwise
    else if(Input::Keys[GLFW_KEY_0])
    {
        if(Input::KeysMode[GLFW_KEY_0] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[Head] += 1.0;
        }
        else
        {
            Controller::horse_->theta[Head] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_1])
    {
        if(Input::KeysMode[GLFW_KEY_1] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[Neck] += 1.0;
        }
        else
        {
            Controller::horse_->theta[Neck] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_2])
    {
        if(Input::KeysMode[GLFW_KEY_2] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[LeftUpperArm] += 1.0;
        }
        else
        {
            Controller::horse_->theta[LeftUpperArm] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_3])
    {
        if(Input::KeysMode[GLFW_KEY_3] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[LeftLowerArm] += 1.0;
        }
        else
        {
            Controller::horse_->theta[LeftLowerArm] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_4])
    {
        if(Input::KeysMode[GLFW_KEY_4] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[RightUpperArm] += 1.0;
        }
        else
        {
            Controller::horse_->theta[RightUpperArm] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_5])
    {
        if(Input::KeysMode[GLFW_KEY_5] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[RightLowerArm] += 1.0;
        }
        else
        {
            Controller::horse_->theta[RightLowerArm] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_6])
    {
        if(Input::KeysMode[GLFW_KEY_6] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[LeftUpperLeg] += 1.0;
        }
        else
        {
            Controller::horse_->theta[LeftUpperLeg] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_7])
    {
        if(Input::KeysMode[GLFW_KEY_7] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[LeftLowerLeg] += 1.0;
        }
        else
        {
            Controller::horse_->theta[LeftLowerLeg] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_8])
    {
        if(Input::KeysMode[GLFW_KEY_8] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[RightUpperLeg] += 1.0;
        }
        else
        {
            Controller::horse_->theta[RightUpperLeg] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_9])
    {
        if(Input::KeysMode[GLFW_KEY_9] == GLFW_MOD_SHIFT)
        {
            Controller::horse_->theta[RightLowerLeg] += 1.0;
        }
        else
        {
            Controller::horse_->theta[RightLowerLeg] -= 1.0;
        }
    }
    else if(Input::Keys[GLFW_KEY_R])
    {
        if(Controller::horse_->run_on) // stop
        {
            Controller::horse_->run_on = false;
        }
        else
        {
            Controller::horse_->run_on = true;
        }
    }
    else if(Input::Keys[GLFW_KEY_EQUAL] && Input::KeysMode[GLFW_KEY_EQUAL] == GLFW_MOD_SHIFT && !Input::KeysProcessed[GLFW_KEY_EQUAL])
    {
        Input::KeysProcessed[GLFW_KEY_EQUAL] = true;
        --(Controller::horse_->speedDivision);
        if(Controller::horse_->speedDivision < 1)
        {
            Controller::horse_->speedDivision = 1;
        }
    }
    else if(Input::Keys[GLFW_KEY_MINUS] && Input::KeysMode[GLFW_KEY_MINUS] == GLFW_MOD_SHIFT && !Input::KeysProcessed[GLFW_KEY_MINUS])
    {
        Input::KeysProcessed[GLFW_KEY_MINUS] = true;
        ++(Controller::horse_->speedDivision);
    }
    else if(Input::Keys[GLFW_KEY_N])//debug
    {
        Controller::horse_->run();
        Controller::horse_->tmp_step += 1;
        if(Controller::horse_->tmp_step > 6)
        {
            Controller::horse_->tmp_step = 1;
        }
    }
    //Render the scene with grass texture on the ground mesh and horse-skin texture on the horse
    else if(Input::Keys[GLFW_KEY_X])//debug
    {
        if(Controller::texture_on)
        {
            Controller::texture_on = false;
            Controller::shadow_on = false;
        }
        else
        {
            Controller::texture_on = true;
        }
    }
    //Render the scene with shadows using two pass shadow algorithm (Key B)
    else if(Input::Keys[GLFW_KEY_B])//debug
    {
        if(Controller::texture_on)
        {
            if(Controller::shadow_on)
            {
                Controller::shadow_on = false;
            }
            else
            {
                Controller::shadow_on = true;
            }
        }
    }
}
