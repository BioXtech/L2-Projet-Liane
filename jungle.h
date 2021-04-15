#ifndef JUNGLE_H_INCLUDED
#define JUNGLE_H_INCLUDED

#include "liste.h"

typedef T_liste T_liane;
typedef T_liste T_jungle;

void initLiane(T_liane* l);
void initJungle(T_jungle* j);
T_liane ajoutNombreALiane(T_liane l, int* nombre);
T_jungle ajoutLianeAJungle(T_jungle j, T_liane *l);

#endif // JUNGLE_H_INCLUDED
