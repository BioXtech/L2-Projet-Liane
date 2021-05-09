#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "liste.h"

// Param�tres : Une T_liste
// R�sultat : Aucun
// Definition : Sans allocation dynamique, la fonction initialise � NULL un pointeur de liste
void initListe(T_liste *l)
{
    *l=NULL;
}

// Param�tres : Une T_liste
// R�sultat : Un booleen
// Definition : Cette fonction permet de savoir si une liste est vide ou non
bool listeVide( T_liste l)
{
    return (l==NULL);
}

// Param�tres : Une T_liste et un entier
// R�sultat : Une T_liste
// Definition : Cette fonction ajoute un entier � la liste pass�e en param�tre
T_liste ajoutEnTete(T_liste l, int mydata)
{
    T_liste newl = (T_liste)malloc(sizeof(struct T_cell)); // Allocation de la nouvelle case pour l'entier
    newl -> data = (int *)malloc(sizeof(int)); // Allocation du nouvel entier
    *(newl -> data) = mydata; // On affecte l'entier � la nouvelle case

    if (listeVide(l)) // Si la liste est vide on cree une nouvelle case avec les pointeurs prec et suiv a NULL (il n'y a donc pas de cases avant et apr�s)
    {
        newl -> suiv = NULL;
        newl -> prec = NULL;
    }
    else // Sinon on ajoute la nouvelle case en la chainant avec la liste donnee en parametre (ajout en tete pour une meilleure complexit�)
    {
        newl->prec = NULL;
        newl -> suiv = l;
        l -> prec = newl;
    }

    return newl; // On retourne le pointeur sur la nouvelle tete de la liste
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

// Param�tres : Une T_liste
// R�sultat : Une T_liste
// Definition : Cette fonction donne le pointeur de la case suivante de celle point�e en param�tre de la liste
T_liste getptrNextCell(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    if (listeVide(l)) // Si la liste est vide (appel � la fonction auxilliaire)
    {
        //printf("\nErreur getptrNextCell : Pointeur NULL, liste vide");
        return NULL; // Retourne NULL
    }
    else // Sinon
    {
        return ptrCourant->suiv; // On retourne le pointeur suiv de la case courante
    }
}

// Param�tres : Une T_liste
// R�sultat : Un pointeur d'un entier
// Definition : Cette fonction donne le pointeur de l'entier de la case point�e de la liste en param�tre
int* getPtrData(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    if (listeVide(l)) // Si la liste est vide (appel � la fonction auxilliaire)
    {
        return NULL; // Retourne NULL
    }
    else
    {
        //printf("\nValeur : %X\n", ptrCourant->data);
        return ptrCourant->data; // On retourne le pointeur de l'entier de la case courante
    }
}

// Param�tres : Une T_liste
// R�sultat : Aucun
// Definition : Cette fonction permet d'afficher une liste
void afficheListeV1(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    printf("Liste\n-----\n");
    while(!listeVide(ptrCourant)) // On parcourt toutes les cases de la liste
    {
        printf("%d\n",*(getPtrData(ptrCourant))); // On affiche l'entier point� par la case courante
        ptrCourant = getptrNextCell(ptrCourant); // Le pointeur courant pointe sur la case suivante pour continuer le parcours
    }
    printf("-----\n\n");
}

// Param�tres : Une T_liste
// R�sultat : Un entier
// Definition : Cette fonction donne le nombre de cellules d'une liste
int getNbreCell(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    int nombre = 1; // On intialise le compteur de case � 1
    if (listeVide(l)) // Si la liste est vide
    {
        return 0; // On retourn 0 (il y a 0 cases)
    }
    else // Sinon
    {
        while (getptrNextCell(ptrCourant) != NULL) // On parcourt toutes les cases de la liste
        {
            ptrCourant = getptrNextCell(ptrCourant); // Le pointeur courant pointe la case suivante par appel d'une fonction auxilliaire
            nombre++; // Le compteur s'incr�mente de un
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre; // On retourne le nombre
    }
}

// Param�tres : Une T_liste et un entier
// R�sultat : Un entier
// Definition : Cette fonction donne le nombre de fois qu'apparait l'entier en param�tre dans la liste
int getOccurences(T_liste l, int data)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    int occurence = 0; // Initialiser du compteur � 0

    if (listeVide(l)) // Si la liste est vide
    {
        printf("\nListe vide, l'element n'apparait aucune fois");
        return 0; // Le nombre d'occurences est �gal � 0
    }
    else // Sinon
    {
        while(!listeVide(ptrCourant)) // Parcours de toute la liste
        {
            if (*(getPtrData(ptrCourant)) == data) // Si le nombre entr� en param�tre est �gal � la valeur point�e de la case point�e
            {
                occurence++; // Alors le compteur d'occurence est incr�ment� de 1
            }
            ptrCourant = getptrNextCell(ptrCourant); // Le pointeur courante pointe sur la case suivante de la liste
        }
    }
    //printf("\nLe nombre d'occurence de %d est %d", data, occurence);
    return occurence; // On retoure finalement le compteur d'occurences
}

// Param�tres : Une T_liste
// R�sultat : Une T_liste
// Definition : Cette fonction lib�re la m�moire prise par une liste
T_liste freeListe(T_liste l)
{
    T_liste ptrCourant = l;
    if (listeVide(l))
    {
        return NULL;
    }
    else
    {
        while(!listeVide(getptrNextCell(ptrCourant)))
        {
            free(getPtrData(ptrCourant));
            ptrCourant = getptrNextCell(ptrCourant);
            free(ptrCourant->prec);
        }
        free(getPtrData(ptrCourant));
        free(ptrCourant);
    }
    return NULL;
}

