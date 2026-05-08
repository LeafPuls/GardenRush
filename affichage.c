#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//=====Header=====
#include "declaration.h"
#include "affichage.h"
#include "game.h"

//=====Initialisation variable=====
int debug_state;
HANDLE hIn;

//=====================================================================================================================================================================Initialisation AFFICHAGE==========================================================================================================================================================================

void initialisation_affichage()//juste de la décoration pour le plateau de jeu
{
    // Plat 1
    dessiner_rectangle(PLAT_L - 3, PLAT_C - 5, 89, 176, MARRON);
    dessiner_rectangle(PLAT_L-2, PLAT_C-3, 87, 172, VERT_FONCE);

    // Plat 2
    dessiner_rectangle(PLAT2_L - 3, PLAT2_C - 5, 89, 176, MARRON);
    dessiner_rectangle(PLAT2_L - 2, PLAT2_C - 3, 87, 172, VERT_FONCE);

    // Score
    dessiner_rectangle(2, 7, 5, 459, GRIS);

    // Haie
    dessiner_rectangle(HAIE_L - 5, HAIE_C - 6, 114, 42, GRIS);
    dessiner_rectangle(HAIE_L-4, HAIE_C-4, 110, 38, VERT_NOIR);

    // Tremplin
    dessiner_rectangle(HAIE_L + 87, HAIE_C - 14, 29, 58, VERT_NOIR);
    dessiner_rectangle(HAIE_L + 89, HAIE_C - 10, 25, 50, BLEU_CIEL);
    dessiner_rectangle(HAIE_L + 91, HAIE_C - 6, 21, 42, VERT_NOIR);
    dessiner_rectangle(HAIE_L + 92, HAIE_C - 3, 19, 36, OR);
}


//==========================================================================================================================================================================Fonction AFFICHAGE==========================================================================================================================================================================

void afficher_plateau_joueur(S_jeu* game, S_joueur joueur[], int j)
{
    int l, c;

    if (j == 0)
    {
        l = PLAT_L;
        c = PLAT_C;
    }
    else
    {
        l = PLAT2_L;
        c = PLAT2_C;
    }

    int nb_lignes = 5;
    int nb_cols = 5;

    int l_case = 15;
    int c_case = 30;

    int espace_ligne = 2;
    int espace_colonne = 4;

    for (int lig = 0; lig < nb_lignes; lig++)
    {
        for (int col = 0; col < nb_cols; col++)
        {
            // --- EXCLUSION DES 4 COINS ---
            if ((lig == 0 && col == 0) || (lig == 0 && col == nb_cols - 1) ||
                    (lig == nb_lignes - 1 && col == 0) || (lig == nb_lignes - 1 && col == nb_cols - 1))
            {
                continue; // Saute cette itération, ne dessine rien
            }

            // Calcul des coord
            int coord_l = l + (lig * (l_case + espace_ligne));
            int coord_c = c + (col * (c_case + espace_colonne));
            char case_actuelle = joueur[j].plat[lig][col];

            switch (case_actuelle)
            {
            case 'C':
                afficher_double_carotte(coord_l, coord_c);
                break;

            case 'c':
                afficher_carotte(coord_l, coord_c);
                break;

            case 'T':
				afficher_double_tomate(coord_l, coord_c);
                break;

            case 't':
				afficher_tomate(coord_l, coord_c);
                break;

            case 'B':
                afficher_double_brocolis(coord_l, coord_c);
                break;

            case 'b':
                afficher_brocolis(coord_l, coord_c);
                break;

            case 'A':
                afficher_double_aubergine(coord_l, coord_c);
                break;

            case 'a':
                afficher_aubergine(coord_l, coord_c);
                break;

            case 'P':
                afficher_double_pdt(coord_l, coord_c);
                break;

            case 'p':
                afficher_pdt(coord_l, coord_c);
                break;

            case '0':
            default:
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, MARRON);
                break;
            }
        }
    }
    debug_update(game, joueur);
}

void afficher_marche(int j)
{
    int l, c;

    if (j == 0)
    {
        l = MARCHE_L;
        c = MARCHE_C;
        dessiner_rectangle(l - 5, c - 2, 93, 36, GRIS);
        dessiner_rectangle(l-4, c-2, 91, 34, CYAN);
    }
    else
    {
        l = MARCHE2_L;
        c = MARCHE2_C;
        dessiner_rectangle(l - 5, c - 4, 93, 36, GRIS);
        dessiner_rectangle(l-4, c-2, 91, 34, ROSE);
    }

	afficher_carotte(l, c);
	afficher_aubergine(l + 17, c);
	afficher_tomate(l + 34, c);
	afficher_brocolis(l + 51, c);
	afficher_pdt(l + 68, c);
}

void afficher_score(S_jeu* game, S_joueur joueur[])
{
    int l = 3;
    int c = 13;

    dessiner_ligne_score(l, c, 45, GRIS_FONCE);//base

    dessiner_rectangle(l, c+(joueur[1].score * (6 + 4)), 3, 6, ROSE);//pion joueur 1
    dessiner_rectangle(l, c+(joueur[0].score * (6 + 4)), 3, 6, BLEU);//pion joueur 2

    debug_update(game, joueur);
}

void dessiner_ligne_score(int ligne, int colonne, int nombre, int couleur)
{
    int largeur_rect = 6;
    int hauteur_rect = 3;
    int espace = 4;

    for (int i = 0; i < nombre; i++)
    {
        int nouvelle_colonne = colonne + (i * (largeur_rect + espace));

        dessiner_rectangle(ligne, nouvelle_colonne, hauteur_rect, largeur_rect, couleur);
    }
}

void afficher_haie(S_jeu* game, S_joueur joueur[])
{
    debug_update(game, joueur);
    afficher_trampoline(game, joueur);
    int l = HAIE_L;
    int c = HAIE_C;

    int nb_lignes = 5;

    int l_case = 15;
    int c_case = 30;

    int espace_ligne = 2;


    for (int lig = 0; lig < nb_lignes; lig++)
    {

        int coord_l = l + (lig * (l_case + espace_ligne));
        int coord_c = c;

        char case_actuelle = game->haie[lig];

        switch (case_actuelle)
        {
        case 'C':
            afficher_double_carotte(coord_l, coord_c);
            break;
        case 'T':
            afficher_double_tomate(coord_l, coord_c);
            break;
        case 'B':
            afficher_double_brocolis(coord_l, coord_c);
            break;
        case 'A':
            afficher_double_aubergine(coord_l, coord_c);
            break;
        case 'P':
            afficher_double_pdt(coord_l, coord_c);
            break;
        case '0':
        default:
            dessiner_rectangle(coord_l, coord_c, l_case, c_case, MARRON);
            break;
        }
    }
}

void afficher_trampoline(S_jeu* game, S_joueur joueur[])
{
    debug_update(game, joueur);
    int l = 108;
    int c = HAIE_C;

    int nb_lignes = 1;

    int l_case = 15;
    int c_case = 30;

    int espace_ligne = 2;


    for (int lig = 0; lig < nb_lignes; lig++)
    {

        int coord_l = l + (lig * (l_case + espace_ligne));
        int coord_c = c;

        char case_actuelle = game->pioche[game->nbr_pioches - 1];

        switch (case_actuelle)
        {
        case 'C':
            afficher_double_carotte(coord_l, coord_c);
            break;
        case 'T':
            afficher_double_tomate(coord_l, coord_c);
            break;
        case 'B':
            afficher_double_brocolis(coord_l, coord_c);
            break;
        case 'A':
            afficher_double_aubergine(coord_l, coord_c);
            break;
        case 'P':
            afficher_double_pdt(coord_l, coord_c);
            break;
        case '0':
        default:
            dessiner_rectangle(coord_l, coord_c, l_case, c_case, MARRON);
            break;
        }
    }
}

int afficher_menu(int j)
{
    int l;
    int c;

    if (j == 0)
    {
        l = MENU_L;
        c = MENU1_C;
    }
    else
    {
        l = MENU_L;
        c = MENU2_C;
    }

    afficher_case(l, c, 2, BEIGE);


//===panier===
    dessiner_rectangle(l + 1, c + 11, 1, 8, MARRON);

    dessiner_rectangle(l + 2, c + 9, 1, 2, MARRON);
    dessiner_rectangle(l + 2, c + 19, 1, 2, MARRON);

    dessiner_rectangle(l + 3, c + 8, 1, 1, MARRON);
    dessiner_rectangle(l + 3, c + 21, 1, 1, MARRON);

    dessiner_rectangle(l + 4, c + 7, 1, 1, MARRON);
    dessiner_rectangle(l + 4, c + 22, 1, 1, MARRON);

    dessiner_rectangle(l + 5, c + 6, 1, 1, MARRON);
    dessiner_rectangle(l + 5, c + 23, 1, 1, MARRON);
    dessiner_rectangle(l + 6, c + 6, 1, 2, MARRON);
    dessiner_rectangle(l + 6, c + 22, 1, 2, MARRON);

    dessiner_rectangle(l + 7, c + 4, 1, 4, MARRON);
    dessiner_rectangle(l + 7, c + 22, 1, 4, MARRON);

    dessiner_rectangle(l + 8, c + 4, 1, 22, MARRON);

    dessiner_rectangle(l + 9, c + 6, 2, 18, MARRON);
    dessiner_rectangle(l + 11, c + 8, 1, 14, MARRON);
    dessiner_rectangle(l + 12, c + 10, 1, 10, MARRON);
    dessiner_rectangle(l + 13, c + 12, 1, 6, MARRON);


//===pelle===
    dessiner_rectangle(l + 3,  c +34 + 25, 1, 2, GRIS_FONCE);

    dessiner_rectangle(l +  5, c +34 + 19, 2, 4, MARRON);
    dessiner_rectangle(l +  6, c +34 + 16, 2, 4, MARRON);
    dessiner_rectangle(l +  7, c +34 + 13, 2, 4, MARRON);

    dessiner_rectangle(l +  8, c +34 + 8, 2, 6, GRIS);
    dessiner_rectangle(l +  9, c +34 + 6, 3, 8, GRIS);
    dessiner_rectangle(l + 11, c +34 + 4, 2, 8, GRIS);
    dessiner_rectangle(l + 12, c +34 + 6, 1, 4, GRIS);

    dessiner_rectangle(l + 4, c +34 + 21, 2, 4, MARRON);

    l = l+6;
    c = c - 45;

    color(0, 14);
    positionner_curseur(l, c);
    printf(" __   ___  __   __        ___  ___  __  ");
    positionner_curseur(l + 1, c);
    printf("|__) |__  /  ` /  \\ |      |  |__  |__) ");
    positionner_curseur(l + 2, c);
    printf("|  \\ |___ \\__, \\__/ |___   |  |___ |  \\ ");
    positionner_curseur(l + 3, c);
    printf("                                        ");

    c = c + 45+69;

    positionner_curseur(l, c);
    printf(" __                 ___  ___  __  ");
    positionner_curseur(l + 1, c);
    printf("|__) |     /\\  |\\ |  |  |__  |__) ");
    positionner_curseur(l + 2, c);
    printf("|    |___ /~~\\ | \\|  |  |___ |  \\ ");
    positionner_curseur(l + 3, c);
    printf("                                  ");

    l = l + 11;
    c = c - 72;

    positionner_curseur(l, c);
    printf("   _                                                                 ");
    positionner_curseur(l + 1, c);
    printf("  /  | o  _.      _  ._    _.     _   _   |  _.    _  _      ._ o  _ ");
    positionner_curseur(l + 2, c);
    printf("  \\_ | | (_| |_| (/_ |    (_| \\/ (/_ (_   | (_|   _> (_) |_| |  | _> ");
    positionner_curseur(l + 3, c);
    printf("           |                                                         ");

    if (j == 0)
    {
        l = MENU_L;
        c = MENU1_C;
    }
    else
    {
        l = MENU_L;
        c = MENU2_C;
    }
    return (clique_plateau(1, 2, l, c));
}


void effacer_menu(int t)
{

    if (t == 0)
    {
        dessiner_rectangle(MENU_L, MENU1_C - 45, 16, 150, NOIR);
        dessiner_rectangle(MENU_L, MENU2_C - 45, 16, 150, NOIR);
    }
    else
    {
        dessiner_rectangle(MENU_L, MENU1_C - 45, 22, 150, NOIR);
        dessiner_rectangle(MENU_L, MENU2_C - 45, 22, 150, NOIR);
    }


}

void garder_case(int p)
{

    if(p!=1)
    {
        afficher_case(ROT, PLAT_C, 1, NOIR);
        afficher_case(ROT, PLAT2_C + 34, 1, NOIR);
    }
    if (p != 2)
    {
        afficher_case(ROT, PLAT_C+34, 1, NOIR);
        afficher_case(ROT, PLAT2_C+34 + 34, 1, NOIR);
    }
    if (p != 3)
    {
        afficher_case(ROT, PLAT_C + 68, 1, NOIR);
        afficher_case(ROT, PLAT2_C + 68 + 34, 1, NOIR);
    }
    if (p != 4)
    {
        afficher_case(ROT, PLAT_C + 102, 1, NOIR);
        afficher_case(ROT, PLAT2_C + 102 + 34, 1, NOIR);
    }

}

//----------MOTIF----------

void afficher_case(int l, int c, int nb, int couleur)
{
    int nb_lignes = 1;//taille plat
    int nb_cols = nb;

    int l_case = 15; // taille case
    int c_case = 30;

    int espace_ligne = 2;
    int espace_colonne = 4;

    for (int lig = 0; lig < nb_lignes; lig++)
    {
        for (int col = 0; col < nb_cols; col++)
        {
            // Calcul des coord
            int coord_l = l + (lig * (l_case + espace_ligne));
            int coord_c = c + (col * (c_case + espace_colonne));
            dessiner_rectangle(coord_l, coord_c, l_case, c_case, couleur);
        }
    }
}

void motif_carotte(int l, int c)
{
    afficher_case(l, c, 2, BEIGE);

    //motif 1 : diagonale de 2 carottes
    dessiner_rectangle(l+2, c+4, 4, 8, GRIS);
    dessiner_rectangle(l + 6, c + 12, 4, 8, ORANGE);

    //motif 2 : diagonale de 4 carottes
    c = c + 30;
    dessiner_rectangle(l + 2, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 5, c + 12, 3, 6, ORANGE);
    dessiner_rectangle(l + 8, c + 18, 3, 6, ORANGE);
    dessiner_rectangle(l + 11, c + 24, 3, 6, ORANGE);

}

void rot1_carotte(int l, int c)
{
    afficher_case(l, c, 2, BEIGE);

    //rot 1
    dessiner_rectangle(l + 2, c + 4, 4, 8, GRIS);
    dessiner_rectangle(l + 6, c + 12, 4, 8, ORANGE);

    //rot 2
    c = c + 35;
    dessiner_rectangle(l + 2, c + 12, 4, 8, GRIS);
    dessiner_rectangle(l + 6, c + 4, 4, 8, ORANGE);

}

void rot2_carotte(int l, int c)
{
    afficher_case(l, c, 2, BEIGE);

    //rot 1
    c = c-2;
    dessiner_rectangle(l + 2, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 5, c + 12, 3, 6, ORANGE);
    dessiner_rectangle(l + 8, c + 18, 3, 6, ORANGE);
    dessiner_rectangle(l + 11, c + 24, 3, 6, ORANGE);

    //rot 2
    c = c + 32;
    dessiner_rectangle(l + 2, c + 24, 3, 6, GRIS);
    dessiner_rectangle(l + 5, c + 18, 3, 6, ORANGE);
    dessiner_rectangle(l + 8, c + 12, 3, 6, ORANGE);
    dessiner_rectangle(l + 11, c + 6, 3, 6, ORANGE);

}


void motif_aubergine(int l, int c)
{

    afficher_case(l, c, 3, BEIGE);

    //motif 1 :
    dessiner_rectangle(l + 5, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 5, c + 16, 4, 8, VIOLET);

    //motif 2 :
    c = c + 34;
    dessiner_rectangle(l + 3, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 3, c + 16, 4, 8, VIOLET);
    dessiner_rectangle(l + 8, c + 6, 4, 8, VIOLET);
    dessiner_rectangle(l + 8, c + 16, 4, 8, VIOLET);

    //motif 3 :
    c = c + 32;
    dessiner_rectangle(l + 4, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 4, c + 14, 3, 6, VIOLET);
    dessiner_rectangle(l + 4, c + 22, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 6, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 14, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 22, 3, 6, VIOLET);


}

void rot1_aubergine(int l, int c)
{

    afficher_case(l, c, 2, BEIGE);

    //rot 1 :
    dessiner_rectangle(l + 5, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 5, c + 16, 4, 8, VIOLET);

    //rot 2 :
    c = c + 36;
    dessiner_rectangle(l + 3, c + 9, 4, 8, GRIS);
    dessiner_rectangle(l + 8, c + 9, 4, 8, VIOLET);
}

void rot3_aubergine(int l, int c)
{

    afficher_case(l, c, 2, BEIGE);

    //rot 1 :
    c = c-2;
    dessiner_rectangle(l + 4, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 4, c + 14, 3, 6, VIOLET);
    dessiner_rectangle(l + 4, c + 22, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 6, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 14, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 22, 3, 6, VIOLET);

    //rot 2 :
    c = c + 36;
    // Ligne 1
    dessiner_rectangle(l + 2, c + 8, 3, 6, GRIS);
    dessiner_rectangle(l + 2, c + 16, 3, 6, VIOLET);
    dessiner_rectangle(l + 6, c + 8, 3, 6, VIOLET);
    dessiner_rectangle(l + 6, c + 16, 3, 6, VIOLET);
    dessiner_rectangle(l + 10, c + 8, 3, 6, VIOLET);
    dessiner_rectangle(l + 10, c + 16, 3, 6, VIOLET);

}

void motif_tomate(int l, int c)
{

    afficher_case(l, c, 3, BEIGE);

    //motif 1 :
    dessiner_rectangle(l + 4, c + 9, 6, 12, ROUGE);

    //motif 2 :
    c = c + 34;
    dessiner_rectangle(l + 7, c + 5, 4, 8, GRIS);
    dessiner_rectangle(l + 2, c + 11, 4, 8, ROUGE);
    dessiner_rectangle(l + 7, c + 18, 4, 8, ROUGE);

    //motif 3 :
    c = c + 33;
    dessiner_rectangle(l + 6, c + 6, 2, 4, ROUGE);
    dessiner_rectangle(l + 8, c + 10, 2, 4, ROUGE);
    dessiner_rectangle(l + 6, c + 14, 2, 4, GRIS);
    dessiner_rectangle(l + 8, c + 18, 2, 4, ROUGE);
    dessiner_rectangle(l + 6, c + 22, 2, 4, ROUGE);

}

void rot2_tomate(int l, int c)
{

    afficher_case(l, c, 4, BEIGE);

    //rot 1 :
    dessiner_rectangle(l + 7, c + 5, 4, 8, ROUGE);
    dessiner_rectangle(l + 2, c + 11, 4, 8, GRIS);
    dessiner_rectangle(l + 7, c + 18, 4, 8, ROUGE);

    //rot 2 :
    c = c + 36;
    dessiner_rectangle(l + 2, c + 6, 4, 8, ROUGE);
    dessiner_rectangle(l + 8, c + 6, 4, 8, ROUGE);
    dessiner_rectangle(l + 5, c + 16, 4, 8, GRIS);

    //rot 3 :
    c = c + 32;
    dessiner_rectangle(l + 2+1, c + 3, 4, 8, ROUGE);
    dessiner_rectangle(l + 2+1, c + 19, 4, 8, ROUGE);
    dessiner_rectangle(l + 7+1, c + 11, 4, 8, GRIS);

    //rot 4 :
    c = c + 36;
    dessiner_rectangle(l + 2, c + 14, 4, 8, ROUGE);
    dessiner_rectangle(l + 8, c + 14, 4, 8, ROUGE);
    dessiner_rectangle(l + 5, c + 4, 4, 8, GRIS);

}

void rot3_tomate(int l, int c)
{

    afficher_case(l, c, 4, BEIGE);

    //rot 1 :
    c = c-1;
    dessiner_rectangle(l + 6, c + 6, 2, 4, ROUGE);
    dessiner_rectangle(l + 8, c + 10, 2, 4, ROUGE);
    dessiner_rectangle(l + 6, c + 14, 2, 4, GRIS);
    dessiner_rectangle(l + 8, c + 18, 2, 4, ROUGE);
    dessiner_rectangle(l + 6, c + 22, 2, 4, ROUGE);

    //rot 2 :
    c = c + 33;
    dessiner_rectangle(l + 2, c + 16, 2, 4, ROUGE); // ex-Haut Gauche, passe en Haut Droite
    dessiner_rectangle(l + 4, c + 12, 2, 4, ROUGE);
    dessiner_rectangle(l + 6, c + 16, 2, 4, GRIS);  // Pointe Centrale Droite
    dessiner_rectangle(l + 8, c + 12, 2, 4, ROUGE);
    dessiner_rectangle(l + 10, c + 16, 2, 4, ROUGE); // ex-Haut Droite, passe en Bas Droite


    //rot 3 :
    c = c + 35;
    dessiner_rectangle(l + 8, c + 6, 2, 4, ROUGE); // ex-Haut Droite, passe en Bas Gauche
    dessiner_rectangle(l + 6, c + 10, 2, 4, ROUGE);
    dessiner_rectangle(l + 8, c + 14, 2, 4, GRIS);  // Pointe Centrale Basse
    dessiner_rectangle(l + 6, c + 18, 2, 4, ROUGE);
    dessiner_rectangle(l + 8, c + 22, 2, 4, ROUGE); // ex-Haut Gauche, passe en Bas Droite


    //rot 4 :
    c = c + 34;
    dessiner_rectangle(l + 2, c + 12, 2, 4, ROUGE); // ex-Haut Droite, passe en Haut Gauche
    dessiner_rectangle(l + 4, c + 16, 2, 4, ROUGE);
    dessiner_rectangle(l + 6, c + 12, 2, 4, GRIS);  // Pointe Centrale Gauche
    dessiner_rectangle(l + 8, c + 16, 2, 4, ROUGE);
    dessiner_rectangle(l + 10, c + 12, 2, 4, ROUGE); // ex-Haut Gauche, passe en Bas Gauche
}

void motif_brocoli(int l, int c)
{

    afficher_case(l, c, 3, BEIGE);

    //motif 1 :
    dessiner_rectangle(l + 4, c + 9, 6, 12, VERT);

    //motif 2 :
    c = c + 34;
    dessiner_rectangle(l + 3, c + 6, 4, 8, VERT);
    dessiner_rectangle(l + 8, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 8, c + 16, 4, 8, VERT);

    //motif 3 :
    c = c + 32;
    dessiner_rectangle(l + 2, c + 14, 3, 6, VERT);
    dessiner_rectangle(l + 4+2, c + 6, 3, 6, VERT);
    dessiner_rectangle(l + 4+2, c + 14, 3, 6, GRIS);
    dessiner_rectangle(l + 4+2, c + 22, 3, 6, VERT);
    dessiner_rectangle(l + 8+2, c + 14, 3, 6, VERT);
}

void rot2_brocoli(int l, int c)
{

    afficher_case(l, c, 4, BEIGE);

    //rot 1 :
    dessiner_rectangle(l + 3, c + 6, 4, 8, VERT);
    dessiner_rectangle(l + 8, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 8, c + 16, 4, 8, VERT);

    //rot 2 :
    c = c + 34;
    dessiner_rectangle(l + 3, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 3, c + 16, 4, 8, VERT);
    dessiner_rectangle(l + 8, c + 6, 4, 8, VERT);


    //rot 3 :
    c = c + 34;
    dessiner_rectangle(l + 3, c + 6, 4, 8, VERT);
    dessiner_rectangle(l + 3, c + 16, 4, 8, GRIS);
    dessiner_rectangle(l + 8, c + 16, 4, 8, VERT);

    //rot 4 :
    c = c + 34;
    dessiner_rectangle(l + 3, c + 16, 4, 8, VERT);
    dessiner_rectangle(l + 8, c + 6, 4, 8, VERT);
    dessiner_rectangle(l + 8, c + 16, 4, 8, GRIS);

}

void motif_patate(int l, int c)
{

    afficher_case(l, c, 3, BEIGE);

    //motif 1 :
    dessiner_rectangle(l + 4, c + 9, 6, 12, OR);

    //motif 2 :
    c = c + 32;
    dessiner_rectangle(l + 6, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 6, c + 14, 3, 6, OR);
    dessiner_rectangle(l + 6, c + 22, 3, 6, OR);

    //motif 3 :
    c = c + 34;
    dessiner_rectangle(l + 4, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 4, c + 14, 3, 6, OR);
    dessiner_rectangle(l + 4, c + 22, 3, 6, OR);
    dessiner_rectangle(l + 8, c + 6, 3, 6, OR);
    dessiner_rectangle(l + 8, c + 22, 3, 6, OR);

}

void rot2_patate(int l, int c)
{

    afficher_case(l, c, 2, BEIGE);

    //rot 1 :
    c = c - 2;
    dessiner_rectangle(l + 6, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 6, c + 14, 3, 6, OR);
    dessiner_rectangle(l + 6, c + 22, 3, 6, OR);

    //rot 2 :
    c = c + 34;
    dessiner_rectangle(l + 2, c + 14, 3, 6, GRIS);
    dessiner_rectangle(l + 6, c + 14, 3, 6, OR);
    dessiner_rectangle(l + 10, c + 14, 3, 6, OR);

}

void rot3_patate(int l, int c)
{

    afficher_case(l, c, 4, BEIGE);

    //Rot 1 :
    c = c - 2;
    dessiner_rectangle(l + 4, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 4, c + 14, 3, 6, OR);
    dessiner_rectangle(l + 4, c + 22, 3, 6, OR);
    dessiner_rectangle(l + 8, c + 6, 3, 6, OR);
    dessiner_rectangle(l + 8, c + 22, 3, 6, OR);

    //rot 2 :
    c = c + 34;
    dessiner_rectangle(l + 2, c + 18, 3, 6, OR);
    dessiner_rectangle(l + 6, c + 18, 3, 6, OR);
    dessiner_rectangle(l + 10, c + 18, 3, 6, OR);
    dessiner_rectangle(l + 2, c + 10, 3, 6, GRIS);
    dessiner_rectangle(l + 10, c + 10, 3, 6, OR);

    //rot 3 :
    c = c + 34;
    dessiner_rectangle(l + 8, c + 22, 3, 6, OR);
    dessiner_rectangle(l + 8, c + 14, 3, 6, OR);
    dessiner_rectangle(l + 8, c + 6, 3, 6, OR);
    dessiner_rectangle(l + 4, c + 22, 3, 6, OR);
    dessiner_rectangle(l + 4, c + 6, 3, 6, GRIS);

    //rot 4 :
    c = c + 34;
    dessiner_rectangle(l + 10, c + 10, 3, 6, OR);
    dessiner_rectangle(l + 6, c + 10, 3, 6, OR);
    dessiner_rectangle(l + 2, c + 10, 3, 6, GRIS);
    dessiner_rectangle(l + 10, c + 18, 3, 6, OR);
    dessiner_rectangle(l + 2, c + 18, 3, 6, OR);
}

//=====Case Légume=====
void afficher_carotte(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 3, colonne + 16, 4, 3, 0x00FF00);
    dessiner_rectangle(ligne + 5, colonne + 12, 4, 4, 0xFFA500);
    dessiner_rectangle(ligne + 7, colonne + 10, 4, 4, 0xFFA500);
}
void afficher_double_carotte(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 3, colonne + 12, 4, 3, 0x00FF00);
    dessiner_rectangle(ligne + 5, colonne + 8, 4, 4, 0xFFA500);
    dessiner_rectangle(ligne + 7, colonne + 6, 4, 4, 0xFFA500);
    dessiner_rectangle(ligne + 4, colonne + 20, 4, 3, 0x00FF00);
    dessiner_rectangle(ligne + 6, colonne + 16, 4, 4, 0xFFA500);
    dessiner_rectangle(ligne + 8, colonne + 14, 4, 4, 0xFFA500);

}
void afficher_pdt(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 7, colonne + 12, 3, 5, 0xE7AC46);
    dessiner_rectangle(ligne + 6, colonne + 10, 3, 9, 0xE7AC46);
    dessiner_rectangle(ligne + 5, colonne + 10, 3, 9, 0xE7AC46);
    dessiner_rectangle(ligne + 4, colonne + 12, 3, 5, 0xE7AC46);
}
void afficher_double_pdt(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    colonne = colonne + 1;
    dessiner_rectangle(ligne + 7, colonne + 7, 3, 5, 0xE7AC46);
    dessiner_rectangle(ligne + 6, colonne + 5, 3, 9, 0xE7AC46);
    dessiner_rectangle(ligne + 5, colonne + 5, 3, 9, 0xE7AC46);
    dessiner_rectangle(ligne + 4, colonne + 7, 3, 5, 0xE7AC46);
    dessiner_rectangle(ligne + 8, colonne + 17, 3, 5, 0xE7AC46);
    dessiner_rectangle(ligne + 7, colonne + 15, 3, 9, 0xE7AC46);
    dessiner_rectangle(ligne + 6, colonne + 15, 3, 9, 0xE7AC46);
    dessiner_rectangle(ligne + 5, colonne + 17, 3, 5, 0xE7AC46);
}

void afficher_tomate(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 8, colonne + 10, 2, 10, 0xC21D17);
    dessiner_rectangle(ligne + 7, colonne + 8, 2, 14, 0xC21D17);
    dessiner_rectangle(ligne + 6, colonne + 8, 2, 14, 0xC21D17);
    dessiner_rectangle(ligne + 5, colonne + 10, 2, 10, 0xC21D17);
}
void afficher_double_tomate(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 6, colonne + 5, 2, 10, 0xC21D17);
    dessiner_rectangle(ligne + 5, colonne + 3, 2, 14, 0xC21D17);
    dessiner_rectangle(ligne + 4, colonne + 3, 2, 14, 0xC21D17);
    dessiner_rectangle(ligne + 3, colonne + 5, 2, 10, 0xC21D17);
    dessiner_rectangle(ligne + 11, colonne + 16, 2, 10, 0xC21D17);
    dessiner_rectangle(ligne + 10, colonne + 14, 2, 14, 0xC21D17);
    dessiner_rectangle(ligne + 9, colonne + 14, 2, 14, 0xC21D17);
    dessiner_rectangle(ligne + 8, colonne + 16, 2, 10, 0xC21D17);
}
void afficher_aubergine(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 3, colonne + 16, 4, 3, 0x168A12);
    dessiner_rectangle(ligne + 5, colonne + 12, 4, 5, 0x261136);
    dessiner_rectangle(ligne + 7, colonne + 10, 4, 5, 0x261136);
}
void afficher_double_aubergine(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    dessiner_rectangle(ligne + 3, colonne + 12, 4, 3, 0x168A12);
    dessiner_rectangle(ligne + 5, colonne + 8, 4, 5, 0x261136);
    dessiner_rectangle(ligne + 7, colonne + 6, 4, 5, 0x261136);
    dessiner_rectangle(ligne + 4, colonne + 20, 4, 3, 0x168A12);
    dessiner_rectangle(ligne + 6, colonne + 16, 4, 5, 0x261136);
    dessiner_rectangle(ligne + 8, colonne + 14, 4, 5, 0x261136);
}
void afficher_brocolis(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    colonne = colonne + 2;
    dessiner_rectangle(ligne + 4, colonne + 14, 4, 4, 0x168A12);
    dessiner_rectangle(ligne + 4, colonne + 9, 4, 4, 0x168A12);
    dessiner_rectangle(ligne + 5, colonne + 11, 4, 5, 0x0E4512);
    dessiner_rectangle(ligne + 6, colonne + 11, 4, 5, 0x0E4512);
}
void afficher_double_brocolis(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne, 15, 30, 0x541F13);
    colonne = colonne + 1;
    ligne = ligne + 1;
    dessiner_rectangle(ligne + 2, colonne + 9, 4, 4, 0x168A12);
    dessiner_rectangle(ligne + 2, colonne + 4, 4, 4, 0x168A12);
    dessiner_rectangle(ligne + 3, colonne + 6, 4, 5, 0x0E4512);
    dessiner_rectangle(ligne + 4, colonne + 6, 4, 5, 0x0E4512);
    dessiner_rectangle(ligne + 5, colonne + 21, 4, 4, 0x168A12);
    dessiner_rectangle(ligne + 5, colonne + 16, 4, 4, 0x168A12);
    dessiner_rectangle(ligne + 6, colonne + 18, 4, 5, 0x0E4512);
    dessiner_rectangle(ligne + 7, colonne + 18, 4, 5, 0x0E4512);
}


//========================================================================================================================================================================Fonction base affichage=========================================================================================================================================================================

void dessine_pixel_hex(int x, int y, int hex_couleur)
{
    // extrait les composantes R, G, B du code hexadécimal
    int r = (hex_couleur >> 16) & 0xFF;
    int g = (hex_couleur >> 8) & 0xFF;
    int b = hex_couleur & 0xFF;

    positionner_curseur(x, y);
    // Print espace avec le fond coloré en RGB
    printf("\x1b[48;2;%d;%d;%dm \x1b[0m", r, g, b);
}

void dessiner_rectangle(int x, int y, int longueur, int hauteur, int hex_couleur)
{
    for (int j = 0; j < hauteur; j++)
    {
        for (int i = 0; i < longueur; i++)
        {
            dessine_pixel_hex(x + i, y + j, hex_couleur);
        }
    }
}

void affichage_caractere_speciaux()
{
    printf("%c\n\n", 218);
    printf("%c\n\n", 196);
    printf("%c\n\n", 191);
    printf("%c\n\n", 179);
    printf("%c\n\n", 195);
    printf("%c\n\n", 180);
    printf("%c\n\n", 192);
    printf("%c\n\n", 217);
}

void color(int couleurDuTexte, int couleurDuFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond * 16 + couleurDuTexte);
}

//==========================================================================================================================================================================Fonction de base==========================================================================================================================================================================


void plein_ecran(int s)
{
    Sleep(100);
    // Basculer en plein écran
    keybd_event(VK_MENU, 0x38, 0, 0); // Appuie sur ALT
    keybd_event(VK_RETURN, 0x1C, 0, 0); // Appuie sur ENTREE
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0); // Relâche ENTREE
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Relâche ALT

    // Attendre un court instant pour que le mode plein écran s'active
    Sleep(500);

    // Appliquer un zoom (CTRL + '-')
    for (int i = 0; i < s; i++)
    {
        keybd_event(VK_CONTROL, 0x1D, 0, 0); // Appuie sur CTRL
        keybd_event(VK_SUBTRACT, 0x4A, 0, 0); // Appuie sur '-'
        keybd_event(VK_SUBTRACT, 0x4A, KEYEVENTF_KEYUP, 0); // Relâche '-'
        keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_KEYUP, 0); // Relâche CTRL

        Sleep(100); // Petite pause entre les actions
    }
}

void positionner_curseur(int ligne, int colonne)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X = colonne;// numéro de la colonne
    pos.Y = ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}


void cacher_curseur()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


//==========================================================================================================================================================================Fonction DEBUG==========================================================================================================================================================================

//aide pour positioner
void afficher_grillage_ligne(int ligne)
{
    positionner_curseur(ligne, 0);
    for (int j = 0; j < 48; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            color(0, i);
            printf("%d", i);
        }
    }
}

void afficher_grillage_colonne(int colonne)
{
    int k = 0;
    for (int j = 0; j < 13; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            positionner_curseur(k, colonne);
            color(0, i);
            printf("%d", i);
            k++;
        }
    }
}


void debug_afficher_matrice(S_joueur p, int l, int c)
{
    int i, j;
    positionner_curseur(l, c);
    color(15, 0);
    // Affichage des données
    for (i = 0; i < 5; i++)
    {
        positionner_curseur(l+i, c);

        for (j = 0; j < 5; j++)
        {
            printf("%c ", p.plat[i][j]);
        }
    }
    // Affichage du score
    positionner_curseur(l + 7, c);
    printf("Score : %d",p.score);
}

void debug_afficher_pioche(S_jeu *game, int l, int c)
{
    int i;
    positionner_curseur(l, c);
    color(15, 0);
    printf("Pioche : ");

    // Utilisation de game-> pour accéder aux membres de la structure
    for (i = 0; i < game->nbr_pioches; i++)
    {
        printf("%c ", game->pioche[i]);
    }

    printf("  nbr_pioches : %d   ", game->nbr_pioches);
}

void debug_afficher_haie(S_jeu *game, int l, int c)
{
    int i;
    color(15, 0);
    for (i = 0; i < 5; i++)
    {
        positionner_curseur(l + i, c);
        printf("%c ", game->haie[i]);
    }
}

void debug_update(S_jeu *game, S_joueur joueur[])
{
    if (debug_state == 1)
    {
        debug_afficher_matrice(joueur[0], DEBUG_J1_L, DEBUG_J1_C);
        debug_afficher_matrice(joueur[1], DEBUG_J2_L, DEBUG_J2_C);

        debug_afficher_pioche(game, DEBUG_J1_L + 9, DEBUG_J1_C);

        debug_afficher_haie(game, DEBUG_J1_L, DEBUG_J1_C + 14);

        positionner_curseur(DEBUG_J1_L + 11, DEBUG_J1_C);
        printf("Tour : %d", game->nbr_tour);
        positionner_curseur(DEBUG_J1_L + 13, DEBUG_J1_C);
        printf("Joueur courant : %d", pair(game->nbr_tour));
        printf("  Joueur adverse : %d", impair(game->nbr_tour));
    }
}

//
