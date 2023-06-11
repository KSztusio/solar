#include "object.h"
#define G 0.66743015151515
object::object(unsigned long long mass, unsigned long long radius, long double x, long double y, long double vx, long double vy, Uint32 c){
    par[0] = mass;
    par[1] = radius;
    xy[0] = x;
    xy[1] = y;
    xy[2] = vx;
    xy[3] = vy;
    color = c;
}
long double *object::get_xy(){
    return xy;
}
unsigned long long *object::get_par(){
    return par;
}
void object::update(unsigned long long m, long double mx, long double my, long double ts){
    long double a, r, rx, ry, fi;
    rx = xy[0]-mx;
    ry = xy[1]-my;
    r = sqrt(abs(rx*rx+ry*ry));
    if(r>par[1]){
    a = (G*m)/(r*r);
    }
    else{
        a = 0;
    }
    fi = atan2(ry, rx);
    xy[2] += a*ts*cos(fi);
    xy[3] += a*ts*sin(fi);
}

void object::update_pos(long double ts){
    xy[0]-=xy[2]*ts;
    xy[1]-=xy[3]*ts;
    std::cout << xy[0] << '\t' << xy[1] << '\t' << xy[2] << '\t' << xy[3] << '\n';
}

void object::rend(std::shared_ptr<SDL_Renderer> &gRenderer){
    int x, y, r;
    x = int(xy[0]);
    y = int(xy[1]);
    r = int(par[1]);
    filledCircleColor(gRenderer.get(), x, y, r, color);
}