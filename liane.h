#ifndef LIANE_H_INCLUDED
#define LIANE_H_INCLUDED

#include <stdbool.h>
#include "liste.h"

typedef struct T_cell_liane
{

    struct T_cell_liane *suiv;
    struct T_cell_liane *prec;
    T_pointAccroche *data;

} *T_liane;

void initLiane(T_liane *liane);
bool lianeVide(T_liane l);
void debugLiane(T_liane l);
T_liane ajoutNombreALiane(T_liane liane, int nombre);
T_liane genererLiane();
T_liane getptrNextPA(T_liane l);
T_liane getptrPrevPA(T_liane l);
T_liane getptrLastPA(T_liane l);
T_liane getptrFirstPA(T_liane l);
T_liane getPAEnN(T_liane liane, int n);
int getNbrePA(T_liane l);
T_pointAccroche *getPA(T_liane l);
int getHauteurSinge(T_liane l);
void swapPA( T_liane source, T_liane destination );
void tri_selection_liane(T_liane l);


#endif // LIANE_H_INCLUDED
