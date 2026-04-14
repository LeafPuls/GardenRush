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


#endif // DECLARATION_H_INCLUDED
