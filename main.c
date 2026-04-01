#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====Header=====
#include "affichage.h"

int main()
{

//=====initialisation de base=====
plein_ecran(3);
dessiner_rectangle(11, 11, 10, 10, ROUGE);



//==============================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(10);
afficher_grillage_colonne(10);

//====Data jeu=====

    return 0;
}
