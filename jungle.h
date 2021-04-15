#ifndef JUNGLE_H_INCLUDED
#define JUNGLE_H_INCLUDED

typedef T_liste T_liane;

typedef struct T_cell_liane {

    struct T_cell_liane *suiv;
    struct T_cell_liane *prec;
    T_liane *liane;

} *T_jungle;

#endif // JUNGLE_H_INCLUDED
