#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdbool.h>

typedef struct T_cell
{

    struct T_cell *suiv;
    struct T_cell *prec;
    int *data;

} * T_liste; // POinteur vers la premiere case d'une liste doublement chainee d'entier

void initListe(T_liste *l);
bool listeVide(T_liste l);

void afficheListeV1(T_liste l);

T_liste ajoutEnTete(T_liste l, int mydata);

//void debug(T_liste l);
T_liste ajoutEnFin(T_liste l, int mydata);
T_liste ajoutEnN(T_liste l, int pos, int mydata);

T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);

T_liste getptrLastCell(T_liste l);
T_liste getptrFirstCell(T_liste l);
T_liste getptrNextCell(T_liste l);
T_liste getptrPrevCell(T_liste l);
T_liste getCellEnN(T_liste liste, int n);
int *getPtrData(T_liste l);

void swapPtrData(T_liste source, T_liste destination);
int getNbreCell(T_liste l);

int getOccurences(T_liste l, int data);

void tri_selection_liste(T_liste l);
bool verifTriListe(T_liste l);

#endif // LISTE_H_INCLUDED
