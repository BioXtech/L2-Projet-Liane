#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "liane.h"
#include "types.h"

// Paramètres : Un pointeur vers un T_liane
// Résultat : Aucun
// Definition : Cette fonction permet d'initialiser une liane sans case a un pointeur nul
void initLiane(T_liane *l)
{
    *l = NULL;
}

// Paramètres : Une T_liane
// Résultat : Un booléen
// Definition : Cette fonction permet de savoir si une liane est vide ou non
bool lianeVide(T_liane l)
{
    return (l==NULL);
}

// Paramètres : Un T_liane
// Résultat : Aucun
// Definition : Cette fonction permet d'afficher toutes les valeurs de la struct d'une T_liane pour voir notament le chainage de la liste
void debugLiane(T_liane l)
{
    T_liane ptrCourant = l;
    printf("Liste\n-----\n");
    while(ptrCourant != NULL) //Pour chaque case affichee
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


// Paramètres : Un T_liane source et une nombre
// Résultat : Un T_liane mis a jour
// Definition : Cette fonction ajoute une nouvelle case en tete de la liane en la chainant correctement
T_liane ajoutNombreALiane(T_liane l, int nombre)
{
    T_liane newl = (T_liane)malloc(sizeof(struct T_cell_liane)); // Allocation de la nouvelle case
    newl->data = initPointAccroche(); // Allocation du nouveau point d'accroche
    remplirPointAccroche(newl->data, nombre, NULL); // Remplissage des valeurs du nouveau point d'accroche

    if (lianeVide(l)) // Si la liste est vide on cree une nouvelle case avec les pointeurs prec et suiv a NULL
    {
        newl->suiv = NULL;
        newl->prec = NULL;
    }
    else // Sinon on ajoute la nouvelle case en la chainant avec la liste donnee en parametre
    {
        newl->prec = NULL;
        newl->suiv = l;
        l->prec = newl;
    }

    return newl; // On retourne le pointeur sur la nouvelle tete de liste
}

#define LONGUEUR_MIN 4 // Longueur min et max d'une liane
#define LONGUEUR_MAX 10
#define VAL_MIN 0 // Valeur min et max d'un point d'accroche
#define VAL_MAX 9

// Paramètres : Aucun
// Résultat : Une T_liane
// Definition : Cette fonction permet de generer une T_liane
T_liane genererLiane()
{
    T_liane liane; // Declaration de la liane
    initLiane(&liane); // Et son initialisation
    int longueur_liane, valeur;

    longueur_liane = (rand() % (LONGUEUR_MAX - LONGUEUR_MIN - 1) + LONGUEUR_MIN); // Genere la longueur de la liane de facon aleatoire

    for (int i = 0; i < longueur_liane; i++) // Pour chaque point d'accroche de la liane
    {
        valeur = (rand() % (VAL_MAX - VAL_MIN - 1) + VAL_MIN); // Genere la valeur du point d'accroche
        liane = ajoutNombreALiane(liane, valeur); // Et le chaine a la liane
    }

    return liane; // Retourne le pointeur sur la premiere case de la liane
}

// Paramètres : Un T_liane
// Résultat : Un T_liane
// Definition : Cette fonction retourne le point d'accroche suivant de la liane donnee en parametre
T_liane getptrNextPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l)) // Si la liane est vide on retourne null
    {
        printf("\nErreur getptrNextPA : Pointeur NULL, liste vide");
        return NULL;
    }
    else // Sinon on retourne le pointeur vers la case suivante
    {
        return ptrCourant->suiv;
    }
}

// Paramètres : Un T_liane
// Résultat : Un T_liane
// Definition : Cette fonction retourne le point d'accroche precedent de la liane donnee en parametre
T_liane getptrPrevPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l)) // Si la liane est vide on retourne null
    {
        printf("\nErreur getptrPrevPA : Pointeur NULL, liste vide");
        return NULL;
    }
    else // Sinon on retourne le pointeur vers la case precedente
    {
        return ptrCourant->prec;
    }
}

// Paramètres : Un T_liane
// Résultat : Un T_liane
// Definition : Cette fonction retourne le dernier point d'accroche de la liane donnee en parametre
T_liane getptrLastPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l)) // Si la liane est vide on retourne null
    {
        printf("\nErreur getptrLastPA : Pointeur NULL");
        return NULL;
    }
    else // Sinon
    {
        // On avance dans la liste afin de retourner le pointeur de la derniere case
        while(getptrNextPA(ptrCourant) != NULL)
        {
            ptrCourant = getptrNextPA(ptrCourant);
        }
        return ptrCourant;
    }
}

// Paramètres : Un T_liane
// Résultat : Un T_liane
// Definition : Cette fonction retourne le premier point d'accroche de la liane donnee en parametre
T_liane getptrFirstPA(T_liane l)
{
    T_liane ptrCourant = l;
    if (lianeVide(l)) // Si la liane est vide on retourne null
    {
        printf("\nErreur getptrFirstPA : Pointeur NULL, Liane vide");
        return NULL;
    }
    else // Sinon
    {
        // On rembobine la liste afin de retourner le pointeur de la première case
        while(getptrPrevPA(ptrCourant) != NULL)
        {
            ptrCourant = getptrPrevPA(ptrCourant);
        }
        return ptrCourant;
    }
}

// Paramètres : Un T_liane et un entier
// Résultat : Un T_liane
// Definition : Cette fonction retourne le n-ieme point d'accroche d'une liane
T_liane getPAEnN(T_liane liane, int n)
{
    T_liane ptrCourant = liane; // Declaration d'un pointeur courant pour parcourir la liste
    for(int i = 0; i < n; i++) // On avance jusqu'a la case n
    {
        ptrCourant = getptrNextPA(ptrCourant);
    }
    return ptrCourant; // On retourne la case demandee
}

// Paramètres : Un T_liane
// Résultat : Un entier
// Definition : Cette fonction retourne le nombre de point d'accroche d'une liane
int getNbrePA(T_liane l)
{
    T_liane ptrCourant = l; // Declaration d'un pointeur courant pour parcourir la liste
    int nombre = 1; // Initialisation du compteur
    if (lianeVide(ptrCourant)) // Si la liste est vide on retourne 0
    {
        nombre = 0;
        return nombre;
    }
    else // Sinon
    {
        while (getptrNextPA(ptrCourant) != NULL) // On parcourt chaque case jusqu'a la fin et on incremente le compteur de 1 a chaque case
        {
            ptrCourant = getptrNextPA(ptrCourant);
            nombre = nombre + 1;
        }
        //printf("\n Le nombre de cellules est : %d\n", nombre);
        return nombre;
    }
}

// Paramètres : Un T_liane
// Résultat : Un pointeur vers un point d'accroche
// Definition : Cette fonction retourne le pointeur vers le point d'accroche
T_pointAccroche *getPA(T_liane l)
{
    if (lianeVide(l)) // Si la liste est vide on retourne un pointeur nul
    {
        return NULL;
    }
    else // Sinon on retourne la valeur du champ data de la case de la liane en parametre
    {
        return l->data;
    }
}

// Paramètres : Un T_liane
// Résultat : Un entier
// Definition : Cette fonction retourne la hauteur d'un singe sur une liane
int getHauteurSinge(T_liane l)
{
    T_liane ptrCourant = l; // Declaration d'un pointeur courant
    int nombre = 0; // Compteur
    if (lianeVide(ptrCourant)) // Si la liste est vide on retourne -1 (0 etant la premiere case d'une liane)
    {
        return -1;
    }
    else // Sinon
    {
        while (!verifSingePresent(*getPA(ptrCourant))) // Tant qu'un point d'accroche ne contient pas de singe
        {
            ptrCourant = getptrNextPA(ptrCourant); // On avance d'une case
            nombre++; // On incremente le compteur
        }
        return nombre; // Puis on retourne la hauteur du singe
    }
}

// Paramètres : Deux T_lianes
// Résultat : Aucun
// Definition : Cette fonction echange la position de deux points d'accroche en echangeant les pointeurs data dans la liane
void swapPA( T_liane source, T_liane destination )
{
    if (!lianeVide(source) && !lianeVide(destination)) // Si les deux cases passees en parametres ne sont pas vide
    {
        T_pointAccroche *entier_temp = destination->data; // On echange les deux pointeurs data
        destination->data = source->data;
        source->data = entier_temp;
    }
}

// Paramètres : Un T_liane
// Résultat : Aucun
// Definition : Cette fonction trie les points d'accroche d'une liane avec un tri par selection
void tri_selection_liane(T_liane l)
{
    T_liane current, j, min;
    for(current = l; getptrNextPA(current) != NULL; current = getptrNextPA(current)) // Pour chaque case
    {
        min = current; // On considere que la case a remplacer est la case actuelle
        for(j = current; j != NULL; j = getptrNextPA(j)) // On va chercher dans le reste du tableu la case la plus petite
        {
            if(getValPointAccroche(*(getPA(j)))< getValPointAccroche(*(getPA(min)))) // Si la case recherchee est plus petite que la case a remplacer
            {
                min = j; // On garde en memoire l'empalcement de la plus petite case trouvee
            }
        }
        swapPA(current,min); // Et a la fin on echange les deux cases
    }
}
