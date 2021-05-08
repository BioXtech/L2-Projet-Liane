#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "liste.h"

//initListe ne fait pas de malloc, juste une initialisation a NULL du pointeur de liste
void initListe(T_liste *l)
{
    *l=NULL;
}

bool listeVide( T_liste l)
{
    return (l==NULL);
}

T_liste ajoutEnTete(T_liste l, int mydata)
{
    T_liste newl = (T_liste)malloc(sizeof(struct T_cell));
    newl -> data = (int *)malloc(sizeof(int));
    *(newl -> data) = mydata;

    if (listeVide(l))
    {
        newl -> suiv = NULL;
        newl -> prec = NULL;
    }
    else
    {
        newl->prec = NULL;
        newl -> suiv = l;
        l -> prec = newl;
    }

    return newl;
}

/*
void debug(T_liste l)
{
    struct T_cell *ptrCourant = l;
    printf("Liste\n-----\n");
    while(ptrCourant != NULL)
    {
        printf("##########\n");
        printf("# Ptr case d'avant: %X\n", ptrCourant->prec);
        printf("# Ptr de la case courante: %X\n",ptrCourant);
        printf("# Valeur : %d\n",*(ptrCourant->data));
        printf("# Ptr case d'apres: %X\n", ptrCourant->suiv);
        printf("##########\n");
        ptrCourant = ptrCourant->suiv;
    }
    printf("-----\n\n");
}
*/

T_liste getptrNextCell(T_liste l)
{
    T_liste ptrCourant = l;
    if (listeVide(l))
    {
        //printf("\nErreur getptrNextCell : Pointeur NULL, liste vide");
        return NULL;
    }
    else
    {
        return ptrCourant->suiv;
    }
}

T_liste getptrPrevCell(T_liste l)
{
    T_liste ptrCourant = l;
    if (listeVide(l))
    {
        printf("\nErreur getptrPrevCell : Pointeur NULL");
        return NULL;
    }
    else
    {
        return ptrCourant->prec;
    }
}


int* getPtrData(T_liste l)
{
    T_liste ptrCourant = l;
    if (listeVide(l))
    {
        return NULL;
    }
    else
    {
        //printf("\nValeur : %X\n", ptrCourant->data);
        return ptrCourant->data;
    }
}

void afficheListeV1(T_liste l)
{
    T_liste ptrCourant = l; // T_list = struct T_cell*
    printf("Liste\n-----\n");
    while(!listeVide(ptrCourant))
    {
        printf("%d\n",*(getPtrData(ptrCourant)));
        ptrCourant = getptrNextCell(ptrCourant);
    }
    printf("-----\n\n");
}

int getNbreCell(T_liste l)
{
    T_liste ptrCourant = l;
    int nombre = 1;
    if (listeVide(l))
    {
        return 0;
    }
    else
    {
        while (getptrNextCell(ptrCourant) != NULL)
        {
            ptrCourant = getptrNextCell(ptrCourant);
            nombre++;
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre;
    }
}

int getOccurences(T_liste l, int data)
{
    T_liste ptrCourant = l;
    int occurence = 0;

    if (listeVide(l))
    {
        printf("\nListe vide, l'element n'apparait aucune fois");
        return 0;
    }
    else
    {
        while(!listeVide(ptrCourant))
        {
            if (*(getPtrData(ptrCourant)) == data)
            {
                occurence++;
            }
            ptrCourant = getptrNextCell(ptrCourant);
        }
    }
    //printf("\nLe nombre d'occurence de %d est %d", data, occurence);
    return occurence;
}


