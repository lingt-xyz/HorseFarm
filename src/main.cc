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
