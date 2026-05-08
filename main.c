#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//=====include=====
#include "declaration.h"
#include "affichage.h"
#include "game.h"

/*
  .-_'''-.      ____    .-------.     ______         .-''-.  ,---.   .--.        .-------.      ___    _    .-'''-. .---.  .---.
 '_( )_   \   .'  __ `. |  _ _   \   |    _ `''.   .'_ _   \ |    \  |  |        |  _ _   \   .'   |  | |  / _     \|   |  |_ _|
|(_ o _)|  ' /   '  \  \| ( ' )  |   | _ | ) _  \ / ( ` )   '|  ,  \ |  |        | ( ' )  |   |   .'  | | (`' )/`--'|   |  ( ' )
. (_,_)/___| |___|  /  ||(_ o _) /   |( ''_'  ) |. (_ o _)  ||  |\_ \|  |        |(_ o _) /   .'  '_  | |(_ o _).   |   '-(_{;}_)
|  |  .-----.   _.-`   || (_,_).' __ | . (_) `. ||  (_,_)___||  _( )_\  |        | (_,_).' __ '   ( \.-.| (_,_). '. |      (_,_)
'  \  '-   .'.'   _    ||  |\ \  |  ||(_    ._) ''  \   .---.| (_ o _)  |        |  |\ \  |  |' (`. _` /|.---.  \  :| _ _--.   |
 \  `-'`   | |  _( )_  ||  | \ `'   /|  (_.\.' /  \  `-'    /|  (_,_)\  |        |  | \ `'   /| (_ (_) _)\    `-'  ||( ' ) |   |
  \        / \ (_ o _) /|  |  \    / |       .'    \       / |  |    |  |        |  |  \    /  \ /  . \ / \       / (_{;}_)|   |
   `'-...-'   '.(_,_).' ''-'   `'-'  '-----'`       `'-..-'  '--'    '--'        ''-'   `'-'    ``-'`-''   `-...-'  '(_,_) '---'
*/

int main()
{
    cacher_curseur();
    srand(time(NULL));


//====================================================================================|
    debug_state = 0;//mettre à 1 pour activer les fonctions de debug 0 pour désactiver|
//====================================================================================|


    plein_ecran(6+debug_state);// ATTENTION CHANGER LA VALEUR SELON L'ECRAN, POUR S'AIDER OBSERVER LE FOND NOIR DE LA CONSOLE SE GENERER
    intro();Sleep(5000);
    dessiner_rectangle(0, 1, 133, 472, NOIR);//fond de la console


//===================================================================================================================================================initialisation de base================================================================================================================================================

    S_joueur joueur[2];// data des joueurs
    S_jeu game;// data des variables du jeu
    game.nbr_tour = 0;

    initialisation_affichage();//dessine le fond vert du plateau de jeu

    InitialiserHandle();//souris activer

    initialisation_plateau(&joueur[0]);// remplit les matrices pour tout mettre à zéro
    initialisation_plateau(&joueur[1]);

    initialisation_pioche(&game);// met les pions dans la pioche
    melanger_pioche(&game);

    initialiser_haie(&game);// remplit de 0
    remplir_haie(&game, joueur);

// 1er affichage avant boucle de jeu
    afficher_score(&game, joueur);
    afficher_plateau_joueur(&game, joueur, 0);
    afficher_plateau_joueur(&game, joueur, 1);
    afficher_marche(0);
    afficher_marche(1);
    afficher_haie(&game, joueur);

//===================================================================================================================================================== BOUCLE DE JEU ================================================================================================================================================

    while (joueur[0].score < 45 && joueur[1].score < 45 && game.nbr_pioches != 0)//tant que personne a gagné et qu'il reste des legumes à piocher
    {
        int action;
        int j1 = pair(game.nbr_tour);
        int j2 = impair(game.nbr_tour);
retour:// si on rate la récolte alors on remet le menu du même joueur pour qu'il puisse choisir une autre action

        debug_update(&game, joueur);
        effacer_menu(1);
        action = afficher_menu(j1);//affiche le menu du joueur actif et récupère son choix d'action
        effacer_menu(0);

        if (action == 1)//---============================== RECOLTE ==============================---
        {
            int temp_score = recolter(&game, joueur, j1);//si le joueur choisit de récolter, on execute la fonction de récolte et on stocke le score gagné dans une variable temporaire
            joueur[j1].score = joueur[j1].score + temp_score;

            if (temp_score == 0)
            {
                goto retour;// si on recolte rien alors on remet le menu du même joueur pour qu'il puisse choisir une autre action
            }
            else // donc si on augmente du score et égalise avec adversaire alors on dépasse son adervaire et on lui donne un point de bonus
            {
                if(joueur[j1].score == joueur[j2].score)
                {
                    joueur[j1].score = joueur[j1].score + 1;//si les joueurs sont à égalité après la récolte, on donne un point de bonus au joueur actif
                    debug_update(&game, joueur);
                }

                //fin du tour si on recolte
                effacer_menu(1);
                afficher_plateau_joueur(&game, joueur, j1);
                afficher_score(&game, joueur);
                game.nbr_tour++;
                debug_update(&game, joueur);
            }
        }

        if (action == 2)//---============================== PLANTE ==============================---
        {
            //si le joueur choisit de planter, on execute la fonction de planter qui deplace le legume choisi de la haie vers le plateau du joueur actif

            if (deplacer_haie_vers_plateau(&game, joueur, j1)!=0)
            {
                goto retour;// si la fct return autre chose que 0 alors y'a rien ou erreur donc on rechoisi une action
            }
            else // donc si on augmente du score et égalise avec adversaire alors on dépasse son adervaire et on lui donne un point de bonus
            {
                //fin du tour si on planter
                effacer_menu(1);
                afficher_plateau_joueur(&game, joueur, j1);
                remplir_haie(&game, joueur);
                afficher_haie(&game, joueur);
                game.nbr_tour++;
                debug_update(&game, joueur);
            }
        }

    }

    if (joueur[0].score > joueur[1].score)
    {
        dessiner_rectangle(0, 1, 133, 472, CYAN);
        victoire();
    }
    else
    {
        dessiner_rectangle(0, 1, 133, 472, CYAN);
        victoire();
    }

//===========================================================================================================================================================DEBUG===================================================================================================================================================

//=====Affichage=====
//afficher_grillage_ligne(0);
//afficher_grillage_colonne(0);

//afficher_plateau_joueur(&game, joueur, 0);
//afficher_score(&game, joueur);
//afficher_haie(&game, joueur);

//====Data jeu=====
    debug_update(&game, joueur);// affiche toutes les données du jeu (pioche, haie, plateau) et le score des joueurs

//debug_afficher_matrice(joueur[0], DEBUG_J1_L, DEBUG_J1_C);
//debug_afficher_matrice(joueur[1], DEBUG_J2_L, DEBUG_J2_C);


    positionner_curseur(150, 0);
    return 0;
}

/*
printf("                                                                                                                                                                     ::::..     .           \n");
printf("                                                                                                                                                         -....                    .         \n");
printf("                                                                                                                                               -.:...                              .        \n");
printf("                                                                                                                                       :::.                 =@*                    .        \n");
printf("                                                                                                                            ::::.                             *%#@*@@=:            .        \n");
printf("                                                                                                                   -:...                                   -%+=......#*#%          .        \n");
printf("                                                                                                           .::..                               -@%%%%#%%##%..........*--*          .        \n");
printf("                                                      .:.......-.                                :::..                       @+        -:.  -+:........++-*.........:*--#          .        \n");
printf("                                                   .               .                    -:...                             ###%- -@#+==...*##+...........++*.........:*--*          .        \n");
printf("                                                 :    :-=.:::-=-     :.         -::..                                  -@%#*:............==+=............*#.........-*--+.:.       .        \n");
printf("                                               .   .=:..:......:-=:    .-:.                         %= *             .#..................+=+=.............%.........-+--+*#        .        \n");
printf("                                              :   ==.............-==                             =@%###%%%%@@%-      -...................==*-.............=........ ==---.:        .        \n");
printf("                                             .  .=:-......+***#+*%%%@.                          %+...........-#@%##  -................-###*#=...................:...+=--*%:        .        \n");
printf("                                            -   ==::.#%%%%##*=#+%         . -:  **@*%%@*--:    #................-*****...........%%%##++.  :=...................:.. *---+          .        \n");
printf("                                      .:.       =%%%#%-   =     . .....   :%==:..........-@%##.*..................*+-*...........:...+-=** ==..............:....-..:*--=*          .        \n");
printf("                              :....            -#          ...           %..................*+++...................*=*...............*--++ +=..::.::::..........-..-*--=*          .        \n");
printf("                       :::                             @*-==#@+=:%###    *...................+==...................-+*...............*--*- *=.....:..:...:::---===--+--=+          .        \n");
printf("              .::                      .=           -#=:.........=+-*    +...................*==........#*=.........**...............+--*  --...::-:.-*--------::--:+--+=          .        \n");
printf("         ..                     =       %+##       @..............*-+*   *........*#-........++=........*=+*........**..........:##%##*+=#*#--===-=:.-+=::::::::::::+--+-          .        \n");
printf("         .         ==- .      -@%@*=:==%#+++**    %%..............#=-+- .+........+#*........*+=....:...*-=#........**..........-+----.-:=-+:-::::-..-=+::::::::::::=-=*:          .        \n");
printf("         .           =###   :%............*+=+#   --..............-+-=# =+........*-........=+==....:...*=*:.......:++.::-----=---:..-.-:=-+::::::-..-==+::::::::::+==+*          .         \n");
printf("         .           #*+**%*................*=+#  %................*=-* .=.................:*-=+....-..:#*:.....:::==+-------::::----=.-:=-+::::::--:-=-+#+*%%%@%#%#*#*           .         \n");
printf("        .              -=+..................:=-+#*=................:*-+:-=.............::-#*=-==....:..:...:-===---+-+:::::::::::::::---:=-+-===+#%%%%##%.                        .         \n");
printf("        .               =..................:+**#.#.......-+.........*--=+=.....:......:...:*=-==.::--=-=------::::+=-+:::::::::::::::::-+**#%                                     .         \n");
printf("        .              #..........=.....=**+=    +.......=#.........++--+-...........::-..--+===--------::::::::=++**#-::::::::-=*%%%%%#+=.                                     +.          \n");
printf("        .           .. %.........****+####*****###....:...+*:.........*--+-...:::--=-=--==..--+=-::::::::::::::-+**#  .=*%%%%%%@%+                                       -@@@@@@:.          \n");
printf("        .             -........++=+**-:......+-==....:..:*##.........-=-+----=-----:::::--:-::+=::::::::::::=*###                     ..                         :%@@@@@@##:                \n");
printf("        .           %#........:*-+...........*-*.....-..-=:..:::---=--+-+::::::::::*:::::---::=-:::::::--#%%%*.              ........                      @@@@@@%*--=+#%..                 \n");
printf("        .          =*=.....:..-*-*....:::-..:*=+.....-....---------:::==+::::::::::+-::::::=#%%##%%%%%%%#=           ......           -#                   @@#-+#@@@@%. .                   \n");
printf("        .          =+=.....:..-*-=+#=....::.-++::--=-=----==-::::::::::=+:::::::::+*###%%%%%+                                        ###                     @*                             \n");
printf("        .        @%%#*.....:..:+*+++..::::--+++:---:::::++==+::::::::::=+==*#%%%%%#=:                                        +      ##+#*                    #.                             \n");
printf("        -            .-....:-....:.:--=----:++::::::::::+--+#====+*%%%%#*+                                             .# ##%      ##++##                    :.                             \n");
printf("         :            *-:---====----:::::::+==:::::::::-**##  -                                            #####.      #####.     ##=+##                      .                             \n");
printf("         +            .+=---::::::::::::::++**==+*%%%%%#=.                                           #######*         ##++*#     ##++##           =####       :                             \n");
printf("         .              *==:::::::::::::**##-                                                     ########            #++=#-    +#++##       #######++##-     :                             \n");
printf("          .               %+-======#%%%%#=                                     ###              ###+#+               :#+==#    ##*+##          -#*++++=#%     :                             \n");
printf("          .                #%                             -#####*           =###*##            ##++*=                #*=++######+++*            ###**###      :                             \n");
printf("          .                ++                      .########*++*####    :####++++##   #%       ##+=*#             ####+===++++++++##%%#%%%#       +###.       :                             \n");
printf("          -                                     *####++#########+++##   -#+++++*##   #### %    -##++###############*++++++**+==++##                           .                             \n");
printf("           =                                    +#++####.      *+++##  ##*++++##    ##++##       ##+=+==+++++=++++++=++####:#+++*#                            .                             \n");
printf("           ..             .::=#@@@@           .##+++#       ####++##     *+++##    ##++##         *+++++=++++*#####+++##    #+++#:                            .                             \n");
printf("            .  :=%@@@@@@@@@@%#+=-++            #+==+-   #####++####    ##*+###   ###+=##      #####++*###*+++#.   #+=+#    ##++##                             .                             \n");
printf("              ...:#**===+*#%@@@@@@@           +#++++#####++*####      ##+*##    ##+++##     ###++#####   #+++#   ##=+##   ######                              .                             \n");
printf("                                 ..           #*=+++++++####+       ###+##+    ##++=*#    =##++###     ###=*##  ##++##    %- +#                              ..                             \n");
printf("                                  .          ##++++++####          ##++##    ###=++=#-    #*=###     ###++##.    #+##    .                                   +                              \n");
printf("                                  .         ##+++===+             ##+=##    ##+++==+#    *#+=*   #####+*###      ###                                         :                              \n");
printf("                                  .         #*++=++++##%#        -#+=+#   ###+++++++###   #+=*####*+*###=         #                                          .                              \n");
printf("                                  :        :#+=#####*++ .#%      #*=++**###+=#####++++#######+++*#####                                                  .+%-.                               \n");
printf("                                   .       #*+*#   +######       ##++++++++###   #######    #####+                                              .#%@@@@@@.                                  \n");
printf("                                   +      ##++#*         #%#      ###**#####                                                           .=*%@@@@@@##%@@=.                                    \n");
printf("                                   +       ####             .#      ####:                                                     .#@@@@@@@@#**#%@@@%-.                                         \n");
printf("                                   :         #                    %                                                 -%@@@@@@@@@*+=+#@@@@@*                                                  \n");
printf("                                   .                                                                       .*@@@@@@@%*===+#%@@@@*.                                                          \n");
printf("                                    .                                   ........                 .%@@@@@@@@%*===+*%@@@@+                                                                    \n");
printf("                                    .                            ...                   +@@@@@@@@@%*=--=+#@@@@@@@+                                                                           \n");
printf("                                    .                                         +%@@@@@@@#+---=*##@@@@@@=                                                                                     \n");
printf("                                    .                              :%@@@@@@@@%*+=-=+#%@@@@%=                                                                                                \n");
printf("                                    .                  .%@@@@@@@@@@%*===+#%@@@@@@@+.                                                                                                        \n");
printf("                                     .    .=*%@@@@@@@@@%*===+*%@@@@@@@+.                                                                                                                    \n");
printf("                                      .-#@@@#***#%%@@@@@+.                                                                                                                                  \n");
printf("                                                                                                                                                                                            \n");
printf("                                                                                                                                                                                            \n");
printf("                                                                                                                                                                                            \n");
*/
