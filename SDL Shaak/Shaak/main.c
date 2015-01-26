#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <fmodex/fmod.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "jouer.h"
#include "autre.h"

wchar_t arme[31] = L"", armure[31] = L"", M_type[8] = L"";
int vie = 0, pv = 0, defense = 0, attaque = 0, pvMax = 0, xp = 0, niv = 0;
unsigned int potionPetite = 0, potionMoyenne = 0, potionGrande = 0, potionMax = 0, potionTeleport = 0, argent = 0;
int M_attaque = 0, M_defense = 0, M_argent = 0, M_vie = 0, M_xp = 0;
int isMusic = 0;
FMOD_SYSTEM *systeme;
FMOD_CHANNELGROUP *channel;
FMOD_SOUND *musique = NULL;
FILE *save_game = NULL, *record = NULL, *banque = NULL;
SDL_Surface *ecran = NULL;
TTF_Font *police = NULL;


void intro()
{
    SDL_Surface *surface1, *surface2;
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    int i = 0;
    int tempsActuel = 0, tempsPrecedent = 0;
    SDL_Event event;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    surface1 = SDL_LoadBMP("images/intro/shaak.bmp");
    surface2 = SDL_LoadBMP("images/intro/shaak_rpg.bmp");
    for (i = 0 ; i < 25 ; i++)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                SDL_Stop(120);
            break;
            default:
            break;
        }
        tempsActuel = SDL_GetTicks();
        if (tempsActuel <= tempsPrecedent + 50)
            i--;
        else
        {
            SDL_SetAlpha(surface1, SDL_SRCALPHA, i*10);
            SDL_BlitSurface(surface1, NULL, ecran, &position);
            SDL_Flip(ecran);
            tempsPrecedent = tempsActuel;
        }
    }
    SDL_FreeSurface(surface1);
    for (i = 0 ; i < 25 ; i++)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                SDL_Stop(121);
            break;
            default:
            break;
        }
        tempsActuel = SDL_GetTicks();
        if (tempsActuel <= tempsPrecedent + 50)
            i--;
        else
        {
            SDL_SetAlpha(surface2, SDL_SRCALPHA, i*10);
            SDL_BlitSurface(surface2, NULL, ecran, &position);
            SDL_Flip(ecran);
            tempsPrecedent = tempsActuel;
        }
    }
    SDL_FreeSurface(surface2);
}

int main(int argc, char* argv[])
{
    //Création du fichier stdout.txt
    printf("Ce fichier est un fichier de débuggage créé par le jeu.\n");
    printf("Ici s'affichent les raisons des différents bugs du jeu.\n");
    printf("Si vous avez un bug dans le jeu communiquez la suite de ce fichier au créateur du jeu.\n");
    printf("Si vous n'avez pas eu de problème alors ignorez ce fichier.\n");
    printf("Si la suite de ce fichier est vide, dites le au créateur du jeu et donnez lui des précisions sur le moment auquel le bug est survenu.\n");
    printf("ATTENTION : Il est possible que la suite du fichier soit vide si vous avez fermé la console (fenêtre noire) en fond.\n");
    printf("Dans ce cas il est normal que le jeu se ferme. Il ne peut pas fonctionner sans.\n\n\n");

    //Déclaration des variables SDL
    TTF_Init();
    char *nomMusique = "intro.mp3";
    char *nomMusiqueComplet = calloc(strlen(MUSIC_FOLDER_NAME) + strlen(nomMusique) + 1, sizeof(char));
    sprintf(nomMusiqueComplet, MUSIC_FOLDER_NAME);
    strcat(nomMusiqueComplet, nomMusique);
    SDL_Surface *imageDeFond = {NULL};
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;
    SDL_Event event;
    police = TTF_OpenFont("fonts/micross.ttf", TAILLE_TEXTE);

    //Création de la fenêtre, de son titre et de ses surfaces
    initialisation_SDL(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("images/icone.png"), NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Shaak", NULL);

    intro();

    imageDeFond = SDL_LoadBMP("images/menus/sound_yes.bmp");
    isMusic = 1;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    srand(time(NULL));
    SDL_EnableKeyRepeat(100, 100);

    while (1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                 SDL_FreeSurface(imageDeFond);
                SDL_Stop(122);
            break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if (isMusic)
                        {
                            SDL_FreeSurface(imageDeFond);
                            imageDeFond = SDL_LoadBMP("images/menus/sound_no.bmp");
                            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                            isMusic = 0;
                        }
                    break;
                    case SDLK_LEFT:
                        if (!isMusic)
                        {
                            SDL_FreeSurface(imageDeFond);
                            imageDeFond = SDL_LoadBMP("images/menus/sound_yes.bmp");
                            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                            isMusic = 1;
                        }
                    break;
                    case SDLK_RETURN:
                        //Fonctions d'initialisations musicales
                        if (isMusic)
                        {
                            FMOD_System_Create (&systeme);
                            FMOD_System_Init (systeme, 5, FMOD_INIT_NORMAL, NULL);
                            FMOD_System_CreateSound (systeme, nomMusiqueComplet, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
                            FMOD_System_PlaySound (systeme, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            FMOD_System_GetMasterChannelGroup (systeme, &channel);
                            FMOD_Sound_SetLoopCount (musique, -1);
                        }
                        SDL_FreeSurface(imageDeFond);
                        menu();
                    break;
                    default:
                    break;
                }
            break;
            default:
            break;
        }
        SDL_Flip(ecran);
    }

    return EXIT_SUCCESS;
}
