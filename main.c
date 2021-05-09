/*
PORRO Guillaume
KORTSMIT Simon
Version 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jungle.h"
#include "types.h"
#include "interface.h"

int main()
{
    srand(time(NULL)); // Initialisation generateur de nombre aleatoire

    choixTypeJeu(); // Lancmeent du jeu

    return 0;
}
