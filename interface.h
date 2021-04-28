#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "jungle.h"
#include "types.h"

void clearConsole();
void afficheLiane(T_liane l, T_singe s, int posX);
void afficheJungle(T_jungle j, T_singe s);

T_singe initSinge();

T_singe choixSinge();
T_jungle creationJungle();
bool choixDirection(T_jungle jungle, T_singe* singe);


void jouer();
void jouerAuto();
void choixTypeJeu();

#endif // INTERFACE_H_INCLUDED
