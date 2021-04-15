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

    initLiane(&liane1);
    initLiane(&liane2);
    initLiane(&liane3);
    initJungle(&jungle);

    int un = 1, deux = 2, trois = 3, quatre = 4;

    liane1 = ajoutNombreALiane(liane1,&un);
    liane1 = ajoutNombreALiane(liane1,&deux);
    liane1 = ajoutNombreALiane(liane1,&trois);
    liane1 = ajoutNombreALiane(liane1,&quatre);

    liane2 = ajoutNombreALiane(liane2,&trois);
    liane2 = ajoutNombreALiane(liane2,&un);
    liane2 = ajoutNombreALiane(liane2,&deux);

    liane3 = ajoutNombreALiane(liane3,&deux);
    liane3 = ajoutNombreALiane(liane3,&un);


    jungle = ajoutLianeAJungle(jungle,&liane1);
    jungle = ajoutLianeAJungle(jungle,&liane2);
    jungle = ajoutLianeAJungle(jungle,&liane3);

    afficheJungle(jungle);
    return 0;
}
