#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====include=====
#include "affichage.h"
#include "game.h"

int main()
{
//==============================================================ATTENTION==============================================================//
                                                                                                                                       //
plein_ecran(4);// mettre 3 pour de la 4k et 4 pour de la 1080p                                                                         //
                                                                                                                                       //
//================================================================================|                                                    //
debug_state = 1;//mettre à 1 pour activer les fonctions de debug 0 pour désactiver|                                                    //
//================================================================================|                                                    //
                                                                                                                                       //
//=====================================================================================================================================//




//==============================================================initialisation de base===========================================================

cadre_ecran();//permet de s'assurer qu'on voit tout le jeu pour éviter les bugs d'affichage

S_plateau J1;//création de la matrice de jeu pour le joueur 1
S_plateau J2;//création de la matrice de jeu pour le joueur 2

initialisation_plateau(&J1);//remplie les matrices pour tout mettre a zéro
initialisation_plateau(&J2);

dessiner_plateau();//affiche le fond du plateau de jeu qui ne s'actualise pas







//==============================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(0);
afficher_grillage_colonne(0);

//====Data jeu=====
//debug_afficher_matrice(&J1, DEBUG_J1_X, DEBUG_J1_Y);
//debug_afficher_matrice(&J2, DEBUG_J2_X, DEBUG_J2_Y);
//debug_update(&J1, &J2);//affiche toutes les fct de debug en meme temps 


positionner_curseur(100, 0);
    return 0;
}
