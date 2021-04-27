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
    srand (time (NULL));


    jouer();
    /*
    T_singe singe = choixSinge();
    T_jungle jungle = creationJungle();
    afficheJungle(jungle, singe);
    jungle = getNextLiane(jungle);
    afficheJungle(jungle, singe);
    */
    //afficheListePref(singe);
    return 0;
}
