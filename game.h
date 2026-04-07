#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "affichage.h"

#ifndef PLATEAU_H
#define PLATEAU_H


//====================================================================================Structure du jeu===============================================================================
struct plateau
{
    char plat[5][5];
	int score;//score du joueur lors de la récolte
};
typedef struct plateau S_plateau;

extern S_plateau plateau[2];
extern char pioche[60];
extern char haie[5];
extern int nbr_pioches;



void initialisation_plateau(S_plateau* plat);
//void afficher_plateau(S_plateau* plat);


//====================================================================================Def des fonctions===============================================================================


//=====Initialisation=====
void initialisation_pioche(char *p, int *nbr);
void initialiser_haie(char h[]);
void initialisation_plateau(S_plateau* p);

//=====Fonction de jeu=====
void melanger_pioche(char* pioche, int* nbr_pioche);
void deplacer_haie_vers_plateau(char haie[], char plat[], int h, int p);
void remplir_haie(char h[], char* pioche, int* nbr_pioches);

#endif
