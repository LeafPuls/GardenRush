#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "affichage.h"

#ifndef PLATEAU_H
#define PLATEAU_H


extern char pioche[60];
extern char haie[5];
extern int nbr_pioches;


//====================================================================================Def des fonctions===============================================================================


//=====Initialisation=====
void initialisation_pioche(char p[], int* nbr);
void initialiser_haie(char h[]);
void initialisation_plateau(S_joueur *p);

//=====Fonction de jeu=====
void melanger_pioche(char* pioche, int* nbr_pioche);
void deplacer_haie_vers_plateau(char haie[], char plat[], int h, int p);
void remplir_haie(char h[], char* pioche, int* nbr_pioches);

#endif
