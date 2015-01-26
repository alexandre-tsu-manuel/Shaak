#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <fmodex/fmod.h>
#include "constantes.h"
#include "jouer.h"
#include "autre.h"

short int isMusic;
FMOD_SYSTEM *systeme;
FMOD_CHANNELGROUP *channel;
FMOD_SOUND *musique = NULL;
Hero hero;

int main()
{
    wchar_t commencer_jeu = 0;
    int win = 0;

    color(White);

    isMusic = wantSound();
    FMOD_System_Create(&systeme);
    FMOD_System_Init(systeme, 5, FMOD_INIT_NORMAL, NULL);
    FMOD_System_GetMasterChannelGroup(systeme, &channel);
    FMOD_Sound_SetLoopCount(musique, -1);
    FMOD_ChannelGroup_SetVolume(channel, isMusic);
    musicPlay("musiques/intro", NB_MUSIQUES_INTRO);

    hero.pv_max = PV_MAX;
    hero.attaque = ATTAQUE;
    hero.money = ARGENT;
    hero.niv = 1;

    srand(time(NULL));

    ecrire(L"Bienvenue dans %oyShaak%o, un jeu de r\x93le comme vous n'en avez jamais vu !\n");
    ecrire(L"Vous incarnez ici un aventurier solitaire. Le but est de vaincre le ");
    ecrire(L"boss de fin de jeu. Vous devrez pour cela acheter des potions, armes, armures, etc...\n\n");
    ecrire(L"Vous jouez sur un plateau de 6x1 cases. Vous commencez \x85 gauche.\nLa case la plus \x85 gauche");
    ecrire(L" est le magasin. Vous pouvez y acheter des objets.\nLa deuxi\x8Ame case contient des monstres de niveaux 1 \x85 2,");
    ecrire(L"\nla troisi\x8Ame case, des niveaux 2 \x85 3,\nla quatri\x8Ame case des niveaux 3 \x85 4,\nla cinqui\x8Ame case des");
    ecrire(L" niveaux 4 \x85 5,\nla sixi\x8Ame case le boss de fin de jeu.\n\n");
    ecrire(L"Vous commencez au niveau %d, avec %d points de vie, une \x82p%lce de puissance %d et %d d'or.\n", hero.niv, hero.pv_max, 130, hero.attaque, hero.money);
    ecrire(L"Bonne chance !\n\n");
    ecrire(L"Tapez un chiffre ou une lettre puis entr%lce pour commencer.\n", 130);
    wscanc(&commencer_jeu);
    cls();
    win = replay(commencer_jeu);
    while(commencer_jeu != 'q')
    {
        if (win == GAGNE)
            ecrire(L"\nVous avez gagn\x82 !\nBravo !\n\n");
        else
            ecrire(L"\nVous avez perdu.\nDommage... R%lcessayez.\n\n", 130);
        ecrire(L"Voulez vous rejouer ?\nSi vous voulez quitter le jeu tapez %orq%ow,\nsinon tapez un chiffre ou une lettre puis entr%lce pour commencer.\n", 130);
        wscanc(&commencer_jeu);
        cls();
        if (commencer_jeu != 'q')
            win = replay(commencer_jeu);
    }

    musicPlay("stop_the_music", 0);
    FMOD_Sound_Release(musique);
	FMOD_System_Close(systeme);
	FMOD_System_Release(systeme);

	ecrire(L"%oyCr%lcdits :%ow\n\n", 130);
	ecrire(L"  %ocProgrammeur :%ow\n");
	ecrire(L"    tsunami33 alias Alexandre MANUEL\n");
	ecrire(L"\n  %ocMusiques :%ow\n");
	ecrire(L"    %ormusique d'introduction :%ow Overcolored entering the rat race - Overcolored\n");
	ecrire(L"    %ormusique de cheat code :%ow Bust this bust that - Professor Klick\n");
	ecrire(L"    %ormusique du magasin :%ow Pizzicato - Ehma\n");
	ecrire(L"    %ormusique de combat :%ow Partie au loin - Chriss Onac / French Artists Projects\n");
	ecrire(L"    %ormusique de combat du boss :%ow My Arrival - Obsidian Shell\n");
	ecrire(L"    Toutes les musiques et les sons sont libres de droit.\n");
	ecrire(L"      Toutes les musiques proviennent de Jamendo.com (%oghttp://jamendo.com%ow)\n");
	ecrire(L"      Tous les sons proviennent de FindSounds.com (%oghttp://findsounds.com%ow)\n");
	ecrire(L"\n  %ocTechnologies utilis%lces :%ow\n", 130);
	ecrire(L"    %orLangage de programmation :%ow Langage C par Dennis Ritchie\n");
	ecrire(L"    %orGestion des accents :%ow Biblioth\x8Aque standard : wchar\n");
	ecrire(L"    %orAudio engine :%ow FMOD Sound System par Firelight Technologies\n");
	ecrire(L"\n  Remerciements sp%lcciaux au site du z\x82ro sans qui ce jeu n'aurait jamais vu le\n  jour. (%oghttp://siteduzero.com%ow)\n", 130);
	ecrire(L"\nAppuyez sur une touche pour quitter.\n");
	wscanc(&commencer_jeu);

    return EXIT_SUCCESS;
}
