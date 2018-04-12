#pragma once

#include <memory>
#include <vector>
#include <list>
#include <tuple>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/text_renderer.h"
#include "grid.h"
#include "axis.h"
#include "lamp.h"
#include "farm.h"
#include "horse.h"
#include "skybox.h"
class HorseFarm
{
public:
    Grid* grid_;
    Axis* axis_;
    Lamp* lamp_;
    Farm* farm_;
    Horse* horse_;
    std::vector<Horse*> horse_list_;

    TextRenderer *text_;

    Skybox* skybox_;
    //std::vector<Horse> vector_horse_;

    // Constructor/Destructor
    HorseFarm(GLuint width, GLuint height);
    ~HorseFarm();
    // Initialize game state (load all shaders/textures/levels)
    void Init();

    void Render();

    void AddHorses(unsigned number);

private:
    GLuint width_;
    GLuint height_;

    unsigned int bricksTexture;
    unsigned int grassTexture;
    unsigned int depthMapFBO;
    unsigned int depthMap;
    std::vector<int> texture_vector_;
    unsigned int texture_vector_size_ = 0;

    void RenderScene(Shader &shader);
};
