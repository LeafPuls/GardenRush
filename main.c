#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====include=====
#include "affichage.h"
#include "game.h"

int main()
{

//=====initialisation de base=====
plein_ecran(3);// mettre 3 pour de la 4k et 4 pour de la 1080p
cadre_ecran();
afficher_plateau();

//=====Tableau data=====
char plat1[5][5];//joueur gauche
char plat2[5][5];//joueur droit



//==============================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(0);
afficher_grillage_colonne(0);

//====Data jeu=====

    return 0;
}
