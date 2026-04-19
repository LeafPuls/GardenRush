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
debug_state = 0;//mettre à 1 pour activer les fonctions de debug 0 pour désactiver|
//================================================================================|


plein_ecran(4+debug_state);


//==============================================================initialisation de base===========================================================

cadre_ecran();//permet de s'assurer qu'on voit tout le jeu pour éviter les bugs d'affichage

S_joueur joueur[2];//data des joueurs
S_jeu game;//data des varables du jeu

initialisation_plateau(&joueur[0]);//remplie les matrices pour tout mettre a zéro
initialisation_plateau(&joueur[1]);
initialisation_pioche(pioche, &nbr_pioches);//remplie la pioche de 60 légumes
initialiser_haie(haie);//remplie la haie de 0
melanger_pioche(pioche, &nbr_pioches);//mélange la pioche pour que les légumes soient dans un ordre aléatoire à chaque partie
remplir_haie(haie, pioche, &nbr_pioches);








//======================================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(0);
afficher_grillage_colonne(0);

//====Data jeu=====
debug_afficher_matrice(joueur[1], DEBUG_J1_L, DEBUG_J1_C);
//debug_afficher_matrice(&J2, DEBUG_J2_X, DEBUG_J2_Y);


positionner_curseur(100, 0);
    return 0;
}
