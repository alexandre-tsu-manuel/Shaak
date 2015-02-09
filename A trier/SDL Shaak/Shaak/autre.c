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
#include <stdarg.h>
#include "constantes.h"
#include "jouer.h"
#include "autre.h"

extern int isMusic;
extern FMOD_SYSTEM *systeme;
extern FMOD_CHANNELGROUP *channel;
extern FMOD_SOUND *musique;
extern SDL_Surface *ecran;
extern TTF_Font *police;

int initialisation_SDL(const int typeInit)
{
    if (SDL_Init(typeInit) == -1) // Démarrage de la SDL. Si erreur alors...
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Ecriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    return 1;
}

void progStop(const int exitValue, const int line, const char *file)
{
    TTF_Quit();
    SDL_Quit();
    printf("\nexit value : %d\nline : %d\nfile : %s", exitValue, line, file);
    exit(exitValue);
}

void changerMusique(const char *nomMusique)
{
    float i = 0;
    char *nomMusiqueComplet = calloc(strlen(MUSIC_FOLDER_NAME) + strlen(nomMusique) + 1, sizeof(char));

    if (isMusic)
    {
        sprintf(nomMusiqueComplet, MUSIC_FOLDER_NAME);
        strcat(nomMusiqueComplet, nomMusique);
        for (i = 1 ; i >= 0 ; i -= 0.01)
        {
            FMOD_ChannelGroup_SetVolume(channel, i);
        }
        FMOD_ChannelGroup_Stop(channel);
        FMOD_ChannelGroup_SetVolume(channel, 1);
        if (strcmp(nomMusique, "stop the music"))
        {
            FMOD_System_CreateSound(systeme, nomMusiqueComplet, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
            FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, musique, 0, NULL);
        }
    }
}

void ecrireShaded (const char *texteAAfficher)
{
    int i = 0, continuer = 1, j = 0, firstWordOfLine = 1, zero = 0, continuer2 = 1;
    char motAPlacer[200] = {0};
    SDL_Color blanc = {255, 255, 255};
    SDL_Color noir = {0, 0, 0};
    SDL_Surface *texte = NULL, *imageFond = NULL;
    SDL_Event event;
    SDL_Rect position;
    SDL_Rect posFond;
    position.x = MARGE_TEXTE;
    position.y = HAUTEUR_FENETRE - HAUTEUR_IMAGE_TEXTE + MARGE_TEXTE;
    posFond.x = 0;
    posFond.y = HAUTEUR_FENETRE - HAUTEUR_IMAGE_TEXTE;

    imageFond = IMG_Load("images/fondTexte.bmp");
    SDL_BlitSurface(imageFond, NULL, ecran, &posFond);
    SDL_FreeSurface(imageFond);
    while (continuer)
    {
        for (j = 0 ; j < 200 ; j++)
            motAPlacer[j] = 0;
        for (j = 0 ; texteAAfficher[i] != '\n' && texteAAfficher[i] != '\0' && texteAAfficher[i] != ' ' ; j++)
        {
            motAPlacer[j] = texteAAfficher[i];
            i++;
        }
        if (texteAAfficher[i] == '\0')
        {
            continuer = 0;
            if (motAPlacer[0])
            {
                texte = TTF_RenderText_Shaded(police, motAPlacer, noir, blanc);
                underline(&position, texte->w, &firstWordOfLine);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                SDL_FreeSurface(texte);
                SDL_Flip(ecran);
                while(continuer2)
                {
                    SDL_WaitEvent(&event);
                    switch(event.type)
                    {
                        case SDL_QUIT:
                            SDL_Stop(1124);
                        break;
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym)
                            {
                                case SDLK_RETURN:
                                    continuer2 = 0;
                                break;
                                default:
                                break;
                            }
                        break;
                        default:
                        break;
                    }
                }
                imageFond = IMG_Load("images/fondTexte.bmp");
                SDL_BlitSurface(imageFond, NULL, ecran, &posFond);
                SDL_FreeSurface(imageFond);
            }
        }
        else if (texteAAfficher[i] == '\n')
        {
            if (motAPlacer[0])
            {
                texte = TTF_RenderText_Shaded(police, motAPlacer, noir, blanc);
                underline(&position, texte->w, &firstWordOfLine);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                SDL_FreeSurface(texte);
            }
            position.y = HAUTEUR_FENETRE;
            position.x = LARGEUR_FENETRE;
            underline(&position, 1, &zero);
        }
        else
        {
            texte = TTF_RenderText_Shaded(police, motAPlacer, noir, blanc);
            underline(&position, texte->w, &firstWordOfLine);
            SDL_BlitSurface(texte, NULL, ecran, &position);
            position.x += texte->w;
            SDL_FreeSurface(texte);
            texte = TTF_RenderText_Shaded(police, " ", noir, blanc);
            SDL_BlitSurface(texte, NULL, ecran, &position);
            position.x += texte->w;
            SDL_FreeSurface(texte);
            firstWordOfLine = 0;
        }
        i++;
    }
}

void underline(SDL_Rect *position, int largeurTexte, int *firstWordOfLine)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Surface *imageDeFond = NULL;
    SDL_Rect posFond;
    posFond.x = 0;
    posFond.y = HAUTEUR_FENETRE - HAUTEUR_IMAGE_TEXTE;

    SDL_Flip(ecran);
    imageDeFond = IMG_Load("images/fondTexte.bmp");
    if (!(*firstWordOfLine) && ((position->x + largeurTexte) > (LARGEUR_FENETRE - MARGE_TEXTE)))
    {
        position->y += TAILLE_TEXTE * 2;
        position->x = MARGE_TEXTE;
        *firstWordOfLine = 1;
        if (position->y > HAUTEUR_FENETRE - MARGE_TEXTE)
        {
            while(continuer)
            {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        SDL_FreeSurface(imageDeFond);
                        SDL_Stop(1123);
                    break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                                position->y = TAILLE_CASE * NB_CASES_H + MARGE_TEXTE;
                                SDL_BlitSurface(imageDeFond, NULL, ecran, &posFond);
                                continuer = 0;
                            break;
                            default:
                            break;
                        }
                    break;
                    default:
                    break;
                }
            }
        }
    }
}

void ecrire(const char *texteAAfficher, ...)
{
    char *texte = calloc((strlen(texteAAfficher) + 1) + 250, sizeof(char)); //texte contiendra le la chaîne assemblée finale. Elle peut contenir la chaîne principale + 250 octets de variables.
    char *argument; //Argument contiendra l'argument étudié si c'est un nombre ou une chaîne de caractères.
    int i = 0, j = 0;
    va_list pa;
    va_start(pa, texteAAfficher);

    while (texteAAfficher[i] != 0) //Tant que je n'arrive pas au bout de la chaîne principale
    {
        while (texteAAfficher[i] != '%' && texteAAfficher[i] != 0)
        {
            texte[j] = texteAAfficher[i];
            i++;
            j++;
        } //Si fin de chaîne ou variable trouvée je sort de la boucle.
        if (texteAAfficher[i] != 0)
            i++; //Si c'est un % alors j'analyse le caractère d'après.
        switch(texteAAfficher[i])
        {
            case '%'://Si je trouve un double % j'en ajoute un à la chaîne finale.
                texte[j] = '%';
                j++;
                i++;
            break;
            case 'd'://Si je trouve un d alors c'est un entier.
                argument = calloc(strlen(itos(*pa, NULL)) + 1, sizeof(char)); //Je réserve la place qu'il faut,
                itos(va_arg(pa, int), argument); //je transforme l'entier en chaîne de caratères,
                strcat(texte, argument); //je l'ajoute à la chaîne finale,
                j += strlen(argument);
                i++;
                free(argument); //et je libère argument.
            break;
            case 'f': //Si c'est un nombre à virgule alors je fait un peux la même chose que pour un entier mais j'appelle dtos à la place de itos
                argument = calloc(strlen(dtos(*pa, NULL)) + 1, sizeof(char));
                dtos(va_arg(pa, double), argument);
                strcat(texte, argument);
                j += strlen(argument);
                i++;
                free(argument);
            break;
            case 'c': //Si c'est un caractère je l'ajoute bêtement à la chaîne finale.
                texte[j] = va_arg(pa, int);
                j++;
                i++;
            break;
            case 's':
                argument = calloc(strlen(pa) + 1, sizeof(char)); //Je réserve la place nécessaire. (pa représente l'argument actuel)
                sprintf(argument, va_arg(pa, char*));
                strcat(texte, argument);
                j += strlen(argument);
                i++;
                free(argument);
            break;
            case 0: //Si c'est la fin de chaîne alors je sort du switch sans rien faire
            break;
            default://Et si je trouve un % sans rien de spécial derrière alors je l'affiche tout simplement.
                texte[j] = '%';
                j++;
            break;
        }
    }

    va_end(pa);
    ecrireShaded(texte); //Enfin j'envoie la chaîne finale à la fonction qui va me l'écrire.
    free(texte);//Je libère la mémoire et fin de fonction.
}

char* dtos(double nb, char* nbTxt)
{
    char *nbTexte = NULL; //nbTexte sera une chaîne de caractères de passerelle entre le double et nbTxt
    int nbEnt = (int)nb; //nbEnt sera aussi une sorte de passerelle. Ici elle contient tout les chiffres avant la virgule du double.
    int i = 0;

    if (nbTxt == NULL) //Si j'ai reçu NULL en argument ou si le pointeur reçu est nul
    {
        nbTxt = calloc(22, sizeof(char)); //Alors je lui alloue de la mémoire
        if (nbTxt == NULL) //Et je gère les erreurs éventuelles.
        {
            printf("Ne peut pas allouer de la memoire ligne %d fichier %s\n", __LINE__, __FILE__);
            SDL_Stop(3); //SDL_Stop est une fonction à moi qui stoppe le programme proprement et s'exite avec la valeur envoyée en paramètre
        }
    }

    sprintf(nbTxt, itos(nb, nbTexte)); //Je met tous les nombres avant la virgule dans la chaîne de caractère finale.
    if (nb != nbEnt) //S'il y a des chiffres après la virgule alors j'affiche la virgule.
        strcat(nbTxt, ",");
    nb -= nbEnt; //Je fait en sorte que nb soit sous la forme 0.xxx avec xxx représentant les nombres après la virgule.
    if (nb < 0) //Si le double était négatif il ne faut pas afficher un deuxième moins après la virgule.
        nb *= -1;
    nb *= 1000000000; //Je prend les dix chiffres après la virgule et je les fait passer avant.
    nb += 0.5; //Je rajoute 0.5 pour arrondir.
    nbEnt = (int)nb; //Je caste tout ça dans un int. Les chiffres après la virgule supplémentaires seront ignorés.
    while (nbEnt % 10 == 0 && i < 10) //Ici j'enlève les zéros en trop. S'il n'y avait que des zéros, de toute façon la boucle s'arrête au bout de dix tours.
    {
        nbEnt /= 10;
        i++;
    }
    strcat(nbTxt, itos(nbEnt, nbTexte)); //Et je rajoute tous ça après la virgule de la chaîne finale.

    return nbTxt; //Et enfin je retourne la chaîne finale. Ainsi je pourrai écrire monPointeurSurChar=dtos(monDouble, NULL);
}

char* itos(const int nb, char* nbTxt)
{
    char DEC[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Je prépare une chaîne de caractères avec tous les nombres sous forme de caractères dedans.

    int i = 0, j = 0, cpt = 0, reste = 0; //reste ira de 0 à 10
    char chaine[11]; //Un int contient dix chiffres maximum plus un octet de signe cela fait 11 char.
    int quotient = nb;

    quotient = abs(quotient); //Je ne travaille pour le moment qu'avec des nombres positifs.
    while (quotient != 0) //Ici j'inscrit les chiffres les uns après les autres mais en commençant par la droite.
    {
        reste = quotient % 10;
        quotient = (int) quotient / 10;
        chaine[cpt] = DEC[reste];
        cpt++;
    }
    if (nb < 0) //Si l'entier reçu est négatif alors je rajoute le moins. (à droite de ma chaîne)
    {
            chaine[cpt]='-';
            cpt++;
    }
    if (nbTxt == NULL) //>Si le pointeur reçu était nul ou même si le paramètre reçu était NULL,
    {
        nbTxt = calloc(cpt, sizeof(char)); //j'alloue la mémoire nécessaire,
        if (nbTxt == NULL) //et je gère les erreurs.
        {
            printf("Ne peut pas allouer de la memoire ligne %d fichier %s\n", __LINE__, __FILE__);
            SDL_Stop(3); //Même fonction que dans dtos.
        }
    }
    for(i = 0, j = cpt - 1 ; i < cpt ; i++, j--) //Enfin je met la chaîne de caractères dans le bon sens.
        nbTxt[j] = chaine[i];
    nbTxt[cpt] = 0; //Je rajoute le caractère de fin de chaîne,

    return nbTxt; //et je renvoie tout ça.
}
