#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//=====Header=====
#include "declaration.h"
#include "affichage.h"
#include "game.h"


//=====Initialisation variable=====



//====================================================================================Initialisation du jeu===============================================================================

void initialisation_plateau(S_joueur *p)//tout à zéro
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

void melanger_pioche(char* pioche, int *nbr_pioche)
{
    int j;
    char temp;
    for (int i = 0; i < *nbr_pioche; i++)
    {
        j = rand() % *nbr_pioche;
        temp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = temp;
    }
}

void initialisation_pioche(char p[], int* nbr)//remplissage de la pioche
{
    int i;
    int k = 0;
        for (i = 0; i < 12; i++)
        {
            p[k] = 'C';//on remplit la pioche de 12 carottes
            k++;
        }
        for (i = 0; i < 12; i++)
        {
            p[k] = 'P';//on remplit la pioche de 12 patates
            k++;
        }
        for (i = 0; i < 12; i++)
        {
			p[k] = 'B';//on remplit la pioche de 12 brocolis
            k++;
        }
        for (i = 0; i < 12; i++)
        {
			p[k] = 'A';//on remplit la pioche de 12 aubergines
            k++;
        }
        for (i = 0; i < 12; i++)
        {
			p[k] = 'T';//on remplit la pioche de 12 tomates
            k++;
        }
    *nbr = 60;//nombre de légumes dans la pioche
}

void initialiser_haie(char h[])//permet de remplir la haie avec les 5 prochains légumes de la pioche
{
    int i;
    for (i = 0; i < 5; i++)
    {
        h[i] = '0';
    }
}

//=====================================================================================Fonction de jeu=====================================================================================

void deplacer_haie_vers_plateau(char haie[], char plat[], int h, int p)//deplace de la haie vers le plateau, h et p sont les positions dans la haie et le plateau
{
    haie[h] = plat[p];
	plat[p] = '0';
}

void remplir_haie(char h[], char* pioche, int* nbr_pioches)//permet de remplir la haie avec les 5 prochains légumes de la pioche
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (*nbr_pioches > 0) // Vérifie s'il reste des légumes dans la pioche
        {
            if (h[i] == '0')
            { // Si la haie est 0 à cette position, on remplit
                h[i] = pioche[*nbr_pioches - 1]; // Prend le dernier légume de la pioche
                *nbr_pioches = *nbr_pioches - 1; // Décrémente le nombre de légumes dans la pioche
            }
        }
        else
        {
            h[i] = 'X'; // Si la pioche est vide, remplit la haie avec 'X'
        }
    }
}
