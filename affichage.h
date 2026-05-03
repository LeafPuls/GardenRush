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
#define GRIS_FONCE    0x404040

// Couleurs
#define ROUGE         0xFF0000
#define ORANGE        0xFFA500
#define OR            0xFFD700
#define JAUNE         0xFFFF00
#define VERT          0x00FF00
#define VERT_FONCE    0x006400
#define VERT_NOIR     0x003200
#define BLEU          0x0000FF
#define BLEU_CIEL     0x87CEEB
#define CYAN          0x00E0FF
#define MAGENTA       0xFF00FF
#define ROSE          0xFFB0B5
#define MARRON        0x654321
#define BEIGE         0xE8D0AE
#define VIOLET        0xEE82EE
#define VIOLET_FONCE  0x800080

//=======Position jeux=======
#define PLAT_L 14
#define PLAT_C 42

#define PLAT2_L 14
#define PLAT2_C 266

#define HAIE_L 14
#define HAIE_C 222

#define MARCHE_L PLAT_L
#define MARCHE_C PLAT_C-39

#define MARCHE2_L PLAT_L
#define MARCHE2_C PLAT2_C+39+136

#define ROT 110

//=======Position DEBUG=======
#define DEBUG_J1_L 133
#define DEBUG_J1_C 0
#define DEBUG_J2_L 133
#define DEBUG_J2_C 20

extern int debug_state;

//=======Def AFFICHAGE=======
void initialisation_affichage();

void dessiner_ligne_score(int ligne, int colonne, int nombre, int couleur);
void afficher_plateau_joueur(S_jeu* game, S_joueur joueur[], int j);
void afficher_marche(int j);
void afficher_score(S_jeu* game, S_joueur joueur[]);
void afficher_case(int l, int c, int nb, int couleur);
void afficher_haie(S_jeu* game, S_joueur joueur[]);
void afficher_trampoline(S_jeu* game, S_joueur joueur[]);

void motif_carotte(int l, int c);
void rot1_carotte(int l, int c);
void rot2_carotte(int l, int c);

void motif_aubergine(int l, int c);
void rot1_aubergine(int l, int c);
void rot3_aubergine(int l, int c);

void motif_tomate(int l, int c);
void rot2_tomate(int l, int c);
void rot3_tomate(int l, int c);

void motif_brocoli(int l, int c);
void rot2_brocoli(int l, int c);

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
