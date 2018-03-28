#include <iostream>

#include <GL/glew.h>	    // include GL Extension Wrangler
#include <GLFW/glfw3.h>     // include GLFW helper library

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "Vertices.h"
#include "MatrixStack.h"
#include "Node.h"
#include "Horse.h"
#include "helper.h"



#include "api/resource_manager.h"
#include "window.h"
#include "input.h"
#include "controller.h"
#include "lamp.h"
#include "axis.h"
#include "grid.h"

void renderScene(Shader &shader_axis);
void renderHorse(Shader &shader_axis);


glm::mat4 View;
glm::mat4 Projection;
glm::vec3 lightPos;
unsigned int bricksTexture;
unsigned int grassTexture;
unsigned int depthMap;
Grid* grid_;

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

int main()
{
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "HorseFarm");

    // build and compile shaders
    // -------------------------
    GLuint shader = ResourceManager::LoadShader("shaders/shadow_mapping.vs", "shaders/shadow_mapping.fs", nullptr, "shadow_mapping").ID;
    GLuint simpleDepthShader = ResourceManager::LoadShader("shaders/shadow_mapping_depth.vs", "shaders/shadow_mapping_depth.fs", nullptr, "shadow_mapping_depth").ID;
    ResourceManager::LoadShader("shaders/simple.vs", "shaders/simple.fs", nullptr, "simple");
    Shader simpleShader = ResourceManager::GetShader("simple");

    // load textures
    // -------------
    ResourceManager::LoadTexture("textures/grass.png", GL_FALSE, "grass");
    ResourceManager::LoadTexture("textures/bricks.jpg", GL_FALSE, "bricks");
    bricksTexture = ResourceManager::GetTexture("bricks").ID;
    grassTexture = ResourceManager::GetTexture("grass").ID;
    // configure depth map FBO
    // -----------------------
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
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


    // shader configuration
    // --------------------
    //shader.use();
    //shader.setInt("diffuseTexture", 0);
    //shader.setInt("shadowMap", 1);
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "diffuseTexture"), 0);
    glUniform1i(glGetUniformLocation(shader, "shadowMap"), 1);

    //horse = Horse();
    // render loop
    // -----------

    lightPos = Controller::light_position_;
    Lamp* lamp_ = new Lamp();
    Axis* axis_ = new Axis();
    grid_ = new Grid();
    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    while (!Window::getWindowShouldClose())
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Input::ProcessInput(deltaTime);

        // render
        // ------
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Controller::UpdateController();
        // Camera matrix
        View = Controller::view;

        Projection = Controller::projection;


        // for shadow only
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
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
            Shader s1 = ResourceManager::GetShader("shadow_mapping_depth");
            renderScene(s1);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // reset viewport
            glViewport(0, 0, Window::width, Window::height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 2. render scene as normal using the generated depth/shadow map
            // --------------------------------------------------------------
        }

        glViewport(0, 0, Window::width, Window::height);
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


        glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(View));

        // set light uniforms
        glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(Controller::c_pos));
        Shader s2 = ResourceManager::GetShader("shadow_mapping");
        renderScene(s2);

        simpleShader.Use();
        simpleShader.SetMatrix4("projection", Projection);
        simpleShader.SetMatrix4("view", View);
        //renderAxis(simpleShader);
        axis_->Draw(simpleShader);

        // only calculate when in normal frame
        if(run_on) // let's run
        {
            run();
            ++tmp_time;
            tmp_time %= (speedDivision+1);
            tmp_step += (tmp_time / speedDivision);
            if(tmp_step > 6)
            {
                tmp_step = 1;
            }
        }

        //renderLamp(simpleShader);
       lamp_->Draw(simpleShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        Window::swapBuffers();
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void renderScene(Shader &shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    // grid
    //renderGrid(shader);
    grid_->Draw(shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bricksTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    // horse
    renderHorse(shader);
}


GLuint horseVAO = 0;
GLuint horseVBO[3];
void renderHorse(Shader &shader_horse)
{
    shader_current = shader_horse.ID;
    if (horseVAO == 0)
    {
        generateBaseCube();

        glGenVertexArrays(1, &horseVAO);
        glGenBuffers(3, horseVBO);

        glBindVertexArray(horseVAO);
        glBindBuffer(GL_ARRAY_BUFFER, horseVBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);// vertices shader, layout=0

        glBindBuffer(GL_ARRAY_BUFFER, horseVBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);// vertices shader, layout=1

        glBindBuffer(GL_ARRAY_BUFFER, horseVBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);// vertices shader, layout=2

        glBindVertexArray(0);

    }

    if(Controller::texture_on && !Controller::shadow_on){
        glUniform1i(glGetUniformLocation(shader_current, "material.diffuse"), 0);
        glUniform3fv(glGetUniformLocation(shader_current, "material.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform1f(glGetUniformLocation(shader_current, "material.shininess"), 64.0f);
    }

    glBindVertexArray(horseVAO);
    initNodes();
    traverse(&nodes[Torso]);

    glBindVertexArray(0);
}
