#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jungle.h"
#include "liste.h"


// Paramètres : Un pointeur vers un T_jungle
// Résultat : Aucun
// Definition : Cette fonction permet d'initialiser une jungle sans case a un pointeur nul
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
    if (jungleVide(j)) // Si la jungle est vide on retourne null
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
    if (jungleVide(j)) // Si la jungle est vide on retourne null
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

// Paramètres : Un T_jungle
// Résultat : Un entier
// Definition : Cette fonction retourne le nombre de lianes d'une jungle
int getNombreLiane(T_jungle j)
{
    T_jungle ptrCourant = j; // Declaration d'un pointeur permettant de parcourir la jungle à travers les lianes
    int compteur = 1; // Declaration d'un compteur qui s'incrémentera selon le nombre de lianes compté
    if (jungleVide(j)) // Si la jungle est vide alors le nombre de lianes vaut 0
    {
        return compteur = 0;
    }
    else // Sinon
    {
        while (ptrCourant->suiv != NULL) // Tant que la case après la liane courante n'est pas nulle (on parcourt toute la jungle à travers chaque liane)
        {
            ptrCourant = ptrCourant->suiv; // On va sur la liane suivante grâce au pointeur courant
            compteur++; // Le compteur s'incrémente de un
        }
        return compteur; // Enfin on retourne la valeur du compteur
    }
}

// Paramètres : Un T_jungle et une T_liane
// Résultat : Un T_jungle
// Definition : Cette fonction ajoute une liane à la jungle passée en paramètre
T_jungle ajoutLianeAJungle(T_jungle j, T_liane l)
{
    T_jungle newj = (T_jungle)malloc(sizeof(struct T_jungle_cell)); // Allocation de la nouvelle case pour la liane
    newj->courante = (T_liane *)malloc(sizeof(T_liane)); // Allocation de la nouvelle liane
    *(newj->courante) = l; // On affecte la liane à la nouvelle case

    if (jungleVide(j)) // Si la jungle est vide on cree une nouvelle case avec les pointeurs prec et suiv a NULL (il n'y a donc pas de lianes avant et après)
    {
        newj->prec = NULL;
        newj->suiv = NULL;
    }
    else // Sinon on ajoute la nouvelle case en la chainant avec la jungle donnee en parametre (ajout en tete pour une meilleure complexité)
    {
        newj->prec = NULL;
        newj->suiv = j;
        j->prec = newj;
    }

    return newj;  // On retourne le pointeur sur la nouvelle tete de la jungle
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

// Paramètres : Aucun
// Résultat : Un T_jungle
// Definition : Cette fonction permet de créer une jungle en faisant appel à la fonction d'ajout de liane à jungle à répétition
T_jungle genererJungle()
{
    T_jungle jungle;
    initJungle(&jungle); // On déclare une jungle
    T_liane liane; // On déclare une liane
    int nombre_lianes; // On déclare le nombre de lianes

    nombre_lianes = (rand() % (NOMBRE_MAX_LIANES - NOMBRE_MIN_LIANES - 1) + NOMBRE_MIN_LIANES); // Creation d'un nombre de lianes aléatoire entre 5 et 10 grâce aux DEFINE au-dessus de la fonction

    for (int i = 0; i < nombre_lianes; i++) // Pour i allant de 0 au nombre de lianes
    {
        liane = genererLiane(); // On fait appel à la fonction de génération d'une liane
        jungle = ajoutLianeAJungle(jungle, liane); // Puis on ajoute la liane créée à la jungle
    }
    return jungle; // On retourne la jungle finale
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller une case au dessus sur la liane suivante
bool verifHaut(T_jungle jungle, T_singe singe)
{
    T_liane liane_suivante = *(getLiane(getNextLiane(jungle))); // Declaration de deux T_liane, la suivante et la courante
    T_liane liane_courante = *(getLiane(jungle));
    int hauteurSinge = getHauteurSinge(liane_courante); // Declaration d'un entier précisant la hauteur du singe (le plus haut est le point 0)

    if (verifSingePresent(*getPA(getptrFirstPA(liane_courante))) || (getNbrePA(liane_suivante)-1 < hauteurSinge-1)) // Si le singe est sur le point d'accorche le plus haut
    {
        // Ou si le nombre de points d'accroche de la liane suivante est inférieure de 2 cases ou plus par rapport à la hauteur du singe actuelle
        return false; // Alors la fonction retourne que ce n'est pas possible
    }
    int nombreCible = getValPointAccroche(*(getPA(getPAEnN(liane_suivante, hauteurSinge-1)))); // Declaration d'un entier qui est la valeur de l'entier du point d'accroche cible
    if (getOccurences(singe.listeIntPreferes, nombreCible) > 0) // Si la valeur de ce dernier est présente dans la liste d'entiers préférés du singe
    {
        return true; // Alors il peut aller en haut
    }
    return false;
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller en face sur la liane suivante
bool verifFace(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle))); // Declaration de deux T_liane, la suivante et la courante
    T_liane liane_courante = *(getLiane(jungle));
    int hauteurSinge = getHauteurSinge(liane_courante); // Declaration d'un entier précisant la hauteur du singe (le plus haut est le point 0)

    if (getNbrePA(lianeSuivante)-1 >= hauteurSinge) // Si le nombre de points de la liane suivante est au minimum aussi grand que la hauteur du singe
    {
        int nombreCible = getValPointAccroche(*(getPA(getPAEnN(lianeSuivante, hauteurSinge)))); // Declaration d'un entier qui est la valeur de l'entier du point d'accroche cible
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0) // Si la valeur de ce dernier est présente dans la liste d'entiers préférés du singe
        {
            return true; // Alors il peut aller en face
        }
    }
    return false;
}

// Paramètres : Une T_jungle et un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller en bas (2 cases plus bas) sur la liane suivante
bool verifBas(T_jungle jungle, T_singe singe)
{
    T_liane lianeSuivante = *(getLiane(getNextLiane(jungle))); // Declaration de deux T_liane, la suivante et la courante
    T_liane liane_courante = *(getLiane(jungle));
    int hauteurSinge = getHauteurSinge(liane_courante); // Declaration d'un entier précisant la hauteur du singe (le plus haut est le point 0)

    if (getNbrePA(lianeSuivante)-1 >= hauteurSinge+2) // // Si le nombre de points de la liane suivante est supérieur de 2 par rapport à la hauteur actuelle du singe
    {
        int nombreCible = getValPointAccroche(*(getPA(getPAEnN(lianeSuivante, hauteurSinge+2)))); // Declaration d'un entier qui est la valeur de l'entier du point d'accroche cible
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0) // Si la valeur de ce dernier est présente dans la liste d'entiers préférés du singe
        {
            return true; // Alors il peut aller en bas
        }
    }
    return false;
}

// Paramètres : Une T_jungle, un T_singe et un pointeur sur un entier
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si le singe peut aller sur la première liane et donc si le jeu peut commencer
bool verifDebut(T_jungle jungle, T_singe singe, int *indice)
{
    T_liane premiere_liane = *(getLiane(jungle)); // Declaration d'une T_liane qui est la premiere liane
    int nombreCible; // Declaration d'un entier qui est la valeur de l'entier du point d'accroche cible

    while (!lianeVide(premiere_liane)) // On parcourt chaque point d'accroche de la premiere liane
    {
        nombreCible = getValPointAccroche(*(getPA(premiere_liane))); // Le nombre cible prend la valeur du point d'accroche ciblé de la boucle
        printf("Nombre cible %d\n",nombreCible);
        if (getOccurences(singe.listeIntPreferes, nombreCible) > 0) // Si la valeur du nombre cible est présente dans la liste d'entiers préférés du singe
        {
            return true; // Alors il peut aller sur le point d'accroche testé
        }
        else // Sinon
        {
            premiere_liane = getptrNextPA(premiere_liane); // On va sur le point d'accroche suivant
            *indice += 1; // L'indice est incrémenté de 1, il nous permet de connaitre la hauteur du singe et de garder cette valeur en mémoire tout en retournant un booléen
        }

    }
    return false;
}

// Paramètres : Une T_jungle
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si on est à la fin (si le singe est sur la dernière liane)
bool verifFin(T_jungle jungle)
{
    return (jungle->suiv == NULL); // Le singe est à la fin si le pointeur de la liane suivante est null (puisqu'il n'y a plus de liane après la courante)
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va en haut ou non
bool allerEnHaut(T_jungle jungle, T_singe *singe)
{
    if (verifHaut(jungle, *singe)) // Appel à la fonction de vérification pour savoir si le singe peut aller en haut
    {
        T_liane lianeSuivante = *(getLiane(getNextLiane(jungle))); // Declaration de deux T_liane, la suivante et la courante
        T_liane liane_courante = *(getLiane(jungle));
        int hauteurSinge = getHauteurSinge(liane_courante); // Declaration d'un entier précisant la hauteur du singe (le plus haut est le point 0)

        T_singe *adresse_singe = getPA(getPAEnN(liane_courante, hauteurSinge))->est_present; // On récupère le T_singe du point d'accroche cible
        getPA(getPAEnN(liane_courante, hauteurSinge))->est_present = NULL; // Le pointeur du point d'accroche ou le singe est actuellement pointe alors NULL (il n'y a plus de T_singe)
        getPA(getPAEnN(lianeSuivante, hauteurSinge-1))->est_present = adresse_singe; // On met le T_singe récupéré temporairement dans le point d'accroche cible
        return true; // Le singe va en haut
    }
    return false;
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va en face ou non
bool allerEnFace(T_jungle jungle, T_singe *singe)
{
    if (verifFace(jungle, *singe)) // Appel à la fonction de vérification pour savoir si le singe peut aller en face
    {
        T_liane lianeSuivante = *(getLiane(getNextLiane(jungle))); // Declaration de deux T_liane, la suivante et la courante
        T_liane liane_courante = *(getLiane(jungle));
        int hauteurSinge = getHauteurSinge(liane_courante); // Declaration d'un entier précisant la hauteur du singe (le plus haut est le point 0)

        T_singe *adresse_singe = getPA(getPAEnN(liane_courante, hauteurSinge))->est_present; // On récupère le T_singe du point d'accroche cible
        getPA(getPAEnN(liane_courante, hauteurSinge))->est_present = NULL; // Le pointeur du point d'accroche ou le singe est actuellement pointe alors NULL (il n'y a plus de T_singe)
        getPA(getPAEnN(lianeSuivante, hauteurSinge))->est_present = adresse_singe; // On met le T_singe récupéré temporairement dans le point d'accroche cible
        return true; // Le singe va en face
    }
    return false;
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va en bas ou non
bool allerEnBas(T_jungle jungle, T_singe *singe)
{
    if (verifBas(jungle, *singe)) // Appel à la fonction de vérification pour savoir si le singe peut aller en bas
    {
        T_liane lianeSuivante = *(getLiane(getNextLiane(jungle))); // Declaration de deux T_liane, la suivante et la courante
        T_liane liane_courante = *(getLiane(jungle));
        int hauteurSinge = getHauteurSinge(liane_courante); // Declaration d'un entier précisant la hauteur du singe (le plus haut est le point 0)

        T_singe *adresse_singe = getPA(getPAEnN(liane_courante, hauteurSinge))->est_present; // On récupère le T_singe du point d'accroche cible
        getPA(getPAEnN(liane_courante, hauteurSinge))->est_present = NULL; // Le pointeur du point d'accroche ou le singe est actuellement pointe alors NULL (il n'y a plus de T_singe)
        getPA(getPAEnN(lianeSuivante, hauteurSinge+2))->est_present = adresse_singe; // On met le T_singe récupéré temporairement dans le point d'accroche cible
        return true; // Le singe va en bas
    }
    return false;
}

// Paramètres : Une T_jungle et un pointeur d'un T_singe
// Résultat : Un booléen
// Definition : Cette fonction permet de dire si le singe va sur la première liane et commence le jeu ou non
void allerPremiereLiane(T_jungle jungle, T_singe *singe)
{
    int hauteur_singe = 0; // Declaration d'un entier étant la hauteur du singe, initialisée à 0
    if (verifDebut(jungle, *singe, &hauteur_singe)) // Appel à la fonction de vérification pour savoir si le singe peut aller sur la premiere liane
    {
        T_liane premiere_liane = *(getLiane(jungle)); // Declaration d'une T_liane qui est la premiere liane

        getPA(getPAEnN(premiere_liane, hauteur_singe))->est_present = singe; // Si la condition est validée, on met le T_singe dans le point d'accroche cible
    }
    else // Sinon si la condition n'est jamais vérifiée
    {
        sauterEau(); // Le singe doit sauter à l'eau (appel de la fonction qui fait sauter le singe à l'eau)
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
void triNextLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle))); // On prend la liane suivante de celle pointée actuellement
    tri_selection_liane(liane); // Appel de la fonction de tri de liane
}

// Paramètres : Une T_jungle
// Résultat : Un booléen
// Definition : Cette fonction permet de vérifier si une liane est triée ou non
bool verifTriLiane(T_jungle jungle)
{
    T_liane liane = *(getLiane(getNextLiane(jungle))); // On prend la liane à vérifier

    T_liane ptrCourant = liane; // Declaration d'un pointeur courant permettant de parcourir les points d'accroche de la liane
    if (lianeVide(liane)) // Si la liane est vide
    {
        //printf("\nLISTE TRIEE");
        return true; // Alors on dit qu'elle est triée
    }
    else // Sinon
    {
        while (getptrNextPA(ptrCourant) != NULL) // On parcourt tous les points d'accroches de la liane
        {
            if (getValPointAccroche(*(getPA(ptrCourant))) <= getValPointAccroche(*(getPA(getptrNextPA(ptrCourant))))) // Si la valeur détenue par le point d'accroche actuel est inférieure à celle du suivant
            {
                ptrCourant = getptrNextPA(ptrCourant); // Alors on pointe le point d'accroche suivant
            }
            else // Sinon
            {
                //printf("\nLISTE NON TRIEE");
                return false; // La liane n'est pas triée
            }
        }
        //printf("\nLISTE TRIEE");
        return true; // Si toute la première condition if est toujours vérifiée, on sort de la boucle while et la liste est alors bien triée
    }
}

// Paramètres : Une T_jungle
// Résultat : Une T_jungle
// Definition : Cette fonction libère la mémoire prise par une jungle
T_jungle freeJungle(T_jungle j)
{
    T_jungle ptrCourant = j;
    if (jungleVide(j))
    {
        return NULL;
    }
    else
    {
        while(!jungleVide(getNextLiane(ptrCourant)))
        {
            freeLiane(*(getLiane(ptrCourant)));
            ptrCourant = getNextLiane(ptrCourant);
            free(ptrCourant->prec);
        }
        freeLiane(*(getLiane(ptrCourant)));
        free(ptrCourant);
    }
    return NULL;
}
