#pragma once
#include <memory>

#include <SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>

#include "object.h"

class vis{
private:
    object* o;
public:
    vis(object* o);
    void rend(std::shared_ptr<SDL_Renderer> &gRenderer);
};