#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

// Param�tres : Aucun
// R�sultat : Un T_pointAccroche
// Definition : Cette fonction alloue un espace m�moire et initialise un T_point d'accroche
T_pointAccroche *initPointAccroche()
{
    T_pointAccroche *pointAccroche = (T_pointAccroche *)malloc(sizeof(T_pointAccroche)); // Allocation d'un espace m�moire pour un point d'accroche
    pointAccroche->val = 0; // La valeur du point d'accroche vaut 0
    pointAccroche->est_present = NULL; // Il n'y a pas de singe sur le point d'accroche au moment de l'initisalisation

    return pointAccroche; // On retourne le point d'accroche initialis�
}

// Param�tres : Un point d'accroche
// R�sultat : Un bool�en
// Definition : Cette fonction v�rifie si un singe est pr�sent sur un point d'accroche ou non
bool verifSingePresent(T_pointAccroche pt_accroche)
{
    return pt_accroche.est_present != NULL; // Si "est_present" est different de NULL, alors il y a un singe sur le point
}

// Param�tres : Un pointeur de point d'accroche, un entier, et un pointeur de T_singe
// R�sultat : Un bool�en
// Definition : Cette fonction remplit un point d'accroche avec les valeurs entr�es en param�tre
void remplirPointAccroche(T_pointAccroche * pt_accroche, int val, T_singe *singe)
{
    pt_accroche->val = val; // val prend la valeur entree en param�tre
    pt_accroche->est_present = singe; // le pointeur de singe prend le singe entre en parametre
}

// Param�tres : Un point d'accroche
// R�sultat : Un entier
// Definition : Cette fonction r�cup�re la valeur enti�re d'un point d'accroche
int getValPointAccroche(T_pointAccroche pt_accroche)
{
    return pt_accroche.val;
}
