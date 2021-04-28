#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jungle.h"
#include "liste.h"

void initLiane(T_liane *l)
{
    *l = NULL;
}

void initJungle(T_jungle *j)
{
    *j = NULL;
}

bool jungleVide(T_jungle j)
{
    return (j == NULL);
}

T_jungle getNextLiane(T_jungle j)
{
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

T_jungle getPrecLiane(T_jungle j)
{
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

T_liane *getLiane(T_jungle j)
{
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

T_jungle getLianeEnN(T_jungle jungle, int n)
{
    T_jungle ptrCourant = jungle;
    for (int i = 0; i <= n; i++)
    {
        ptrCourant = getNextLiane(ptrCourant);
    }
    return ptrCourant;
}

int getNombreLiane(T_jungle j)
{
    T_jungle ptrCourant = j;
    int compteur = 1;
    if (jungleVide(j))
    {
        return compteur = 0;
    }
    else
    {
        while (ptrCourant->suiv != NULL)
        {
            ptrCourant = ptrCourant->suiv;
            compteur += 1;
        }
        return compteur;
    }
}

T_liane ajoutNombreALiane(T_liane l, int nombre)
{
    return ajoutEnFin(l, nombre);
}

T_jungle ajoutLianeAJungle(T_jungle j, T_liane l)
{
    T_jungle newj = (T_jungle)malloc(sizeof(struct T_jungle_cell));
    newj->courante = (T_liane *)malloc(sizeof(T_liane));
    *(newj->courante) = l;

    if (jungleVide(j))
    {
        newj->prec = NULL;
        newj->suiv = NULL;
        return newj;
    }
    else
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
}

void afficheListePref(T_singe s)
{
    afficheListeV1(s.listeIntPreferes);
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

#define NOMBRE_MAX_LIANES 10
#define NOMBRE_MIN_LIANES 5

T_jungle genererJungle()
{
    T_jungle jungle;
    initJungle(&jungle);
    T_liane liane;
    int nombre_lianes;

    nombre_lianes = (rand() % (NOMBRE_MAX_LIANES - NOMBRE_MIN_LIANES - 1) + NOMBRE_MIN_LIANES);

    for (int i = 0; i < nombre_lianes; i++)
    {
        liane = genererLiane();
        jungle = ajoutLianeAJungle(jungle, liane);
    }
    return jungle;
}

bool verifHaut(T_jungle jungle, T_singe singe)
{
    T_liane liane_suivante = *(getLiane(getNextLiane(jungle)));
    if (singe.posY == 0 || getNbreCell(liane_suivante)-1 < singe.posY-1)
    {
        return false;
    }
    int nombreCible = *(getPtrData(getCellEnN(liane_suivante, singe.posY - 1)));
    if (getOccurences(singe.listeIntPreferes, nombreCible) >= 1)
    {
        return true;
    }
    return false;
}

bool verifFace(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));

    if (getNbreCell(lianeSuivante)-1 >= singe.posY)
    {
        int nombreCible = *(getPtrData(getCellEnN(lianeSuivante, singe.posY)));
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
        {
            return true;
        }
    }
    return false;
}

bool verifBas(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));

    if (getNbreCell(lianeSuivante)-1 >= singe.posY + 2)
    {
        int nombreCible = *(getPtrData(getCellEnN(lianeSuivante, singe.posY + 2)));
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
        {
            return true;
        }
    }
    return false;
}

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

bool verifFin(T_jungle jungle, T_singe singe)
{
    int nombreLianes = getNombreLiane(jungle);
    return (singe.posX == nombreLianes - 1);
}

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

bool allerEnFace(T_jungle jungle, T_singe *singe)
{
    if (verifFace(jungle, *singe))
    {
        singe->posX++;
        return true;
    }
    return false;
}

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

void sauterEau()
{
    printf("\nPLOUF !\n");
    exit(EXIT_SUCCESS);
}

void triLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle)));
    tri_selection_liste(liane);
}

bool verifTriLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle)));
    return verifTriListe(liane);
}
