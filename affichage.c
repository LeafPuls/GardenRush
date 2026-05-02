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

//=====================================================================================================================================================================Initialisation AFFICHAGE==========================================================================================================================================================================

void initialisation_affichage(S_jeu* game, S_joueur joueur[], int j)
{
   
}


//==========================================================================================================================================================================Fonction AFFICHAGE==========================================================================================================================================================================

void afficher_plateau_joueur(S_jeu* game, S_joueur joueur[], int j)
{
    int l, c; // Ligne et colonne de départ du plateau

    if (j == 0) {
        l = PLAT_L;
        c = PLAT_C;
    }
    else {
        l = PLAT2_L;
        c = PLAT2_C;
    }

    int nb_lignes = 5;//taille
    int nb_cols = 5;

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
            char case_actuelle = joueur[j].plat[lig][col];

            switch (case_actuelle)
            {
                // ------ Carottes ------
            case 'C':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, ORANGE);
                break;
            case 'c':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, OR);
                break;

                // ------ Tomates ------
            case 'T':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, ROUGE);
                break;
            case 't':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, ROSE);
                break;

                // ------ Brocolis ------
            case 'B':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, VERT_FONCE);
                break;
            case 'b':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, VERT);
                break;

                // ------ Aubergines ------
            case 'A':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, VIOLET_FONCE);
                break;
            case 'a':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, VIOLET);
                break;

                // ------ Patates ------
            case 'P':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, JAUNE);
                break;
            case 'p':
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, BEIGE);
                break;

                // ------ Case Vide / Terre nue ------
            case '0':
            default:
                dessiner_rectangle(coord_l, coord_c, l_case, c_case, MARRON);
                break;
            }
        }
    }
}

void afficher_marche(int j) 
{
    int l, c;

    if (j == 0) {
        l = MARCHE_L;
        c = MARCHE_C;
        dessiner_rectangle(l-4, c-2, 91, 34, BLEU);
    }
    else {
        l = MARCHE2_L;
        c = MARCHE2_C;
        dessiner_rectangle(l-4, c-2, 91, 34, ROUGE);
    }

    int nb_lignes = 5;//taille plat
    int nb_cols = 1;

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
            dessiner_rectangle(coord_l, coord_c, l_case, c_case, BEIGE);
        }
    }
}

void afficher_score(S_jeu* game, S_joueur joueur[]) {
	int l = 2;
	int c = 10;

    dessiner_ligne_score(l, c, 45, GRIS);//base

	dessiner_rectangle(l, c+(joueur[1].score * (6 + 4)), 3, 6, ROSE);//pion joueur 1
    dessiner_rectangle(l, c+(joueur[0].score * (6 + 4)), 3, 6, BLEU);//pion joueur 2
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



//----------LEGUMES----------

void afficher_carotte(int ligne, int colonne)
{
    dessiner_rectangle(ligne, colonne + 4, 2, 1, VERT);
    dessiner_rectangle(ligne + 1, colonne + 2, 2, 2, ORANGE);
    dessiner_rectangle(ligne + 2, colonne, 2, 2, ORANGE);
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

void motif_carotte(int l, int c) {
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

void rot1_carotte(int l, int c) {
    afficher_case(l, c, 2, BEIGE);

    //rot 1 
    dessiner_rectangle(l + 2, c + 4, 4, 8, GRIS);
    dessiner_rectangle(l + 6, c + 12, 4, 8, ORANGE);

    //rot 2 
    c = c + 35;
    dessiner_rectangle(l + 2, c + 12, 4, 8, GRIS);
    dessiner_rectangle(l + 6, c + 4, 4, 8, ORANGE);

}

void rot2_carotte(int l, int c) {
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


void motif_aubergine(int l, int c) {
    afficher_case(l, c, 3, BEIGE);

    //motif 1 : diagonale de 2 aubergines
    dessiner_rectangle(l + 5, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 5, c + 16, 4, 8, VIOLET);

    //motif 2 : diagonale de 4 aubergines
    c = c + 34;
    dessiner_rectangle(l + 3, c + 6, 4, 8, GRIS);
    dessiner_rectangle(l + 3, c + 16, 4, 8, VIOLET);
    dessiner_rectangle(l + 8, c + 6, 4, 8, VIOLET);
    dessiner_rectangle(l + 8, c + 16, 4, 8, VIOLET);

    //motif 2 : diagonale de 4 aubergines
    c = c + 32;
    dessiner_rectangle(l + 4, c + 6, 3, 6, GRIS);
    dessiner_rectangle(l + 4, c + 14, 3, 6, VIOLET);
    dessiner_rectangle(l + 4, c + 22, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 6, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 14, 3, 6, VIOLET);
    dessiner_rectangle(l + 8, c + 22, 3, 6, VIOLET);


}

void rot1_aubergine(int l, int c) {

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
    for (int j = 0; j < 8; j++)
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

    }
}

