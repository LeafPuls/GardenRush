#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====include=====
#include "declaration.h"
#include "affichage.h"
#include "game.h"

int main()
{
srand(time(NULL));
//================================================================================|
debug_state = 1;//mettre à 1 pour activer les fonctions de debug 0 pour désactiver|
//================================================================================|


plein_ecran(4+debug_state);


//==============================================================initialisation de base===========================================================

cadre_ecran();//permet de s'assurer qu'on voit tout le jeu pour éviter les bugs d'affichage

S_joueur joueur[2];//data des joueurs
S_jeu game;//data des variables du jeu

initialisation_plateau(&joueur[0]);//remplie les matrices pour tout mettre a zéro
initialisation_plateau(&joueur[1]);
initialisation_pioche(&game);//met les pions dans la pioche
initialiser_haie(&game);//remplie de 0
melanger_pioche(&game);
remplir_haie(&game);








//======================================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(0);
afficher_grillage_colonne(0);

//====Data jeu=====
debug_update(&game, joueur);

//debug_afficher_matrice(joueur[0], DEBUG_J1_L, DEBUG_J1_C);
//debug_afficher_matrice(joueur[1], DEBUG_J2_L, DEBUG_J2_C);


positionner_curseur(100, 0);
    return 0;
}
