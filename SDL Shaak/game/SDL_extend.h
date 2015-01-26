/*
    Fichier créé le 18/08/2013 à 20h35

    -----------------------------------------------------------------

    Fichier créé par tsunami33 pour le projet Shaak

    -----------------------------------------------------------------

    Fichier regrouppant toutes les fonctions d'amélioration de la SDL
*/

#ifndef H_SDL_EXTEND
    #define H_SDL_EXTEND

    #include <SDL_ttf.h>

    typedef struct Fonts Fonts;
    struct Fonts
    {
        TTF_Font *minecraftia35;
    };

    typedef struct Config Config;
    struct Config
    {
        int bpp; // Bits per pixel
        int h; // Screen height
        int w; // Screen width
        int fs; // Boolean for fullscreen (SDL_FULLSCREEN or 0)
        int memAlloc; // Boolean for the SDL_Surfaces location in memory (SDL_HWSURFACE or SDL_SWSURFACE)
        int mbh; // Messagebox height
        int th; // Tile height in pixels
        int tw; // Tile width in pixels
        int nt; // Number of tiles
        int nn; // Number of NPC
        int nd; // Number of decorations
        int cpl; // Cases per line
        int cpc; // Cases per column
        int tnc; // Total number of cases
        int sf; // Save frequency in seconds
        int sv; // Sound volume (between 0 and 100)
    };

    #define monoColor(x) {x, x, x}
    #define createSurface(w, h) SDL_CreateRGBSurface(cfg.memAlloc, w, h, cfg.bpp, 0, 0, 0, 0)
    #define fillRect(x, y) SDL_FillRect(x, NULL, y)
    #define blitSurface(x, y, z) SDL_BlitSurface(x, NULL, y, z)

    void loadFonts();
    void progStop();
    void checkQuit(SDL_Event e);
    int blitOnScreen(SDL_Surface* src, SDL_Rect p);
    int flip();
    Uint32 mapRGB(int r, int g, int b);
    Uint32 mapMonoColor(int x);
    int eraseScreen();

#endif
