#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SDL_extend.h"
#include "Button.h"

extern Config cfg;
extern Fonts fonts;

void B_Load(Button* this, int style, int x, int y, char* text)
{
    SDL_Surface *textSurf = NULL;
    SDL_Rect pos;

    if (style == MENU)
    {
        SDL_Color bg = monoColor(207), fg = monoColor(0), fghover = monoColor(124);
        pos.x = 10;
        pos.y = 0;
        textSurf = TTF_RenderText_Blended(fonts.minecraftia35, text, fg);
        this->pos.h = textSurf->h;
        this->pos.w = textSurf->w;
        this->normal = createSurface(textSurf->w + pos.x * 2, textSurf->h + pos.y * 2);
        fillRect(this->normal, mapRGB(bg.r, bg.g, bg.b));
        blitSurface(textSurf, this->normal, &pos);
        SDL_FreeSurface(textSurf);

        textSurf = TTF_RenderText_Shaded(fonts.minecraftia35, text, fghover, bg);
        this->hover = createSurface(textSurf->w + pos.x * 2, textSurf->h + pos.y * 2);
        fillRect(this->hover, mapRGB(bg.r, bg.g, bg.b));
        blitSurface(textSurf, this->hover, &pos);
        SDL_FreeSurface(textSurf);
    }

    this->pos.x = x - this->pos.w / 2;
    this->pos.y = y - this->pos.h / 2;
}

void B_free(Button* this)
{
    SDL_FreeSurface(this->normal);
    SDL_FreeSurface(this->hover);
}

char B_isHover(Button this)
{
    int x, y;

    SDL_GetMouseState(&x, &y);
    return (x >= this.pos.x && y >= this.pos.y && x <= this.pos.x + this.pos.w && y <= this.pos.y + this.pos.h);
}

void B_display(Button this)
{
    if (B_isHover(this))
        blitOnScreen(this.hover, this.pos);
    else
        blitOnScreen(this.normal, this.pos);
}
