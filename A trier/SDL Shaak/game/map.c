#include <SDL/SDL.h>
#include "SDL_extend.h"
#include "map.h"
#include "tiles.h"

extern Config cfg;
Map this;

void M_Load(int ID)
{
    this.cases = malloc(sizeof(Case) * cfg.tnc);
    this.map = createSurface(cfg.cpl * cfg.tw, cfg.cpc * cfg.th);
    M_Refresh();
}

void M_free()
{
    SDL_FreeSurface(this.map);
    free(this.cases);
}

void M_Refresh()
{
    int i;
    SDL_Rect pos = {0};
    SDL_Surface* surf = NULL;

    for (i = 0 ; i < cfg.tnc ; i++)
    {
        pos.x = i % cfg.cpl;
        pos.y = i / cfg.cpl;
        blitSurface(T_Get(this.cases[i], surf), this.map, &pos);
    }
}

void M_display()
{
    blitOnScreen(this.map, (SDL_Rect){0});
}
