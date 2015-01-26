/*
Fichier créé le 21/01/2012 à 19h04

-----------------------------------------------------------------

Fichier créé par tsunami33 pour le projet shaak

-----------------------------------------------------------------

Fichier header regroupant les fonctions liées aux actions de jeu.
*/

#ifndef DEF_JOUER
    #define DEF_JOUER

    #define CONTINUE 0
    #define PERD 1
    #define GAGNE 2

    int replay(wchar_t commencer_jeu); //Lance une partie
        void load(char* nomFichier); //Charge une partie
        int action_case_actuelle(); //Englobe la totalité des actions d'un tour

            //case magasin
            void action_magasin(); //Englobe tout le magasin
                void achat_objet(); //Fonction d'achat du magasin
                    void achat_potion(); //Fonction d'achat des potions
                    void achat_arme(); //Fonction d'achat des armes
                    void achat_armure(); //Fonction d'achat des armures
                void vente_objet(); //Permet de vendre tous les objets possédés et vendables
                int outdoor(); //Execute tout ce qui se passe en dehors du magasin
                void save(); //Sauve une partie

            //Combat
            void generate_monster(); //Génère un monstre
                int combat(); //Englobe toute la phase de combat et retourne 1 si le joueur a gagné et 0 sinon
                    int critical_chance(); //indique si l'attaque était une attaque ratée, normale ou un coup critique
                    void regenerate(); //Pour regenerer lors d'un combat grâce à une fiole de résurrection
                    int actualise_niveaux(); //Monte d'un niveau si l'experience est suffisament grande

            //Général
            void inventaire(); //Englobe tout l'inventaire
                void stats(); //Affiche les stats du joueur
                void use_item(); //Permet d'utiliser des objets depuis l'inventaire

    typedef struct Hero Hero;
    struct Hero
    {
        int case_actuelle;
        int vie;
        int pv;
        int defense;
        int attaque;
        int pv_max;
        int xp;
        int niv;
        int petite_potion;
        int moyenne_potion;
        int grande_potion;
        int potion_max;
        int money;
        wchar_t arme[31];
        wchar_t armure[31];
    };

    typedef struct Monster Monster;
    struct Monster
    {
        char type[10];
        int niveau;
        int attaque;
        int defense;
        int money;
        int pv;
        int xp;
    };

#endif
