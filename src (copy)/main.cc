#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/input.h"
#include "api/window.h"
#include "api/resource_manager.h"
#include "horse_farm.h"
#include "controller.h"

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

HorseFarm horse_farm(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
    // create window
	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "HorseFarm");

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    horse_farm.Init();

    while (!Window::getWindowShouldClose())
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        Input::ProcessInput(deltaTime);

        // Render
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Controller::UpdateController();
        horse_farm.Render();

        Window::swapBuffers();
    }

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}
