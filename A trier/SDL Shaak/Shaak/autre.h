/*
Fichier créé le 24/04/2011 à 02h31

-----------------------------------------------------------------

Fichier créé par tsunami33 pour le projet Shaak

-----------------------------------------------------------------

Fichier header regroupant les fonctions permettant d'écrire du texte à l'écran.
Il regroupe aussi les fonstions de gestion du son.
Il regroupe également des fonctions permettant de teste un fichier, initialiser la SDL et stopper le programme.
*/

#ifndef DEF_AUTRE
    #define DEF_AUTRE

    int initialisation_SDL(const int typeInit); //Initialise la SDL.
    void progStop(const int exitValue, const int line, const char *file); //Stope la SDL et exit le programme avec la valeur demandée.
    void changerMusique(const char *nomMusique); //Met la musique indiquée à la place de la précédente si l'utilisateur a demandé du son.
    void ecrire(const char *texteAAfficher, ...); //met toutes les variables reçues dans une chaîne de caractères et l'écrit avec ecrireShaded().
        char* dtos(double nb, char* nbTxt); //Convertit un double en chaîne de caractères.
        char* itos(int nb, char* nbTxt); //Convertit un int en chaîne de caractères.
        void ecrireShaded(const char *texteAAfficher); //écrit une chaîne de caractères à l'écran.
            void underline(SDL_Rect *position, int largeurTexte, int *firstWordOfLine); //Permet à ecrireShaded() de faire un retour à la ligne.

#endif
