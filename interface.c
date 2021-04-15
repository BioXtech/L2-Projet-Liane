#include "interface.h"
#include "liste.h"

void afficheLiane(T_liane l)
{
    T_liane ptrCourant = l; // T_liane = struct T_cell*
    while(listeVide(ptrCourant))
    {
        printf("%d-",*(getPtrData(ptrCourant)));
        ptrCourant = getptrNextCell(ptrCourant);
    }
    printf("\n");
}

void afficheJungle(T_jungle j)
{
    T_jungle ptrCourant = j; // T_jungle = struct T_cell*
    printf("\n########## JUNGLE ##########\n");
    while(listeVide(ptrCourant))
    {
        afficheLiane(getPtrData(ptrCourant));
        ptrCourant = getptrNextCell(ptrCourant);
    }
    printf("\n############################\n");
}
