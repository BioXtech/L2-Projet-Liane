#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdbool.h>
#include "types.h"

void initListe(T_liste *l);
bool listeVide( T_liste l);

void afficheListeV1( T_liste l);

T_liste ajoutEnTete(T_liste l, int mydata);

//void debug(T_liste l);

T_liste getptrNextCell(T_liste l);

int* getPtrData(T_liste l);

int getNbreCell(T_liste l);
int getOccurences(T_liste l, int data);

T_liste freeListe(T_liste l);

#endif // LISTE_H_INCLUDED
