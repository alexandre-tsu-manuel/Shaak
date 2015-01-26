#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>
#include <ctype.h>
#include <fmodex/fmod.h>
#include "autre.h"
#include "constantes.h"
#ifdef WINDOWS
    #include <windows.h>
#endif

extern int isMusic;
extern FMOD_SYSTEM *systeme;
extern FMOD_CHANNELGROUP *channel;
extern FMOD_SOUND *musique;

void cls()
{
    #ifdef WINDOWS
        system("cls");
    #else
        system("clear");
    #endif
}

int color(WORD theColor)
{
    #ifdef WINDOWS
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleTextAttribute(hConsole,theColor) ? 1 : 0;
    #else
        return 2;
    #endif
}

int wantSound()
{
    char ans;

    while(ans != 'o' && ans != 'n')
    {
        ecrire(L"Voulez vous du son ? (%oro%ow/%orn%ow)\n");
        scanc(&ans);
        cls();
        if (ans != 'o' && ans != 'n')
            ecrire(L"Veuillez entrer %oro%ow ou %orn%ow svp.\n");
    }
    if(ans == 'o')
        return 1;
    return 0;
}

void musicPlay(char* nomMusique, int nbTotalMusics)
{
    int nbMusic = 0;
    char cat[200] = {0}, cat2[6] = {0};
    char number;

    if(isMusic)
    {
        FMOD_ChannelGroup_Stop(channel);
        if (strcmp(nomMusique, "stop_the_music"))
        {
            nbMusic = rand() % nbTotalMusics + 1;
            sprintf(cat, nomMusique);
            strcat(cat, "-");
            number = (char)(nbMusic + 48);
            cat2[0] = number;
            strcat(cat2, ".mp3");
            strcat(cat, cat2);
            FMOD_System_CreateSound(systeme, cat, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
            FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, musique, 0, NULL);
        }
    }
}

int powInt(const int nb1, int nb2)
{
    int nbReturn = 0;

    if (nb2 <= 0)
        return 1;
    nbReturn = nb1;
    while (nb2 != 1)
    {
        nbReturn *= nb1;
        nb2--;
    }
    return nbReturn;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int scans(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
            *positionEntree = '\0';
        else
            viderBuffer();
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

void scand(int *var)
{
    scanf("%d", var);
    getchar();
}

void scanc(char* caractere)
{
    *caractere = getchar();
    *caractere = tolower(*caractere);
    while (getchar() != '\n');
    switch(*caractere)
    {
        case '1':
            *caractere = 'a';
        break;
        case '2':
            *caractere = 'b';
        break;
        case '3':
            *caractere = 'c';
        break;
        case '4':
            *caractere = 'd';
        break;
        case '5':
            *caractere = 'e';
        break;
        case '6':
            *caractere = 'f';
        break;
        case '9':
            *caractere = 's';
        break;
        case '0':
            *caractere = 'p';
        break;
    }
}

void wscanc(wchar_t* caractere)
{
    *caractere = getchar();
    *caractere = tolower(*caractere);
    while (getchar() != '\n');
}

void ecrire(const wchar_t *text, ...)
{
    int i = 0;
    va_list pa;
    va_start(pa, text);

    while (text[i] != 0) //Tant que je n'arrive pas au bout de la chaîne principale
    {
        while (text[i] != '%' && text[i] != 0)
        {
            putchar(text[i]);
            i++;
        } //Si fin de chaîne ou variable trouvée je sort de la boucle.
        if (text[i] != 0)
            i++; //Si c'est un % alors j'analyse le caractère d'après.
        switch(text[i])
        {
            case '%'://Si je trouve un double % j'en ajoute un à la chaîne finale.
                putchar('%');
                i++;
            break;
            case 'o':
                i++;
                switch(text[i])
                {
                    case 'c':
                        color(LightCyan);
                        i++;
                    break;
                    case 'g':
                        color(LightGreen);
                        i++;
                    break;
                    case 'r':
                        color(LightRed);
                        i++;
                    break;
                    case 'y':
                        color(Yellow);
                        i++;
                    break;
                    case 'w':
                        color(White);
                        i++;
                    break;
                    default:
                        color(White);
                    break;
                }
            break;
            case 'd'://Si je trouve un d alors c'est un entier.
                color(LightGreen);
                printf("%d", va_arg(pa, int)); //je l'ajoute à la chaîne finale,
                color(White);
                i++;
            break;
            case 'f':
                color(LightGreen);
                printf("%f", va_arg(pa, double));
                color(White);
                i++;
            break;
            case 'c': //Si c'est un caractère je l'ajoute bêtement à la chaîne finale.
                putchar(va_arg(pa, int));
                i++;
            break;
            case 'l': //Si c'est un caractère je l'ajoute bêtement à la chaîne finale.
                i++;
                switch(text[i])
                {
                    case 'c':
                        i++;
                        putchar(va_arg(pa, int));
                    break;
                    case 's':
                        color(LightPurple);
                        wprintf(va_arg(pa, wchar_t*));
                        color(White);
                        i++;
                    break;
                    default:
                    break;
                }
            break;
            case 's':
                color(LightPurple);
                printf(va_arg(pa, char*));
                color(White);
                i++;
            break;
            case 0: //Si c'est la fin de chaîne alors je sort du switch sans rien faire
            break;
            default://Et si je trouve un % sans rien de spécial derrière alors je l'affiche tout simplement.
                putchar('%');
            break;
        }
    }

    va_end(pa);
}
