/*
Fichier créé le 24/04/2011 à 02h31

-----------------------------------------------------------------

Fichier créé par tsunami33 pour le projet Shaak

-----------------------------------------------------------------

Fichier header regroupant les fonctions liées aux actions de jeu.
*/

#ifndef DEF_JOUER
    #define DEF_JOUER

    #define ERROR printf("erreur ligne %d fichier %s\n", __LINE__, __FILE__)
    #define SDL_Stop(exitValue) progStop(exitValue, __LINE__, __FILE__)
    #define RANDMAX (pnj[i].direction[0] + pnj[i].direction[1] + pnj[i].direction[2] + pnj[i].direction[3])

    typedef struct Pnj
    {
        int carte; //Carte affectée au personnage
        int sType; //Numéro du personnage
        int direction[4]; //Direction vers lesquelles peut pointer le personnage
        int x;
        int y;
    }Pnj;

    typedef struct Case
    {
        int type; //Type de case
        int sType; //Sous type de case
        int pnj; //S'il y a un pnj sur la case ou non
    }Case;

    void menu(); //Menu principal du jeu
        void replay(); //Permet de (re)commencer une partie
        void chargerCarte(int carte, SDL_Surface *images[NB_IMAGES], SDL_Surface *imagesPnj[NB_CARTES][NB_MAX_PNJ][4], int movePlayer); //Lis et blitte la carte sur l'écran
        void jouer(int carte); //Permet au joueur de jouer sur une des cartes du jeu
            int deplacerJoueur(SDL_Rect *pos, int direction, int *carte, SDL_Surface *images[], SDL_Surface *imagesPnj[NB_CARTES][NB_MAX_PNJ][4]); //Déplace le joueur et gère les collisions
            void actionEvent(const int sType, const int direction, SDL_Rect *pos, int *carte);
            void eventualAction(SDL_Rect *pos, int direction, int carte); //Donne l'ordre d'effectuer une action ou non en fonction de la position du joueur lorsqu'il le demande
                void actionEventButton(int sType); //Effectue une action demandée par eventualAction()

    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {ZERO, VIDE, BLOCK, EVENT_BUTTON, EVENT};

#endif
