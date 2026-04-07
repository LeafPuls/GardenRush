#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//=====Header=====
#include "affichage.h"
#include "game.h"




//====================================================================================Initialisation du jeu===============================================================================

void initialisation_plateau(S_plateau *p)//tout à zéro
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

void melanger_pioche(int* pioche, int nbr_pioche)
{
    int j;
    int temp;
    for (int i = 0; i < nbr_pioche; i++)
    {
        j = rand() % nbr_pioche; 
        temp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = temp;
    }
}

void initialisation_pioche()//remplissage de la pioche
{
    int i;
    int k = 0;
        for (i = 0; i < 12; i++)
        {
            pioche[k] = "C";//on remplit la pioche de 12 carottes
            k++;
        }
        for (i = 0; i < 12; i++)
        {
            pioche[k] = "P";//on remplit la pioche de 12 patates
            k++;
        }
        for (i = 0; i < 12; i++)
        {
			pioche[k] = "B";//on remplit la pioche de 12 brocolis
            k++;
        }
        for (i = 0; i < 12; i++)
        {
			pioche[k] = "A";//on remplit la pioche de 12 aubergines
            k++;
        }
        for (i = 0; i < 12; i++)
        {
			pioche[k] = "T";//on remplit la pioche de 12 tomates
            k++;
        }
    nbr_pioches = 60;//nombre de légumes dans la pioche
}


//=====================================================================================Fonction de jeu=====================================================================================
