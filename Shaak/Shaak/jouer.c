#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <string.h>
#include <fmodex/fmod.h>
#include "constantes.h"
#include "jouer.h"
#include "autre.h"

extern Hero hero;
Monster monster;

int replay(wchar_t commencer_jeu)
{
    sprintf(monster.type, "monstre");
    swprintf(hero.arme, L"B\x83ton de bois");
    swprintf(hero.armure, L"Aucune armure");
    hero.xp = 0;
    hero.vie = VIES_DEBUT;
    hero.pv = hero.pv_max;
    hero.defense = DEFENSE;
    hero.petite_potion = P_POTION;
    hero.moyenne_potion = M_POTION;
    hero.grande_potion = G_POTION;
    hero.potion_max = MAX_POTION;
    hero.case_actuelle = 1;
    if (commencer_jeu == 130)
    {
        musicPlay("musiques/code", NB_MUSIQUES_CODE);
        cls();
        ecrire(L"Combien d'or ?\n");
        scand(&hero.money);
        ecrire(L"Combien de PVs max ?\n");
        scand(&hero.pv_max);
        hero.pv = hero.pv_max;
        ecrire(L"Combien de fioles de r%lcsurrection\n", 130);
        scand(&hero.vie);
        hero.vie += VIES_DEBUT;
        ecrire(L"Combien d'attaque ?\n");
        scand(&hero.attaque);
        ecrire(L"Combien de d%lcfense ?\n", 130);
        scand(&hero.defense);
        ecrire(L"Combien de petites potions ?\n");
        scand(&hero.petite_potion);
        ecrire(L"Combien de potions moyennes ?\n");
        scand(&hero.moyenne_potion);
        ecrire(L"Combien de grandes potions ?\n");
        scand(&hero.grande_potion);
        ecrire(L"Combien de potions max ?\n");
        scand(&hero.potion_max);
        cls();
        ecrire(L"d%lcbut de la partie\nCodes triches activ\x82s\n\n", 130);
    }
    else
        ecrire(L"d%lcbut de la partie\n\n", 130);
    return action_case_actuelle();
}

void load(char* nomFichier)
{

}

int action_case_actuelle()
{
    int exit = CONTINUE;

    while(exit == CONTINUE)
    {
        if (hero.case_actuelle == 1)
        {
            musicPlay("musiques/magasin", NB_MUSIQUES_MAGASIN);
            hero.pv = hero.pv_max;
            action_magasin();
        }
        else if (hero.case_actuelle < 6)
        {
            musicPlay("musiques/combat_monstre", NB_MUSIQUES_COMBAT_MONSTRE);
            generate_monster();
            exit = combat();
        }
        else
        {
            musicPlay("musiques/combat_boss", NB_MUSIQUES_COMBAT_BOSS);
            sprintf(monster.type, "boss");
            monster.pv = hero.pv_max - 500;
            if (hero.pv_max <= 1500)
                monster.pv = 1000;
            monster.attaque = 250;
            monster.defense = rand() % 6 + 60;
            monster.money = 0;
            monster.niveau = 0;
            monster.xp = 0;
            exit = combat();
        }
    }
    return exit;
}

void action_magasin()
{
    char choix = 0;
    int continuer = 1;

    while(continuer)
    {
        ecrire(L"%oc[1]%ow | 2 | 3 | 4 | 5 | 6 \n\n");
        ecrire(L"Vous \x88tes au magasin. Vous pouvez ici acheter ou vendre une multitude d'objets.\n\n");
        ecrire(L"Pour acc%lcder \x85 votre inventaire, tapez %ora%ow\n", 130);
        ecrire(L"Pour consulter la liste des objets en vente, tapez %orb%ow\n");
        ecrire(L"Pour vendre des objets, tapez %orc%ow\n");
        ecrire(L"Pour vous reg\x82n\x82rer \x85 la fontaine, tapez %ord%ow\n");
        ecrire(L"Pour quitter le magasin, tapez %ore%ow\n");
        ecrire(L"Pour sauver la partie tapez %ors%ow\n");
        scanc(&choix);
        cls();
        switch (choix)
        {
            case 'a':
                inventaire();
            break;
            case 'b':
                achat_objet();
            break;
            case 'c':
                vente_objet();
            break;
            case 'd':
                hero.pv = hero.pv_max;
                ecrire(L"Vous vous \x88tes soign\x82 \x85 la fontaine.\n");
                ecrire(L"Points de vie : %d/%d\n\n", hero.pv, hero.pv_max);
            break;
            case 'e':
                continuer = outdoor();
            break;
            case 's':
                save();
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

void achat_objet()
{
    char choix = 0;

    while(choix != 'p')
    {
        ecrire(L"Vous avez demand\x82 \x85 acheter des objets.\nVous avez %d d'or.\n", hero.money);
        ecrire(L"Quel type d'objet voulez vous acheter ?\n");
        ecrire(L"Pour des potions tapez %ora%ow,\npour des armes tapez %orb%ow,\npour des armures tapez %orc%ow.\n");
        ecrire(L"Pour revenir au magasin tapez %orp%ow\n", 130, 130);
        scanc(&choix);
        cls();
        switch (choix)
        {
            case 'a':
                achat_potion();
            break;
            case 'b':
                achat_arme();
            break;
            case 'c':
                achat_armure();
            break;
            case 'p':
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

void achat_potion()
{
    char choix = 0;

    while(choix != 'p')
    {
        ecrire(L"Vous avez demand\x82 \x85 acheter des potions.\nVous avez %d d'or.\nVoici la liste des objets que vous pouvez acheter :\n\n", hero.money);
        if (hero.money < PRIX_ACHAT_P_POTION)
            ecrire (L"  Vous ne pouvez rien acheter car vous n'avez pas assez d'or\n\n");
        if (hero.money >= PRIX_ACHAT_P_POTION)
            ecrire(L"  * petite potion de vie (tapez %ora%ow) : %d or\n    Restaure %d PVs\n\n", PRIX_ACHAT_P_POTION, AJOUT_VIE_P_POTION);
        if (hero.money >= PRIX_ACHAT_M_POTION)
            ecrire(L"  * potion de vie moyenne (tapez %orb%ow) : %d or\n    Restaure %d PVs\n\n", PRIX_ACHAT_M_POTION, AJOUT_VIE_M_POTION);
        if (hero.money >= PRIX_ACHAT_G_POTION)
            ecrire(L"  * grande potion de vie (tapez %orc%ow) : %d or\n    Restaure %d PVs\n\n", PRIX_ACHAT_G_POTION, AJOUT_VIE_G_POTION);
        if (hero.money >= PRIX_ACHAT_MAX_POTION)
        {
            if (AJOUT_VIE_MAX_POTION == hero.pv_max)
                ecrire(L"  * potion max (tapez %ord%ow) : %d or\n    Restaure tous les PVs\n\n", PRIX_ACHAT_MAX_POTION);
            else
                ecrire(L"  * potion max (tapez %ord%ow) : %d or\n    Restaure %d PVs\n\n", PRIX_ACHAT_MAX_POTION, AJOUT_VIE_MAX_POTION);
        }
        if (hero.money >= PRIX_ACHAT_ELIXIR_VIE)
            ecrire(L"  * \x82lixir de vie (tapez %ore%ow) : %d or\n    Augmente les PVs max de %d\n      ATTENTION : L'\x82lixir est utilis\x82 automatiquement \x85 l'achat\n\n", PRIX_ACHAT_ELIXIR_VIE, AJOUT_DE_PV_MAX_POUR_ELIXIR);
        if (hero.money >= PRIX_ACHAT_FIOLE_RESURRECTION)
            ecrire(L"  * fiole de r\x82surrection (tapez %orf%ow) : %d or\n    Vous ram\x8Anera \x85 la vie lorsque vous mourrez.\n      ATTENTION : La fiole de r\x82surrection n'est pas revendable.\n\n", PRIX_ACHAT_FIOLE_RESURRECTION);
        ecrire(L"Pour retourner au menu du magasin tapez %orp%ow\n");
        scanc(&choix);
        cls();
        switch (choix)
        {
            case 'p':
            break;
            case 'a':
                if (hero.money < PRIX_ACHAT_P_POTION)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    hero.petite_potion++;
                    hero.money -= PRIX_ACHAT_P_POTION;
                    ecrire(L"achat r\x82ussi\n\n");
                }
            break;
            case 'b':
                if (hero.money < PRIX_ACHAT_M_POTION)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    hero.moyenne_potion++;
                    hero.money -= PRIX_ACHAT_M_POTION;
                    ecrire(L"achat r\x82ussi\n\n");
                }
            break;
            case 'c':
                if (hero.money < PRIX_ACHAT_G_POTION)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    hero.grande_potion++;
                    hero.money -= PRIX_ACHAT_G_POTION;
                    ecrire(L"achat r\x82ussi\n\n");
                }
            break;
            case 'd':
                if (hero.money < PRIX_ACHAT_MAX_POTION)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    hero.potion_max++;
                    hero.money -= PRIX_ACHAT_MAX_POTION;
                    ecrire(L"achat r\x82ussi\n\n");
                }
            break;
            case 'e':
                if (hero.money < PRIX_ACHAT_ELIXIR_VIE)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    hero.pv_max += AJOUT_DE_PV_MAX_POUR_ELIXIR;
                    hero.pv += AJOUT_DE_PV_MAX_POUR_ELIXIR;
                    hero.money -= PRIX_ACHAT_ELIXIR_VIE;
                    ecrire(L"achat r\x82ussi\n\n");
                }
            break;
            case 'f':
                if (hero.money < PRIX_ACHAT_FIOLE_RESURRECTION)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    hero.vie++;
                    hero.money -= PRIX_ACHAT_FIOLE_RESURRECTION;
                    ecrire(L"achat r\x82ussi\n\n");
                }
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

void achat_arme()
{
    char choix = 0;
    wchar_t epee[15] = {0};
    swprintf(epee, L"\x82p%lce de bronze", 130);

    while(choix !='p')
    {
        ecrire(L"Vous avez demand\x82 \x85 acheter des armes.\nVous avez %d d'or\nVoici la liste des objets que vous pouvez acheter :\n\n", hero.money);
        if (hero.money < PRIX_ACHAT_ARME_BRONZE)
            ecrire(L"  Vous ne pouvez rien acheter car vous n'avez pas assez d'or\n\n");
        if (hero.money >= PRIX_ACHAT_ARME_BRONZE)
        {
            if (hero.niv < 3)
                ecrire(L"  %lc niveau 3 requis : \x82p%lce de bronze : %d attaque : %d or\n\n", 16, 130, EFFET_ARME_BRONZE, PRIX_ACHAT_ARME_BRONZE);
            else
                ecrire(L"  * \x82p%lce de bronze : %d attaque : %d or (tapez %ora%ow)\n\n", 130, EFFET_ARME_BRONZE, PRIX_ACHAT_ARME_BRONZE);
        }
        if (hero.money >= PRIX_ACHAT_ARME_ACIER)
        {
            if (hero.niv < 5)
                ecrire(L"  %lc niveau 5 requis : hache d'acier : %d attaque : %d or\n\n", 16, EFFET_ARME_ACIER, PRIX_ACHAT_ARME_ACIER);
            else
                ecrire(L"  * hache d'acier : %d attaque : %d or (tapez %orb%ow)\n\n", EFFET_ARME_ACIER, PRIX_ACHAT_ARME_ACIER);
        }
        if (hero.money >= PRIX_ACHAT_ARME_MAITRE)
        {
            if (hero.niv < 7)
                ecrire(L"  %lc niveau 7 requis : marteau de ma\x8Ctre : %d attaque : %d or\n\n", 16, EFFET_ARME_MAITRE, PRIX_ACHAT_ARME_MAITRE);
            else
                ecrire(L"  * marteau de ma\x8Ctre : %d attaque : %d or (tapez %orc%ow)\n\n", EFFET_ARME_MAITRE, PRIX_ACHAT_ARME_MAITRE);
        }
        if (hero.money >= PRIX_ACHAT_ARME_PHOENIX)
        {
            if (hero.niv < 9)
                ecrire(L"  %lc niveau 9 requis : lance du Phoenix : %d attaque : %d or\n\n", 16, EFFET_ARME_PHOENIX, PRIX_ACHAT_ARME_PHOENIX);
            else
                ecrire(L"  * lance du Phoenix : %d attaque : %d or (tapez %ord%ow)\n\n", EFFET_ARME_PHOENIX, PRIX_ACHAT_ARME_PHOENIX);
        }
        ecrire(L"Pour retourner au menu du magasin tapez %orp%ow\n");
        scanc(&choix);
        cls();
        switch (choix)
        {
            case 'p':
            break;
            case 'a':
                if (hero.money < PRIX_ACHAT_ARME_BRONZE)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 3)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.arme, epee))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette arme\n\n", 130);
                    else
                    {
                        hero.attaque = EFFET_ARME_BRONZE;
                        swprintf(hero.arme, L"\x82p%lce de bronze", 130);
                        hero.money -= PRIX_ACHAT_ARME_BRONZE;
                        ecrire(L"achat d'\x82p%lce de bronze r\x82ussi\n\n", 130);
                    }
                }
            break;
            case 'b':
                if (hero.money < PRIX_ACHAT_ARME_ACIER)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 5)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.arme, L"hache d'acier"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette arme\n\n", 130);
                    else
                    {
                        hero.attaque = EFFET_ARME_ACIER;
                        swprintf(hero.arme, L"hache d'acier");
                        hero.money -= PRIX_ACHAT_ARME_ACIER;
                        ecrire(L"achat d'hache d'acier r\x82ussi\n\n");
                    }
                }
            break;
            case 'c':
                if (hero.money < PRIX_ACHAT_ARME_MAITRE)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 7)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.arme, L"marteau de ma\x8Ctre"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette arme\n\n", 130);
                    else
                    {
                        hero.attaque = EFFET_ARME_MAITRE;
                        swprintf(hero.arme, L"marteau de ma\x8Ctre");
                        hero.money -= PRIX_ACHAT_ARME_MAITRE;
                        ecrire(L"achat du marteau de ma\x8Ctre r\x82ussi\n\n");
                    }
                }
            break;
            case 'd':
                if (hero.money < PRIX_ACHAT_ARME_PHOENIX)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 9)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.arme, L"lance du Phoenix"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette arme\n\n", 130);
                    else
                    {
                        hero.attaque = EFFET_ARME_PHOENIX;
                        swprintf(hero.arme, L"lance du Phoenix");
                        hero.money -= PRIX_ACHAT_ARME_PHOENIX;
                        ecrire(L"achat de la lance du Phoenix r\x82ussi\n\n");
                    }
                }
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

void achat_armure()
{
    char choix = 0;

    while(choix != 'p')
    {
        ecrire(L"Vous avez demand\x82 \x85 acheter des armures.\nVous avez %d d'or\nVoici la liste des objets que vous pouvez acheter :\n\n", hero.money);
        if (hero.money < PRIX_ACHAT_ARMURE_BOIS)
            ecrire(L"  Vous ne pouvez rien acheter car vous n'avez pas assez d'or\n\n");
        if (hero.money >= PRIX_ACHAT_ARMURE_BOIS)
        {
            if (hero.niv < 2)
                ecrire(L"  %lc niveau 2 requis : armure en bois : %d d%lcfense : %d or\n\n", 16, EFFET_ARMURE_BOIS, 130, PRIX_ACHAT_ARMURE_BOIS);
            else
                ecrire(L"  * armure en bois : %d d%lcfense : %d or (tapez %ora%ow)\n\n", EFFET_ARMURE_BOIS, 130, PRIX_ACHAT_ARMURE_BOIS);
        }
        if (hero.money >= PRIX_ACHAT_ARMURE_BRONZE)
        {
            if (hero.niv < 4)
                ecrire(L"  %lc niveau 4 requis : armure de bronze : %d d%lcfense : %d or\n\n", 16, EFFET_ARMURE_BRONZE, 130, PRIX_ACHAT_ARMURE_BRONZE);
            else
                ecrire(L"  * armure de bronze : %d d%lcfense : %d or (tapez %orb%ow)\n\n", EFFET_ARMURE_BRONZE, 130, PRIX_ACHAT_ARMURE_BRONZE);
        }
        if (hero.money >= PRIX_ACHAT_ARMURE_ACIER)
        {
            if (hero.niv < 6)
                ecrire(L"  %lc niveau 6 requis : armure d'acier : %d d%lcfense : %d or\n\n", 16, EFFET_ARMURE_ACIER, 130, PRIX_ACHAT_ARMURE_ACIER);
            else
                ecrire(L"  * armure d'acier : %d d%lcfense : %d or (tapez %orc%ow)\n\n", EFFET_ARMURE_ACIER, 130, PRIX_ACHAT_ARMURE_ACIER);
        }
        if (hero.money >= PRIX_ACHAT_ARMURE_MAITRE)
        {
            if (hero.niv < 8)
                ecrire(L"  %lc niveau 8 requis : armure de ma\x8Ctre : %d d%lcfense : %d or\n\n", 16, EFFET_ARMURE_MAITRE, 130, PRIX_ACHAT_ARMURE_MAITRE);
            else
                ecrire(L"  * armure de ma\x8Ctre : %d d%lcfense : %d or (tapez %ord%ow)\n\n", EFFET_ARMURE_MAITRE, 130, PRIX_ACHAT_ARMURE_MAITRE);
        }
        if (hero.money >= PRIX_ACHAT_ARMURE_PHOENIX)
        {
            if (hero.niv < 10)
                ecrire(L"  %lc niveau 10 requis : armure du Phoenix : %d d%lcfense : %d or\n\n", 16, EFFET_ARMURE_PHOENIX, 130, PRIX_ACHAT_ARMURE_PHOENIX);
            else
                ecrire(L"  * armure du Phoenix : %d d%lcfense : %d or (tapez %ore%ow)\n\n", EFFET_ARMURE_PHOENIX, 130, PRIX_ACHAT_ARMURE_PHOENIX);
        }
        ecrire(L"Pour retourner au menu du magasin tapez %orp%ow\n");
        scanc(&choix);
        cls();
        switch (choix)
        {
            case 'p':
            break;
            case 'a':
                if (hero.money < PRIX_ACHAT_ARMURE_BOIS)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 2)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.armure, L"armure en bois"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette armure\n\n", 130);
                    else
                    {
                        hero.defense = EFFET_ARMURE_BOIS;
                        swprintf(hero.armure, L"armure en bois");
                        hero.money -= PRIX_ACHAT_ARMURE_BOIS;
                        ecrire(L"achat de l'armure en bois r\x82ussi\n\n");
                    }
                }
            break;
            case 'b':
                if (hero.money < PRIX_ACHAT_ARMURE_BRONZE)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 4)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.armure, L"armure de bronze"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette armure\n\n", 130);
                    else
                    {
                        hero.defense = EFFET_ARMURE_BRONZE;
                        swprintf(hero.armure, L"armure de bronze");
                        hero.money -= PRIX_ACHAT_ARMURE_BRONZE;
                        ecrire(L"achat de l'armure de bronze r\x82ussi\n\n");
                    }
                }
            break;
            case 'c':
                if (hero.money < PRIX_ACHAT_ARMURE_ACIER)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 6)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.armure, L"armure d'acier"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette armure\n\n", 130);
                    else
                    {
                        hero.defense = EFFET_ARMURE_ACIER;
                        swprintf(hero.armure, L"armure d'acier");
                        hero.money -= PRIX_ACHAT_ARMURE_ACIER;
                        ecrire(L"achat de l'armure d'acier r\x82ussi\n\n");
                    }
                }
            break;
            case 'd':
                if (hero.money < PRIX_ACHAT_ARMURE_MAITRE)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 8)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.armure, L"armure de ma\x8Ctre"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette armure\n\n", 130);
                    else
                    {
                        hero.defense = EFFET_ARMURE_MAITRE;
                        swprintf(hero.armure, L"armure de ma\x8Ctre");
                        hero.money -= PRIX_ACHAT_ARMURE_MAITRE;
                        ecrire(L"achat de l'armure de ma\x8Ctre r\x82ussi\n\n");
                    }
                }
            break;
            case 'e':
                if (hero.money < PRIX_ACHAT_ARMURE_PHOENIX)
                    ecrire(L"Veuillez entrer un choix valide\n\n");
                else
                {
                    if (hero.niv < 10)
                        ecrire(L"Vous n'avez pas le niveau requis\n\n");
                    else if (!wcscmp(hero.armure, L"armure du Phoenix"))
                        ecrire(L"Vous poss%lcdez d\x82j\x85 cette armure\n\n", 130);
                    else
                    {
                        hero.defense = EFFET_ARMURE_PHOENIX;
                        swprintf(hero.armure, L"armure du Phoenix");
                        hero.money -= PRIX_ACHAT_ARMURE_PHOENIX;
                        ecrire(L"achat de l'armure du Phoenix r\x82ussi\n\n");
                    }
                }
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

void vente_objet()
{
    char choix = 0;

    while(choix != 'p')
    {
        ecrire(L"Vous avez demand\x82 \x85 vendre des objets.\nVous avez %d d'or.\nVoici la liste des objets que vous pouvez vendre :\n\n", hero.money);
        if (hero.petite_potion == 0 && hero.moyenne_potion == 0 && hero.grande_potion == 0 && hero.potion_max == 0)
            ecrire(L"  Vous n'avez aucun objet \x85 vendre\n\n");
        if (hero.petite_potion > 0)
            ecrire(L"  * petite potion de vie (tapez %ora%ow) : %d or\n\n", PRIX_VENTE_P_POTION);
        if (hero.moyenne_potion > 0)
            ecrire(L"  * potion de vie moyenne (tapez %orb%ow) : %d or\n\n", PRIX_VENTE_M_POTION);
        if (hero.grande_potion > 0)
            ecrire(L"  * grande potion de vie (tapez %orc%ow) : %d or\n\n", PRIX_VENTE_G_POTION);
        if (hero.potion_max > 0)
            ecrire(L"  * potion max (tapez %ord%ow) : %d or\n\n", PRIX_VENTE_MAX_POTION);
        ecrire(L"Pour retourner au menu du magasin tapez %orp%ow\n");
        scanc(&choix);
        cls();
        switch (choix)
        {
            case 'p':
            break;
            case 'a':
                if(hero.petite_potion > 0)
                {
                    hero.petite_potion--;
                    hero.money += PRIX_VENTE_P_POTION;
                    ecrire(L"potion vendue\n\n");
                }
                else
                    ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
            case 'b':
                if(hero.moyenne_potion > 0)
                {
                    hero.moyenne_potion--;
                    hero.money += PRIX_VENTE_M_POTION;
                    ecrire(L"potion vendue\n\n");
                }
                else
                    ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
            case 'c':
                if(hero.grande_potion > 0)
                {
                    hero.grande_potion--;
                    hero.money += PRIX_VENTE_G_POTION;
                    ecrire(L"potion vendue\n\n");
                }
                else
                    ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
            case 'd':
                if(hero.potion_max > 0)
                {
                    hero.potion_max--;
                    hero.money += PRIX_VENTE_MAX_POTION;
                    ecrire(L"potion vendue\n\n");
                }
                else
                    ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

int outdoor()
{
    char choix = 0;

    ecrire(L"Vous avez quitt\x82 le magasin\n\n");
    ecrire(L"Pour vous deplacer vers la case %og2%ow tapez %ord%ow\n");
    ecrire(L"Pour retourner dans le magasin tapez %orp%ow\n");
    scanc(&choix);
    cls();
    if (choix == 'p')
        return 1;
    else if (choix == 'd')
    {
        hero.case_actuelle++;
        return 0;
    }
    else
    {
        ecrire(L"Veuillez entrer un choix valide\n\n");
        return outdoor();
    }
}

void save()
{
    char *vide = NULL;
    char **names = calloc(NB_SLOTS, 80 * sizeof(char));
    char confirm = 0;
    char choix = 0;
    int continuer = 0;
    int i = 0, j = 0;
    FILE* myFile[NB_SLOTS] = {0};
    char fileName[80] = {0};
    char character = 0;

    for (i = 0 ; i < NB_SLOTS ; i++)
    {
        sprintf(fileName, "files/save-%d.shf", i+1);
        myFile[i] = fopen(fileName, "a");
        fclose(myFile[i]);
        myFile[i] = fopen(fileName, "r+");
        printf("%s\n", fileName);
    }
    if(myFile == NULL)
        exit(1234);
    for(i = 0 ; i < NB_SLOTS ; i++)
    {
        /*while ((character = fgetc(myFile[i])) != EOF)
            printf("%c", character);*/
        printf("%s", names[i]);
        fscanf(myFile[i], "%s", names[i]);
        printf("%s", names[i]);
        fgets(vide, 10000, myFile[i]);
    }
    while(!continuer)
    {
        while(!(choix > '0' && choix <= (NB_SLOTS + '0')))
        {
            ecrire(L"Sur quel slot voulez vous sauver votre partie ?\n");
            ecrire(L"Pour choisir le slot, entrez son num\x82ro.\n");
            ecrire(L"Pour retourner au menu pr%lcc%lcdent, tapez %orp%ow\n\n", 130, 130);
            for (i = 0 ; i < NB_SLOTS ; i++)
                ecrire(L"Slot %d : %s\n", i + 1, names[i]);
            ecrire(L"Entrez le num\x82ro du slot choisi :\n");
            scanc(&choix);
            cls();
            if(!(choix > '0' && choix <= (NB_SLOTS + '0')))
                ecrire(L"Entrez un num\x82ro de slot valide.\n\n");
        }
        if(strcmp(names[choix - '0'], "vide"))
        {
            while(confirm != 'o' && confirm != 'n')
            {
                ecrire(L"Le slot %og%c%ow contient d\x82j\x85 une sauvegarde.\n", choix);
                ecrire(L"La pr%lcc%lcdente sauvegarde sera perdue.\n", 130, 130);
                ecrire(L"\xD2tes vous s\xEArs de vouloir continuer ? (%oro%ow/%orn%ow)\n");
                scanc(&confirm);
                cls();
                if(confirm != 'o' && confirm != 'n')
                    ecrire(L"Veuillez entrer %oro%ow ou %orn%ow svp.\n\n");
            }
            if(confirm == 'o')
                continuer = 1;
            else
                continuer = 0;
        }
        else
            continuer = 1;
        if (continuer)
        {

        }
    }
    for (i = 0 ; i < NB_SLOTS ; i++)
        fclose(myFile[i]);
}

void generate_monster()
{
    int MIN, MAX;

    monster.niveau = hero.case_actuelle - (rand() % 2);
    monster.pv = (monster.niveau * 100) + (rand() % 20) - 10;
    switch (monster.niveau)
    {
        case 1:
            MIN = 8;
            MAX = 53;
        break;
        case 2:
            MIN = 26;
            MAX = 74;
        break;
        case 3:
            MIN = 53;
            MAX = 92;
        break;
        case 4:
            MIN = 74;
            MAX = 12;
        break;
        case 5:
            MIN = 92;
            MAX = 140;
        break;
    }
    monster.attaque = rand() % (MAX - MIN + 1) + MIN;
    monster.defense = rand() % 11 + monster.niveau * 10 - 10;
    switch (monster.niveau)
    {
        case 1:
            MIN = 25;
            MAX = 50;
        break;
        case 2:
            MIN = 50;
            MAX = 100;
        break;
        case 3:
            MIN = 100;
            MAX = 200;
        break;
        case 4:
            MIN = 200;
            MAX = 400;
        break;
        case 5:
            MIN = 400;
            MAX = 800;
        break;
    }
    monster.money = ((rand() % (MAX - MIN + 1)) + MIN) * MONSTER_COEFF_MONEY;
    monster.xp = monster.niveau * COEFF_EXPERIENCE;
}

int combat()
{
    char choix = 0;
    int critical = 0, degats = 0;

    while(monster.pv > 0)
    {
        switch (hero.case_actuelle)
        {
            case 2:
                ecrire(L" 1 | %oc[2]%ow | 3 | 4 | 5 | 6 \n");
            break;
            case 3:
                ecrire(L" 1 | 2 | %oc[3]%ow | 4 | 5 | 6 \n");
            break;
            case 4:
                ecrire(L" 1 | 2 | 3 | %oc[4]%ow | 5 | 6 \n");
            break;
            case 5:
                ecrire(L" 1 | 2 | 3 | 4 | %oc[5]%ow | 6 \n");
            break;
            default:
                ecrire(L" 1 | 2 | 3 | 4 | 5 | %oc[6]%ow \n");
            break;
        }
        if (monster.niveau)
            ecrire(L"monstre niveau %d\n\n", monster.niveau);
        else
            ecrire(L"BOSS\n\n");
        ecrire(L"Vous avez %d PVs\n", hero.pv);
        ecrire(L"Le %s a %d PVs\n", monster.type, monster.pv);
        ecrire(L"Que voulez vous faire ?\n");
        ecrire(L"pour acc%lcder \x85 l'inventaire tapez %ora%ow\n", 130);
        ecrire(L"pour attaquer le %s tapez %orb%ow\n", monster.type);
        scanc(&choix);
        cls();
        if (choix == 'a')
            inventaire();
        else if (choix == 'b')
        {
            critical = critical_chance();
            if (!critical)
                ecrire(L"Vous ratez votre attaque, vous n'infligez donc aucun d\x82g\x83t\n");
            else
            {
                if (critical == 2)
                {
                    ecrire(L"Coup critique ! Votre force d'attaque est doubl%lce !\n", 130);
                    hero.attaque *= 2;
                }
                degats = hero.attaque - monster.defense;
                if (hero.attaque < monster.defense)
                    degats = 0;
                ecrire(L"Vous attaquez avec une force %d et le %s ", hero.attaque, monster.type);
                ecrire(L"se d%lcfend avec une force %d\n", 130, monster.defense);
                ecrire(L"Vous lui infligez donc %d d\x82g\x83ts\n", degats);
                monster.pv -= degats;
                if (critical == 2)
                    hero.attaque /= 2;
            }
            ecrire(L"\n");
            if (monster.pv > 0)
            {
                critical = critical_chance();
                if (!critical)
                {
                    ecrire(L"Le %s ", monster.type);
                    ecrire(L"a rat\x82 son attaque, il ne vous inflige donc aucun d\x82g\x83t\n\n");
                }
                else
                {
                    if (critical == 2)
                    {
                        ecrire(L"Coup critique ! La force d'attaque du %s ", monster.type);
                        ecrire(L"est doubl%lce !\n", 130);
                        monster.attaque *= 2;
                    }
                    degats = monster.attaque - hero.defense;
                    if (monster.attaque < hero.defense)
                        degats = 0;
                    ecrire(L"Le %s ", monster.type);
                    ecrire(L"vous attaque avec une force %d et vous vous d%lcfendez avec une\nforce %d\n", monster.attaque, 130, hero.defense);
                    ecrire(L"Il vous inflige donc %d d\x82g\x83ts\n\n", degats);
                    hero.pv -= degats;
                    if (critical == 2)
                        monster.attaque /= 2;
                }
            }
            else
            {
                cls();
                ecrire(L"Vous avez vaincu le %s\n\n", monster.type);
                if (hero.case_actuelle < 6)
                {
                    ecrire(L"Vous gagnez %d d'exp\x82rience\n", monster.xp);
                    ecrire(L"Vous r%lccup\x82rez %d d'or\n", 130, monster.money);
                    hero.money += monster.money;
                    ecrire(L"Vous poss%lcdez maintenant %d d'or et il vous reste %d PVs\n\n", 130, hero.money, hero.pv);
                }
                ecrire(L"Appuyez sur une touche pour continuer\n");
                scanc(&choix);
                cls();
                if(hero.case_actuelle == 6)
                    return GAGNE;
                while (monster.xp != 0)
                {
                    monster.xp--;
                    hero.xp++;
                    if (actualise_niveaux())
                    {
                        ecrire(L"Vous avez gagn\x82 un niveau !\nVous \x88tes maintenant niveau %d !\nAuppuyez sur une touche pour continuer\n", hero.niv);
                        scanc(&choix);
                        cls();
                    }
                }
                choix = 0;
                if (hero.case_actuelle < 6)
                {
                    while (choix != 'd' && choix != 'g' && choix != 's')
                    {
                        if (choix != 0)
                            ecrire(L"Veuillez entrer un choix valide\n\n");
                        ecrire(L"Pour aller vers la case sup\x82rieure, tapez %ord%ow\n");
                        ecrire(L"Pour aller vers la case inf\x82rieure, tapez %org%ow\n");
                        ecrire(L"Pour rester sur cette case, tapez %ors%ow\n");
                        scanc(&choix);
                        cls();
                    }
                    if (choix == 'd')
                        hero.case_actuelle++;
                    else if (choix == 'g')
                        hero.case_actuelle--;
                }
            }
            if (hero.pv <= 0)
            {
                cls();
                ecrire(L"Le monstre vous a tu\x82\n");
                regenerate();
                if(hero.vie <= 0)
                    return PERD;
            }
        }
        else
            ecrire(L"Veuillez entrer un choix valide\n\n");
    }

    return CONTINUE;
}

int critical_chance()
{
    int critical = 0, isCritical = 0;

    critical = rand() % 100;
    if (critical < 8)
        isCritical = 0;
    else if (critical >= 92)
        isCritical = 2;
    else
        isCritical = 1;

    return isCritical;
}

void regenerate()
{
    hero.vie--;
    if (hero.vie > 0)
    {
        ecrire(L"Vous revenez \x85 la vie gr%lcce a une fiole de r\x82surrection\n", 131);
        hero.pv = hero.pv_max;
    }
}

int actualise_niveaux()
{
    if (hero.xp == 1 || hero.xp == 4 || hero.xp == 9 || hero.xp == 16 || hero.xp == 25 || hero.xp == 36 || hero.xp == 49 || hero.xp == 64 || hero.xp == 81)
    {
        hero.niv++;
        return 1;
    }
    return 0;
}

void inventaire()
{
    char choix = 0;

    while(choix != 'p')
    {
        ecrire(L"Vous \x88tes dans l'inventaire\n\n");
        ecrire(L"Pour voir vos stats tapez %ora%ow\nPour voir/utiliser vos objets tapez %orb%ow\nPour revenir au jeu tapez %orp%ow\n");
        scanc(&choix);
        cls();
        switch(choix)
        {
            case 'a':
                stats();
            break;
            case 'b':
                use_item();
            break;
            case 'p':
            break;
            default:
                ecrire(L"Veuillez entrer un choix valide\n\n");
            break;
        }
    }
}

void stats()
{
    char precedent = 0;
    int fiolesDeResurrection = hero.vie - VIES_DEBUT;

    if (fiolesDeResurrection < 0)
        fiolesDeResurrection = 0;
    ecrire(L"Stats :\n");
    ecrire(L"Niveau : %d\n", hero.niv);
    ecrire(L"Exp\x82rience : %d\n", hero.xp);
    ecrire(L"Exp\x82rience pour le prochain niveau : ");
    if (hero.niv == 10)
        ecrire(L"niveau max atteint\n");
    else
        ecrire(L"%d\n", powInt(hero.niv, 2) - hero.xp);
    ecrire(L"Arme : %ls\n", hero.arme);
    ecrire(L"Armure : %ls\n", hero.armure);
    ecrire(L"Or : %d\n", hero.money);
    ecrire(L"Points de Vie (pv) : %d/%d\n", hero.pv, hero.pv_max);
    ecrire(L"Attaque : %d\n", hero.attaque);
    ecrire(L"D%lcfense : %d\n", 130, hero.defense);
    ecrire(L"Fiole(s) de r\x82surrection : %d\n", fiolesDeResurrection);
    ecrire(L"\nPour revenir au menu de l'inventaire, tapez %orp%ow\n");
    scanc(&precedent);
    cls();
}

void use_item()
{
    char choix = 0;
    int fioles_de_resurrection = hero.vie - VIES_DEBUT;

    if (fioles_de_resurrection < 0)
        fioles_de_resurrection = 0;
    ecrire(L"Objets :\n");
    ecrire(L"Arme : %s\n", hero.arme);
    ecrire(L"Armure : %s\n", hero.armure);
    ecrire(L"Petite(s) potion(s) : %d (tapez %ora%ow pour utiliser)\n", hero.petite_potion);
    ecrire(L"Potion(s) moyenne(s) : %d (tapez %orb%ow pour utiliser)\n", hero.moyenne_potion);
    ecrire(L"Grande(s) potion(s) : %d (tapez %orc%ow pour utiliser)\n", hero.grande_potion);
    ecrire(L"Potion(s) max : %d (tapez %ord%ow pour utiliser)\n", hero.potion_max);
    ecrire(L"Or : %d\n", hero.money);
    ecrire(L"Fiole(s) de r\x82surrection : %d", fioles_de_resurrection);
    ecrire(L"\nTapez %orp%ow pour revenir au menu de l'inventaire\n");
    scanc(&choix);
    cls();
    switch (choix)
    {
        case 'a':
            if (hero.petite_potion > 0 && hero.pv != hero.pv_max)
            {
                hero.pv += AJOUT_VIE_P_POTION;
                hero.petite_potion--;
                if(hero.pv > hero.pv_max)
                    hero.pv = hero.pv_max;
                ecrire(L"petite potion utilis%lce\n\n", 130);
                use_item();
            }
            else if (hero.petite_potion <= 0)
            {
                ecrire(L"Vous n'avez pas de petite potion\n\n");
                use_item();
            }
            else if (hero.pv == hero.pv_max)
            {
                ecrire(L"Vos points de vie sont au maximum\n\n");
                use_item();
            }
        break;
        case 'b':
            if (hero.moyenne_potion > 0 && hero.pv != hero.pv_max)
            {
                hero.pv += AJOUT_VIE_M_POTION;
                hero.moyenne_potion--;
                if(hero.pv > hero.pv_max)
                    hero.pv = hero.pv_max;
                ecrire(L"potion moyenne utilis%lce\n\n", 130);
                use_item();
            }
            else if (hero.moyenne_potion == 0)
            {
                ecrire(L"Vous n'avez pas de potion moyenne\n\n");
                use_item();
            }
            else if (hero.pv == hero.pv_max)
            {
                ecrire(L"Vos points de vie sont au maximum\n\n");
                use_item();
            }
        break;
        case 'c':
            if (hero.grande_potion > 0 && hero.pv != hero.pv_max)
            {
                hero.pv += AJOUT_VIE_G_POTION;
                if(hero.pv > hero.pv_max)
                    hero.pv = hero.pv_max;
                hero.grande_potion--;
                ecrire(L"grande potion utilis%lce\n\n", 130);
                use_item();
            }
            else if (hero.grande_potion == 0)
            {
                ecrire(L"Vous n'avez pas de grande potion\n\n");
                use_item();
            }
            else if (hero.pv == hero.pv_max)
            {
                ecrire(L"Vos points de vie sont au maximum\n\n");
                use_item();
            }
        break;
        case 'd':
            if (hero.potion_max > 0 && hero.pv != hero.pv_max)
            {
                hero.pv += AJOUT_VIE_MAX_POTION;
                if(hero.pv > hero.pv_max)
                    hero.pv = hero.pv_max;
                hero.potion_max--;
                ecrire(L"potion max utilis%lce\n\n", 130);
                use_item();
            }
            else if (hero.potion_max == 0)
            {
                ecrire(L"Vous n'avez pas de potion max\n\n");
                use_item();
            }
            else if (hero.pv == hero.pv_max)
            {
                ecrire(L"Vos points de vie sont au maximum\n\n");
                use_item();
            }
        break;
        case 'p':
            inventaire();
        break;
        default:
            ecrire(L"Veuillez entrer un choix valide\n\n");
            use_item();
        break;
    }
}
