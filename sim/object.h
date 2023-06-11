#pragma once
#include <cmath>
#include <memory>
#include <SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include <iostream>
#include <cfloat>

class object{
private:
    unsigned long long par[2];
    long double xy[4];
    Uint32 color;
public:
    long double* get_xy();
    unsigned long long* get_par();
    void update_pos(long double ts);
    object(unsigned long long mass, unsigned long long radius, long double x, long double y, long double vx, long double vy, Uint32 c);
    void update(unsigned long long m, long double mx, long double my, long double ts);
    void rend(std::shared_ptr<SDL_Renderer> &gRenderer);
};