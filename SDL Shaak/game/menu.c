#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_extend.h"
#include "button.h"
#include "credits.h"
#include "play.h"
#include "editor.h"
#include "menu.h"

extern SDL_Surface *screen;
extern Config cfg;

void menu()
{
    int i;
    SDL_Event event;
    Button buttons[5];

    B_Load(&buttons[0], MENU, cfg.w/2, cfg.h/2 - 200, "Jouer");
    B_Load(&buttons[1], MENU, cfg.w/2, cfg.h/2 - 100, "Editeur");
    B_Load(&buttons[2], MENU, cfg.w/2, cfg.h/2, "Options");
    B_Load(&buttons[3], MENU, cfg.w/2, cfg.h/2 + 100, "Credits");
    B_Load(&buttons[4], MENU, cfg.w/2, cfg.h/2 + 200, "Quitter");
    eraseScreen();

    while(1)
    {
        for (i = 0 ; i < 5 ; i++)
            B_display(buttons[i]);
        flip();
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (B_isHover(buttons[0]))
                playMenu();
            else if (B_isHover(buttons[1]))
                editorMenu();
            else if (B_isHover(buttons[2]))
                optionsMenu();
            else if (B_isHover(buttons[3]))
                credits();
            else if (B_isHover(buttons[4]))
                return;
        }
        checkQuit(event);
        SDL_WaitEvent(&event);
    }
}

void playMenu()
{
    int i;
    SDL_Event event;
    Button buttons[3];

    B_Load(&buttons[0], MENU, cfg.w/2, cfg.h/2 - 100, "Nouvelle Partie");
    B_Load(&buttons[1], MENU, cfg.w/2, cfg.h/2, "Charger une sauvegarde");
    B_Load(&buttons[2], MENU, cfg.w/2, cfg.h/2 + 100, "Précédent");
    eraseScreen();

    while(1)
    {
        for (i = 0 ; i < 3 ; i++)
            B_display(buttons[i]);
        flip();
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (B_isHover(buttons[0]))
                while (play());
            else if (B_isHover(buttons[1]))
                playLoadMenu();
            else if (B_isHover(buttons[2]))
            {
                for (i = 0 ; i < 3 ; i++)
                    B_free(&buttons[i]);
                eraseScreen();
                return;
            }
        }
        checkQuit(event);
        SDL_WaitEvent(&event);
    }
}

void editorMenu()
{
    int i;
    SDL_Event event;
    Button buttons[3];

    B_Load(&buttons[0], MENU, cfg.w/2, cfg.h/2 - 100, "Nouvelle Carte");
    B_Load(&buttons[1], MENU, cfg.w/2, cfg.h/2, "Charger une carte");
    B_Load(&buttons[2], MENU, cfg.w/2, cfg.h/2 + 100, "Précédent");
    eraseScreen();

    while(1)
    {
        for (i = 0 ; i < 3 ; i++)
            B_display(buttons[i]);
        flip();
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (B_isHover(buttons[0]))
                editor(0);
            else if (B_isHover(buttons[1]))
                editorLoadMenu();
            else if (B_isHover(buttons[2]))
            {
                for (i = 0 ; i < 3 ; i++)
                    B_free(&buttons[i]);
                eraseScreen();
                return;
            }
        }
        checkQuit(event);
        SDL_WaitEvent(&event);
    }
}

void optionsMenu()
{
    return;
}

void playLoadMenu()
{
    return;
}

void editorLoadMenu()
{
    return;
}
