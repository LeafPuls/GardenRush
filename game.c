#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//=====Header=====
#include "affichage.h"
#include "game.h"



//================================================Matrice de jeu================================================




//=====Initialisation de la matrice de jeu=====
void init_plat()
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			plat1[i][j] = '0';//vide
			plat2[i][j] = '0';//vide
		}
	}
}

