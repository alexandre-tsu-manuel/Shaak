#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <fmodex/fmod.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "constantes.h"
#include "jouer.h"
#include "autre.h"

extern wchar_t arme[31], armure[31], M_type[8];
extern int vie, pv, defense, attaque, pvMax, xp, niv;
extern unsigned int potionPetite, potionMoyenne, potionGrande, potionMax, potionTeleport, argent;
extern int M_attaque, M_defense, M_argent, M_vie, M_xp;
extern FILE *save_game, *record, *banque;
extern SDL_Surface *ecran;
extern TTF_Font *police;

void menu()
{
    int positionMenu = 0;

    SDL_Surface *fleche = {NULL};
    SDL_Rect positionFleche;
    positionFleche.x = 0;
    positionFleche.y = 220;
    SDL_Event eventMenu;
    SDL_Surface *imageDeFond = {NULL};
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;

    fleche = IMG_Load("images/menus/fleche.jpg");
    imageDeFond = SDL_LoadBMP("images/menus/menu.bmp");
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
    SDL_Flip(ecran);

    while (1)
    {
        SDL_WaitEvent(&eventMenu);
        switch(eventMenu.type)
        {
            case SDL_QUIT:
                SDL_Stop(123);
            break;
            case SDL_KEYUP:
                switch (eventMenu.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (positionMenu)
                        {
                            if (positionMenu == 1)
                                positionFleche.y = 220;
                            else
                                positionFleche.y = 330;
                            positionMenu--;
                        }
                    break;
                    case SDLK_DOWN:
                        if (positionMenu == 0 || positionMenu == 1)
                        {
                            if (positionMenu == 0)
                                positionFleche.y = 330;
                            else
                                positionFleche.y = 430;
                            positionMenu++;
                        }
                        break;
                    case SDLK_RETURN:
                        switch (positionMenu)
                        {
                            case 0:
                                replay();
                            break;
                            case 1:
                                SDL_Stop(124);
                            break;
                            case 2:
                                SDL_Stop(125);
                            break;
                            default:
                            break;
                        }
                    break;
                    default:
                    break;
                }
            break;
            default:
            break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
        SDL_Flip(ecran);
    }
}

void replay()
{
    SDL_Event commencerJeu;
    SDL_Surface *imageDeFond = {NULL};
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;

    imageDeFond = SDL_LoadBMP("images/menus/menu_debutDePartie.bmp");
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);

    srand(time(NULL));

    while (1)
    {
        SDL_WaitEvent(&commencerJeu);
        switch(commencerJeu.type)
        {
            case SDL_QUIT:
                SDL_Stop(126);
            break;
            case SDL_KEYDOWN:
                switch (commencerJeu.key.keysym.sym)
                {
                    case SDLK_n:
                        swprintf(arme, L"B\x83ton de bois");
                        swprintf(armure, L"Aucune armure");
                        swprintf(M_type, L"monstre");
                        pvMax = PV_MAX;
                        attaque = ATTAQUE;
                        argent = ARGENT;
                        niv = 1;
                        vie = VIES_DEBUT;
                        pv = PV_MAX;
                        defense = DEFENSE;
                        potionPetite = P_POTION;
                        potionMoyenne = M_POTION;
                        potionGrande = G_POTION;
                        potionMax = MAX_POTION;
                        xp = 0;
                        changerMusique("magasin.mp3");
                        SDL_Flip(ecran);
                        while (1)
                            jouer(1);
                    break;
                    default:
                    break;
                }
            break;
        }
        /*else if (commencer_jeu == 130)
        {
            printf(L"please wait...\n");
            changer_de_musique("code.mp3");
            system("cls");

            xp = 0;
            case_actuelle = 1;
            swprintf(arme, L"B\x83ton de bois");
            swprintf(armure, L"Aucune armure");
            swprintf(M_type, L"monstre");

            printf(L"Combien d'or ?\n");
            scand(&argent);
            printf(L"Combien de PVs max ?\n");
            scand(&pv_max);
            pv = pv_max;
            printf(L"Combien de fioles de r%lcsurrection\n", 130);
            scand(&vie);
            vie += VIES_DEBUT;
            printf(L"Combien d'attaque ?\n");
            scand(&attaque);
            printf(L"Combien de d%lcfense ?\n", 130);
            scand(&defense);
            printf(L"Combien de petites potions ? ?\n");
            scand(&petite_potion);
            printf(L"Combien de potions moyennes ?\n");
            scand(&moyenne_potion);
            printf(L"Combien de grandes potions ?\n");
            scand(&grande_potion);
            printf(L"Combien de potions max ?\n");
            scand(&potion_max);
            system("cls");
            printf(L"please wait\n");
            changer_de_musique("musiques/magasin.mp3");
            system("cls");
            printf(L"d%lcbut de la partie\nCodes triches activ\x82s\n\n", 130);
            while (1)
            {
                action_case_actuelle();
            }
        }*/
    }

    exit(EXIT_FAILURE);
}

void chargerCarte(int carte, SDL_Surface *images[], SDL_Surface *imagesPnj[NB_CARTES][NB_MAX_PNJ][4], int movePlayer)
{
    FILE* fichierCarte = NULL;
    int i = 0, j = 0, k = 0, l = 0, m = 0, randResult = 0;
    int nbPnj = 0;
    char ligneFichier[1200];
    Case cases[NB_CASES];
    Pnj pnj[NB_MAX_PNJ];
    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    fichierCarte = fopen("files/cartes.shf", "r");
    if (fichierCarte == NULL)
        SDL_Stop(2123);
    rewind(fichierCarte);
    for (i = 1 ; i < carte ; i++)
        fgets(ligneFichier, 1200, fichierCarte);
    fscanf(fichierCarte, "%d # ", &nbPnj);
    for (i = 0 ; i < NB_CASES ; i++)
        fscanf(fichierCarte, "%d:%d; ", &cases[i].type, &cases[i].sType);
    for (i = 0 ; i < nbPnj ; i++)
        fscanf(fichierCarte, "%d:%d!%d:%d:%d:%d!%d:%d; ", &pnj[i].carte, &pnj[i].sType, &pnj[i].direction[0], &pnj[i].direction[1], &pnj[i].direction[2], &pnj[i].direction[3], &pnj[i].x, &pnj[i].y);
    fclose(fichierCarte);
    l = 0;
    for (m = 0 ; m < NB_CASES ; m++)
    {
        for (i = 1 ; i <= NB_TYPES_IMAGES ; i++)
        {
            switch (i)
            {
                case 1:
                    k = NB_IMAGES_TYPE_1;
                break;
                case 2:
                    k = NB_IMAGES_TYPE_2;
                break;
                case 3:
                    k = NB_IMAGES_TYPE_3;
                break;
                case 4:
                    k = NB_IMAGES_TYPE_4;
                break;
            }
            for (j = 1 ; j <= k ; j++)
            {
                if (cases[m].type == i && cases[m].sType == j)
                {
                    SDL_BlitSurface(images[l], NULL, ecran, &position);
                    position.x += TAILLE_CASE;
                }
                if (position.x >= (NB_CASES_W*TAILLE_CASE))
                {
                    position.y += TAILLE_CASE;
                    position.x = 0;
                }
                l++;
            }
        }
        l = 0;
    }
    j = 0;
    k = 0;
    SDL_BlitSurface(images[NB_IMAGES], NULL, ecran, &position);
    for (i = 0 ; i < nbPnj ; i++)
    {
        k = 1;
        randResult = rand() % RANDMAX;
        position.x = pnj[i].x * TAILLE_CASE;
        position.y = pnj[i].y * TAILLE_CASE;
        while(k)
        {
            if (randResult < pnj[i].direction[j])
            {
                SDL_BlitSurface(imagesPnj[carte][i][j], NULL, ecran, &position);
                k = 0;
            }
            else
            {
                randResult -= pnj[i].direction[j];
                j++;
            }
        }
    }
}

int deplacerJoueur(SDL_Rect *pos, int direction, int carte, SDL_Surface *images[], SDL_Surface *imagesPnj[NB_CARTES][NB_MAX_PNJ][4])
{
    FILE* fichierCarte;
    Case cases[NB_CASES_H][NB_CASES_W];
    char ligneFichier[1200] = {0};
    int i = 0, j = 0;
    int nbPnj = 0;
    SDL_Surface *perso;

    fichierCarte = fopen("files/cartes.shf", "r");
    if (fichierCarte == NULL)
        SDL_Stop(3123);
    rewind(fichierCarte);
    for (i = 1 ; i < carte ; i++)
        fgets(ligneFichier, 1200, fichierCarte);
    fscanf(fichierCarte, "%d # ", &nbPnj);
    for (i = 0 ; i < NB_CASES_H ; i++)
        for (j = 0 ; j < NB_CASES_W ; j++)
            fscanf(fichierCarte, "%d:%d; ", &cases[i][j].type, &cases[i][j].sType);
    fclose(fichierCarte);
    switch (direction)
    {
        case HAUT:
            perso = IMG_Load("images/haut.png");
            if (pos->y == 0)
                break;
            if (cases[pos->y / TAILLE_CASE - 1][pos->x / TAILLE_CASE].type == BLOCK)
                break;
            if (cases[pos->y / TAILLE_CASE - 1][pos->x / TAILLE_CASE].type == EVENT_BUTTON)
                break;
            if (cases[pos->y / TAILLE_CASE - 1][pos->x / TAILLE_CASE].type == EVENT)
                break;
            pos->y -= TAILLE_CASE;
        break;
        case BAS:
            perso = IMG_Load("images/bas.png");
            if (pos->y + TAILLE_CASE == HAUTEUR_FENETRE - HAUTEUR_IMAGE_TEXTE)
                break;
            if (cases[pos->y / TAILLE_CASE + 1][pos->x / TAILLE_CASE].type == BLOCK)
                break;
            if (cases[pos->y / TAILLE_CASE + 1][pos->x / TAILLE_CASE].type == EVENT_BUTTON)
                break;
            if (cases[pos->y / TAILLE_CASE + 1][pos->x / TAILLE_CASE].type == EVENT)
                break;
            pos->y += TAILLE_CASE;
        break;
        case GAUCHE:
            perso = IMG_Load("images/gauche.png");
            if (pos->x == 0)
                break;
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE - 1].type == BLOCK)
                break;
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE - 1].type == EVENT_BUTTON)
                break;
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE - 1].type == EVENT)
                break;
            pos->x -= TAILLE_CASE;
        break;
        case DROITE:
            perso = IMG_Load("images/droite.png");
            if (pos->x + TAILLE_CASE == LARGEUR_FENETRE)
                break;
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE + 1].type == BLOCK)
                break;
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE + 1].type == EVENT_BUTTON)
                break;
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE + 1].type == EVENT)
                break;
            pos->x += TAILLE_CASE;
        break;
    }
    chargerCarte(carte, images, imagesPnj, 1);
    SDL_BlitSurface(perso, NULL, ecran, pos);
    return direction;
}

void jouer(int carte)
{
    int i = 0, j = 0, k = 0, l = 0;
    int directionPerso = BAS;
    char nomFichier[30] = {0};
    SDL_Event event;
    SDL_Surface *joueur;
    SDL_Surface *images[NB_IMAGES];
    SDL_Surface *imagesPnj[NB_CARTES][NB_MAX_PNJ][4];
    SDL_Rect positionJoueur;
    positionJoueur.x = 6 * TAILLE_CASE - TAILLE_CASE;
    positionJoueur.y = 6 * TAILLE_CASE - TAILLE_CASE;

    for (i = 1 ; i <= NB_TYPES_IMAGES ; i++)
    {
        switch (i)
        {
            case 1:
                k = NB_IMAGES_TYPE_1;
            break;
            case 2:
                k = NB_IMAGES_TYPE_2;
            break;
            case 3:
                k = NB_IMAGES_TYPE_3;
            break;
            case 4:
                k = NB_IMAGES_TYPE_4;
            break;
        }
        for (j = 1 ; j <= k ; j++)
        {
            sprintf(nomFichier, "images/%d-%d.png", i, j);
            printf("%d : %s\n", l, nomFichier);
            images[l] = IMG_Load(nomFichier);
            l++;
        }
    }
    images[l] = IMG_Load("images/fondTexte.bmp");
    joueur = IMG_Load("images/bas.png");
    for (i = 1 ; i <= NB_CARTES ; i++)
    {
        switch (i)
        {
            case 1:
                k = NB_PNJ_CARTE_1;
            break;
            case 2:
                k = NB_PNJ_CARTE_2;
            break;
        }
        for (j = 1 ; j <= k ; j++)
        {
            for (l = 0 ; l < 4 ; l++)
                sprintf(nomFichier, "images/%d!%d!%d.png", i, j, l);
            imagesPnj[i][j][l] = IMG_Load(nomFichier);
        }
    }
    chargerCarte(1, images, imagesPnj, 0);
    SDL_BlitSurface(joueur, NULL, ecran, &positionJoueur);

    while (1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                SDL_Stop(130);
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        directionPerso = deplacerJoueur(&positionJoueur, HAUT, carte, images, imagesPnj);
                    break;
                    case SDLK_DOWN:
                        directionPerso = deplacerJoueur(&positionJoueur, BAS, carte, images, imagesPnj);
                    break;
                    case SDLK_LEFT:
                        directionPerso = deplacerJoueur(&positionJoueur, GAUCHE, carte, images, imagesPnj);
                    break;
                    case SDLK_RIGHT:
                        directionPerso = deplacerJoueur(&positionJoueur, DROITE, carte, images, imagesPnj);
                    break;
                    case SDLK_RETURN:
                        eventualAction(&positionJoueur, directionPerso, carte);
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
}

void eventualAction(SDL_Rect *pos, int direction, int carte)
{
    FILE *fichierCarte;
    Case cases[NB_CASES_H][NB_CASES_W];
    int i = 0, j = 0, nbPnj = 0;
    char ligneFichier[1200] = {0};

    fichierCarte = fopen("files/cartes.shf", "r");
    if (fichierCarte == NULL)
        exit(0);
    rewind(fichierCarte);
    for (i = 1 ; i < carte ; i++)
        fgets(ligneFichier, 1200, fichierCarte);
    fscanf(fichierCarte, "%d # ", &nbPnj);
    for (i = 0 ; i < NB_CASES_H ; i++)
        for (j = 0 ; j < NB_CASES_W ; j++)
            fscanf(fichierCarte, "%d:%d; ", &cases[i][j].type, &cases[i][j].sType);
    fclose(fichierCarte);
    switch (direction)
    {
        case HAUT:
            if (cases[pos->y / TAILLE_CASE - 1][pos->x / TAILLE_CASE].type == EVENT_BUTTON)
                sureAction(cases[pos->y / TAILLE_CASE - 1][pos->x / TAILLE_CASE].sType);
        break;
        case BAS:
            if (cases[pos->y / TAILLE_CASE + 1][pos->x / TAILLE_CASE].type == EVENT_BUTTON)
                sureAction(cases[pos->y / TAILLE_CASE + 1][pos->x / TAILLE_CASE].sType);
        break;
        case GAUCHE:
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE - 1].type == EVENT_BUTTON)
                sureAction(cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE - 1].sType);
        break;
        case DROITE:
            if (cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE + 1].type == EVENT_BUTTON)
                sureAction(cases[pos->y / TAILLE_CASE][pos->x / TAILLE_CASE + 1].sType);
                sureAction(3);
        break;
        default:
        break;
    }
}

void sureAction(int sType)
{
    switch (sType)
    {
        case 1:
            if (pv != pvMax)
            {
                ecrire("Vous vous êtes soigné à la fontaine. Vous avez maintenant récupéré tous vos points de vie. (%d PVs)", pvMax);
                pv = pvMax;
            }
            else
                ecrire("Vous avez déjà tous vos points de vie. Inutile de vous soigner à la fontaine.");
        break;
        case 2:
            sureAction(1);
        break;
        default:
            ERROR;
            printf("sous type : %d", sType);
        break;
    }
}
