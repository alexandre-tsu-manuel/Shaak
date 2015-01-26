/*
Fichier créé le 21/01/2012 à 19h05

-----------------------------------------------------------------

Fichier créé par tsunami33 pour le projet shaak

-----------------------------------------------------------------

Fichier header regroupant les fonctions permettant d'améliorer la fonction scanf.
Il regroupe aussi les fonstions de gestion du son.
*/

#ifndef DEF_AUTRE
    #define DEF_AUTRE

    #include "constantes.h"
    #ifdef WINDOWS
        #include <windows.h>
    #endif

    void cls(); //Efface la console
    void pause(); //Fonction portable qui attend une frappe de l'utilisateur
    int color(WORD theColor); //Permet de changer la couleur d'écriture et de fond
    int wantSound(); //Demande à l'utilisateur s'il veut du son ou non
    void musicPlay(char* nomMusique, int nbTotalMusics); //Joue une musique si le son est activé
    int powInt(const int nb1, int nb2); //Calcule nb1 puissance nb2 et renvoie le résultat
    int scans(char *chaine, int longueur); //Demande une chaîne de caractère
    void scand(int *var); //Demande un nombre entier
    void scanc(char* caractere); //Demande un caractère
    void wscanc(wchar_t* caractere); //Demande un caractère (accents possibles)
    void ecrire(const wchar_t *text, ...); //Permet d'écrire avec des couleurs

    typedef struct Music Music;
    struct Music
    {
        short int isMusic;
        FMOD_SYSTEM **systeme;
        FMOD_CHANNELGROUP **channel;
        FMOD_SOUND **musique;
    };

    enum Color
    {
        Black        = 0,
        Grey         = FOREGROUND_INTENSITY,
        LightGrey    = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
        White        = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        Blue         = FOREGROUND_BLUE,
        Green        = FOREGROUND_GREEN,
        Cyan         = FOREGROUND_GREEN | FOREGROUND_BLUE,
        Red          = FOREGROUND_RED,
        Purple       = FOREGROUND_RED   | FOREGROUND_BLUE,
        LightBlue    = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
        LightGreen   = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        LightCyan    = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
        LightRed     = FOREGROUND_RED   | FOREGROUND_INTENSITY,
        LightPurple  = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
        Orange       = FOREGROUND_RED   | FOREGROUND_GREEN,
        Yellow       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        BBlack       = 0,
        BGrey        = BACKGROUND_INTENSITY,
        BLightGrey   = BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_BLUE,
        BWhite       = BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
        BBlue        = BACKGROUND_BLUE,
        BGreen       = BACKGROUND_GREEN,
        BCyan        = BACKGROUND_GREEN | BACKGROUND_BLUE,
        BRed         = BACKGROUND_RED,
        BPurple      = BACKGROUND_RED   | BACKGROUND_BLUE,
        BLightBlue   = BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
        BLightGreen  = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
        BLightCyan   = BACKGROUND_GREEN | BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
        BLightRed    = BACKGROUND_RED   | BACKGROUND_INTENSITY,
        BLightPurple = BACKGROUND_RED   | BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
        BOrange      = BACKGROUND_RED   | BACKGROUND_GREEN,
        BYellow      = BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
    };

#endif
