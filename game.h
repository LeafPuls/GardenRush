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
void deplacer_haie_vers_plateau(S_jeu *p_game, S_joueur *p_joueur, int h, int lig, int col);

#endif
