#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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








//=======Def AFFICHAGE=======
void cadre_ecran();
void afficher_plateau();
//=======


//=======Def outil affichage=======
void dessine_pixel_hex(int x, int y, int hex_couleur);//couleur en HEX
void dessiner_rectangle(int x, int y, int longueur, int hauteur, int hex_couleur);
//=======


//=======Def de base=======
void affichage_caractere_speciaux();
void color(int couleurDuTexte, int couleurDuFond);//couleur de base
void positionner_curseur(int ligne, int colonne);
void cacher_curseur();
void plein_ecran(int s);
//=======


//=======DEF DEBUG=======
void afficher_grillage_ligne(int ligne);//aide graphique pour positioner
void afficher_grillage_colonne(int colonne);//aide graphique pour positioner
//=======
