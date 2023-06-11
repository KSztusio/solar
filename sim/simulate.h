#pragma once
#include "object.h"
#include <memory>
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include <cfloat>
int init(std::shared_ptr<SDL_Window>& gWindow, std::shared_ptr<SDL_Renderer>& gRenderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);