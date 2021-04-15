#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

typedef struct T_cell{

    struct T_cell *suiv;
    struct T_cell *prec;
    int *integer;

} *T_liste;

#endif // LISTE_H_INCLUDED
