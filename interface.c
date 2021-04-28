#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "interface.h"
#include "liste.h"

void clearConsole()
{
    for(int i = 0; i < 50; i++)
    {
        printf("\n");
    }
}

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
    while(getPrecLiane(ptrCourant) != NULL)
    {
        ptrCourant = getPrecLiane(ptrCourant);
    }
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

    singe.posX = -1;
    singe.posY = -1;

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
    sleep(0.5);
    printf(".");
    sleep(0.5);
    T_jungle jungle = genererJungle();
    printf(".");
    sleep(0.5);
    printf(".");
    printf("\nJungle creee !!!");
    return jungle;
}

bool choixDirection(T_jungle jungle, T_singe* singe)
{
    int numero_menu;

    do
    {
        printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
        afficheJungle(jungle, *singe);

        printf("\nChoisissez parmi les propositions suivantes le traitement a effectuer (taper le numero)\n");
        printf("\n-----------------------------------------------------------\n");
        if (verifHaut(jungle,*singe)) printf("1/ Aller en haut\n");
        if (verifFace(jungle,*singe)) printf("2/ Aller en face\n");
        if (verifBas(jungle,*singe)) printf("3/ Aller en bas\n");
        printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
        printf("5/ Sauter a l'eau\n");
        printf("-----------------------------------------------------------\n");

        printf("\nChoisissez un numero parmi les possibilites : \n");
        scanf("%d", &numero_menu);

        switch(numero_menu)
        {
            case 1 :
                printf("\nVous avez choisi d'aller en haut\n");
                return allerEnHaut(jungle, singe);
            case 2 :
                printf("\nVous avez choisi d'aller en face\n");
                return allerEnFace(jungle, singe);
            case 3 :
                printf("\nVous avez choisi d'aller en bas\n");
                return allerEnBas(jungle, singe);
            case 4 :
                printf("\nVous avez invoque le dieu DONKEY-KONG !!!\n");
                triLiane(jungle);
                return false;
            case 5 :
                printf("\nVous avez choisi de sauter a l'eau\n");
                sauterEau();
                break;
            default :
                printf("\nVotre choix n'est pas valide, saisissez un numero entre 1 et 5\n");
                break;
        }
    }
    while(numero_menu < 1 && numero_menu > 5);
    return false;
}

bool choixDirectionAuto(T_jungle jungle, T_singe* singe)
{
    int numero_menu;

    do
    {
        printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
        afficheJungle(jungle, *singe);

        printf("\nLes possibilites sont les suivantes\n");
        printf("\n-----------------------------------------------------------\n");
        if (verifHaut(jungle,*singe)) printf("1/ Aller en haut\n");
        if (verifFace(jungle,*singe)) printf("2/ Aller en face\n");
        if (verifBas(jungle,*singe)) printf("3/ Aller en bas\n");
        printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
        printf("5/ Sauter a l'eau\n");
        printf("-----------------------------------------------------------\n");

        printf("\nChoix parmi les possibilites : \n");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".");
        numero_menu = 5;

        if (verifHaut(jungle,*singe)) numero_menu = 1;
        else if (verifFace(jungle,*singe)) numero_menu = 2;
        else if (verifBas(jungle,*singe)) numero_menu = 3;
        else if (!verifTriLiane(jungle)) numero_menu = 4;
        else numero_menu = 5;


        switch(numero_menu)
        {
            case 1 :
                printf("\nLe singe est alle en haut\n");
                return allerEnHaut(jungle, singe);
            case 2 :
                printf("\nLe singe est alle en face\n");
                return allerEnFace(jungle, singe);
            case 3 :
                printf("\nLe singe est alle en bas\n");
                return allerEnBas(jungle, singe);
            case 4 :
                printf("\nInvocation du dieu DONKEY-KONG !!!\n");
                triLiane(jungle);
                return false;
            case 5 :
                printf("\nLe singe a saute a l'eau\n");
                sauterEau();
                break;
            default :
                printf("\nNumero non compris entre 1 et 5\n");
                break;
        }
    }
    while(numero_menu < 1 && numero_menu > 5);
    return false;
}

void jouer()
{
    T_singe singe = choixSinge();
    T_jungle jungle = creationJungle();
    afficheJungle(jungle, singe);
    allerPremiereLiane(jungle, &singe);

    T_jungle jungleCourante = jungle;
    bool doitAvancer = false;

    do
    {
        doitAvancer = choixDirection(jungleCourante, &singe);
        if(doitAvancer) jungleCourante = getNextLiane(jungleCourante);
        clearConsole();
    }
    while(!verifFin(jungle, singe));

    printf("Vous avez gagne !\n");
    printf("Le singe a reussi a traverser la riviere !\n");

}

void jouerAuto()
{
    T_singe singe = choixSinge();
    T_jungle jungle = creationJungle();
    afficheJungle(jungle, singe);
    allerPremiereLiane(jungle, &singe);

    T_jungle jungleCourante = jungle;
    bool doitAvancer = false;

    do
    {
        doitAvancer = choixDirectionAuto(jungleCourante, &singe);
        if(doitAvancer) jungleCourante = getNextLiane(jungleCourante);
        clearConsole();
    }
    while(!verifFin(jungle, singe));

    printf("Vous avez gagne !\n");
    printf("Le singe a reussi a traverser la riviere !\n");

}

void choixTypeJeu()
{
    int numero_menu;

    printf("\n########## JEU DU SINGE ##########");

    printf("\nSouhaitez vous jouer vous-meme ou lancer le mode automatique ? (taper le numero)\n");
    printf("\n-----------------------------------------------------------\n");
    printf("1/ Mode Manuel\n");
    printf("2/ Mode Automatique\n");
    printf("-----------------------------------------------------------\n");

    printf("\nChoisissez un numero parmi les deux possibilites : \n");
    scanf("%d", &numero_menu);

    switch(numero_menu)
    {
        case 1 :
            printf("\nVous avez choisi le mode manuel\n");
            jouer();
            break;
        case 2 :
            printf("\nVous avez choisi le mode automatique\n");
            jouerAuto();
            break;
        default :
            printf("\nNumero non compris entre 1 et 5\n");
            break;
        }
}

