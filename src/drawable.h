#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "api/resource_manager.h"
#include "api/texture.h"
#include "api/text_renderer.h"

#include "sprite_renderer.h"

class Drawable
{
public:
    // Render state
    Texture2D sprite_;

    // Constructor(s)
    Drawable();
    virtual ~Drawable();
    // Draw sprite
    virtual void Draw(SpriteRenderer &renderer);
};

