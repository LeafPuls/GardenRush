#pragma once
#ifndef DECLARATION_H_INCLUDED
#define DECLARATION_H_INCLUDED

//====================================================================================Structure du jeu===============================================================================
struct joueur
{
    char plat[5][5];
    int score;//score du joueur lors de la récolte
};
typedef struct joueur S_joueur;

struct jeu
{
    char pioche[60];
    char haie[5];
    int nbr_pioches;
	int nbr_tour;
};
typedef struct jeu S_jeu;

#endif // DECLARATION_H_INCLUDED
