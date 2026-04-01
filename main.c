#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====include=====
#include "affichage.h"
#include "game.h"

int main()
{
//==============================================================ATTENTION==============================================================

plein_ecran(3);// mettre 3 pour de la 4k et 4 pour de la 1080p

//=========================================================|
debug = 0;//mettre à 1 pour activer les fonctions de debug |
//=========================================================|


//=====initialisation de base=====
cadre_ecran();



S_plateau J1;
S_plateau J2;

initialisation_plateau(&J1);
initialisation_plateau(&J2);







//==============================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(0);
afficher_grillage_colonne(0);

//====Data jeu=====
debug_afficher_matrice(&J1, DEBUG_J1_X, DEBUG_J1_Y);
debug_afficher_matrice(&J2, DEBUG_J2_X, DEBUG_J2_Y);

positionner_curseur(85, 0);
    return 0;
}
