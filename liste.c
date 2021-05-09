#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "liste.h"

// Paramètres : Une T_liste
// Résultat : Aucun
// Definition : Sans allocation dynamique, la fonction initialise à NULL un pointeur de liste
void initListe(T_liste *l)
{
    *l=NULL;
}

// Paramètres : Une T_liste
// Résultat : Un booleen
// Definition : Cette fonction permet de savoir si une liste est vide ou non
bool listeVide( T_liste l)
{
    return (l==NULL);
}

// Paramètres : Une T_liste et un entier
// Résultat : Une T_liste
// Definition : Cette fonction ajoute un entier à la liste passée en paramètre
T_liste ajoutEnTete(T_liste l, int mydata)
{
    T_liste newl = (T_liste)malloc(sizeof(struct T_cell)); // Allocation de la nouvelle case pour l'entier
    newl -> data = (int *)malloc(sizeof(int)); // Allocation du nouvel entier
    *(newl -> data) = mydata; // On affecte l'entier à la nouvelle case

    if (listeVide(l)) // Si la liste est vide on cree une nouvelle case avec les pointeurs prec et suiv a NULL (il n'y a donc pas de cases avant et après)
    {
        newl -> suiv = NULL;
        newl -> prec = NULL;
    }
    else // Sinon on ajoute la nouvelle case en la chainant avec la liste donnee en parametre (ajout en tete pour une meilleure complexité)
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

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction donne le pointeur de la case suivante de celle pointée en paramètre de la liste
T_liste getptrNextCell(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    if (listeVide(l)) // Si la liste est vide (appel à la fonction auxilliaire)
    {
        //printf("\nErreur getptrNextCell : Pointeur NULL, liste vide");
        return NULL; // Retourne NULL
    }
    else // Sinon
    {
        return ptrCourant->suiv; // On retourne le pointeur suiv de la case courante
    }
}

// Paramètres : Une T_liste
// Résultat : Un pointeur d'un entier
// Definition : Cette fonction donne le pointeur de l'entier de la case pointée de la liste en paramètre
int* getPtrData(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    if (listeVide(l)) // Si la liste est vide (appel à la fonction auxilliaire)
    {
        return NULL; // Retourne NULL
    }
    else
    {
        //printf("\nValeur : %X\n", ptrCourant->data);
        return ptrCourant->data; // On retourne le pointeur de l'entier de la case courante
    }
}

// Paramètres : Une T_liste
// Résultat : Aucun
// Definition : Cette fonction permet d'afficher une liste
void afficheListeV1(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    printf("Liste\n-----\n");
    while(!listeVide(ptrCourant)) // On parcourt toutes les cases de la liste
    {
        printf("%d\n",*(getPtrData(ptrCourant))); // On affiche l'entier pointé par la case courante
        ptrCourant = getptrNextCell(ptrCourant); // Le pointeur courant pointe sur la case suivante pour continuer le parcours
    }
    printf("-----\n\n");
}

// Paramètres : Une T_liste
// Résultat : Un entier
// Definition : Cette fonction donne le nombre de cellules d'une liste
int getNbreCell(T_liste l)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    int nombre = 1; // On intialise le compteur de case à 1
    if (listeVide(l)) // Si la liste est vide
    {
        return 0; // On retourn 0 (il y a 0 cases)
    }
    else // Sinon
    {
        while (getptrNextCell(ptrCourant) != NULL) // On parcourt toutes les cases de la liste
        {
            ptrCourant = getptrNextCell(ptrCourant); // Le pointeur courant pointe la case suivante par appel d'une fonction auxilliaire
            nombre++; // Le compteur s'incrémente de un
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre; // On retourne le nombre
    }
}

// Paramètres : Une T_liste et un entier
// Résultat : Un entier
// Definition : Cette fonction donne le nombre de fois qu'apparait l'entier en paramètre dans la liste
int getOccurences(T_liste l, int data)
{
    T_liste ptrCourant = l; // Declaration d'un pointeur permettant de parcourir la liste
    int occurence = 0; // Initialiser du compteur à 0

    if (listeVide(l)) // Si la liste est vide
    {
        printf("\nListe vide, l'element n'apparait aucune fois");
        return 0; // Le nombre d'occurences est égal à 0
    }
    else // Sinon
    {
        while(!listeVide(ptrCourant)) // Parcours de toute la liste
        {
            if (*(getPtrData(ptrCourant)) == data) // Si le nombre entré en paramètre est égal à la valeur pointée de la case pointée
            {
                occurence++; // Alors le compteur d'occurence est incrémenté de 1
            }
            ptrCourant = getptrNextCell(ptrCourant); // Le pointeur courante pointe sur la case suivante de la liste
        }
    }
    //printf("\nLe nombre d'occurence de %d est %d", data, occurence);
    return occurence; // On retoure finalement le compteur d'occurences
}

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction libère la mémoire prise par une liste
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

