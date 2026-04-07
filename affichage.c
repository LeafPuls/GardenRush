#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//=====Header=====
#include "affichage.h"
#include "game.h"


//=====================================================================================Fonction AFFICHAGE=====================================================================================
void cadre_ecran() {
	dessiner_rectangle(0, 0, 88, 1, GRIS);//côté
    dessiner_rectangle(0, 313, 88, 1, GRIS);
	dessiner_rectangle(0, 0, 1, 314, GRIS);//haut et bas
    dessiner_rectangle(87, 0, 1, 314, GRIS);
}

void dessiner_plateau() {
	dessiner_rectangle(PLAT_L, PLAT_C, 60, 310, VERT_FONCE);
}

//====================================================================================Fonction base affichage====================================================================================

void dessine_pixel_hex(int x, int y, int hex_couleur) {
    // extrait les composantes R, G, B du code hexadécimal
    int r = (hex_couleur >> 16) & 0xFF;
    int g = (hex_couleur >> 8) & 0xFF;
    int b = hex_couleur & 0xFF;

    positionner_curseur(x, y);
    // Print espace avec le fond coloré en RGB
    printf("\x1b[48;2;%d;%d;%dm \x1b[0m", r, g, b);
}

void dessiner_rectangle(int x, int y, int longueur, int hauteur, int hex_couleur) {
    for (int j = 0; j < hauteur; j++) {
        for (int i = 0; i < longueur; i++) {
            dessine_pixel_hex(x + i, y + j, hex_couleur);
        }
    }
}

void affichage_caractere_speciaux()
{
    printf("%c\n\n", 218);
    printf("%c\n\n", 196);
    printf("%c\n\n", 191);
    printf("%c\n\n", 179);
    printf("%c\n\n", 195);
    printf("%c\n\n", 180);
    printf("%c\n\n", 192);
    printf("%c\n\n", 217);
}

void color(int couleurDuTexte, int couleurDuFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond * 16 + couleurDuTexte);
}

//=====================================================================================Fonction de base=====================================================================================


void plein_ecran(int s)
{
    // Basculer en plein écran
    keybd_event(VK_MENU, 0x38, 0, 0); // Appuie sur ALT
    keybd_event(VK_RETURN, 0x1C, 0, 0); // Appuie sur ENTREE
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0); // Relâche ENTREE
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Relâche ALT

    // Attendre un court instant pour que le mode plein écran s'active
    Sleep(500);

    // Appliquer un zoom (CTRL + '-')
    for (int i = 0; i < s; i++)
    {
        keybd_event(VK_CONTROL, 0x1D, 0, 0); // Appuie sur CTRL
        keybd_event(VK_SUBTRACT, 0x4A, 0, 0); // Appuie sur '-'
        keybd_event(VK_SUBTRACT, 0x4A, KEYEVENTF_KEYUP, 0); // Relâche '-'
        keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_KEYUP, 0); // Relâche CTRL

        Sleep(100); // Petite pause entre les actions
    }
}

void positionner_curseur(int ligne, int colonne)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X = colonne;// numéro de la colonne
    pos.Y = ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}


void cacher_curseur() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


//=====================================================================================Fonction DEBUG=====================================================================================

//aide pour positioner
void afficher_grillage_ligne(int ligne) {
    positionner_curseur(ligne, 0);
    for (int j = 0; j < 24; j++) {
        for (int i = 0; i < 10; i++) {
            color(0, i);
            printf("%d", i);
        }
    }
}
void afficher_grillage_colonne(int colonne) {
	int k = 0;
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 10; i++) {
            positionner_curseur(k, colonne);
            color(0, i);
            printf("%d", i);
			k++;
        }
    }
}

void debug_afficher_matrice(int p, int l, int c)
{
     
        int i, j;
        positionner_curseur(l, c);
		color(15, 0);
        // Affichage des données
        for (i = 0; i < 5; i++)
        {
            positionner_curseur(l+i, c);

            for (j = 0; j < 5; j++)
            {
                printf("%c ", plateau[p].plat[i][j]);
            }
        }

        // Affichage du score
        positionner_curseur(l + 7, c);
        printf("Score : %d", plateau[p].score);
	
    
}

void debug_afficher_pioche(int l, int c) 
{
    int i;
    positionner_curseur(l, c);
    color(15, 0);
    printf("Pioche : ");
    for (i = 0; i < nbr_pioches; i++) {
        printf("%c ", pioche[i]);
    }
	printf("  nbr_pioches : %d    ", nbr_pioches);
}

void debug_afficher_haie(int l, int c)
{
    int i;
    positionner_curseur(l, c);
    color(15, 0);
    for (i = 0; i < 5; i++) {
		positionner_curseur(l+i, c);
        printf("%c ", haie[i]);
    }
}

void debug_update()
{
    if (debug_state==1)
    {
		debug_afficher_matrice(0, DEBUG_J1_L, DEBUG_J1_C);
		debug_afficher_matrice(1, DEBUG_J2_L, DEBUG_J2_C);
        debug_afficher_pioche(DEBUG_J1_L+9, DEBUG_J1_C);
		debug_afficher_haie(DEBUG_J1_L, DEBUG_J1_C+14);
    }
}

void autoriser_scroll()//permet d'avoir une console plus grande que l'écran pour pouvoir scroller et éviter les bugs d'affichage pour afficher le debug sous notre jeu
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // On sécurise la largeur pour éviter une erreur de dimension X
    short largeurFenetre = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    short largeurBuffer = csbi.dwSize.X;

    COORD nouvelleTaille;
    nouvelleTaille.X = (largeurBuffer > largeurFenetre) ? largeurBuffer : largeurFenetre;
    nouvelleTaille.Y = 500; // On demande 500 lignes de scroll

    // Si Windows refuse la modification du scroll :
    if (SetConsoleScreenBufferSize(hConsole, nouvelleTaille) == 0)
    {
        positionner_curseur(0, 0);
        printf("ERREUR WINDOWS %lu : Impossible de creer un scroll en mode ALT+ENTREE.\n", GetLastError());
        Sleep(5000); // Laisse 5 secondes pour que tu puisses lire
    }
}
