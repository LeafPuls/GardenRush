#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====include=====
#include "affichage.h"
#include "game.h"

int main()
{
srand(time(NULL));                                                                                      
plein_ecran(4);  
autoriser_scroll();//marche pas bien    
                     

//================================================================================|    
debug_state = 1;//mettre à 1 pour activer les fonctions de debug 0 pour désactiver|    
//================================================================================|    
                                                                                       


//==============================================================initialisation de base===========================================================

srand(time(NULL));
cadre_ecran();//permet de s'assurer qu'on voit tout le jeu pour éviter les bugs d'affichage

initialisation_plateau(&plateau[0]);//remplie les matrices pour tout mettre a zéro
initialisation_plateau(&plateau[1]);
initialisation_pioche(&pioche, &nbr_pioches);//remplie la pioche de 60 légumes
initialiser_haie(&haie);//remplie la haie de 0 
melanger_pioche(&pioche, &nbr_pioches);//mélange la pioche pour que les légumes soient dans un ordre aléatoire à chaque partie
remplir_haie(&haie, &pioche, &nbr_pioches);
dessiner_plateau(&plateau[0], &plateau[1]);//affiche le fond du plateau de jeu qui ne s'actualise pas








//======================================================================DEBUG==============================================================

//=====Affichage=====
afficher_grillage_ligne(0);
afficher_grillage_colonne(0);

//====Data jeu=====
//debug_afficher_matrice(&J1, DEBUG_J1_X, DEBUG_J1_Y);
//debug_afficher_matrice(&J2, DEBUG_J2_X, DEBUG_J2_Y);
debug_update();//affiche toutes les fct de debug en meme temps 


positionner_curseur(100, 0);
    return 0;
}
