#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "liste.h"

// Paramètres : Une T_liste
// Résultat : Aucun
// Definition : Sans allocation dynamique, la fonction initialise à NULL un pointeur de liste
void initListe(T_liste *l)
{
    *l = NULL;
}

// Paramètres : Une T_liste
// Résultat : Un booleen
// Definition : Cette fonction permet de savoir si une liste est vide ou non
bool listeVide(T_liste l)
{
    return (l == NULL);
}

// Paramètres : Une T_liste
// Résultat : Aucun
// Definition : Cette fonction affiche une liste
void afficheListeV1(T_liste l)
{
    T_liste ptrCourant = l; // T_list = struct T_cell*
    printf("Liste\n-----\n");
    while (ptrCourant != NULL)
    {
        printf("%d\n", *(ptrCourant->data));
        ptrCourant = ptrCourant->suiv;
    }
    printf("-----\n\n");
}

// Paramètres : Une T_liste et un entier
// Résultat : Une T_liste mise a jour
// Definition : Cette fonction ajoute une case en tete de liste
T_liste ajoutEnTete(T_liste l, int mydata)
{
    T_liste newl = (T_liste)malloc(sizeof(struct T_cell));
    newl->data = (int *)malloc(sizeof(int));
    *(newl->data) = mydata;

    if (listeVide(l))
    {
        newl->suiv = NULL;
        newl->prec = NULL;
    }
    else
    {
        newl->prec = NULL;
        newl->suiv = l;
        l->prec = newl;
    }

    return newl;
}

/*
void debug(T_liste l)
{
    struct T_cell *ptrCourant = l;
    printf("Liste\n-----\n");
    while (ptrCourant != NULL)
    {
        printf("##########\n");
        printf("# Ptr case d'avant: %X\n", ptrCourant->prec);
        printf("# Ptr de la case courante: %X\n", ptrCourant);
        printf("# Valeur : %d\n", *(ptrCourant->data));
        printf("# Ptr case d'apres: %X\n", ptrCourant->suiv);
        printf("##########\n");
        ptrCourant = ptrCourant->suiv;
    }
    printf("-----\n\n");
}
*/

// Paramètres : Une T_liste et un entier
// Résultat : Une T_liste mise a jour
// Definition : Cette fonction ajoute une case en fin de liste
T_liste ajoutEnFin(T_liste l, int mydata)
{
    T_liste newl = (T_liste)malloc(sizeof(struct T_cell));
    newl->data = (int *)malloc(sizeof(int));
    *(newl->data) = mydata;

    if (listeVide(l))
    {
        newl->suiv = NULL;
        newl->prec = NULL;

        return newl;
    }
    else
    {
        T_liste temp_l = l;
        while (temp_l->suiv != NULL)
        {
            temp_l = temp_l->suiv;
        }
        temp_l->suiv = newl;
        newl->prec = temp_l;
        newl->suiv = NULL;

        return l;
    }
}

// Paramètres : Une T_liste, un entier pos et un entier data
// Résultat : Une T_liste mise a jour
// Definition : Cette fonction ajoute une case en n-ieme position dans la liste
T_liste ajoutEnN(T_liste l, int pos, int mydata)
{

    int len = 0;
    T_liste Cptr_l = l;
    while (Cptr_l->suiv != NULL)
    {
        Cptr_l = Cptr_l->suiv;
        len++;
    }

    if (pos == 0)
    {
        l = ajoutEnTete(l, mydata);
    }
    else if (pos >= len)
    {
        l = ajoutEnFin(l, mydata);
    }
    else
    {
        T_liste newl = (T_liste)malloc(sizeof(struct T_cell));
        newl->data = (int *)malloc(sizeof(int));
        *(newl->data) = mydata;

        T_liste temp_l = l;
        T_liste temp_l2 = l;
        for (int i = 0; i < pos; i++)
        {
            temp_l = temp_l->suiv;
            temp_l2 = temp_l2->suiv;
        }
        temp_l2 = temp_l2->suiv;

        temp_l->suiv = newl;
        newl->prec = temp_l;
        newl->suiv = temp_l2;
        temp_l2->prec = newl;
    }

    return l;
}

// Paramètres : Une T_liste
// Résultat : Une T_liste mise a jour
// Definition : Cette fonction supprime une case en tete de liste et retourne la liste mise a jour
T_liste suppEnTete(T_liste l)
{
    if (listeVide(l))
    {
        return NULL;
    }
    else
    {
        T_liste tmp = l->suiv;
        free(l);
        return tmp;
    }
}

// Paramètres : Une T_liste
// Résultat : Une T_liste mise a jour
// Definition : Cette fonction supprime une case en fin de liste et retourne la liste mise a jour
T_liste suppEnFin(T_liste l)
{
    T_liste tmp = l;
    while (tmp->suiv != NULL)
    {
        tmp = tmp->suiv;
    }
    (tmp->prec)->suiv = NULL;
    free(tmp);
    return l;
}

// Paramètres : Une T_liste
// Résultat : Une T_liste mise a jour
// Definition : Cette fonction supprime une case en n-ieme position dans la liste et retourne la liste mise a jour
T_liste suppEnN(T_liste l, int pos)
{
    if (listeVide(l))
    {
        perror("Erreur : La liste est vide !");
        return l;
    }

    T_liste ptrCourant = l;
    for (int i = 0; i < pos; i++)
    {
        if (ptrCourant == NULL)
        {
            perror("Erreur : la liste n'est pas assez longue !");
            return l;
        }

        ptrCourant = ptrCourant->suiv;
    }

    T_liste casePrec = ptrCourant->prec;
    T_liste caseSuiv = ptrCourant->suiv;

    casePrec->suiv = caseSuiv;
    caseSuiv->prec = casePrec;

    free(ptrCourant->data);
    free(ptrCourant);

    return l;
}

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction retourne la derniere case d'une liste
T_liste getptrLastCell(T_liste l)
{
    struct T_cell *ptrCourant = l;
    if (listeVide(l))
    {
        printf("\nErreur getptrLastCell : Pointeur NULL");
        return NULL;
    }
    else
    {
        // On rembobine la liste afin de retourner le pointeur de la première case
        while (ptrCourant->suiv != NULL)
        {
            ptrCourant = ptrCourant->suiv;
        }
        return ptrCourant;
    }
}

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction retourne la premiere case d'une liste
T_liste getptrFirstCell(T_liste l)
{
    struct T_cell *ptrCourant = l;
    if (listeVide(l))
    {
        printf("\nErreur getptrFirstCell : Pointeur NULL, Liste vide");
        return NULL;
    }
    else
    {
        // On rembobine la liste afin de retourner le pointeur de la première case
        while (ptrCourant->prec != NULL)
        {
            ptrCourant = ptrCourant->prec;
        }
        return ptrCourant;
    }
}

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction retourne la case suivante de la case passee en parametre
T_liste getptrNextCell(T_liste l)
{
    struct T_cell *ptrCourant = l;
    if (listeVide(l))
    {
        printf("\nErreur getptrNextCell : Pointeur NULL, liste vide");
        return NULL;
    }
    else
    {
        return ptrCourant->suiv;
    }
}

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction retourne la case precedente de la case passee en parametre
T_liste getptrPrevCell(T_liste l)
{
    struct T_cell *ptrCourant = l;
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

// Paramètres : Une T_liste
// Résultat : Une T_liste
// Definition : Cette fonction retourne la case n-ieme de la liste en parametre
T_liste getCellEnN(T_liste liste, int n)
{
    T_liste ptrCourant = liste;
    for (int i = 0; i < n; i++)
    {
        ptrCourant = getptrNextCell(ptrCourant);
    }
    return ptrCourant;
}

// Paramètres : Une T_liste
// Résultat : Un entier
// Definition : Cette fonction retourne le champ data de la case en parametre
int *getPtrData(T_liste l)
{
    struct T_cell *ptrCourant = l;
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

// Paramètres : Deux T_liste
// Résultat : Aucun
// Definition : Cette fonction echange les deux champs data des deux cases
void swapPtrData(T_liste source, T_liste destination)
{
    if (listeVide(source) || listeVide(destination))
    {
        return;
    }
    else
    {
        int *entier_temp = destination->data;
        destination->data = source->data;
        source->data = entier_temp;
    }
}

// Paramètres : Une T_liste
// Résultat : Un entier
// Definition : Cette fonction retourne le nombre decase d'une liste
int getNbreCell(T_liste l)
{
    struct T_cell *ptrCourant = l;
    int nombre = 1;
    if (listeVide(l))
    {
        nombre = 0;
        return nombre;
    }
    else
    {
        while (ptrCourant->suiv != NULL)
        {
            ptrCourant = ptrCourant->suiv;
            nombre = nombre + 1;
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre;
    }
}

// Paramètres : Une T_liste et un entier
// Résultat : Un entier
// Definition : Cette fonction donne le nombre de fois qu'apparait l'entier en paramètre dans la liste
int getOccurences(T_liste l, int data)
{
    T_liste ptrCourant = l;
    int occurence = 0;

    if (listeVide(l))
    {
        //printf("\nListe vide, l'element n'apparait aucune fois");
        return 0;
    }
    else
    {
        while (ptrCourant != NULL)
        {
            if (*(ptrCourant->data) == data)
            {
                occurence++;
            }
            ptrCourant = ptrCourant->suiv;
        }
    }
    //printf("\nLe nombre d'occurence de %d est %d", data, occurence);
    return occurence;
}

// Paramètres : Une T_liste
// Résultat : Aucun
// Definition : Cette fonction tri une lste avec un tri par selection
void tri_selection_liste(T_liste l)
{
    T_liste current, j, min;
    for (current = l; getptrNextCell(current) != NULL; current = getptrNextCell(current))
    {
        min = current;
        for (j = current; j != NULL; j = getptrNextCell(j))
        {
            if (*(getPtrData(j)) < *(getPtrData(min)))
            {
                min = j;
            }
        }
        swapPtrData(current, min);
    }
}

// Paramètres : Une T_liste
// Résultat : Un booleen
// Definition : Cette fonction verifie si une liste est triee
bool verifTriListe(T_liste l)
{
    T_liste ptrCourant = l;
    if (listeVide(l))
    {
        //printf("\nLISTE TRIEE");
        return true;
    }
    else
    {
        while (getptrNextCell(ptrCourant) != NULL)
        {
            if (*(getPtrData(ptrCourant)) <= *(getPtrData(getptrNextCell(ptrCourant))))
            {
                ptrCourant = getptrNextCell(ptrCourant);
            }
            else
            {
                //printf("\nLISTE NON TRIEE");
                return false;
            }
        }
        //printf("\nLISTE TRIEE");
        return true;
    }
}
