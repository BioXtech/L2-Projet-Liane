#include <stdio.h>

#include "interface.h"
#include "liste.h"

void afficheLiane(T_liane l, T_singeV1 s, int posX)
{
    T_liane ptrCourant = l; // T_liane = struct T_cell*
    int posY = 0;
    while(!listeVide(ptrCourant))
    {
        if(posX == s.posX && posY == s.posY){
            printf("-%c-", s.nom[0]);
        }
        else{
            printf("-%d-", *getPtrData(ptrCourant));
        }
        posY++;
        ptrCourant = getptrNextCell(ptrCourant);
    }
    printf("\n");
}

void afficheJungle(T_jungle j, T_singeV1 s)
{
    T_jungle ptrCourant = j; // T_jungle = struct T_cell*
    int posX = 0;
    printf("\n########## JUNGLE ##########\n\n");
    while(!jungleVide(ptrCourant))
    {
        afficheLiane(*getLiane(ptrCourant), s, posX);
        ptrCourant = getNextLiane(ptrCourant);
        posX++;
    }
    printf("\n############################\n");
}

T_singeV1 initSinge(){

}
