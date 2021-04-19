/*
PORRO Guillaume
KORTSMIT Simon
Version 1
*/


#include <stdio.h>
#include <stdlib.h>

#include "jungle.h"
#include "types.h"
#include "interface.h"

int main()
{

    T_liane liane1, liane2, liane3;
    T_jungle jungle;
    T_singeV1 singe;


    initLiane(&liane1);
    initLiane(&liane2);
    initLiane(&liane3);
    initJungle(&jungle);

    liane1 = ajoutNombreALiane(liane1,1);
    liane1 = ajoutNombreALiane(liane1,2x);
    liane1 = ajoutNombreALiane(liane1,3);
    liane1 = ajoutNombreALiane(liane1,4);

    liane2 = ajoutNombreALiane(liane2,3);
    liane2 = ajoutNombreALiane(liane2,1);
    liane2 = ajoutNombreALiane(liane2,2);

    liane3 = ajoutNombreALiane(liane3,2);
    liane3 = ajoutNombreALiane(liane3,1);


    jungle = ajoutLianeAJungle(jungle,liane1);
    jungle = ajoutLianeAJungle(jungle,liane2);
    jungle = ajoutLianeAJungle(jungle,liane3);

    afficheJungle(jungle);
    return 0;
}
