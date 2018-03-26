#include "iostream"
#include "api/camera.h"
#include "api/resource_manager.h"
#include "api/text_renderer.h"
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
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 10.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width_), static_cast<GLfloat>(this->height_), 0.0f, 1.0f, 100.0f);
    float near_plane = 1.0f, far_plane = 100.0f;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)(this->width_) / (GLfloat)(this->height_), near_plane, far_plane);
    Shader shader_simple = ResourceManager::GetShader("simple");
    shader_simple.Use();
    shader_simple.SetMatrix4("view", view);
    shader_simple.SetMatrix4("projection", projection);
    this->grid_ = new Grid(shader_simple);
    this->axis_ = new Axis(shader_simple);
    this->lamp_ = new Lamp(shader_simple);

}

void HorseFarm::Render()
{
    Texture2D texture = ResourceManager::GetTexture("grass");

    grid_->Draw();
    axis_->Draw();
    lamp_->Draw();

}
