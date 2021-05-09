#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdbool.h>

typedef struct T_cell
{

    struct T_cell *suiv;
    struct T_cell *prec;
    int *data;

} *T_liste;

typedef T_liste T_liste_int;

typedef struct
{
    int id;     //la première lettre du nom sera affiché sur l'IHM version
    char nom[10];
    T_liste_int listeIntPreferes;
} T_singeV2;

typedef T_singeV2 T_singe;

typedef struct
{
    int val;
    T_singe *est_present; //NULL si pas de singe, l'adresse du singe si présent
} T_pointAccroche;

int getValPointAccroche(T_pointAccroche pt_accroche);
bool verifSingePresent(T_pointAccroche pt_accroche);
T_pointAccroche* initPointAccroche();
void remplirPointAccroche(T_pointAccroche *pt_accroche, int val, T_singe *singe);

void afficheListePref(T_singe singe);

T_pointAccroche *freePA(T_pointAccroche *pt_accroche);

#endif // TYPES_H_INCLUDED
