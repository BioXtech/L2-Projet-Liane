#include <stdlib.h>
#include <stdio.h>

#include "liane.h"
#include "liste.h"
#include "types.h"


void initLiane(T_liane *l)
{
    *l = NULL;
}

T_liane ajoutNombreALiane(T_liane l, int nombre)
{
    T_liane newl = (T_liane)malloc(sizeof(struct T_cell_liane));
    newl->data = initPointAccroche();
    remplirPointAccroche(newl->data, nombre, NULL);

    if (listeVide(l))
    {
        newl -> suiv = NULL;
        newl -> prec = NULL;
    }
    else
    {
        newl -> suiv = l;
        l -> prec = newl;
    }

    return newl;
}

#define LONGUEUR_MIN 4
#define LONGUEUR_MAX 10
#define VAL_MIN 0
#define VAL_MAX 9

T_liane genererLiane()
{
    T_liane liane;
    initLiane(&liane);
    int longueur_liane, valeur;

    longueur_liane = (rand() % (LONGUEUR_MAX - LONGUEUR_MIN - 1) + LONGUEUR_MIN);

    for (int i = 0; i < longueur_liane; i++)
    {
        valeur = (rand() % (VAL_MAX - VAL_MIN - 1) + VAL_MIN);
        liane = ajoutNombreALiane(liane, valeur);
    }

    return liane;
}
