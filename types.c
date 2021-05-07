#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

T_pointAccroche * initPointAccroche()
{
    T_pointAccroche * pointAccroche = (T_pointAccroche *)malloc(sizeof(T_pointAccroche));
    pointAccroche->val = 0;
    pointAccroche->est_present = NULL;

    return pointAccroche;
}
bool verifSingePresent(T_pointAccroche pt_accroche)
{
    return pt_accroche.est_present != NULL;
}

void remplirPointAccroche(T_pointAccroche * pt_accroche, int val, T_singe * singe)
{
    pt_accroche->val = val;
    pt_accroche->est_present = singe;
}

int getValPointAccroche(T_pointAccroche pt_accroche)
{
    return pt_accroche.val;
}
