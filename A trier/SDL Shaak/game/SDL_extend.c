#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SDL_extend.h"

extern SDL_Surface *screen;
Fonts fonts;
char altStatus;

void loadFonts()
{
    fonts.minecraftia35 = TTF_OpenFont("fonts/minecraftia.ttf", 35);
}

void progStop()
{
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void checkQuit(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_RALT)
            altStatus |= 0b10;
        else if (e.key.keysym.sym == SDLK_LALT)
            altStatus |= 0b01;
    }
    else if (e.type == SDL_KEYUP)
    {
        if (e.key.keysym.sym == SDLK_RALT)
            altStatus &= 0b01;
        else if (e.key.keysym.sym == SDLK_LALT)
            altStatus &= 0b10;
    }
    if (e.type == SDL_QUIT || (altStatus && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F4))
        progStop();
}

int blitOnScreen(SDL_Surface* src, SDL_Rect p) {return SDL_BlitSurface(src, NULL, screen, &p);}
int flip() {return SDL_Flip(screen);}
Uint32 mapRGB(int r, int g, int b) {return SDL_MapRGB(screen->format, r, g, b);}
Uint32 mapMonoColor(int x) {return SDL_MapRGB(screen->format, x, x, x);}
int eraseScreen() {return SDL_FillRect(screen, NULL, mapMonoColor(0));}

