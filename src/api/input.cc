#include "helper.h"

#include "input.h"
#include "../controller.h"

bool Input::Keys[1024];
bool Input::KeysProcessed[1024];

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

    if (Input::Keys[GLFW_KEY_LEFT])
    {
        Controller::c_horizontal += 1.0f;
    }
    else if (Input::Keys[GLFW_KEY_RIGHT])
    {
        Controller::c_horizontal -= 1.0f;
    }
    else if (Input::Keys[GLFW_KEY_UP])
    {
        Controller::c_vertical += 1.0f;
        if(Controller::c_vertical >= 90.0)
        {
            Controller::c_vertical = 89.0f;
        }
    }
    else if (Input::Keys[GLFW_KEY_DOWN])
    {
        Controller::c_vertical -= 1.0f;
        if(Controller::c_vertical < 0)
        {
            Controller::c_vertical = 0.0f;
        }
    }
}
