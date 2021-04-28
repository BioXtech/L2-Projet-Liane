#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "liste.h"

//initListe ne fait pas de malloc, juste une initialisation � NULL du pointeur de liste
void initListe(T_liste *l)
{
    *l=NULL;
}


bool listeVide( T_liste l)
{
    return (l==NULL);
}

//A vous la suite
/*
void afficheListeV1( T_liste l){
    if (listeVide(l))
    {
        printf("\nLa liste doublement chainee est vide\n");
    }
    //else if (l -> suiv = NULL){
    //    printf("\nValeur unique : %d \n", *(l -> data));
   // }
    else
    {
        while(l -> suiv != NULL){
            printf("Valeur : %d \n", *(l -> data));
            l = l  -> suiv;
        }
    }
}
*/

void afficheListeV1(T_liste l)
{
    T_liste ptrCourant = l; // T_list = struct T_cell*
    printf("Liste\n-----\n");
    while(ptrCourant != NULL)
    {
        printf("%d\n",*(ptrCourant->data));
        ptrCourant = ptrCourant->suiv;
    }
    printf("-----\n\n");
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
        newl -> suiv = l;
        l -> prec = newl;
    }

    return newl;
}


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

//dans cette version "l" est un pointeur sur le pointeur de la 1ere cellule.
void ajoutEnTetePtr2Ptr(T_liste *l, int mydata)
{
    T_liste nouv = (T_liste)malloc(sizeof(struct T_cell));
    //struct T_cell * nouv = (struct T_cell *)malloc(sizeof(struct T_cell))  //equivalent
    nouv->data = (int*)malloc(sizeof(int));
    *(nouv->data)=mydata;

    if (*l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;
        nouv->prec = NULL;
    }
    else  // la lste n'etait pas vide, on doit donc faire les branchements
    {
        nouv->suiv = *l;
        (*l)->prec = nouv;
    }
    //on modifie l'adresse de la t�te de la liste, soit le contenu point� par l
    *l=nouv;
}


T_liste ajoutEnFin(T_liste l, int mydata)
{
    T_liste newl = (T_liste)malloc(sizeof(struct T_cell));
    newl -> data = (int *)malloc(sizeof(int));
    *(newl -> data) = mydata;

    if (listeVide(l))
    {
        newl -> suiv = NULL;
        newl -> prec = NULL;

        return newl;
    }
    else
    {
        T_liste temp_l = l;
        while( temp_l -> suiv != NULL)
        {
            temp_l = temp_l -> suiv;
        }
        temp_l -> suiv = newl;
        newl -> prec = temp_l;
        newl -> suiv = NULL;

        return l;
    }
}


T_liste ajoutEnN(T_liste l, int pos, int mydata)
{

    int len = 0;
    T_liste Cptr_l = l;
    while (Cptr_l -> suiv != NULL)
    {
        Cptr_l = Cptr_l -> suiv;
        len++;
    }

    if (pos == 0)
    {
        l = ajoutEnTete(l, mydata);
    }
    else if(pos >= len)
    {
        l = ajoutEnFin(l, mydata);
    }
    else
    {
        T_liste newl = (T_liste)malloc(sizeof(struct T_cell));
        newl -> data = (int *)malloc(sizeof(int));
        *(newl -> data) = mydata;

        T_liste temp_l = l;
        T_liste temp_l2 = l;
        for(int i = 0; i < pos; i ++)
        {
            temp_l = temp_l -> suiv;
            temp_l2 = temp_l2 -> suiv;
        }
        temp_l2 = temp_l2 -> suiv;

        temp_l -> suiv = newl;
        newl -> prec = temp_l;
        newl -> suiv = temp_l2;
        temp_l2 -> prec = newl;
    }

    return l;
}


T_liste suppEnTete(T_liste l)
{
    if (listeVide(l))
    {
        return NULL;
    }
    else
    {
        T_liste tmp = l -> suiv;
        free(l);
        return tmp;
    }
}

T_liste suppEnFin(T_liste l)
{
    T_liste tmp = l;
    while(tmp->suiv != NULL)
    {
        tmp = tmp->suiv;
    }
    (tmp->prec)->suiv = NULL;
    free(tmp);
    return l;
}

T_liste suppEnN(T_liste l, int pos)
{
    if(listeVide(l))
    {
        perror("Erreur : La liste est vide !");
        return l;
    }

    T_liste ptrCourant = l;
    for(int i = 0; i < pos; i++)
    {
        if(ptrCourant == NULL)
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
        while(ptrCourant -> suiv != NULL)
        {
            ptrCourant = ptrCourant->suiv;
        }
        return ptrCourant;
    }
}

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
        while(ptrCourant -> prec != NULL)
        {
            ptrCourant = ptrCourant->prec;
        }
        return ptrCourant;
    }
}


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

T_liste getCellEnN(T_liste liste, int n)
{
    T_liste ptrCourant = liste;
    for(int i = 0; i < n; i++)
    {
        ptrCourant = getptrNextCell(ptrCourant);
    }
    return ptrCourant;
}

int* getPtrData(T_liste l)
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

void swapPtrData( T_liste source, T_liste destination )
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

int getSizeBytes(T_liste l)
{
    int nbre_octets = sizeof(struct T_cell) *getNbreCell(l);
    printf("\n Nombre d'octets : %d", nbre_octets);
    return nbre_octets;
}

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2)
{
    T_liste ptrCourantl1 = l1;
    T_liste ptrCourantl2 = l2;
    T_liste liste_finale;
    initListe(&liste_finale);

    if (listeVide(l1))
    {
        return ptrCourantl2;
    }
    else if (listeVide(l2))
    {
        return ptrCourantl1;
    }
    else
    {
        while(ptrCourantl1 != NULL)
        {
            liste_finale = ajoutEnFin(liste_finale, *(getPtrData(ptrCourantl1)));
            ptrCourantl1 = ptrCourantl1->suiv;
        }
        while(ptrCourantl2 != NULL)
        {
            liste_finale = ajoutEnFin(liste_finale, *(getPtrData(ptrCourantl2)));
            ptrCourantl2 = ptrCourantl2->suiv;
        }
        return liste_finale;
    }
}


T_liste addBehind(T_liste debut, T_liste suite)
{
    T_liste ptrCourantl1 = debut;
    T_liste ptrCourantl2 = suite;

    if (listeVide(debut))
    {
        return ptrCourantl2;
    }
    else if (listeVide(suite))
    {
        return ptrCourantl1;
    }
    else
    {
        while(ptrCourantl2 != NULL)
        {
            int valeur = *(getPtrData(ptrCourantl2));
            debut = ajoutEnFin(debut, valeur);
            ptrCourantl2 = ptrCourantl2->suiv;
        }
        return debut;
    }
}


T_liste findCell(T_liste l, int data)
{
    T_liste ptrCourant = l;
    if (listeVide(l))
    {
        return NULL;
    }
    else
    {
        while(ptrCourant != NULL && (*(ptrCourant->data) != data))
        {
            ptrCourant = ptrCourant->suiv;
        }

        if(ptrCourant != NULL)
        {
            //printf("\nLe pointeur de la cellule recherchee est : %X", ptrCourant);
            return ptrCourant;
        }
        else
        {
            //printf("\nL'element recherche n'est pas dans la liste doublement chainee");
            return NULL;
        }
    }
}

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
        while(ptrCourant != NULL)
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

void tri_selection_liste(T_liste l)
{
    T_liste current, j, min;
    for(current = l; getptrNextCell(current) != NULL; current = getptrNextCell(current))
    {
        min = current;
        for(j = current; j != NULL; j = getptrNextCell(j))
        {
            if(*(getPtrData(j))< *(getPtrData(min)))
            {
                min = j;
            }
        }
        swapPtrData(current,min);
    }
}

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
