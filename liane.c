#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "liane.h"
#include "liste.h"
#include "types.h"


void initLiane(T_liane *l)
{
    *l = NULL;
}

bool lianeVide(T_liane l)
{
    return (l==NULL);
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

T_liane getptrNextPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l))
    {
        printf("\nErreur getptrNextCell : Pointeur NULL, liste vide");
        return NULL;
    }
    else
    {
        return ptrCourant->suiv;
    }
}

T_liane getptrPrevPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l))
    {
        printf("\nErreur getptrPrevCell : Pointeur NULL");
        return NULL;
    }
    else
    {
        return ptrCourant->prec;
    }
}

T_liane getptrLastPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l))
    {
        printf("\nErreur getptrLastPA : Pointeur NULL");
        return NULL;
    }
    else
    {
        // On rembobine la liste afin de retourner le pointeur de la première case
        while(getptrNextPA(l) != NULL)
        {
            ptrCourant = getptrNextPA(l);
        }
        return ptrCourant;
    }
}

T_liane getptrFirstPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l))
    {
        printf("\nErreur getptrFirstPA : Pointeur NULL, Liane vide");
        return NULL;
    }
    else
    {
        // On rembobine la liste afin de retourner le pointeur de la première case
        while(getptrPrevPA(l) != NULL)
        {
            ptrCourant = getptrPrevPA(l);
        }
        return ptrCourant;
    }
}


T_liane getPAEnN(T_liane liane, int n)
{
    T_liane ptrCourant = liane;
    for(int i = 0; i < n; i++)
    {
        ptrCourant = getptrNextPA(ptrCourant);
    }
    return ptrCourant;
}

int getNbrePA(T_liane l)
{
    T_liane ptrCourant = l;
    int nombre = 1;
    if (lianeVide(l))
    {
        nombre = 0;
        return nombre;
    }
    else
    {
        while (getptrNextPA(l) != NULL)
        {
            ptrCourant = getptrNextPA(l);
            nombre = nombre + 1;
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre;
    }
}

T_pointAccroche *getPA(T_liane l)
{
    if (lianeVide(l))
    {
        return NULL;
    }
    else
    {
        //printf("\nValeur : %X\n", ptrCourant->data);
        return ptrCourant->data;
    }
}

int getHauteurSinge(T_liane l)
{
    T_liane ptrCourant = l;
    int nombre = 0;
    if (lianeVide(l))
    {
        return -1;
    }
    else
    {
        while (!verifSingePresent(getPA(l)))
        {
            ptrCourant = getptrNextPA(l);
            nombre = nombre + 1;
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre;
    }
}
