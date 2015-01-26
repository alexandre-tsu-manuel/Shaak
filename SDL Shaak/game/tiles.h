/*
    Fichier créé le 26/08/2013 à 15h58

    -----------------------------------------------------------------

    Fichier créé par tsunami33 pour le projet Shaak

    -----------------------------------------------------------------

    Fichier lié à la structure Tiles et à ses méthodes
*/

#ifndef H_TILES
    #define H_TILES
    #include "map.h"

    void T_Load();
    void T_Free();
    SDL_Surface* T_Get(Case item, SDL_Surface* surf);

#endif
