#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "liste.h"

typedef T_liste T_liane;

typedef struct T_jungle_cell{
    struct T_jungle_cell* suiv;
    struct T_jungle_cell* prec;
    T_liane* courante;
}* T_jungle;

typedef T_liste T_liste_int;

typedef struct
{
    int id;
    char nom[10];                   //la première lettre du nom sera affiché sur l'IHM version
                                    //console pour indiquer la position du singe sur une liane
    int posX;                       //le numéro de la liane où est le singe
    int posY;                       //le numéro du point d'accroche sur la liane en question
    T_liste_int listeIntPreferes;   //liste d'entiers contenant les valeurs des
                                    //points d'accroches possibles pour ce singe
} T_singeV1;

#endif // TYPES_H_INCLUDED
