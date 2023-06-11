#include "vis.h"
vis::vis(object *o) : o(o) {}

void vis::rend(std::shared_ptr<SDL_Renderer> &gRenderer){
    float * par;
    float x, y, r;
    par = o->get_par();
    x = par[2];
    y = par[3];
    r = par[1];
    filledCircleColor(gRenderer.get(), x, y, r, 0xFFFF0000);
}