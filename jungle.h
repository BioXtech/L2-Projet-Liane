#ifndef JUNGLE_H_INCLUDED
#define JUNGLE_H_INCLUDED

#include <stdbool.h>

#include "liste.h"
#include "types.h"

void initLiane(T_liane* l);
void initJungle(T_jungle* j);

bool jungleVide(T_jungle j);

T_jungle getNextLiane(T_jungle j);
T_jungle getPrecLiane(T_jungle j);
T_liane* getLiane(T_jungle j);

int getNombreLiane(T_jungle j);

T_liane ajoutNombreALiane(T_liane l, int nombre);
T_jungle ajoutLianeAJungle(T_jungle j, T_liane l);




#endif // JUNGLE_H_INCLUDED
