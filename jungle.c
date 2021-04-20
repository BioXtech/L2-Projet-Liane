#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jungle.h"
#include "liste.h"

void initLiane(T_liane* l){
    *l = NULL;
}

void initJungle(T_jungle* j){
    *j = NULL;
}

bool jungleVide(T_jungle j){
    return (j==NULL);
}

T_jungle getNextLiane(T_jungle j){
    struct T_jungle_cell * ptrCourant = j;
    if (jungleVide(j))
    {
        printf("\nErreur getNextLiane : Liste vide");
        return NULL;
    }
    else
    {
        return ptrCourant->suiv;
    }
}

T_jungle getPrecLiane(T_jungle j){
    struct T_jungle_cell * ptrCourant = j;
    if (jungleVide(j))
    {
        printf("\nErreur getPrecLiane : Liste vide");
        return NULL;
    }
    else
    {
        return ptrCourant->prec;
    }
}

T_liane* getLiane(T_jungle j){
    struct T_jungle_cell * ptrCourant = j;
    if (jungleVide(j))
    {
        printf("\nErreur getLiane : Liste vide");
        return NULL;
    }
    else
    {
        return ptrCourant->courante;
    }
}

int getNombreLiane(T_jungle j){
    struct T_jungle_cell * ptrCourant = j;
    int compteur = 1;
    if (jungleVide(j))
    {
        return compteur = 0;
    }
    else
    {
        while (ptrCourant->suiv !=NULL)
        {
            ptrCourant = ptrCourant->suiv;
            compteur += 1;
        }
        return compteur;
    }
}

T_liane ajoutNombreALiane(T_liane l, int nombre){
    return ajoutEnFin(l,nombre);
}

T_jungle ajoutLianeAJungle(T_jungle j, T_liane l){

}
