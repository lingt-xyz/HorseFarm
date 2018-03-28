#include "iostream"
#include "api/camera.h"
#include "api/resource_manager.h"
#include "api/text_renderer.h"
#include "api/input.h"
#include "controller.h"
#include "horse_farm.h"



unsigned int loadTexture(const char *path);
unsigned int bricksTexture;
unsigned int grassTexture;
unsigned int depthMap;



TextRenderer *text_;
const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
unsigned int depthMapFBO;
//unsigned int depthMap;

HorseFarm::HorseFarm(GLuint width, GLuint height)
{
    this->width_ = width;
    this->height_ = height;
}

HorseFarm::~HorseFarm()
{
    delete text_;

    delete this->test_;
    delete this->grid_;
    delete this->axis_;
    delete this->lamp_;
    delete this->farm_;
    delete this->horse_;
}

void HorseFarm::Init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/test.vs", "shaders/test.fs", nullptr, "test");
    ResourceManager::LoadShader("shaders/simple.vs", "shaders/simple.fs", nullptr, "simple");
    ResourceManager::LoadShader("shaders/horse.vs", "shaders/horse.fs", nullptr, "horse");
    ResourceManager::LoadShader("shaders/light.vs", "shaders/light.fs", nullptr, "light");
    //ResourceManager::LoadShader("shaders/texture.vs", "shaders/texture.fs", nullptr, "texture");
    ResourceManager::LoadShader("shaders/shadow.vs", "shaders/shadow.fs", nullptr, "shadow");
    ResourceManager::LoadShader("shaders/shadow_depth.vs", "shaders/shadow_depth.fs", nullptr, "shadow_depth");









ResourceManager::LoadShader("shaders/shadow_mapping.vs", "shaders/shadow_mapping.fs", nullptr, "shadow_mapping");
ResourceManager::LoadShader("shaders/shadow_mapping_depth.vs", "shaders/shadow_mapping_depth.fs", nullptr, "shadow_mapping_depth");
ResourceManager::LoadTexture("textures/grass.png", GL_FALSE, "grass");
ResourceManager::LoadTexture("textures/bricks.jpg", GL_FALSE, "bricks");
bricksTexture = ResourceManager::GetTexture("bricks").ID;
grassTexture = ResourceManager::GetTexture("grass").ID;











    // Load textures
    ResourceManager::LoadTexture("textures/grass.png", GL_FALSE, "grass");
    ResourceManager::LoadTexture("textures/bricks.jpg", GL_FALSE, "bricks");

    // configure depth map FBO
    // -----------------------
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
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

    Shader shader_shadow = ResourceManager::GetShader("shadow");
    shader_shadow.Use();
    shader_shadow.SetInteger("diffuseTexture", 0);
    shader_shadow.SetInteger("shadowMap", 1);

    this->test_ = new Test();
    this->axis_ = new Axis();
    this->grid_ = new Grid();
    this->lamp_ = new Lamp();
    this->farm_ = new Farm();
    this->horse_ = new Horse();
    Controller::horse_ = this->horse_;
}

void HorseFarm::Render()
{
    Shader shader_test = ResourceManager::GetShader("test");
    Shader shader_simple = ResourceManager::GetShader("simple");
    Shader shader_horse = ResourceManager::GetShader("horse");
    Shader shader_light = ResourceManager::GetShader("light");
    //Shader shader_texture = ResourceManager::GetShader("texture");
    Shader shader_shadow = ResourceManager::GetShader("shadow");



GLuint shader = ResourceManager::GetShader("shadow_mapping").ID;
GLuint simpleDepthShader =ResourceManager::GetShader("shadow_mapping_depth").ID;

glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "diffuseTexture"), 0);
    glUniform1i(glGetUniformLocation(shader, "shadowMap"), 1);
 // for shadow only
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        glm::vec3 lightPos = Controller::light_position_;
if(Controller::shadow_on)
        {
            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);

            // 1. render depth of scene to texture (from light's perspective)
            // --------------------------------------------------------------
            float near_plane = 1.0f, far_plane = 100.0f;
            //// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
            lightProjection = glm::perspective(glm::radians(130.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
            //lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 0.0, 1.0));
            lightSpaceMatrix = lightProjection * lightView;
            // render scene from light's point of view
            glUseProgram(simpleDepthShader);
            glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
           // renderScene(simpleDepthShader);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // reset viewport
            glViewport(0, 0, this->width_, this->width_);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 2. render scene as normal using the generated depth/shadow map
            // --------------------------------------------------------------
        }

        glViewport(0, 0, this->width_, this->width_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        if(Controller::texture_on){
            glUniform1i(glGetUniformLocation(shader, "texture_on"), 1);
            if(Controller::shadow_on){
                glUniform1i(glGetUniformLocation(shader, "shadow_on"), 1);
            }else{
                glUniform1i(glGetUniformLocation(shader, "shadow_on"), 0);
            }
        }else{
            glUniform1i(glGetUniformLocation(shader, "texture_on"), 0);
            glUniform1i(glGetUniformLocation(shader, "shadow_on"), 0);
        }

        // for shadow only
        glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, glm::value_ptr(lightPos));
        glUniformMatrix4fv(glGetUniformLocation(shader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        // for lighting only (no shadow, with or without texture)
        glUniform3fv(glGetUniformLocation(shader, "light.position"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader, "light.ambient"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(shader, "light.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(shader, "light.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));


        glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(Controller::projection));
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(Controller::view));

        // set light uniforms
        glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(Controller::c_pos));

         glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bricksTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

     if(Controller::texture_on && !Controller::shadow_on){
        glUniform1i(glGetUniformLocation(shader, "material.diffuse"), 0);
        glUniform3fv(glGetUniformLocation(shader, "material.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform1f(glGetUniformLocation(shader, "material.shininess"), 64.0f);
    }
    Shader t = ResourceManager::GetShader("shadow_mapping");
horse_->Draw(t);

        //simpleShader.use();
        //simpleShader.setMat4("projection", Projection);
       // simpleShader.setMat4("view", Controller::view);
        //renderAxis(simpleShader);



        //renderLamp(simpleShader);
return;


    /*
    shader_test.Use();
    shader_test.SetVector3f("objectColor", 1.0f, 0.5f, 0.31f);
    shader_test.SetVector3f("lightColor", 1.0f, 1.0f, 1.0f);
    shader_test.SetVector3f("lightPos", Controller::light_position_);
    shader_test.SetVector3f("viewPos", Controller::c_pos);
    test_->Draw(shader_test);
    return;
    */

    shader_light.Use();
    shader_light.SetVector3f("objectColor", 1.0f, 0.5f, 0.31f);
    shader_light.SetVector3f("lightColor", 1.0f, 1.0f, 1.0f);
    shader_light.SetVector3f("lightPos", Controller::light_position_);
    shader_light.SetVector3f("viewPos", Controller::c_pos);
    horse_->Draw(shader_light);
    return;

    axis_->Draw(shader_simple);

    if(!Controller::light_on) // this is the assignment1
    {
        grid_->Draw(shader_simple);
        horse_->Draw(shader_horse);
    }
    else // add lighting
    {
        lamp_->Draw(shader_simple);

        shader_light.Use();
        shader_light.SetVector3f("objectColor", 1.0f, 0.5f, 0.31f);
        shader_light.SetVector3f("lightColor", 1.0f, 1.0f, 1.0f);
        shader_light.SetVector3f("lightPos", Controller::light_position_);
        shader_light.SetVector3f("viewPos", Controller::c_pos);

        if(!Controller::texture_on) // only lighting without texturing
        {
            grid_->Draw(shader_simple);
            horse_->Draw(shader_light);
        }
        else
        {
            // for shadow only
            glm::mat4 lightProjection, lightView;
            glm::mat4 lightSpaceMatrix;

            shader_shadow.SetVector3f("lightPos", Controller::light_position_);
            shader_shadow.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

            // for lighting only (no shadow, with or without texture)
            shader_shadow.SetVector3f("light.position", Controller::light_position_);
            shader_shadow.SetVector3f("light.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
            shader_shadow.SetVector3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            shader_shadow.SetVector3f("light.specular", glm::vec3(0.5f, 0.5f, 0.5f));

            // set light uniforms
            shader_shadow.SetVector3f("viewPos", Controller::c_pos);

            Texture2D texture_grass = ResourceManager::GetTexture("grass");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_grass.ID);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthMap);
            farm_->Draw(shader_shadow);

            Texture2D texture_bricks = ResourceManager::GetTexture("bricks");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_bricks.ID);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthMap);
            horse_->Draw(shader_shadow);

            if(!Controller::shadow_on) // lighting and texturing
            {
                farm_->Draw(shader_shadow);
                horse_->Draw(shader_shadow);
            }
            else  // lighting, texturing, and shadowing
            {
                glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
                glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
                glClear(GL_DEPTH_BUFFER_BIT);

                // 1. render depth of scene to texture (from light's perspective)
                // --------------------------------------------------------------
                //// note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
                lightProjection = glm::perspective(glm::radians(130.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, 1.0f, 100.0f);
                //lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
                lightView = glm::lookAt(Controller::light_position_, glm::vec3(0.0f), glm::vec3(0.0, 0.0, 1.0));
                lightSpaceMatrix = lightProjection * lightView;
                // render scene from light's point of view
                Shader shader_shadow_depth = ResourceManager::GetShader("shadow_depth");
                shader_shadow_depth.Use();
                shader_shadow_depth.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

                //TODO
                //renderScene(simpleDepthShader);

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                // reset viewport
                glViewport(0, 0, this->width_, this->height_);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // 2. render scene as normal using the generated depth/shadow map
                // --------------------------------------------------------------

                farm_->Draw(shader_shadow);
                horse_->Draw(shader_shadow);
            }
        }
    }
}
