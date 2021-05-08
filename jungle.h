#ifndef JUNGLE_H_INCLUDED
#define JUNGLE_H_INCLUDED

#include <stdbool.h>

#include "liane.h"
#include "types.h"

typedef struct T_jungle_cell
{
    struct T_jungle_cell *suiv;
    struct T_jungle_cell *prec;
    T_liane *courante;
}* T_jungle;

void initJungle(T_jungle *jungle);

bool jungleVide(T_jungle jungle);

T_jungle getNextLiane(T_jungle jungle);
T_jungle getPrecLiane(T_jungle jungle);

T_liane *getLiane(T_jungle jungle);

int getNombreLiane(T_jungle jungle);

T_jungle ajoutLianeAJungle(T_jungle jungle, T_liane liane);

//void debugJungle(T_jungle jungle);

bool verifHaut(T_jungle jungle, T_singe singe);
bool verifFace(T_jungle jungle, T_singe singe);
bool verifBas(T_jungle jungle, T_singe singe);
bool verifDebut(T_jungle jungle, T_singe singe, int *indice);
bool verifFin(T_jungle jungle);

bool allerEnHaut(T_jungle jungle, T_singe *singe);
bool allerEnFace(T_jungle jungle, T_singe *singe);
bool allerEnBas(T_jungle jungle, T_singe *singe);
void allerPremiereLiane(T_jungle jungle, T_singe *singe);

void afficheListePref(T_singe s);

T_jungle genererJungle();

void sauterEau();

void triNextLiane(T_jungle jungle);

bool verifTriLiane(T_jungle jungle);

#endif // JUNGLE_H_INCLUDED
