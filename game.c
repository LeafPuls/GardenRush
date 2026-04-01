#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//=====Header=====
#include "affichage.h"
#include "game.h"



//=====================================================================================Matrice de jeu=====================================================================================



//=====Initialisation de la matrice de jeu=====
void initialisation_plateau(S_plateau *p)
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            
            p->plat[i][j] = '0';
        }
    }
    p->score = 0;//score de base à 0
}

