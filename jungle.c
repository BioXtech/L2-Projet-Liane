#include <stdio.h>
#include <stdlib.h>

#include "jungle.h"
#include "liste.h"

void initLiane(T_liane* l){
    *l = NULL;
}

void initJungle(T_jungle* j){
    *j = NULL;
}

T_liane ajoutNombreALiane(T_liane l, int* nombre){
    return ajoutEnFin(l,nombre);
}

T_jungle ajoutLianeAJungle(T_jungle j, T_liane* l){
    return ajoutEnFin(j, *l);
}
