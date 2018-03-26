#include "iostream"
#include "api/camera.h"
#include "api/resource_manager.h"
#include "api/text_renderer.h"
#include "api/input.h"
#include "controller.h"
#include "horse_farm.h"


TextRenderer *text_;

HorseFarm::HorseFarm(GLuint width, GLuint height)
{
    this->width_ = width;
    this->height_ = height;
    //this->farm_ = new Farm(this->width_, this->height_);
}

HorseFarm::~HorseFarm()
{
    delete text_;
    delete this->grid_;
    delete this->axis_;
    delete this->farm_;
    delete this->lamp_;
}

void HorseFarm::Init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/simple.vs", "shaders/simple.fs", nullptr, "simple");

    // Load textures
    ResourceManager::LoadTexture("textures/grass.jpg", GL_FALSE, "grass");

    // Configure shaders
    //Camera camera(glm::vec3(0.0f, 20.0f, 10.0f));
    //glm::mat4 view = camera.GetViewMatrix();

    // glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width_), static_cast<GLfloat>(this->height_), 0.0f, 1.0f, 100.0f);
    float near_plane = 1.0f, far_plane = 100.0f;


    Shader shader_simple = ResourceManager::GetShader("simple");
    shader_simple.Use();

    this->grid_ = new Grid(shader_simple);
    this->axis_ = new Axis(shader_simple);
    this->lamp_ = new Lamp(shader_simple);

    Texture2D texture = ResourceManager::GetTexture("grass");
}

void HorseFarm::Render()
{
    grid_->Draw();
    axis_->Draw();
    lamp_->Draw();

}

void HorseFarm::ProcessInput(GLfloat dt)
{

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
