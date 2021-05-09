#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jungle.h"
#include "liste.h"

// Paramètres : Un pointeur vers un T_liane
// Résultat : Aucun
// Definition : Cette fonction permet d'initialiser une liane sans case a un pointeur nul
void initLiane(T_liane *l)
{
    *l = NULL;
}

// Paramètres : Une T_jungle
// Résultat : Un booleen
// Definition : Cette fonction permet de savoir si une jungle est vide ou non
void initJungle(T_jungle *j)
{
    *j = NULL;
}

// Paramètres : Une T_jungle
// Résultat : Un booleen
// Definition : Cette fonction permet de savoir si une jungle est vide ou non
bool jungleVide(T_jungle j)
{
    return (j == NULL);
}

// Paramètres : Un T_jungle
// Résultat : Un T_jungle
// Definition : Cette fonction retourne la liane suivante de la jungle donnee en parametre
T_jungle getNextLiane(T_jungle j)
{
    T_jungle ptrCourant = j; // Declaration d'un pointeur permettant de parcourir la jungle à travers les lianes
    if (jungleVide(j))       // Si la jungle est vide on retourne null
    {
        printf("\nErreur getNextLiane : Liste vide");
        return NULL;
    }
    else // Sinon on retourne le pointeur vers la liane suivante
    {
        return ptrCourant->suiv;
    }
}

// Paramètres : Un T_jungle
// Résultat : Un T_jungle
// Definition : Cette fonction retourne la liane précédente de la jungle donnee en parametre
T_jungle getPrecLiane(T_jungle j)
{
    T_jungle ptrCourant = j; // Declaration d'un pointeur permettant de parcourir la jungle à travers les lianes
    if (jungleVide(j))       // Si la jungle est vide on retourne null
    {
        printf("\nErreur getPrecLiane : Liste vide");
        return NULL;
    }
    else // Sinon on retourne le pointeur vers la liane précédente
    {
        return ptrCourant->prec;
    }
}

// Paramètres : Un T_jungle
// Résultat : Une T_liane
// Definition : Cette fonction retourne la liane courante de la jungle donnee en parametre
T_liane *getLiane(T_jungle j)
{
    T_jungle ptrCourant = j;
    if (jungleVide(j)) // Si la jungle est vide on retourne null
    {
        printf("\nErreur getLiane : Liste vide");
        return NULL;
    }
    else // Sinon on retourne le pointeur vers la liane courante
    {
        return ptrCourant->courante;
    }
}

// Paramètres : Un T_jungle et un entier n
// Résultat : Un T_jungle
// Definition : Cette fonction retourne la n-ieme liane de la jungle donnee en parametre
T_jungle getLianeEnN(T_jungle jungle, int n)
{
    T_jungle ptrCourant = jungle;
    for (int i = 0; i <= n; i++)
    {
        ptrCourant = getNextLiane(ptrCourant);
    }
    return ptrCourant;
}

// Paramètres : Un T_jungle
// Résultat : Un entier
// Definition : Cette fonction retourne le nombre de lianes d'une jungle
int getNombreLiane(T_jungle j)
{
    T_jungle ptrCourant = j; // Declaration d'un pointeur permettant de parcourir la jungle à travers les lianes
    int compteur = 1;        // Declaration d'un compteur qui s'incrémentera selon le nombre de lianes compté
    if (jungleVide(j))       // Si la jungle est vide alors le nombre de lianes vaut 0
    {
        return compteur = 0;
    }
    else // Sinon
    {
        while (ptrCourant->suiv != NULL) // Tant que la case après la liane courante n'est pas nulle (on parcourt toute la jungle à travers chaque liane)
        {
            ptrCourant = ptrCourant->suiv; // On va sur la liane suivante grâce au pointeur courant
            compteur++;                    // Le compteur s'incrémente de un
        }
        return compteur; // Enfin on retourne la valeur du compteur
    }
}

// Paramètres : Un T_liane source et une nombre
// Résultat : Un T_liane mis a jour
// Definition : Cette fonction ajoute une nouvelle case à la liane en la chainant correctement
T_liane ajoutNombreALiane(T_liane l, int nombre)
{
    return ajoutEnFin(l, nombre); // Appel a la fonction de la bibliotheque de liste
}

// Paramètres : Un T_jungle et une T_liane
// Résultat : Un T_jungle
// Definition : Cette fonction ajoute une liane à la jungle passée en paramètre
T_jungle ajoutLianeAJungle(T_jungle j, T_liane l)
{
    T_jungle newj = (T_jungle)malloc(sizeof(struct T_jungle_cell)); // Allocation de la nouvelle case pour la liane
    newj->courante = (T_liane *)malloc(sizeof(T_liane));            // Allocation de la nouvelle liane
    *(newj->courante) = l;                                          // On affecte la liane à la nouvelle case

    if (jungleVide(j)) // Si la jungle est vide on cree une nouvelle case avec les pointeurs prec et suiv a NULL (il n'y a donc pas de lianes avant et après)
    {
        newj->prec = NULL;
        newj->suiv = NULL;
        return newj;
    }
    else // Sinon on ajoute la nouvelle case en la chainant avec la jungle donnee en parametre
    {
        T_jungle temp = j;
        while (temp->suiv != NULL)
        {
            temp = temp->suiv;
        }
        newj->prec = temp;
        newj->suiv = NULL;
        temp->suiv = newj;
    }

    return j;
}

/*
void debugJungle(T_jungle j)
{
    T_jungle ptrCourant = j;
    printf("Jungle\n-----\n");
    while (ptrCourant != NULL)
    {
        printf("##########\n");
        printf("# Ptr case d'avant: %X\n", ptrCourant->prec);
        printf("# Ptr de la case courante: %X\n", ptrCourant);
        printf("# Ptr vers la liane : %X\n", ptrCourant->courante);
        printf("# Ptr case d'apres: %X\n", ptrCourant->suiv);
        printf("##########\n");
        ptrCourant = ptrCourant->suiv;
    }
    printf("-----\n\n");
}*/

// Paramètres : Un T_singe
// Résultat : Aucun
// Definition : Cette fonction affiche la liste des entiers preferes du singe
void afficheListePref(T_singe s)
{
    afficheListeV1(s.listeIntPreferes);
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
    T_liane liane;     // Declaration de la liane
    initLiane(&liane); // Et son initialisation
    int longueur_liane, valeur;

    longueur_liane = (rand() % (LONGUEUR_MAX - LONGUEUR_MIN - 1) + LONGUEUR_MIN); // Genere la longueur de la liane de facon aleatoire

    for (int i = 0; i < longueur_liane; i++) // Pour chaque point d'accroche de la liane
    {
        valeur = (rand() % (VAL_MAX - VAL_MIN - 1) + VAL_MIN); // Genere la valeur du point d'accroche
        liane = ajoutNombreALiane(liane, valeur);              // Et le chaine a la liane
    }

    return liane; // Retourne le pointeur sur la premiere case de la liane
}

#define NOMBRE_MAX_LIANES 10
#define NOMBRE_MIN_LIANES 5

// Paramètres : Aucun
// Résultat : Un T_jungle
// Definition : Cette fonction permet de créer une jungle en faisant appel à la fonction d'ajout de liane à jungle à répétition
T_jungle genererJungle()
{
    T_jungle jungle;
    initJungle(&jungle); // On déclare une jungle
    T_liane liane;       // On déclare une liane
    int nombre_lianes;   // On déclare le nombre de lianes

    nombre_lianes = (rand() % (NOMBRE_MAX_LIANES - NOMBRE_MIN_LIANES - 1) + NOMBRE_MIN_LIANES); // Creation d'un nombre de lianes aléatoire entre 5 et 10 grâce aux DEFINE au-dessus de la fonction

    for (int i = 0; i < nombre_lianes; i++) // Pour i allant de 0 au nombre de lianes
    {
        liane = genererLiane();                    // On fait appel à la fonction de génération d'une liane
        jungle = ajoutLianeAJungle(jungle, liane); // Puis on ajoute la liane créée à la jungle
    }
    return jungle; // On retourne la jungle finale
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller une case au dessus sur la liane suivante
bool verifHaut(T_jungle jungle, T_singe singe)
{
    T_liane liane_suivante = *(getLiane(getNextLiane(jungle)));
    if (singe.posY == 0 || getNbreCell(liane_suivante) - 1 < singe.posY - 1) // Si le singe est sur le point d'accorche le plus haut ou si le nombre de points d'accroche de la liane suivante est inférieure de 2 cases ou plus par rapport à la hauteur du singe actuelle
    {
        return false; // Alors la fonction retourne que ce n'est pas possible
    }
    int nombreCible = *(getPtrData(getCellEnN(liane_suivante, singe.posY - 1))); // Sinon il monte d'une case sur la prochaine case
    if (getOccurences(singe.listeIntPreferes, nombreCible) >= 1)
    {
        return true;
    }
    return false;
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller en face sur la liane suivante
bool verifFace(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));

    if (getNbreCell(lianeSuivante) - 1 >= singe.posY)
    {
        int nombreCible = *(getPtrData(getCellEnN(lianeSuivante, singe.posY)));
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
        {
            return true;
        }
    }
    return false;
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller en face sur la liane suivante
bool verifBas(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));

    if (getNbreCell(lianeSuivante) - 1 >= singe.posY + 2)
    {
        int nombreCible = *(getPtrData(getCellEnN(lianeSuivante, singe.posY + 2)));
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
        {
            return true;
        }
    }
    return false;
}

// Paramètres : Une T_jungle, un T_singe et un pointeur sur un entier
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller sur la première liane et donc si le jeu peut commencer
bool verifDebut(T_jungle jungle, T_singe singe, int *indice)
{
    T_liane premiere_liane = *(getLiane(jungle));
    int nombreCible;

    while (!listeVide(premiere_liane))
    {
        nombreCible = *(getPtrData(premiere_liane));
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
        {
            return true;
        }
        else
        {
            premiere_liane = getptrNextCell(premiere_liane);
            *indice += 1;
        }
    }
    return false;
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si on est à la fin (si le singe est sur la dernière liane)
bool verifFin(T_jungle jungle, T_singe singe)
{
    int nombreLianes = getNombreLiane(jungle);
    return (singe.posX == nombreLianes - 1);
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va en haut ou non
bool allerEnHaut(T_jungle jungle, T_singe *singe)
{
    if (verifHaut(jungle, *singe))
    {
        singe->posX++;
        singe->posY--;
        return true;
    }
    return false;
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va en face ou non
bool allerEnFace(T_jungle jungle, T_singe *singe)
{
    if (verifFace(jungle, *singe))
    {
        singe->posX++;
        return true;
    }
    return false;
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va en bas ou non
bool allerEnBas(T_jungle jungle, T_singe *singe)
{
    if (verifBas(jungle, *singe))
    {
        singe->posX++;
        singe->posY += 2;
        return true;
    }
    return false;
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va sur la première liane et commence le jeu ou non
void allerPremiereLiane(T_jungle jungle, T_singe *singe)
{
    int indice = 0;
    if (verifDebut(jungle, *singe, &indice))
    {
        singe->posX = 0;
        singe->posY = indice;
    }
    else
    {
        sauterEau();
    }
}

// Paramètres : Aucun
// Résultat : Aucun
// Definition : Cette fonction permet de faire sauter le singe à l'eau (affichage d'un printf console) et de terminer le programme
void sauterEau()
{
    printf("\nPLOUF !\n");
    exit(EXIT_SUCCESS);
}

// Paramètres : Une T_jungle
// Résultat : Aucun
// Definition : Cette fonction permet de trier la liane suivante (après celle pointée actuellement)
void triLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle)));
    tri_selection_liste(liane);
}

// Paramètres : Une T_jungle
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si une liane est triée ou non
bool verifTriLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle)));
    return verifTriListe(liane);
}
