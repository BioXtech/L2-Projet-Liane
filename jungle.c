#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jungle.h"
#include "liste.h"



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
}
*/
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
    T_liane liane_courante = *(getLiane(jungle));
    int hauteurSinge = getHauteurSinge(liane_courante);

    if (verifSingePresent(*getPA(getptrFirstPA(liane_courante))) || (getNbrePA(liane_suivante)-1 < hauteurSinge-1))
    {
        return false;
    }
    int nombreCible = getValPointAccroche(*(getPA(getPAEnN(liane_suivante, hauteurSinge-1))));
    if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
    {
        return true;
    }
    return false;
}

bool verifFace(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));
    T_liane liane_courante = *(getLiane(jungle));
    int hauteurSinge = getHauteurSinge(liane_courante);

    if (getNbrePA(lianeSuivante)-1 >= hauteurSinge)
    {
        int nombreCible = getValPointAccroche(*(getPA(getPAEnN(lianeSuivante, hauteurSinge))));
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
    T_liane liane_courante = *(getLiane(jungle));
    int hauteurSinge = getHauteurSinge(liane_courante);

    if (getNbrePA(lianeSuivante)-1 >= hauteurSinge+2)
    {
        int nombreCible = getValPointAccroche(*(getPA(getPAEnN(lianeSuivante, hauteurSinge+2))));
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

    while (!lianeVide(premiere_liane))
    {
        nombreCible = getValPointAccroche(*(getPA(premiere_liane)));
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0)
        {
            return true;
        }
        else
        {
            premiere_liane = getptrNextPA(premiere_liane);
            *indice += 1;
        }

    }
    return false;
}

bool verifFin(T_jungle jungle)
{
    return (jungle->suiv == NULL);
}

bool allerEnHaut(T_jungle jungle, T_singe *singe)
{
    if (verifHaut(jungle, *singe))
    {
        T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));
        T_liane liane_courante = *(getLiane(jungle));
        int hauteurSinge = getHauteurSinge(liane_courante);

        T_singe *adresse_singe = getPA(getPAEnN(liane_courante, hauteurSinge))->est_present;
        getPA(getPAEnN(liane_courante, hauteurSinge))->est_present = NULL;
        getPA(getPAEnN(lianeSuivante, hauteurSinge-1))->est_present = adresse_singe;
        return true;
    }
    return false;
}

bool allerEnFace(T_jungle jungle, T_singe *singe)
{
    if (verifFace(jungle, *singe))
    {
        T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));
        T_liane liane_courante = *(getLiane(jungle));
        int hauteurSinge = getHauteurSinge(liane_courante);

        T_singe *adresse_singe = getPA(getPAEnN(liane_courante, hauteurSinge))->est_present;
        printf("ADRESSE SINGE : %X PROUT %X", singe, adresse_singe);
        getPA(getPAEnN(liane_courante, hauteurSinge))->est_present = NULL;
        getPA(getPAEnN(lianeSuivante, hauteurSinge))->est_present = adresse_singe;
        return true;
    }
    return false;
}

bool allerEnBas(T_jungle jungle, T_singe *singe)
{
    if (verifBas(jungle, *singe))
    {
        T_liane lianeSuivante = *(getLiane(getNextLiane(jungle)));
        T_liane liane_courante = *(getLiane(jungle));
        int hauteurSinge = getHauteurSinge(liane_courante);

        T_singe *adresse_singe = getPA(getPAEnN(liane_courante, hauteurSinge))->est_present;
        getPA(getPAEnN(liane_courante, hauteurSinge))->est_present = NULL;
        getPA(getPAEnN(lianeSuivante, hauteurSinge+2))->est_present = adresse_singe;
        return true;
    }
    return false;
}

void allerPremiereLiane(T_jungle jungle, T_singe *singe)
{
    int hauteur_singe = 0;
    if (verifDebut(jungle, *singe, &hauteur_singe))
    {
        T_liane premiere_liane = *(getLiane(jungle));

        getPA(getPAEnN(premiere_liane, hauteur_singe))->est_present = singe;
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

void triNextLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle)));
    tri_selection_liane(liane);
}

bool verifTriLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle)));

    T_liane ptrCourant = liane;
    if (lianeVide(liane))
    {
        //printf("\nLISTE TRIEE");
        return true;
    }
    else
    {
        while (getptrNextPA(ptrCourant) != NULL)
        {
            if (getValPointAccroche(*(getPA(ptrCourant))) <= getValPointAccroche(*(getPA(getptrNextPA(ptrCourant)))))
            {
                ptrCourant = getptrNextPA(ptrCourant);
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
