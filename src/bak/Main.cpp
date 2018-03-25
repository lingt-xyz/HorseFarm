#include <iostream>

#include <GL/glew.h>	    // include GL Extension Wrangler
#include <GLFW/glfw3.h>     // include GLFW helper library

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#include <stb_image.h>
#include <shader_gl.h>

#include "Vertices.h"
#include "Config.h"
#include "Helper.h"
#include "MatrixStack.h"
#include "Node.h"

#include "Horse.h"

int init_window(int width, int height, const std::string title);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void renderScene(const GLuint &shader);
void renderGrid(const GLuint &shader_grid);
void renderHorse(const GLuint &shader_horse);

void renderAxis(const Shader &shader_axis);
void renderLamp(const Shader &shader_lamp);

unsigned int loadTexture(const char *path);

GLFWwindow* window;

glm::mat4 View;
glm::mat4 Projection;

unsigned int bricksTexture;
unsigned int grassTexture;
unsigned int depthMap;

int main()
{
    if (init_window(WIDTH, HEIGHT, TITLE) != 0)
    {
        return -1;
    }

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    GLuint shader = loadShaders("shaders/shadow_mapping.vs", "shaders/shadow_mapping.fs");
    GLuint simpleDepthShader = loadShaders("shaders/shadow_mapping_depth.vs", "shaders/shadow_mapping_depth.fs");

    Shader simpleShader("shaders/simple.vs", "shaders/simple.fs");

    // load textures
    // -------------
    bricksTexture = loadTexture("resources/bricks.jpg");
    grassTexture = loadTexture("resources/grass.jpg");

    // configure depth map FBO
    // -----------------------
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
//    unsigned int depthMap;
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
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double c_pos_x = c_radius * glm::cos(glm::radians(c_vertical)) * glm::cos(glm::radians(c_horizontal));
        double c_pos_y = c_radius * glm::sin(glm::radians(c_vertical));
        double c_pos_z = c_radius * glm::cos(glm::radians(c_vertical)) * glm::sin(glm::radians(c_horizontal));
        c_pos = glm::vec3(c_pos_x, c_pos_y, c_pos_z); // camera position
        c_dir = glm::vec3(c_dir_x, c_dir_y, c_dir_z); // camera direction
        // Camera matrix
        View = glm::lookAt(c_pos, c_dir, c_up);

        Projection = glm::perspective(glm::radians(fov), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
        //std::cout << "texture_on:" << texture_on << ", shadow_on:" << shadow_on << std::endl;

        // for shadow only
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        if(shadow_on)
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
            renderScene(simpleDepthShader);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // reset viewport
            glViewport(0, 0, WIDTH, HEIGHT);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 2. render scene as normal using the generated depth/shadow map
            // --------------------------------------------------------------
        }

        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        if(texture_on){
            glUniform1i(glGetUniformLocation(shader, "texture_on"), 1);
            if(shadow_on){
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
        glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(c_pos));

        renderScene(shader);

        simpleShader.use();
        simpleShader.setMat4("projection", Projection);
        simpleShader.setMat4("view", View);
        renderAxis(simpleShader);

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

        renderLamp(simpleShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

void renderScene(const GLuint &shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    // grid
    renderGrid(shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bricksTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    // horse
    renderHorse(shader);
}

GLuint vertexArray_grid = 0;
GLuint vertexBuffer_grid = 0;
GLuint EBO = 0;
void renderGrid(const GLuint &shader_grid)
{

    if(vertexArray_grid == 0)
    {
        glGenVertexArrays(1, &vertexArray_grid);
        glGenBuffers(1, &vertexBuffer_grid);
        glGenBuffers(1, &EBO);

/*
        GLfloat buffer_data_grid[] =
        {
            -50.f, 0.f, 50.f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            50.f, 0.f, 50.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            50.f, 0.f, -50.f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -50.f, 0.f, -50.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        };
*/

        glBindVertexArray(vertexArray_grid);
        glBindBuffer(GL_ARRAY_BUFFER, vertexArray_grid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_grid), buffer_data_grid, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    glBindVertexArray(vertexArray_grid);

    // for no texture only
    glUniform4fv(glGetUniformLocation(shader_grid, "shader_color"), 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

    // for texture only
    glUniform1i(glGetUniformLocation(shader_grid, "material.diffuse"), 0.3);
    glUniform3fv(glGetUniformLocation(shader_grid, "material.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    glUniform1f(glGetUniformLocation(shader_grid, "material.shininess"), 64.0f);

/*
    glUniformMatrix4fv(glGetUniformLocation(shader_grid, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    if(texture_on)
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_LINE_LOOP, 0, 4*2);
    }
    return;
*/

    for(int i=1; i<=gridX; ++i)
    {
        glm::mat4 anchor_x1 = glm::translate(glm::mat4(1.0f), glm::vec3(i-1, 0.f, 0.f));
        for(int j=1; j<=gridZ; ++j)
        {
            glm::mat4 anchor_z1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, j-1));
            glUniformMatrix4fv(glGetUniformLocation(shader_grid, "model"), 1, GL_FALSE, glm::value_ptr(anchor_x1 * anchor_z1));
            if(texture_on)
            {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_LINE_LOOP, 0, 4*2);
            }

            glm::mat4 anchor_z2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -j));
            glUniformMatrix4fv(glGetUniformLocation(shader_grid, "model"), 1, GL_FALSE, glm::value_ptr(anchor_x1 * anchor_z2));
            if(texture_on)
            {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_LINE_LOOP, 0, 4*2);
            }
        }

        glm::mat4 anchor_x2 = glm::translate(glm::mat4(1.0f), glm::vec3(-i, 0.f, 0.f));
        for(int j=1; j<=gridZ; ++j)
        {
            glm::mat4 anchor_1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, j-1));
            glUniformMatrix4fv(glGetUniformLocation(shader_grid, "model"), 1, GL_FALSE, glm::value_ptr(anchor_x2 * anchor_1));
            if(texture_on)
            {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_LINE_LOOP, 0, 4*2);
            }

            glm::mat4 anchor_2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -j));
            glUniformMatrix4fv(glGetUniformLocation(shader_grid, "model"), 1, GL_FALSE, glm::value_ptr(anchor_x2 * anchor_2));
            if(texture_on)
            {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_LINE_LOOP, 0, 4*2);
            }
        }
    }
    glBindVertexArray(0);
}

GLuint horseVAO = 0;
GLuint horseVBO[3];
void renderHorse(const GLuint &shader_horse)
{
    shader_current = shader_horse;
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

    if(texture_on && !shadow_on){
        glUniform1i(glGetUniformLocation(shader_horse, "material.diffuse"), 0);
        glUniform3fv(glGetUniformLocation(shader_horse, "material.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform1f(glGetUniformLocation(shader_horse, "material.shininess"), 64.0f);
    }

    glBindVertexArray(horseVAO);
    initNodes();
    traverse(&nodes[Torso]);

    glBindVertexArray(0);
}

GLuint vertexArray_axis = 0;
GLuint vertexBuffer_axis = 0;
void renderAxis(const Shader &shader_axis)
{
    if(vertexArray_axis == 0)
    {
        glGenVertexArrays(1, &vertexArray_axis);
        glGenBuffers(1, &vertexBuffer_axis);

        glBindVertexArray(vertexArray_axis);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_axis);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_axis), buffer_data_axis, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));

        glBindVertexArray(0);
    }

    glBindVertexArray(vertexArray_axis);
    shader_axis.setMat4("model", glm::mat4(1.0f));
    shader_axis.setBool("self_color", true);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(5.0f);
    glDrawArrays(GL_LINES, 0, 3*2);
    glDrawArrays(GL_LINES, 6, 3*2);
    glDrawArrays(GL_LINES, 12, 3*2);
    glLineWidth(0.5f);
    glBindVertexArray(0);
}

unsigned int vertexArray_lamp = 0;
unsigned int lightVBO = 0;
void renderLamp(const Shader &shader_lamp)
{
    if(vertexArray_lamp == 0)
    {
        glGenVertexArrays(1, &vertexArray_lamp);
        glGenBuffers(1, &lightVBO);

        glBindVertexArray(vertexArray_lamp);
        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_cube), buffer_data_cube, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindVertexArray(0);
    }

    glBindVertexArray(vertexArray_lamp);
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    shader_lamp.setBool("self_color", false);
    shader_lamp.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //Pressing the spacebar should re-position the horse at a random location on the grid
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        if(getRandomBool())
        {
            base_x = getRandomFromRange(gridX);
            base_z = getRandomFromRange(gridX);
        }
        else
        {
            base_x = -getRandomFromRange(gridX);
            base_z = -getRandomFromRange(gridX);
        }
    }
    //pressing ‘U’ for scale-up and ‘J’ for scale-down
    else if (key == GLFW_KEY_U && action == GLFW_PRESS)
    {
        base_scale += 0.1f;
        updateTorso();

    }
    else if (key == GLFW_KEY_J && action == GLFW_PRESS)
    {
        if(base_scale >= 0.1)
        {
            base_scale -= 0.1f;
        }
        updateTorso();
    }
    //A ​ → move left 1 grid unit,
    //D → move right 1 grid unit,
    //W → move up 1 grid unit,
    //S → move down 1 grid unit
    //a ​ → rotate left 5 degrees about Y axis,
    //d → rotate right 5 degrees about Y axis,
    //w → rotate upwards 5 degrees raising the front legs,
    //s → rotate downwards 5 degrees raising the hind legs.
    else if(key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            --base_x;
        }
        else
        {
            rotateY +=5;
        }
    }
    else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            ++base_x;
        }
        else
        {
            rotateY -=5;
        }
    }
    else if(key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            ++base_y;
        }
        else
        {
            rotateZ +=5;
        }
    }
    else if(key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            if(base_y >= 1.0f)
            {
                --base_y;
            }
        }
        else
        {
            rotateZ -=5;
        }
    }
    else if(key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            ++base_z;
        }
        else
        {
            rotateX +=5;
        }
    }
    else if(key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            if(base_z >= 1.0f)
            {
                --base_z;
            }
        }
        else
        {
            rotateX -=5;
        }
    }
    //The world orientation
    else if (key == GLFW_KEY_LEFT)
    {
        if(action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            c_horizontal += 1.0f;
        }

    }
    else if(key == GLFW_KEY_RIGHT)
    {
        if(action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            c_horizontal -= 1.0f;
        }
    }
    else if(key == GLFW_KEY_UP)
    {
        if(action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            c_vertical += 1.0f;
            if(c_vertical >= 90.0)
            {
                c_vertical = 89.0f;
            }
        }

    }
    else if(key == GLFW_KEY_DOWN)
    {
        if(action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            c_vertical -= 1.0f;
            if(c_vertical < 0)
            {
                c_vertical = 0.0f;
            }
        }
    }
    //Pressing the “Home” button should reset to the initial world position and orientation
    else if(key == GLFW_KEY_HOME && action == GLFW_PRESS)
    {
        resetConfiguration();
        resetHorse();
    }
    //rendering mode
    //‘P’ for points, key ‘L’ for lines, key ‘T’ for triangles
    else if(key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if(key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if(key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    //Rotate joint 0 by 5 degrees (Key_0 clockwise and the corresponding Shift + Key_0 for counterclockwise
    else if(key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[Head] += 1.0;
        }
        else
        {
            theta[Head] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[Neck] += 1.0;
        }
        else
        {
            theta[Neck] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[LeftUpperArm] += 1.0;
        }
        else
        {
            theta[LeftUpperArm] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[LeftLowerArm] += 1.0;
        }
        else
        {
            theta[LeftLowerArm] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[RightUpperArm] += 1.0;
        }
        else
        {
            theta[RightUpperArm] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[RightLowerArm] += 1.0;
        }
        else
        {
            theta[RightLowerArm] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[LeftUpperLeg] += 1.0;
        }
        else
        {
            theta[LeftUpperLeg] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[LeftLowerLeg] += 1.0;
        }
        else
        {
            theta[LeftLowerLeg] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_8 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[RightUpperLeg] += 1.0;
        }
        else
        {
            theta[RightUpperLeg] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        if(mode == GLFW_MOD_SHIFT)
        {
            theta[RightLowerLeg] += 1.0;
        }
        else
        {
            theta[RightLowerLeg] -= 1.0;
        }
    }
    else if(key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        if(run_on) // stop
        {
            run_on = false;
        }
        else
        {
            run_on = true;
        }
    }
    else if(key == GLFW_KEY_EQUAL && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
    {
        --speedDivision;
        if(speedDivision < 1)
        {
            speedDivision = 1;
        }
    }
    else if(key == GLFW_KEY_MINUS && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
    {
        ++speedDivision;
    }
    else if(key == GLFW_KEY_N && action == GLFW_PRESS)//debug
    {
        run();
        tmp_step += 1;
        if(tmp_step > 6)
        {
            tmp_step = 1;
        }
    }
    //Render the scene with grass texture on the ground mesh and horse-skin texture on the horse
    else if(key == GLFW_KEY_X && action == GLFW_PRESS)//debug
    {
        if(texture_on)
        {
            texture_on = false;
            shadow_on = false;
        }
        else
        {
            texture_on = true;
        }
    }
    //Render the scene with shadows using two pass shadow algorithm (Key B)
    else if(key == GLFW_KEY_B && action == GLFW_PRESS)//debug
    {
        if(texture_on)
        {
            if(shadow_on)
            {
                shadow_on = false;
            }
            else
            {
                shadow_on = true;
            }
        }
    }
}

float lastX;
float lastY;
bool leftMouseButton=false, middleMouseButton=false, rightMouseButton=false;//varibles for detecting the mouse button action
bool firstMouse=true;

void cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
    if(firstMouse)
    {
        lastX=xPos;
        lastY=yPos;
        firstMouse=false;
        return;
    }

    float xOffset=xPos-lastX;
    float yOffset=yPos-lastY;
    lastX=xPos;
    lastY=yPos;

    //while right button is pressed → use mouse movement in x direction to pan
    if(rightMouseButton)//yaw
    {
        c_dir_x += 0.1 * xOffset;
    }
    //while middle button is pressed → use mouse movement in y direction to tilt.
    if(middleMouseButton)//pitch
    {
        c_dir_y -= 0.1*yOffset;
    }
    //while left button is pressed use mouse movement to move into/out of the scene
    if(leftMouseButton)//zoom in and out by adjusting the fov degree
    {
        if(fov >= 1.0f && fov <= 80.0f)
            fov += 0.1*yOffset;
        if(fov <= 1.0f)
            fov = 1.0f;
        if(fov >= 80.0f)
            fov = 80.0f;
    }
}

void mouse_button_callback(GLFWwindow* window, int key, int action, int mods)
{
    if(key==GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
        {
            rightMouseButton=true;
        }
        else if(action == GLFW_RELEASE)
        {
            rightMouseButton=false;
        }
    }
    else if(key==GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if(action == GLFW_PRESS)
        {
            middleMouseButton=true;
        }
        else if(action == GLFW_RELEASE)
        {
            middleMouseButton=false;
        }
    }
    else if(key==GLFW_MOUSE_BUTTON_LEFT)
    {
        if(action == GLFW_PRESS)
        {
            leftMouseButton=true;
        }
        else if(action == GLFW_RELEASE)
        {
            leftMouseButton=false;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

int init_window(int width, int height, const std::string title)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    // Needed for core profile
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    return 0;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
