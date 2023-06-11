#include "simulate.h"
using namespace std;
#define time_step 0.00001
int menu(vector <object> *list, unsigned long long *overall_mass);
void sim(vector <object>*list, int n, long double overall_mass);

int main(int argv, char** args){
    vector <object> list;
    int n;
    unsigned long long overall_mass = 0;
    n = menu(&list, &overall_mass);
    if(n>0){
    sim(&list, n, overall_mass);
    }
    return 0;
}

int menu(vector <object> *list, unsigned long long *overall_mass){
    unsigned long long m, r;
    long double x, y, vx, vy;
    Uint32 c;
    char z;
    bool g = 1;
    while(cin >> z && g){
        switch(z){
            case 'a':
                cout << "mass, radius, x, y, vx, vy, color hex\n";
                cin >> m >> r >> x >> y >> vx >> vy;
                cin >> hex >> c;
                list->push_back(object(m,r,x+640,360-y,vx,-vy, c));
                (*overall_mass)+=m;
            break;
            case 's':
                return list->size();
                break;
            default:
                break;
        }
    }
    return -1;
}

void sim(vector <object>*list, int n, long double overall_mass){
    std::shared_ptr<SDL_Window> gWindow = nullptr;
    std::shared_ptr<SDL_Renderer> gRenderer = nullptr;
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    long double mx, my;
    if (init(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) >= 0){
        SDL_Event e;
        bool quit = false;
        while(!quit){
            while (SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    quit = true;
                }
                
            }
            long double lx = 0, ly = 0, *xy, *xy1;
            unsigned long long *par, *par1;
                for(int i = 0; i < n; i++){
                    par = (*list)[i].get_par();
                    xy = (*list)[i].get_xy();
                    lx += par[0]*xy[0];
                    ly += par[0]*xy[1];
                }
                mx = lx/overall_mass;
                my = ly/overall_mass;
                
                SDL_Delay((int)time_step*1000);
                SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(gRenderer.get());
                for(int i = 0; i < n; i++){
                    (*list)[i].rend(gRenderer);
                }
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        if(i!=j){
                            xy1 = (*list)[j].get_xy();
                            par1 = (*list)[j].get_par();
                            (*list)[i].update(par1[0], xy1[0],xy1[1], time_step);
                        }
                    }
                    (*list)[i].update_pos(time_step);
                }
                SDL_RenderPresent(gRenderer.get());
        }
    }
    SDL_Quit();
}

int init(std::shared_ptr<SDL_Window>& gWindow, std::shared_ptr<SDL_Renderer>& gRenderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if (SDL_Init(SDL_INIT_VIDEO) >= 0)
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        gWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow("sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
        gRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(gWindow.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
        SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    }
    else
    {
        std::cout << "SDL_ERROR: " << SDL_GetError() << std::endl;
        return -1;
    }
    return 0;
}