#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_extend.h"
#include "map.h"
#include "tiles.h"

extern Config cfg;
SDL_Surface* cache;

/*
void T_Load()
{
    int i;
    char path[100] = {0};
    SDL_Surface* tmp = createSurface(cfg.tw * 8, cfg.th * 8);

    this.base = malloc(sizeof(SDL_Surface*) * cfg.nt);
    this.npc = malloc(sizeof(SDL_Surface*) * cfg.nn);
    this.deco = malloc(sizeof(SDL_Surface*) * cfg.nd);

    for (i = 0 ; i < cfg.nt ; i++)
    {
        sprintf(path, "images/base/%d.png", i);
        this.base[i] = IMG_Load(path);
    }
    for (i = 0 ; i < cfg.nn ; i++)
    {
        sprintf(path, "images/npc/%d.png", i);
        this.npc[i] = IMG_Load(path);
    }
    for (i = 0 ; i < cfg.nd ; i++)
    {
        sprintf(path, "images/deco/%d.png", i);
        this.deco[i] = IMG_Load(path);
    }
}*/

void T_Free()
{
    int i;

    for (i = 0 ; i < cfg.nt * 64 ; i++)
        SDL_FreeSurface(this.base[i]);
    for (i = 0 ; i < cfg.nn * 64 ; i++)
        SDL_FreeSurface(this.npc[i]);
    for (i = 0 ; i < cfg.nd * 64 ; i++)
        SDL_FreeSurface(this.deco[i]);
}

SDL_Surface* T_Get(Case item, SDL_Surface* surf)
{
    return surf;
}
