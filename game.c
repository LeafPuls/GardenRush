#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====Header=====
#include "declaration.h"
#include "affichage.h"
#include "game.h"

//====================================================================================Initialisation du jeu===============================================================================

void initialisation_plateau(S_joueur *joueur) //tout à zéro
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            joueur->plat[i][j] = '0';
        }
    }
    joueur->score = 0; //score de base à 0
}

void initialisation_pioche(S_jeu *game) //remplissage de la pioche
{
    int i;
    int k = 0;
    for (i = 0; i < 12; i++)
    {
        game->pioche[k] = 'C'; //on remplit la pioche de 12 carottes
        k++;
    }
    for (i = 0; i < 12; i++)
    {
        game->pioche[k] = 'P'; //on remplit la pioche de 12 patates
        k++;
    }
    for (i = 0; i < 12; i++)
    {
        game->pioche[k] = 'B'; //on remplit la pioche de 12 brocolis
        k++;
    }
    for (i = 0; i < 12; i++)
    {
        game->pioche[k] = 'A'; //on remplit la pioche de 12 aubergines
        k++;
    }
    for (i = 0; i < 12; i++)
    {
        game->pioche[k] = 'T'; //on remplit la pioche de 12 tomates
        k++;
    }
    game->nbr_pioches = 60; //nombre de légumes dans la pioche
}

void melanger_pioche(S_jeu *game)
{
    int j;
    char temp;
    for (int i = 0; i < game->nbr_pioches; i++)
    {
        j = rand() % game->nbr_pioches;
        temp = game->pioche[i];
        game->pioche[i] = game->pioche[j];
        game->pioche[j] = temp;
    }
}

void initialiser_haie(S_jeu *game) //permet de mettre la haie à zéro
{
    int i;
    for (i = 0; i < 5; i++)
    {
        game->haie[i] = '0';
    }
}

//=====================================================================================Fonction de jeu=====================================================================================

int recolter(S_jeu* game, S_joueur joueur[], int j)
{
    char choix;
    int motif;
	int rot;
	int l, c;

    scanf_s("%c", &choix);//correspond au legumes à fair plus tard avec des cliques souris ou clavier

    switch (choix)
    {
	case 'C'://===========Carottes==========

        scanf_s("%d", &motif);
        if (motif==2) {
            scanf_s("%d", &rot);
			if (rot == 0) {//faire motif 2 sans rotation
                scanf_s("%d", &l);
                scanf_s("%d", &c);
				joueur[j].plat[l][c] = 'C';
            }
        }
        if(motif==4) {
           //higligh les 4 combinaisons diagnolales via affichage puis demander de cliquer 
        }
        
        
        break;
        
    
    case 'P':
        break;

    
    case 'B':
        break;

    
    case 'A':
        break;

    
    case 'T':
        break;
    }
	return 0;
}

int deplacer_haie_vers_plateau(S_jeu* game, S_joueur joueur[], int j, int h, int l, int c)//deplacer_haie_vers_plateau(&game, joueurs, num joueur, h, l, c);
{
    // On prend le légume de la haie et on le met sur le plateau du joueur
    if ((l == 0 && c == 0) || (l == 0 && c == 4) || (l == 4 && c == 0) || (l == 4 && c == 4) || (h > 4) || (l >= 5) || (c >= 5)) {
        debug_update(game, joueur);
        return 404;
    }
    if (game->haie[h] == '0') {
        debug_update(game, joueur);
        return 5;
    }
    // On utilise l'index pour accéder au bon joueur
    if (joueur[j].plat[l][c] != '0') {
        debug_update(game, joueur);
        return 21;
    }

    if (game->haie[h] != '0') {
        if (l == h) {
            joueur[j].plat[l][c] = game->haie[h];
            game->haie[h] = '0';

            // L'appel à debug_update est maintenant correct !
            debug_update(game, joueur);
            return 0;
        }

        if (l != h) {
            int temp = soustraire_legume(game->haie[h]);
            joueur[j].plat[l][c] = temp;
            game->haie[h] = '0';

            // L'appel à debug_update est maintenant correct !
            debug_update(game, joueur);
            return 0;
        }
    }
    debug_update(game, joueur); 
    return 404;
}

char soustraire_legume(char leg)
{
	if (leg >= 'A' && leg <= 'Z')//utuilise le code ascii pour vérifier si c'est une majuscule et la convertir en minuscule via ajout de 32 parce que ascii c trop bien fait youpi 
    {
        return leg + 32; // Conversion Majuscule -> Minuscule (ex: 'C' -> 'c')
    }

    if ((leg >= 'a' && leg <= 'z') || leg == '0')
    {
        return '0'; // Déjà minuscule ou vide -> devient vide
    }

    return '0'; // Par sécurité pour tout autre caractère (comme ton 'X' de pioche vide)
}

void remplir_haie(S_jeu *game) //permet de remplir la haie avec les 5 prochains légumes de la pioche
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (game->nbr_pioches > 0) // Vérifie s'il reste des légumes dans la pioche
        {
            if (game->haie[i] == '0')
            { // Si la haie est 0 à cette position, on remplit donc le 0 c'est notre état vide on l'affiche sans pion
                game->haie[i] = game->pioche[game->nbr_pioches - 1]; // Prend le dernier légume de la pioche
                game->nbr_pioches = game->nbr_pioches - 1; // Décrémente le nombre de légumes dans la pioche
            }
        }
        else
        {
            if (game->haie[i] == '0')
            {
                game->haie[i] = 'X'; // Si la pioche est vide, remplit la haie avec 'X'
            }
        }
    }
}
