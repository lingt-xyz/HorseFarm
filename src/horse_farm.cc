#include "iostream"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helper.h"
#include "api/resource_manager.h"
#include "api/text_renderer.h"
#include "window.h"
#include "input.h"

#include "controller.h"
#include "lamp.h"
#include "axis.h"
#include "grid.h"
#include "horse.h"

#include "horse_farm.h"

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

HorseFarm::HorseFarm(GLuint width, GLuint height)
{
    this->width_ = width;
    this->height_ = height;
}

HorseFarm::~HorseFarm()
{
    //delete this->text_;

    delete this->grid_;
    delete this->axis_;
    delete this->lamp_;
    delete this->farm_;
    delete this->horse_;
    horse_list_.remove_if([](Horse *theElement)
    {
        delete theElement;
        return true;
    });

    //while(!horse_list_.empty()) delete horse_list_.front(), horse_list_.pop_front();
}

void HorseFarm::Init()
{
    // build and compile shaders
    // -------------------------
    ResourceManager::LoadShader("shaders/shadow_mapping.vs", "shaders/shadow_mapping.fs", nullptr, "shadow_mapping");
    ResourceManager::LoadShader("shaders/shadow_mapping_depth.vs", "shaders/shadow_mapping_depth.fs", nullptr, "shadow_mapping_depth");
    ResourceManager::LoadShader("shaders/simple.vs", "shaders/simple.fs", nullptr, "simple");

    // load textures
    // -------------
    ResourceManager::LoadTexture("textures/grass.png", GL_FALSE, "grass");
    ResourceManager::LoadTexture("textures/bricks.jpg", GL_FALSE, "bricks");
    bricksTexture = ResourceManager::GetTexture("bricks").ID;
    grassTexture = ResourceManager::GetTexture("grass").ID;
    // configure depth map FBO
    // -----------------------
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    // unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Shader shader_shadow_mapping = ResourceManager::GetShader("shadow_mapping");
    shader_shadow_mapping.Use();
    shader_shadow_mapping.SetInteger("diffuseTexture", 0);
    shader_shadow_mapping.SetInteger("shadowMap", 1);

    this->axis_ = new Axis();
    this->grid_ = new Grid();
    this->lamp_ = new Lamp();
    this->farm_ = new Farm();
    this->horse_ = new Horse();
    Controller::horse_ = horse_;
}

void HorseFarm::Render()
{
    Shader shader_simple = ResourceManager::GetShader("simple");
    Shader shader_horse = ResourceManager::GetShader("horse");
    Shader shader_light = ResourceManager::GetShader("light");
    //Shader shader_texture = ResourceManager::GetShader("texture");
    Shader shader_shadow = ResourceManager::GetShader("shadow");

    // render
    // ------
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Controller::UpdateController();


    if(Controller::final_on)
    {
        if(!Controller::added)
        {
            this->AddHorses(20);
            Controller::added = true;
        }
    }
    else
    {
        horse_list_.remove_if([](Horse *theElement)
        {
            delete theElement;
            return true;
        });
    }
    // for shadow only
    glm::mat4 lightSpaceMatrix;
    if(Controller::shadow_on)
    {
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        //// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        glm::mat4 lightProjection = glm::perspective(glm::radians(130.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, 1.0f, 100.0f);
        lightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, 1.0f, 100.0f);
        glm::mat4 lightView = glm::lookAt(Controller::light_position_, glm::vec3(0.0f), glm::vec3(0.0, 0.0, 1.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view
        Shader shader_mapping_depth = ResourceManager::GetShader("shadow_mapping_depth");
        shader_mapping_depth.Use();
        shader_mapping_depth.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

        RenderScene(shader_mapping_depth);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // reset viewport
        glViewport(0, 0, Window::width, Window::height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. render scene as normal using the generated depth/shadow map
        // --------------------------------------------------------------
    }

    glViewport(0, 0, Window::width, Window::height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint shader = ResourceManager::GetShader("shadow_mapping").ID;
    glUseProgram(shader);

    if(Controller::texture_on)
    {
        glUniform1i(glGetUniformLocation(shader, "texture_on"), 1);
        if(Controller::shadow_on)
        {
            glUniform1i(glGetUniformLocation(shader, "shadow_on"), 1);
        }
        else
        {
            glUniform1i(glGetUniformLocation(shader, "shadow_on"), 0);
        }
    }
    else
    {
        glUniform1i(glGetUniformLocation(shader, "texture_on"), 0);
        glUniform1i(glGetUniformLocation(shader, "shadow_on"), 0);
    }

    // for shadow only
    glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, glm::value_ptr(Controller::light_position_));
    glUniformMatrix4fv(glGetUniformLocation(shader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

    // for lighting only (no shadow, with or without texture)
    glUniform3fv(glGetUniformLocation(shader, "light.position"), 1, glm::value_ptr(Controller::light_position_));
    glUniform3fv(glGetUniformLocation(shader, "light.ambient"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    glUniform3fv(glGetUniformLocation(shader, "light.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    glUniform3fv(glGetUniformLocation(shader, "light.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));


    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(Controller::projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(Controller::view));

    // set light uniforms
    glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(Controller::c_pos));
    Shader s2 = ResourceManager::GetShader("shadow_mapping");
    RenderScene(s2);

    Shader simpleShader = ResourceManager::GetShader("simple");
    simpleShader.Use();
    simpleShader.SetMatrix4("projection", Controller::projection);
    simpleShader.SetMatrix4("view", Controller::view);
    axis_->Draw(simpleShader);
    lamp_->Draw(simpleShader);
}

void HorseFarm::RenderScene(Shader &shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);


    if(!Controller::texture_on)
    {
        grid_->Draw(shader);
    }
    else
    {
        farm_->Draw(shader);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bricksTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    if(!Controller::final_on)
    {
        horse_->Draw(shader);
    }
    else
    {

        for (Horse* h : horse_list_)
        {
            h->Draw(shader);
            h->Animation(horse_list_);
        }
    }
}

void HorseFarm::AddHorses(unsigned number)
{
    for(int i=0; i<number; i++)
    {
        Horse* horse = new Horse();
        do
        {
            horse->GenerateRandomHorse();
        }
        while(horse->CollisionDetection(this->horse_list_));
        horse_list_.push_back(horse);
    }
}
