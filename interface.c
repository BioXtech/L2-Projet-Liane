#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    T_jungle ptrCourant = j; // T_jungle = struct T_jungle_cell*
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
    T_singeV1 singe;
    printf("\n########## INITIALISATION DU SINGE ##########");
    int id;
    printf("\nSaisissez l'ID du singe (numero entre 1 et 50 : ");
    scanf("%d", &id);
    singe.id = id;

    char nom[10];
    printf("\nSaisissez le nom a attribuer au singe : ");
    scanf("%s", nom);
    strcpy(singe.nom,nom);

    singe.posX = 1;
    singe.posY = 1;

    T_liste liste_pref;
    initListe(&liste_pref);
    int val = 0;

    while (val > -1)
    {
        printf("\nSaisissez une valeur a ajouter a la liste du singe (-1 pour arreter) : ");
        scanf("%d", &val);
        if(val >= 0 && val <= 9){
            liste_pref = ajoutEnFin(liste_pref, val);
        }
    }
    singe.listeIntPreferes = liste_pref;

    //printf("\n %d %s", id, nom);

    return singe;
}
