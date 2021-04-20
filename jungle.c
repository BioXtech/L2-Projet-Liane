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
    T_jungle ptrCourant = j;
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
    T_jungle ptrCourant = j;
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
    T_jungle ptrCourant = j;
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
    T_jungle ptrCourant = j;
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

T_jungle ajoutLianeAJungle(T_jungle j, T_liane *l){
    T_jungle newj = (T_jungle)malloc(sizeof(struct T_jungle_cell));
    newj->courante = l;
    if(jungleVide(j)){
        newj->prec = NULL;
        newj->suiv = NULL;
        return newj;
    }
    else{
        T_jungle temp = j;
        while(temp -> suiv != NULL){
            temp = temp -> suiv;
        }
        newj -> prec = temp;
        newj -> suiv = NULL;
        temp -> suiv = newj;
    }

    return j;
}

void debugJungle(T_jungle j)
{
    T_jungle ptrCourant = j;
    printf("Jungle\n-----\n");
    while(ptrCourant != NULL)
    {
        printf("##########\n");
        printf("# Ptr case d'avant: %X\n", ptrCourant->prec);
        printf("# Ptr de la case courante: %X\n",ptrCourant);
        printf("# Ptr vers la liane : %X\n",ptrCourant->courante);
        printf("# Ptr case d'apres: %X\n", ptrCourant->suiv);
        printf("##########\n");
        ptrCourant = ptrCourant->suiv;
    }
    printf("-----\n\n");
}

void afficheListePref(T_singeV1 s){
    afficheListeV1(s.listeIntPreferes);
}
