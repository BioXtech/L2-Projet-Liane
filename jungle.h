#ifndef JUNGLE_H_INCLUDED
#define JUNGLE_H_INCLUDED

#include <stdbool.h>

#include "liste.h"
#include "types.h"

void initLiane(T_liane* liane);
void initJungle(T_jungle* jungle);

bool jungleVide(T_jungle jungle);

T_jungle getNextLiane(T_jungle jungle);
T_jungle getPrecLiane(T_jungle jungle);
T_liane* getLiane(T_jungle jungle);

int getNombreLiane(T_jungle jungle);

T_liane ajoutNombreALiane(T_liane liane, int nombre);
T_jungle ajoutLianeAJungle(T_jungle jungle, T_liane *liane);

void debugJungle(T_jungle jungle);

void afficheListePref(T_singeV1 singe);

bool verifHaut(T_jungle jungle, T_singeV1 singe);
bool verifFace(T_jungle jungle, T_singeV1 singe);
bool verifBas(T_jungle jungle, T_singeV1 singe);

void allerEnHaut(T_singeV1* singe);
void allerEnFace(T_singeV1* singe);
void allerEnBas(T_singeV1* singe);




#endif // JUNGLE_H_INCLUDED
