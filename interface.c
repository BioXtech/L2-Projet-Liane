#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "interface.h"
#include "liste.h"

void afficheLiane(T_liane l, T_singe s, int posX)
{
    T_liane ptrCourant = l; // T_liane = struct T_cell*
    int posY = 0;
    while(!listeVide(ptrCourant))
    {
        if(posX == s.posX && posY == s.posY)
        {
            printf("-%c-", s.nom[0]);
        }
        else
        {
            printf("-%d-", *getPtrData(ptrCourant));
        }
        posY++;
        ptrCourant = getptrNextCell(ptrCourant);
    }
    printf("\n");
}

void afficheJungle(T_jungle j, T_singe s)
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

T_singe initSinge()
{
    T_singe singe;
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
        if(val >= 0 && val <= 9)
        {
            liste_pref = ajoutEnFin(liste_pref, val);
        }
    }
    singe.listeIntPreferes = liste_pref;

    //printf("\n %d %s", id, nom);

    return singe;
}

T_singe choixSinge()
{
    printf("\n########## JEU DU SINGE ##########");
    printf("\nVous allez pouvoir saisir l'ID, le nom, ainsi que la liste d'entiers preferes de votre singe\n");

    T_singe singe = initSinge();
    printf("\nSinge cree !!!");
    return singe;
}

T_jungle creationJungle()
{
    printf("\nCreation de la jungle en cours");
    sleep(1);
    printf(".");
    sleep(1);
    T_jungle jungle = genererJungle();
    printf(".");
    sleep(1);
    printf(".");
    printf("\nJungle creee !!!");
    return jungle;
}

void choixDirection(T_jungle jungle, T_singe singe)
{
    int numero_menu;

    do
    {
        printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
        afficheJungle(jungle, singe);

        printf("\nChoisissez parmi les propositions suivantes le traitement a effectuer (taper le numero)\n");
        printf("\n-----------------------------------------------------------\n");
        if (verifHaut(jungle,singe)) printf("1/ Aller en haut\n");
        if (verifFace(jungle,singe)) printf("2/ Aller en face\n");
        if (verifBas(jungle,singe)) printf("3/ Aller en bas\n");
        printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
        printf("5/ Sauter a l'eau\n");
        printf("-----------------------------------------------------------\n");

        printf("\nChoisissez un numero parmi les possibilites : \n");
        scanf("%d", &numero_menu);

        switch(numero_menu)
        {
        case 1 :
            printf("\nVous avez choisi d'aller en haut\n");
            allerEnHaut(jungle, &singe);
            break;
        case 2 :
            printf("\nVous avez choisi d'aller en face\n");
            allerEnFace(jungle, &singe);
            break;
        case 3 :
            printf("\nVous avez choisi d'aller en bas\n");
            allerEnBas(jungle, &singe);
            break;
        case 4 :
            printf("\nVous avez invoque le dieu DONKEY-KONG !!!\n");
            triLiane(jungle,singe);
            break;
        case 5 :
            printf("\nVous avez choisi de sauter a l'eau\n");
            int intensite = choix_intensite_pixellisation();
            ptr_image = PixellisationImage(ptr_image, intensite);
            break;
        default :
            printf("\nVotre choix n'est pas valide, saisissez un numero entre 1 et 5\n");
            break;
        }

    }
    while(numero_menu >= 1 && numero_menu <= 5);
}

