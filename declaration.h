#pragma once
#ifndef DECLARATION_H_INCLUDED
#define DECLARATION_H_INCLUDED

//====================================================================================Structure du jeu===============================================================================
struct joueur
{
    char plat[5][5];// tableau à 2 dimensions où les legumes sont stockés
    int score;// score du joueur lors de la récolte
};
typedef struct joueur S_joueur;

struct jeu
{
    char pioche[60];// Contient tout les légumes
    char haie[5];// Tableau qui contient les légumes à planter
    int nbr_pioches;// éléments (légumes) restant dans la pioche
    int nbr_tour;// nombre de tour de jeu, permet d'alterner le joueur en vérifiant sa parité
};
typedef struct jeu S_jeu;

#endif // DECLARATION_H_INCLUDED
