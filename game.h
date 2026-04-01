#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "affichage.h"

//Def de la structure
struct plateau
{
    char plat[5][5];
	int score;//score du joueur lors de la récolte
};
typedef struct plateau S_plateau;


void initialisation_plateau(S_plateau* plat);
//void afficher_plateau(S_plateau* plat);
