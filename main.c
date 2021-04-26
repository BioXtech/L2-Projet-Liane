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
    T_jungle jungle;
    T_singe singe = initSinge();
    jungle = genererJungle();

    afficheJungle(jungle,singe);

    //afficheListePref(singe);
    return 0;
}
