#include <iostream>

#include <GL/glew.h>	    // include GL Extension Wrangler
#include <GLFW/glfw3.h>     // include GLFW helper library

#include "api/resource_manager.h"
#include "input.h"
#include "window.h"
#include "horse_farm.h"


const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

int main()
{
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "HorseFarm");

    glm::vec2 position_ = glm::vec2(0.0, 0.0);
    float rotateY = 90.0;
    float unit_ = 0.5f;
    glm::vec2 points[12];
    glm::vec2 vector1 = glm::vec2(glm::cos(glm::radians(rotateY)), -glm::sin(glm::radians(rotateY))) * unit_;
    glm::vec2 vector2 = glm::vec2(glm::sin(glm::radians(rotateY)), glm::cos(glm::radians(rotateY))) * unit_;
    points[0] = position_ + vector1 + vector2;
    points[1] = points[0] + vector1 + vector1;
    points[2] = points[1] + vector1 + vector1;
    points[3] = position_ + vector1 - vector2;
    points[4] = points[3] + vector1 + vector1;
    points[5] = points[4] + vector1 + vector1;
    points[6] = position_ - vector1 - vector2;
    points[7] = points[6] - vector1 - vector1;
    points[8] = points[7] - vector1 - vector1;
    points[9] = position_ - vector1 + vector2;
    points[10] = points[9] - vector1 - vector1;
    points[11] = points[10] - vector1 - vector1;

    for(glm::vec2 pos : points)
    {
        //std::cout << glm::floor(pos.x) << ":" << glm::floor(pos.y) << std::endl;
    }


    glm::vec2 position1 = glm::vec2(10, 0);
    float offset1 = 1;
    float offset2 = 2;
    glm::vec2 position0 = glm::vec2(0, 0);;
    glm::vec2 projection = position1 - position0;

    float dotProduct0 = glm::dot(position0, projection);
    float scalarProjection0 = dotProduct0/glm::length(projection);

    float dotProduct1 = glm::dot(position1, projection);
    float scalarProjection1 = dotProduct1/glm::length(projection);
    if(scalarProjection0 + scalarProjection1 + offset1 + offset2 < glm::distance(position0, position1)){

    }

    //return 0;

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    HorseFarm* horseFarm = new HorseFarm(SCREEN_WIDTH, SCREEN_HEIGHT);
    horseFarm->Init();
    while (!Window::getWindowShouldClose())
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Input::ProcessInput(deltaTime);

        horseFarm->Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        Window::swapBuffers();
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    ResourceManager::Clear();
    delete horseFarm;

    glfwTerminate();
    return 0;
}
