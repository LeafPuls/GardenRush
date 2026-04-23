#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "affichage.h"

#ifndef PLATEAU_H
#define PLATEAU_H


//====================================================================================Def des fonctions===============================================================================


//=====Initialisation=====
void initialisation_plateau(S_joueur *joueur);
void initialisation_pioche(S_jeu *game);
void melanger_pioche(S_jeu *game);
void initialiser_haie(S_jeu *game);

//=====Fonction de jeu=====
void remplir_haie(S_jeu *game);
int deplacer_haie_vers_plateau(S_jeu* game, S_joueur joueur[], int j, int h, int l, int c);
char soustraire_legume(char leg);
int recolter(S_jeu* game, S_joueur joueur[], int j);

#endif
