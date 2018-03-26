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
}

HorseFarm::~HorseFarm()
{
    delete text_;
    delete this->grid_;
    delete this->axis_;
    delete this->farm_;
    delete this->lamp_;
    delete this->farm_;
    delete this->horse_;
}

void HorseFarm::Init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/simple.vs", "shaders/simple.fs", nullptr, "simple");

    // Load textures
    ResourceManager::LoadTexture("textures/grass.jpg", GL_FALSE, "grass");

    Shader shader_simple = ResourceManager::GetShader("simple");
    shader_simple.Use();

    Controller::shadow_on;
    Controller::texture_on;

    this->axis_ = new Axis(shader_simple);
    if(!Controller::light_on){
        this->grid_ = new Grid(shader_simple);
    }
    this->lamp_ = new Lamp(shader_simple);
    //this->farm_ = new Farm(shader_simple);

   // else{

        //if(!Controller::texture_on)//{

      // }
    //}


    this->horse_ = new Horse(shader_simple);

    Texture2D texture = ResourceManager::GetTexture("grass");
}

void HorseFarm::Render()
{
    grid_->Draw();
    axis_->Draw();
    lamp_->Draw();
    //farm_->Draw();
    horse_->Draw();
}
