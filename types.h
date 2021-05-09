#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "liste.h"

typedef T_liste T_liane; // Une T_liane est un alias d'une T_liste

typedef struct T_jungle_cell
{
    struct T_jungle_cell *suiv;
    struct T_jungle_cell *prec;
    T_liane *courante;
} * T_jungle; // Une T_jungle est un pointeur vers la premiere case d'une liste doublement chainee de T_liane

typedef T_liste T_liste_int; // Une T_liste_int est une alias d'une T_liste

typedef struct
{
    int id;
    char nom[10];                 //la premiere lettre du nom sera affiche sur l'IHM version
                                  //console pour indiquer la position du singe sur une liane
    int posX;                     //le numero de la liane ou est le singe
    int posY;                     //le numero du point d'accroche sur la liane en question
    T_liste_int listeIntPreferes; //liste d'entiers contenant les valeurs des
                                  //points d'accroches possibles pour ce singe
} T_singeV1;

typedef T_singeV1 T_singe; // Alias permettant d'avoir ensuite le meme type si l'on change la structure de donnee pour la version 2

#endif // TYPES_H_INCLUDED
