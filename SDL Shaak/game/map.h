/*
    Fichier créé le 26/08/2013 à 14h37

    -----------------------------------------------------------------

    Fichier créé par tsunami33 pour le projet Shaak

    -----------------------------------------------------------------

    Fichier lié à la structure Map et à ses méthodes
*/

#ifndef H_MAP
    #define H_MAP

    typedef struct Case Case;
    struct Case
    {
        int base;
        int deco;
        int event;
        char blocking;
    };

    typedef struct Map Map;
    struct Map
    {
        Case *cases;
        SDL_Surface *map;
    };

    void M_Load(int ID);
    void M_free();
    void M_Refresh();
    void M_display();

#endif
