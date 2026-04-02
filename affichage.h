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

//=======Position jeux=======
#define PLAT_L 15
#define PLAT_C 2

//=======Position DEBUG=======
#define DEBUG_J1_X 90
#define DEBUG_J1_Y 0
#define DEBUG_J2_X 90
#define DEBUG_J2_Y 20



//=======Def AFFICHAGE=======
int debug_state;//variable globale pour activer les fonctions de debug
void cadre_ecran();
void dessiner_plateau();
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
void debug_afficher_matrice(S_plateau* p, int x, int y);
void debug_update(int* j1, int* j2);
//=======