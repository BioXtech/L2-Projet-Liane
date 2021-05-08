/*
PORRO Guillaume
KORTSMIT Simon
Version 2
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jungle.h"
#include "types.h"
#include "interface.h"

int main()
{
    srand (time (NULL)); // Initialise le generateur aleatoire

    // Commence le jeu
    choixTypeJeu();

    exit(EXIT_SUCCESS); // Quitte le jeu
}
