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
S_plateau plateau[2];// 0=joueur 1 / 1=joueur 2

#endif

char pioche[60];//pioche de base pour le jeu, elle contient les 60 légumes à piocher
char haie[5];//haie de base pour le jeu, elle contient les 5 légumes à récolter au choix du joueur, elle se remplit à chaque fois qu'on pioche un légume
int nbr_pioches;//nombre de légumes restant dans la pioche, elle diminue à chaque fois qu'on pioche un légume


void initialisation_plateau(S_plateau* plat);
//void afficher_plateau(S_plateau* plat);


//====================================================================================Def des fonctions===============================================================================


//=====Initialisation=====
void initialisation_pioche();
void initialiser_haie(char h[]);
void initialisation_plateau(S_plateau* p);
void initialisation_pioche(char *p, int *nbr);

//=====Fonction de jeu=====
void melanger_pioche(char* pioche, int* nbr_pioche);
void deplacer_haie_vers_plateau(char haie[], char plat[], int h, int p);
void remplir_haie(char h[], char* pioche, int* nbr_pioches);
