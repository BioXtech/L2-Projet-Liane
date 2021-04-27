#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "jungle.h"
#include "types.h"

void afficheLiane(T_liane l, T_singe s, int posX);
void afficheJungle(T_jungle j, T_singe s);

T_singe initSinge();

T_singe choixSinge();
T_jungle creationJungle();
void choixDirection(T_jungle jungle, T_singe singe);


#endif // INTERFACE_H_INCLUDED
