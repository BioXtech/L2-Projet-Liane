#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

// Paramètres : Aucun
// Résultat : Un T_pointAccroche
// Definition : Cette fonction alloue un espace mémoire et initialise un T_point d'accroche
T_pointAccroche *initPointAccroche()
{
    T_pointAccroche *pointAccroche = (T_pointAccroche *)malloc(sizeof(T_pointAccroche)); // Allocation d'un espace mémoire pour un point d'accroche
    pointAccroche->val = 0; // La valeur du point d'accroche vaut 0
    pointAccroche->est_present = NULL; // Il n'y a pas de singe sur le point d'accroche au moment de l'initisalisation

    return pointAccroche; // On retourne le point d'accroche initialisé
}

// Paramètres : Un point d'accroche
// Résultat : Un booléen
// Definition : Cette fonction vérifie si un singe est présent sur un point d'accroche ou non
bool verifSingePresent(T_pointAccroche pt_accroche)
{
    return pt_accroche.est_present != NULL; // Si "est_present" est different de NULL, alors il y a un singe sur le point
}

// Paramètres : Un pointeur de point d'accroche, un entier, et un pointeur de T_singe
// Résultat : Un booléen
// Definition : Cette fonction remplit un point d'accroche avec les valeurs entrées en paramètre
void remplirPointAccroche(T_pointAccroche * pt_accroche, int val, T_singe *singe)
{
    pt_accroche->val = val; // val prend la valeur entree en paramètre
    pt_accroche->est_present = singe; // le pointeur de singe prend le singe entre en parametre
}

// Paramètres : Un point d'accroche
// Résultat : Un entier
// Definition : Cette fonction récupère la valeur entière d'un point d'accroche
int getValPointAccroche(T_pointAccroche pt_accroche)
{
    return pt_accroche.val;
}
