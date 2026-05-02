#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "game.h"

//======DEFINE HEX COULEUR=====
// Couleurs standards
#define NOIR          0x000000
#define BLANC         0xFFFFFF
#define GRIS          0x808080

// Couleurs
#define ROUGE         0xFF0000
#define ORANGE        0xFFA500
#define OR            0xFFD700
#define JAUNE         0xFFFF00
#define VERT          0x00FF00
#define VERT_FONCE    0x006400
#define BLEU          0x0000FF
#define BLEU_CIEL     0x87CEEB
#define CYAN          0x00FFFF
#define MAGENTA       0xFF00FF
#define ROSE          0xFFC0CB
#define MARRON        0x654321
#define BEIGE         0xE8D0AE

//=======Position jeux=======
#define PLAT_L 20
#define PLAT_C 40
#define PLAT2_L 20
#define PLAT2_C 350

//=======Position DEBUG=======
#define DEBUG_J1_L 120
#define DEBUG_J1_C 0
#define DEBUG_J2_L 120
#define DEBUG_J2_C 20

extern int debug_state;

//=======Def AFFICHAGE=======
void initialisation_affichage(S_jeu* game, S_joueur joueur[], int j);

void cadre_ecran();
void afficher_carotte(int ligne, int colonne);
void afficher_plateau_gauche(int  x, int y);
void afficher_plateau_droite(int x, int y);
void dessiner_case(int ligne, int colonne);
void dessiner_ligne_score(int ligne, int colonne, int nombre, int couleur);
void afficher_score(S_jeu* game, S_joueur joueur[]);
void afficher_parcelles_terre(int x_start, int y_start);
//=======


//=======Def outil affichage=======
void dessine_pixel_hex(int x, int y, int hex_couleur);//couleur en HEX
void dessiner_rectangle(int x, int y, int longueur, int hauteur, int hex_couleur);
void color(int couleurDuTexte, int couleurDuFond);//couleur de base
void affichage_caractere_speciaux();
//=======


//=======Def de base=======
void positionner_curseur(int ligne, int colonne);
void cacher_curseur();
void plein_ecran(int s);
//=======


//=======DEF DEBUG=======
void afficher_grillage_ligne(int ligne);//aide graphique pour positioner
void afficher_grillage_colonne(int colonne);//aide graphique pour positioner
void debug_afficher_matrice(S_joueur p, int l, int c);
void debug_afficher_pioche(S_jeu* game, int l, int c);
void debug_afficher_haie(S_jeu* game, int l, int c);
void debug_update(S_jeu* game, S_joueur joueur[]);
//=======
