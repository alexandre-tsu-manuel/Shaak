/*
    Fichier cr�� le 26/08/2013 � 15h58

    -----------------------------------------------------------------

    Fichier cr�� par tsunami33 pour le projet Shaak

    -----------------------------------------------------------------

    Fichier li� � la structure Tiles et � ses m�thodes
*/

#ifndef H_TILES
    #define H_TILES
    #include "map.h"

    void T_Load();
    void T_Free();
    SDL_Surface* T_Get(Case item, SDL_Surface* surf);

#endif
