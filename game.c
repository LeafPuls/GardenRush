#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====Header=====
#include "declaration.h"
#include "affichage.h"
#include "game.h"

//====================================================================================Initialisation du jeu===============================================================================

void InitialiserHandle() {
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}


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

//=====================================================================================Action de jeu=====================================================================================

/*
int menu(S_jeu* game, S_joueur joueur[], int j) {

    int choix;
    do
    {
        //afficher menu base avec soit recolter soit planter soit arreter son tour
        //choix = Clique menu
        //cacher menu

        //-----Recolter-----
        if (choix = 1) {
			joueur[j].score = joueur[j].score + recolter(game, joueur, j);
        }

		//-----Planter-----
        if (choix = 2) {
			int h, l, c;
            int clique;
            //clique plateau
			//h = ligne, l = colonne, c = legume dans la haie
			deplacer_haie_vers_plateau(game, joueur, j, h, l, c);
        }

    } while (choix != 0);
}
*/
int case_L(int c) { // convertit le numéro de la case en ligne (0 à 4)
    if (c < 1 || c > 25) return -1; // si PB (case hors limites)
    return (c - 1) / 5;   // 0 pour 1-5, 1 pour 6-10, 2 pour 11-15, 3 pour 16-20, 4 pour 21-25
}

int case_C(int c) { // convertit le numéro de la case en colonne (0 à 4)
    if (c < 1 || c > 25) return -1; // si PB (case hors limites)
    return (c - 1) % 5;   // 0 pour 1,6,11,16,21 ; … ; 4 pour 5,10,15,20,25
}


int clique_plateau(int baseLigne, int baseColonne) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ev;
    DWORD count;

    // Boucle infinie jusqu'à un clic valide
    while (1) {

        if (!ReadConsoleInput(hIn, &ev, 1, &count))
            continue;

        // event est un clic gauche de la souris
        if (ev.EventType == MOUSE_EVENT &&
            (ev.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {

            // recup des coord de la console
            int c = ev.Event.MouseEvent.dwMousePosition.X; // Colonne
            int l = ev.Event.MouseEvent.dwMousePosition.Y; // Ligne

            int hauteur = 17;  // hauteur d'une case à analyser
            int largeur = 34;  // largeur d'une case

			// hors du plateau 5x5 => on ignore
            if (l < baseLigne || l >= baseLigne + 5 * hauteur ||
                c < baseColonne || c >= baseColonne + 5 * largeur) {
                continue;
            }

            // Calcul ration selon tableu et case 
            int ligne = (l - baseLigne) / hauteur;
            int colonne = (c - baseColonne) / largeur;

            // return numéro case
            return ligne * 5 + colonne + 1;
        }
    }
}

//=====================================================================================Fonction de jeu=====================================================================================

int recolter(S_jeu* game, S_joueur joueur[], int j)
{
    char choix;
    int motif;
    int rot;
    int l, c;

    positionner_curseur(0,0);
    color(15, 0);
    printf("choix : ");
    scanf_s(" %c", &choix);

    switch (choix)
    {
    case 'C': // ================= Carottes =================

        // Demande la taille du motif (2 ou 4)
        positionner_curseur(0,0);
        color(15, 0);
        printf("motif : ");
        scanf_s("%d", &motif);

        //-------------------========== Motif 1 : Récolte d'une diag de 2 carottes ==========-------------------
        if (motif == 1) {

            positionner_curseur(0, 0);
            color(15, 0);
            printf("rotation : ");

            scanf_s("%d", &rot);
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            //----------Rotation 1 : Bas-Droite (+1 ligne, +1 colonne)----------
            if (rot == 1) {
                // On vérifie que la 2ème case ne sort pas du plateau 5x5
                if (l + 1 < 5 && c + 1 < 5) {
                    // L'épicentre ou la 2ème case ne doivent pas être dans les coins (0,0 ou 4,4)
                    if (!((l == 0 && c == 0) || (l + 1 == 4 && c + 1 == 4))) {
                        // verif C ou c
                        if ((joueur[j].plat[l][c] == 'C' || joueur[j].plat[l][c] == 'c') &&
                            (joueur[j].plat[l + 1][c + 1] == 'C' || joueur[j].plat[l + 1][c + 1] == 'c'))

                        {// supp                        
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);

                            return 2;
                            debug_update(game, joueur);
                        }
                    }
                }
            }
            //----------Rotation 2 : Bas-Gauche (+1 ligne, -1 colonne)----------
            else if (rot == 2) {
                // On vérifie que la 2ème case ne sort pas du plateau 5x5
                if (l + 1 < 5 && c - 1 >= 0) {
                    //L'épicentre ou la 2ème case ne doivent pas être dans les coins (0,0 ou 4,4)
                    if (!((l == 0 && c == 4) || (l + 1 == 4 && c - 1 == 0))) {
                        // verif C ou c
                        if ((joueur[j].plat[l][c] == 'C' || joueur[j].plat[l][c] == 'c') &&
                            (joueur[j].plat[l + 1][c - 1] == 'C' || joueur[j].plat[l + 1][c - 1] == 'c'))

                        {// supp
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c - 1] = soustraire_legume(joueur[j].plat[l + 1][c - 1]);

                            return 2;
                            debug_update(game, joueur);
                        }
                    }
                }
            }
        }

        //-------------------========== Motif 2 : Récolte d'une diag de 4 carottes ==========-------------------
        if (motif == 2) {

            positionner_curseur(0,0);
			color(15, 0);
            printf("rotation : ");

            scanf_s("%d", &rot);
            scanf_s("%d", &l);
            scanf_s("%d", &c);


            //----------Rotation 1 : diagonale vers le Bas-Droite (+1 ligne, +1 colonne)----------
            if (rot == 1) {
				// verif que tout rentre dans le plat, genre on prend la taille max via les position recu + taille motif et on s'embete meme pas a faire si c'est en dehors
                if (l + 3 < 5 && c + 3 < 5) {
                    // Ni l'épicentre, ni la dernière case ne touchent les coins (0,0 et 4,4) 
                    if (!((l == 0 && c == 0) || (l + 3 == 4 && c + 3 == 4))) {

                        // verif que chaque case contient soit un 'C' majuscule, soit un 'c' minuscule
                        if ((joueur[j].plat[l][c] == 'C' || joueur[j].plat[l][c] == 'c') &&
                            (joueur[j].plat[l + 1][c + 1] == 'C' || joueur[j].plat[l + 1][c + 1] == 'c') &&
                            (joueur[j].plat[l + 2][c + 2] == 'C' || joueur[j].plat[l + 2][c + 2] == 'c') &&
                            (joueur[j].plat[l + 3][c + 3] == 'C' || joueur[j].plat[l + 3][c + 3] == 'c'))

                        {// On soustrait les légumes sur les 4 cases                            
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);
                            joueur[j].plat[l + 2][c + 2] = soustraire_legume(joueur[j].plat[l + 2][c + 2]);
                            joueur[j].plat[l + 3][c + 3] = soustraire_legume(joueur[j].plat[l + 3][c + 3]);

                            debug_update(game, joueur);
                            return 4;
                        }
                    }
                }
            }


            //----------Rotation 2 : Diagonale vers le Bas-Gauche (+1 ligne, -1 colonne)----------
            else if (rot == 2) {
                // verif que la ligne ne dépasse pas 4 en bas, la colonne ne dépasse pas 0 à gauche
                if (l + 3 < 5 && c - 3 >= 0) {
                    // Exclusion des coins morts opposés (0,4 et 4,0)
                    if (!((l == 0 && c == 4) || (l + 3 == 4 && c - 3 == 0))) {

                        // verif de la présence des carottes sur la diagonale inversée
                        if ((joueur[j].plat[l][c] == 'C' || joueur[j].plat[l][c] == 'c') &&
                            (joueur[j].plat[l + 1][c - 1] == 'C' || joueur[j].plat[l + 1][c - 1] == 'c') &&
                            (joueur[j].plat[l + 2][c - 2] == 'C' || joueur[j].plat[l + 2][c - 2] == 'c') &&
                            (joueur[j].plat[l + 3][c - 3] == 'C' || joueur[j].plat[l + 3][c - 3] == 'c'))

                        {// soustrait                       
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c - 1] = soustraire_legume(joueur[j].plat[l + 1][c - 1]);
                            joueur[j].plat[l + 2][c - 2] = soustraire_legume(joueur[j].plat[l + 2][c - 2]);
                            joueur[j].plat[l + 3][c - 3] = soustraire_legume(joueur[j].plat[l + 3][c - 3]);

                            debug_update(game, joueur);
                            return 4;
                        }
                    }
                }
            }
        }
        debug_update(game, joueur);
        break;

   case 'A': //======================================================Aubergines======================================================

       positionner_curseur(0, 0);
       color(15, 0);
       printf("motif : ");
       scanf_s("%d", &motif);

       //-------------------========== Motif 1 : 2 Aubergines ==========-------------------
       if (motif == 1) {

           positionner_curseur(0, 0);
           color(15, 0);
           printf("rotation : ");

           scanf_s("%d", &rot);
           scanf_s("%d", &l);
           scanf_s("%d", &c);

           // Rotation 1 : 
           if (rot == 1) {
               // Limites strictes
               if (l >= 0 && l < 5 && c >= 0 && c + 1 < 5) {
                   // vérif des angles morts pour les 2 extrémités du bloc
                   if (!((l == 0 && c == 0) || (l == 4 && c == 0) || (l == 0 && c + 1 == 4) || (l == 4 && c + 1 == 4))) {
                       // Validation
                       if ((joueur[j].plat[l][c] == 'A' || joueur[j].plat[l][c] == 'a') &&
                           (joueur[j].plat[l][c + 1] == 'A' || joueur[j].plat[l][c + 1] == 'a'))

                       {
                           joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                           joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);

                           debug_update(game, joueur);
                           return 2; 
                       }
                   }
               }
           }
           // Rotation 2 : 
           else if (rot == 2) {
               if (l >= 0 && l + 1 < 5 && c >= 0 && c < 5) {
                   if (!((l == 0 && c == 0) || (l == 0 && c == 4) || (l + 1 == 4 && c == 0) || (l + 1 == 4 && c == 4))) {

                       if ((joueur[j].plat[l][c] == 'A' || joueur[j].plat[l][c] == 'a') &&
                           (joueur[j].plat[l + 1][c] == 'A' || joueur[j].plat[l + 1][c] == 'a'))

                       {
                           joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                           joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);

                           debug_update(game, joueur);
                           return 2;
                       }
                   }
               }
           }
       }

       //-------------------========== Motif 2 : Carré de 2x2 Aubergines ==========-------------------
       else if (motif == 2) {
           scanf_s("%d", &l);
           scanf_s("%d", &c);

           //pas de rot car carré
           if (l >= 0 && l + 1 < 5 && c >= 0 && c + 1 < 5) {
               // Seuls les 4 coins du carré peuvent théoriquement toucher un coin du plateau
               if (!((l == 0 && c == 0) || (l == 0 && c + 1 == 4) || (l + 1 == 4 && c == 0) || (l + 1 == 4 && c + 1 == 4))) {

                   if ((joueur[j].plat[l][c] == 'A' || joueur[j].plat[l][c] == 'a') &&
                       (joueur[j].plat[l][c + 1] == 'A' || joueur[j].plat[l][c + 1] == 'a') &&
                       (joueur[j].plat[l + 1][c] == 'A' || joueur[j].plat[l + 1][c] == 'a') &&
                       (joueur[j].plat[l + 1][c + 1] == 'A' || joueur[j].plat[l + 1][c + 1] == 'a'))

                   {
                       joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                       joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);
                       joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);
                       joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);

                       debug_update(game, joueur);
                       return 4; 
                   }
               }
           }
       }

       //-------------------========== Motif 3 : Rectangle 2x3 ou 3x2 Aubergines ==========-------------------
       else if (motif == 3) {

           positionner_curseur(0, 0);
           color(15, 0);
           printf("rotation : ");

           scanf_s("%d", &rot);
           scanf_s("%d", &l);
           scanf_s("%d", &c);

           // Rotation 1 : 
           if (rot == 1) {
               if (l >= 0 && l + 1 < 5 && c >= 0 && c + 2 < 5) {//verif que c'est bien dedans
				   if (!((l == 0 && c == 0) || (l + 1 == 4 && c == 0) || (l == 0 && c + 2 == 4) || (l + 1 == 4 && c + 2 == 4))) {//verif que les coins du rectangle ne sont pas dans les coins du plateau

                       if ((joueur[j].plat[l][c] == 'A' || joueur[j].plat[l][c] == 'a') &&
                           (joueur[j].plat[l][c + 1] == 'A' || joueur[j].plat[l][c + 1] == 'a') &&
                           (joueur[j].plat[l][c + 2] == 'A' || joueur[j].plat[l][c + 2] == 'a') &&
                           (joueur[j].plat[l + 1][c] == 'A' || joueur[j].plat[l + 1][c] == 'a') &&
                           (joueur[j].plat[l + 1][c + 1] == 'A' || joueur[j].plat[l + 1][c + 1] == 'a') &&
                           (joueur[j].plat[l + 1][c + 2] == 'A' || joueur[j].plat[l + 1][c + 2] == 'a'))

                       {
                           joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                           joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);
                           joueur[j].plat[l][c + 2] = soustraire_legume(joueur[j].plat[l][c + 2]);
                           joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);
                           joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);
                           joueur[j].plat[l + 1][c + 2] = soustraire_legume(joueur[j].plat[l + 1][c + 2]);

                           debug_update(game, joueur);
                           return 6;
                       }
                   }
               }
           }
           // Rotation 2 
           else if (rot == 2) {
               if (l >= 0 && l + 2 < 5 && c >= 0 && c + 1 < 5) {
                   if (!((l == 0 && c == 0) || (l == 0 && c + 1 == 4) || (l + 2 == 4 && c == 0) || (l + 2 == 4 && c + 1 == 4))) {

                       if ((joueur[j].plat[l][c] == 'A' || joueur[j].plat[l][c] == 'a') &&
                           (joueur[j].plat[l][c + 1] == 'A' || joueur[j].plat[l][c + 1] == 'a') &&
                           (joueur[j].plat[l + 1][c] == 'A' || joueur[j].plat[l + 1][c] == 'a') &&
                           (joueur[j].plat[l + 1][c + 1] == 'A' || joueur[j].plat[l + 1][c + 1] == 'a') &&
                           (joueur[j].plat[l + 2][c] == 'A' || joueur[j].plat[l + 2][c] == 'a') &&
                           (joueur[j].plat[l + 2][c + 1] == 'A' || joueur[j].plat[l + 2][c + 1] == 'a'))

                       {
                           joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                           joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);
                           joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);
                           joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);
                           joueur[j].plat[l + 2][c] = soustraire_legume(joueur[j].plat[l + 2][c]);
                           joueur[j].plat[l + 2][c + 1] = soustraire_legume(joueur[j].plat[l + 2][c + 1]);

                           debug_update(game, joueur);
                           return 6;
                       }
                   }
               }
           }
       }
       break;

    case 'T': //======================================================Tomates======================================================

        positionner_curseur(0, 0);
        color(15, 0);
        printf("motif : ");
        scanf_s("%d", &motif);

        //-------------------========== Motif 1 : Une seule Tomate (Pas de rotation) ==========-------------------
        if (motif == 1) {
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            // verif des limites tia capté comme d'hab
            if (l >= 0 && l < 5 && c >= 0 && c < 5 && !((l == 0 || l == 4) && (c == 0 || c == 4))) {
                // verif que ya dla tomaaateee
                if (joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') 
                
                {// soustraiiiiitt
                    joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);

                    debug_update(game, joueur);
                    return 1;
                }
            }
        }

        //-------------------========== Motif 2 : Chevron V ==========-------------------
        else if (motif == 2) {

            positionner_curseur(0, 0);
            color(15, 0);
            printf("rotation : ");
            scanf_s("%d", &rot);
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            // Rotation 1 : *:
            if (rot == 1) {
                if (l - 1 >= 0 && l + 1 < 5 && c >= 0 && c + 1 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c + 1 == 0 || c + 1 == 4)) && !((l + 1 == 0 || l + 1 == 4) && (c + 1 == 0 || c + 1 == 4))) {
                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l - 1][c + 1] == 'T' || joueur[j].plat[l - 1][c + 1] == 't') &&
                            (joueur[j].plat[l + 1][c + 1] == 'T' || joueur[j].plat[l + 1][c + 1] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c + 1] = soustraire_legume(joueur[j].plat[l - 1][c + 1]);
                            joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);

                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
            // Rotation 2 : .*.
            else if (rot == 2) {
                if (l >= 0 && l + 1 < 5 && c - 1 >= 0 && c + 1 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l + 1 == 0 || l + 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l + 1 == 0 || l + 1 == 4) && (c + 1 == 0 || c + 1 == 4))) {
                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l + 1][c - 1] == 'T' || joueur[j].plat[l + 1][c - 1] == 't') &&
                            (joueur[j].plat[l + 1][c + 1] == 'T' || joueur[j].plat[l + 1][c + 1] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c - 1] = soustraire_legume(joueur[j].plat[l + 1][c - 1]);
                            joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);

                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
            // Rotation 3 : :*
            else if (rot == 3) {
                if (l - 1 >= 0 && l + 1 < 5 && c - 1 >= 0 && c < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l + 1 == 0 || l + 1 == 4) && (c - 1 == 0 || c - 1 == 4))) {
                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l - 1][c - 1] == 'T' || joueur[j].plat[l - 1][c - 1] == 't') &&
                            (joueur[j].plat[l + 1][c - 1] == 'T' || joueur[j].plat[l + 1][c - 1] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c - 1] = soustraire_legume(joueur[j].plat[l - 1][c - 1]);
                            joueur[j].plat[l + 1][c - 1] = soustraire_legume(joueur[j].plat[l + 1][c - 1]);

                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
            // Rotation 4 : *.*
            else if (rot == 4) {
                if (l - 1 >= 0 && l < 5 && c - 1 >= 0 && c + 1 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c + 1 == 0 || c + 1 == 4))) {
                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l - 1][c - 1] == 'T' || joueur[j].plat[l - 1][c - 1] == 't') &&
                            (joueur[j].plat[l - 1][c + 1] == 'T' || joueur[j].plat[l - 1][c + 1] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c - 1] = soustraire_legume(joueur[j].plat[l - 1][c - 1]);
                            joueur[j].plat[l - 1][c + 1] = soustraire_legume(joueur[j].plat[l - 1][c + 1]);

                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
        }

        //-------------------========== Motif 3 : Forme de 'W' ==========-------------------
        else if (motif == 3) {

            positionner_curseur(0, 0);
            color(15, 0);
            printf("rotation : ");
            scanf_s("%d", &rot);
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            // Rotation 1 : W
            if (rot == 1) {

                if (l >= 0 && l + 1 < 5 && c - 2 >= 0 && c + 2 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l + 1 == 0 || l + 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l == 0 || l == 4) && (c - 2 == 0 || c - 2 == 4)) &&
                        !((l + 1 == 0 || l + 1 == 4) && (c + 1 == 0 || c + 1 == 4)) && !((l == 0 || l == 4) && (c + 2 == 0 || c + 2 == 4))) {

                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l + 1][c - 1] == 'T' || joueur[j].plat[l + 1][c - 1] == 't') &&
                            (joueur[j].plat[l][c - 2] == 'T' || joueur[j].plat[l][c - 2] == 't') &&
                            (joueur[j].plat[l + 1][c + 1] == 'T' || joueur[j].plat[l + 1][c + 1] == 't') &&
                            (joueur[j].plat[l][c + 2] == 'T' || joueur[j].plat[l][c + 2] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c - 1] = soustraire_legume(joueur[j].plat[l + 1][c - 1]);
                            joueur[j].plat[l][c - 2] = soustraire_legume(joueur[j].plat[l][c - 2]);
                            joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);
                            joueur[j].plat[l][c + 2] = soustraire_legume(joueur[j].plat[l][c + 2]);

                            debug_update(game, joueur);
                            return 5;
                        }
                    }
                }
            }
            // Rotation 2 : Σ 
            else if (rot == 2) {

                if (l - 2 >= 0 && l + 2 < 5 && c - 1 >= 0 && c < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l - 2 == 0 || l - 2 == 4) && (c == 0 || c == 4)) &&
                        !((l + 1 == 0 || l + 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l + 2 == 0 || l + 2 == 4) && (c == 0 || c == 4))) {

                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l - 1][c - 1] == 'T' || joueur[j].plat[l - 1][c - 1] == 't') &&
                            (joueur[j].plat[l - 2][c] == 'T' || joueur[j].plat[l - 2][c] == 't') &&
                            (joueur[j].plat[l + 1][c - 1] == 'T' || joueur[j].plat[l + 1][c - 1] == 't') &&
                            (joueur[j].plat[l + 2][c] == 'T' || joueur[j].plat[l + 2][c] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c - 1] = soustraire_legume(joueur[j].plat[l - 1][c - 1]);
                            joueur[j].plat[l - 2][c] = soustraire_legume(joueur[j].plat[l - 2][c]);
                            joueur[j].plat[l + 1][c - 1] = soustraire_legume(joueur[j].plat[l + 1][c - 1]);
                            joueur[j].plat[l + 2][c] = soustraire_legume(joueur[j].plat[l + 2][c]);

                            debug_update(game, joueur);
                            return 5;
                        }
                    }
                }
            }
            // Rotation 3 : M
            else if (rot == 3) {
                if (l - 1 >= 0 && l < 5 && c - 2 >= 0 && c + 2 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c - 1 == 0 || c - 1 == 4)) && !((l == 0 || l == 4) && (c - 2 == 0 || c - 2 == 4)) &&
                        !((l - 1 == 0 || l - 1 == 4) && (c + 1 == 0 || c + 1 == 4)) && !((l == 0 || l == 4) && (c + 2 == 0 || c + 2 == 4))) {

                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l - 1][c - 1] == 'T' || joueur[j].plat[l - 1][c - 1] == 't') &&
                            (joueur[j].plat[l][c - 2] == 'T' || joueur[j].plat[l][c - 2] == 't') &&
                            (joueur[j].plat[l - 1][c + 1] == 'T' || joueur[j].plat[l - 1][c + 1] == 't') &&
                            (joueur[j].plat[l][c + 2] == 'T' || joueur[j].plat[l][c + 2] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c - 1] = soustraire_legume(joueur[j].plat[l - 1][c - 1]);
                            joueur[j].plat[l][c - 2] = soustraire_legume(joueur[j].plat[l][c - 2]);
                            joueur[j].plat[l - 1][c + 1] = soustraire_legume(joueur[j].plat[l - 1][c + 1]);
                            joueur[j].plat[l][c + 2] = soustraire_legume(joueur[j].plat[l][c + 2]);

                            debug_update(game, joueur);
                            return 5;
                        }
                    }
                }
            }
            // Rotation 4 : ∃
            else if (rot == 4) {
                if (l - 2 >= 0 && l + 2 < 5 && c >= 0 && c + 1 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) && !((l - 1 == 0 || l - 1 == 4) && (c + 1 == 0 || c + 1 == 4)) && !((l - 2 == 0 || l - 2 == 4) && (c == 0 || c == 4)) &&
                        !((l + 1 == 0 || l + 1 == 4) && (c + 1 == 0 || c + 1 == 4)) && !((l + 2 == 0 || l + 2 == 4) && (c == 0 || c == 4))) {

                        if ((joueur[j].plat[l][c] == 'T' || joueur[j].plat[l][c] == 't') &&
                            (joueur[j].plat[l - 1][c + 1] == 'T' || joueur[j].plat[l - 1][c + 1] == 't') &&
                            (joueur[j].plat[l - 2][c] == 'T' || joueur[j].plat[l - 2][c] == 't') &&
                            (joueur[j].plat[l + 1][c + 1] == 'T' || joueur[j].plat[l + 1][c + 1] == 't') &&
                            (joueur[j].plat[l + 2][c] == 'T' || joueur[j].plat[l + 2][c] == 't')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c + 1] = soustraire_legume(joueur[j].plat[l - 1][c + 1]);
                            joueur[j].plat[l - 2][c] = soustraire_legume(joueur[j].plat[l - 2][c]);
                            joueur[j].plat[l + 1][c + 1] = soustraire_legume(joueur[j].plat[l + 1][c + 1]);
                            joueur[j].plat[l + 2][c] = soustraire_legume(joueur[j].plat[l + 2][c]);

                            debug_update(game, joueur);
                            return 5;
                        }
                    }
                }
            }
        }
        break;

    case 'B'://======================================================Brocoli======================================================

        positionner_curseur(0, 0);
        color(15, 0);
        printf("motif : ");
        scanf_s("%d", &motif);

        //-------------------========== Motif 1 : Une seule Tomate ==========-------------------
        if (motif == 1) {

            positionner_curseur(0, 0);
            color(15, 0);
            printf("rotation : ");
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            // verif des limites tia capté comme d'hab
            if (l >= 0 && l < 5 && c >= 0 && c < 5 && !((l == 0 || l == 4) && (c == 0 || c == 4))) {
                // verif que ya du broco
                if (joueur[j].plat[l][c] == 'B' || joueur[j].plat[l][c] == 'b') 
                
                {// soustraiiiiitt                 
                    joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);

                    debug_update(game, joueur);
                    return 1;
                }
            }
        }

        //-------------------========== Motif 2 : L ==========-------------------
        else if (motif == 2) {

            positionner_curseur(0, 0);
            color(15, 0);
            printf("rotation : ");
            scanf_s("%d", &rot);
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            // Rotation 1 : |_
            if (rot == 1) {
                if (l - 1 >= 0 && l < 5 && c >= 0 && c + 1 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) &&
                        !((l - 1 == 0 || l - 1 == 4) && (c == 0 || c == 4)) &&
                        !((l == 0 || l == 4) && (c + 1 == 0 || c + 1 == 4))) {

                        if ((joueur[j].plat[l][c] == 'B' || joueur[j].plat[l][c] == 'b') &&
                            (joueur[j].plat[l - 1][c] == 'B' || joueur[j].plat[l - 1][c] == 'b') &&
                            (joueur[j].plat[l][c + 1] == 'B' || joueur[j].plat[l][c + 1] == 'b')) {

                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c] = soustraire_legume(joueur[j].plat[l - 1][c]);
                            joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);
                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
            // Rotation 2 : |^
            else if (rot == 2) {
                if (l >= 0 && l + 1 < 5 && c >= 0 && c + 1 < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) &&
                        !((l + 1 == 0 || l + 1 == 4) && (c == 0 || c == 4)) &&
                        !((l == 0 || l == 4) && (c + 1 == 0 || c + 1 == 4))) {

                        if ((joueur[j].plat[l][c] == 'B' || joueur[j].plat[l][c] == 'b') &&
                            (joueur[j].plat[l + 1][c] == 'B' || joueur[j].plat[l + 1][c] == 'b') &&
                            (joueur[j].plat[l][c + 1] == 'B' || joueur[j].plat[l][c + 1] == 'b')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);
                            joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);
                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
            // Rotation 3 : ^|
            else if (rot == 3) {
                if (l >= 0 && l + 1 < 5 && c - 1 >= 0 && c < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) &&
                        !((l + 1 == 0 || l + 1 == 4) && (c == 0 || c == 4)) &&
                        !((l == 0 || l == 4) && (c - 1 == 0 || c - 1 == 4))) {

                        if ((joueur[j].plat[l][c] == 'B' || joueur[j].plat[l][c] == 'b') &&
                            (joueur[j].plat[l + 1][c] == 'B' || joueur[j].plat[l + 1][c] == 'b') &&
                            (joueur[j].plat[l][c - 1] == 'B' || joueur[j].plat[l][c - 1] == 'b')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);
                            joueur[j].plat[l][c - 1] = soustraire_legume(joueur[j].plat[l][c - 1]);
                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
            // Rotation 4 : _|
            else if (rot == 4) {
                if (l - 1 >= 0 && l < 5 && c - 1 >= 0 && c < 5) {
                    if (!((l == 0 || l == 4) && (c == 0 || c == 4)) &&
                        !((l - 1 == 0 || l - 1 == 4) && (c == 0 || c == 4)) &&
                        !((l == 0 || l == 4) && (c - 1 == 0 || c - 1 == 4))) {

                        if ((joueur[j].plat[l][c] == 'B' || joueur[j].plat[l][c] == 'b') &&
                            (joueur[j].plat[l - 1][c] == 'B' || joueur[j].plat[l - 1][c] == 'b') &&
                            (joueur[j].plat[l][c - 1] == 'B' || joueur[j].plat[l][c - 1] == 'b')) 
                        
                        {
                            joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                            joueur[j].plat[l - 1][c] = soustraire_legume(joueur[j].plat[l - 1][c]);
                            joueur[j].plat[l][c - 1] = soustraire_legume(joueur[j].plat[l][c - 1]);
                            debug_update(game, joueur);
                            return 3;
                        }
                    }
                }
            }
        }

        //-------------------========== Motif 3 : La Croix (+) de 5 Brocolis ==========-------------------
        else if (motif == 3) {
            scanf_s("%d", &l);
            scanf_s("%d", &c);

            if (l >= 1 && l <= 3 && c >= 1 && c <= 3) {

                if ((joueur[j].plat[l][c] == 'B' || joueur[j].plat[l][c] == 'b') &&
                    (joueur[j].plat[l - 1][c] == 'B' || joueur[j].plat[l - 1][c] == 'b') &&
                    (joueur[j].plat[l + 1][c] == 'B' || joueur[j].plat[l + 1][c] == 'b') &&
                    (joueur[j].plat[l][c - 1] == 'B' || joueur[j].plat[l][c - 1] == 'b') &&
                    (joueur[j].plat[l][c + 1] == 'B' || joueur[j].plat[l][c + 1] == 'b')) 
                
                {
                    joueur[j].plat[l][c] = soustraire_legume(joueur[j].plat[l][c]);
                    joueur[j].plat[l - 1][c] = soustraire_legume(joueur[j].plat[l - 1][c]);
                    joueur[j].plat[l + 1][c] = soustraire_legume(joueur[j].plat[l + 1][c]);
                    joueur[j].plat[l][c - 1] = soustraire_legume(joueur[j].plat[l][c - 1]);
                    joueur[j].plat[l][c + 1] = soustraire_legume(joueur[j].plat[l][c + 1]);
                    debug_update(game, joueur);
                    return 5;
                }
            }
        }
        break;

    case 'P':



        break;
    }

    debug_update(game, joueur);
    return 0;
}


int deplacer_haie_vers_plateau(S_jeu* game, S_joueur joueur[], int j, int h, int l, int c)// deplacer_haie_vers_plateau(&game, joueurs, num joueur, h, l, c);
{
    // On prend le légume de la haie et on le met sur le plateau du joueur
    if ((l == 0 && c == 0) || (l == 0 && c == 4) || (l == 4 && c == 0) || (l == 4 && c == 4) || (h > 4) || (l >= 5) || (c >= 5)) {
        debug_update(game, joueur);
        return 404;//hors zone
    }

    if (game->haie[h] == '0') {
        debug_update(game, joueur);
        return 5;//haie vide ici
    }

    if (joueur[j].plat[l][c] != '0') {
        debug_update(game, joueur);
		return 21;//plateau deja occupé
    }

    if (game->haie[h] != '0') {//place legume
        if (l == h) {
            joueur[j].plat[l][c] = game->haie[h];
            game->haie[h] = '0';

            debug_update(game, joueur);
            return 0;
        }

        if (l != h) {
            int temp = soustraire_legume(game->haie[h]);
            joueur[j].plat[l][c] = temp;
            game->haie[h] = '0';

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
        return '0'; // deja minuscule ou vide -> devient vide
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
