#include "api/camera.h"
#include "horse_farm.h"

SpriteRenderer *renderer_;
TextRenderer *text_;

HorseFarm::HorseFarm(GLuint width, GLuint height)
{
    this->width_ = width;
    this->height_ = height;
    this->farm_ = new Farm(this->width_, this->height_);
}

HorseFarm::~HorseFarm()
{
    delete renderer_;
    delete text_;
    delete this->farm_;
}

void HorseFarm::Init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/grid.vs", "shaders/grid.fs", nullptr, "grid");
    //ResourceManager::LoadShader("shaders/shadow_mapping.vs", "shaders/shadow_mapping.fs", nullptr, "grid");
    //ResourceManager::LoadShader("shaders/shadow_mapping_depth.vs", "shaders/shadow_mapping_depth.fs", nullptr, "particle");

    // Load textures
    ResourceManager::LoadTexture("textures/grass.jpg", GL_FALSE, "grass");

    // Configure shaders
    Camera camera(glm::vec3(0.0f, 20.0f, 10.0f));
    glm::mat4 view = camera.GetViewMatrix();
   // glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width_), static_cast<GLfloat>(this->height_), 0.0f, 1.0f, 100.0f);
    float near_plane = 1.0f, far_plane = 100.0f;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)(this->width_) / (GLfloat)(this->height_), near_plane, far_plane);
    Shader shader_grid = ResourceManager::GetShader("grid");
    shader_grid.Use();
    shader_grid.SetMatrix4("view", view);
    shader_grid.SetMatrix4("projection", projection);

    renderer_ = new SpriteRenderer(shader_grid);

 //   text_ = new TextRenderer(this->width_, this->height_);
//    text_->Load("fonts/FreeMono.ttf", 24);
}

void HorseFarm::Render()
{
    Texture2D texture = ResourceManager::GetTexture("grass");

    renderer_->DrawSprite(texture);
    //std::stringstream string_level; string_level << this->Level;
    //Text->RenderText("Level:" + string_level.str() + ", Lives:" + string_lives.str(), 5.0f, 5.0f, 1.0f);
    //text_->RenderText("Test text", 5.0f, 5.0f, 1.0f);
}
