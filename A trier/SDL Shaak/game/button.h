/*
    Fichier créé le 18/08/2013 à 19h51

    -----------------------------------------------------------------

    Fichier créé par tsunami33 pour le projet Shaak

    -----------------------------------------------------------------

    Fichier lié à la structure Button et à ses méthodes.
*/

#ifndef H_BUTTON
    #define H_BUTTON

    typedef struct Button Button;
    struct Button
    {
        SDL_Rect pos;
        SDL_Surface *normal, *hover;
    };

    enum {MENU};

    void B_Load(Button* this, int style, int x, int y, char* text);
    void B_free(Button* this);
    char B_isHover(Button this);
    void B_display(Button this);

#endif
