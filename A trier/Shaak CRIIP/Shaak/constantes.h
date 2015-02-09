/*
Fichier créé le 24/04/2011 à 02h31

-----------------------------------------------------------------

Fichier créé par tsunami33 pour le projet Shaak

-----------------------------------------------------------------

Fichier header regroupant toutes les constantes du jeu.
*/

#ifndef DEF_CONSTANTES
    #define DEF_CONSTANTES

    #define NB_IMAGES_TYPE_1 4
    #define NB_IMAGES_TYPE_2 9
    #define NB_IMAGES_TYPE_3 18
    #define NB_IMAGES_TYPE_4 13

    #define NB_IMAGES_PNJ 3
    #define NB_MAX_PNJ 3
    #define NB_PNJ_CARTE_1 0
    #define NB_PNJ_CARTE_2 3
    #define NB_CARTES 2

    #define MUSIC_FOLDER_NAME "musics/"
    #define TAILLE_CASE 50
    #define NB_CASES_H 10
    #define NB_CASES_W 12
    #define NB_TYPES_IMAGES 4
    #define HAUTEUR_IMAGE_TEXTE 150
    #define NB_CASES (NB_CASES_H*NB_CASES_W)
    #define NB_IMAGES (NB_IMAGES_TYPE_1+NB_IMAGES_TYPE_2+NB_IMAGES_TYPE_3+NB_IMAGES_TYPE_4)
    #define LARGEUR_FENETRE (NB_CASES_W*TAILLE_CASE)
    #define HAUTEUR_FENETRE (NB_CASES_H*TAILLE_CASE+HAUTEUR_IMAGE_TEXTE)
    #define TAILLE_TEXTE 18
    #define MARGE_TEXTE 10

    #define PV_MAX 50
    #define DEFENSE 0
    #define ATTAQUE 4
    #define VIES_DEBUT 1
    #define P_POTION 0
    #define M_POTION 1
    #define G_POTION 0
    #define MAX_POTION 0
    #define ARGENT 100

    #define AJOUT_VIE_P_POTION 10
    #define AJOUT_VIE_M_POTION 25
    #define AJOUT_VIE_G_POTION 60
    #define AJOUT_VIE_MAX_POTION pv_max
    #define PRIX_ACHAT_P_POTION 25
    #define PRIX_ACHAT_M_POTION 50
    #define PRIX_ACHAT_G_POTION 100
    #define PRIX_ACHAT_MAX_POTION 200
    #define PRIX_ACHAT_ELIXIR_VIE 100
    #define PRIX_ACHAT_FIOLE_RESURRECTION 250
    #define PRIX_ACHAT_POTION_TELEPORT 300
    #define PRIX_VENTE_P_POTION 12
    #define PRIX_VENTE_M_POTION 25
    #define PRIX_VENTE_G_POTION 50
    #define PRIX_VENTE_MAX_POTION 100
    #define PRIX_VENTE_POTION_TELEPORT 300
    #define AJOUT_DE_PV_MAX_POUR_ELIXIR 10
    #define PRIX_ACHAT_ARMURE_BOIS 100
    #define PRIX_ACHAT_ARMURE_BRONZE 300
    #define PRIX_ACHAT_ARMURE_ACIER 600
    #define PRIX_ACHAT_ARMURE_MAITRE 1200
    #define PRIX_ACHAT_ARMURE_PHOENIX 2400
    #define PRIX_ACHAT_ARME_BRONZE 200
    #define PRIX_ACHAT_ARME_ACIER 400
    #define PRIX_ACHAT_ARME_MAITRE 800
    #define PRIX_ACHAT_ARME_PHOENIX 1600
    #define EFFET_ARMURE_BOIS 1
    #define EFFET_ARMURE_BRONZE 2
    #define EFFET_ARMURE_ACIER 3
    #define EFFET_ARMURE_MAITRE 5
    #define EFFET_ARMURE_PHOENIX 7
    #define EFFET_ARME_BRONZE 7
    #define EFFET_ARME_ACIER 12
    #define EFFET_ARME_MAITRE 18
    #define EFFET_ARME_PHOENIX 25
    #define COEFF_EXPERIENCE 1

#endif
