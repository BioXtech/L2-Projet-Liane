#ifndef LIANE_H_INCLUDED
#define LIANE_H_INCLUDED

#include "liste.h"

typedef struct T_cell_liane
{

    struct T_cell_liane *suiv;
    struct T_cell_liane *prec;
    T_pointAccroche *data;

} *T_liane;

void initLiane(T_liane *liane);
T_liane ajoutNombreALiane(T_liane liane, int nombre);
T_liane genererLiane();

#endif // LIANE_H_INCLUDED
