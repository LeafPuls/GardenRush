#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "affichage.h"

//====================================================================================Structure du jeu===============================================================================
struct plateau
{
    char plat[5][5];
	int score;//score du joueur lors de la récolte
};
typedef struct plateau S_plateau;

char pioche[60];//pioche de base pour le jeu, elle contient les 60 légumes à piocher
int nbr_pioches;//nombre de légumes restant dans la pioche, elle diminue à chaque fois qu'on pioche un légume


void initialisation_plateau(S_plateau* plat);
//void afficher_plateau(S_plateau* plat);


//====================================================================================Def des fonctions===============================================================================

void initialisation_pioche();
void melanger_pioche(int* pioche, int nbr_pioche);
void initialisation_plateau(S_plateau* p);
void initialisation_pioche();
