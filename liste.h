#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdbool.h>

typedef struct T_cell{

    struct T_cell *suiv;
    struct T_cell *prec;
    void *data;

} *T_liste;

void initListe(T_liste *l);
bool listeVide( T_liste l);
void afficheListeV1( T_liste l);
T_liste ajoutEnTete(T_liste l, void* ptrData);
void debug(T_liste l);
void ajoutEnTetePtr2Ptr(T_liste *l, void* ptrData);
T_liste ajoutEnFin(T_liste l, void* ptrData);
T_liste ajoutEnN(T_liste l, int pos, void* ptrData);
T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);
T_liste getptrLastCell(T_liste l);
T_liste getptrFirstCell(T_liste l);
T_liste getptrNextCell(T_liste l);
T_liste getptrPrevCell(T_liste l);
void* getPtrData(T_liste l);
void swapPtrData( T_liste source, T_liste destination );
int getNbreCell(T_liste l);
int getSizeBytes(T_liste l);
T_liste creatNewListeFromFusion(T_liste l1, T_liste l2);
T_liste addBehind(T_liste debut, T_liste suite);
T_liste findCell(T_liste l, int data);
int getOccurences(T_liste l, int data);

#endif // LISTE_H_INCLUDED
