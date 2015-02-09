#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "SDL_extend.h"
#include "tiles.h"
#include "menu.h"

SDL_Surface *screen;
Config cfg;

void loadConfig()
{
    cfg.bpp = 32;
    cfg.h = 600;
    cfg.w = 800;
    cfg.fs = 0;//SDL_FULLSCREEN;
    cfg.memAlloc = SDL_HWSURFACE;
    cfg.mbh = 150;
    cfg.th = cfg.tw = 50;
    cfg.nt = 24;
    cfg.nn = 0;
    cfg.nd = 0;
    cfg.cpl = cfg.w / cfg.tw;
    cfg.cpc = (cfg.h - cfg.mbh) / cfg.th;
    cfg.tnc = cfg.cpl * cfg.cpc;
    cfg.sf = 0;
    cfg.sv = 50;
}

void intro()
{
    //vid de seb
}

int main(int argc, char* argv[])
{
    loadConfig();
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    loadFonts();

    screen = SDL_SetVideoMode(cfg.w, cfg.h, cfg.bpp, SDL_DOUBLEBUF | cfg.memAlloc | cfg.fs);
    SDL_WM_SetCaption("Shaak", NULL);

    intro();
    T_Load();
    menu();

    progStop();
    return 0;
}
