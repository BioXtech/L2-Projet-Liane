#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "interface.h"
#include "liste.h"

// Param�tres : Aucun
// R�sultat : Aucun
// Definition : Cette fonction permet de faire de l'espace dans la console et ainsi d'offrir une meilleure lisibilit�
void clearConsole()
{
    for(int i = 0; i < 50; i++) // Pour i allant de 0 � 49
    {
        printf("\n"); // On affiche un retour � la ligne
    }
}

// Param�tres : Une liane l et un singe s
// R�sultat : Aucun
// Definition : Cette fonction permet d'afficher une liane
void afficheLiane(T_liane l, T_singe s)
{
    T_liane ptrCourant = l; // Creation d'un pointeur copie de la liane en param�tre, afin de parcourir cette derni�re.
    while(!lianeVide(ptrCourant)) // Tant que la case point�e de la liane n'est pas nulle, c'est-�-dire tant que le pointeur n'a pas parcouru toute la liane
    {
        if(verifSingePresent(*getPA(ptrCourant))) // Si le singe est pr�sent sur le point d'accroche de la case point�e de la liane
        {
            printf("-%c-", s.nom[0]); // Alors on affiche l'initiale du singe appel� en param�tre
        }
        else
        {
            printf("-%d-", getValPointAccroche(*getPA(ptrCourant))); // Sinon, on affiche la valeur enti�re du point d'accroche de la case point�e de la liane
        }
        ptrCourant = getptrNextPA(ptrCourant); // Le pointeur pointe la case suivante de la liane, et ainsi on rev�rifie la condition du while
    }
    printf("\n"); // On affiche un retour � la ligne
}

// Param�tres : Une jungle j et un singe s
// R�sultat : Aucun
// Definition : Cette fonction permet d'afficher la jungle en appelant la fonction d'affichage d'une liane plusieurs fois
void afficheJungle(T_jungle j, T_singe s)
{
    T_jungle ptrCourant = j; // Creation d'un pointeur copie de la jungle en param�tre, afin de parcourir cette derni�re.
    while(getPrecLiane(ptrCourant) != NULL) // Tant que le pointeur ne pointe pas sur la premi�re liane (case pr�c�dente doit �tre nulle)
    {
        ptrCourant = getPrecLiane(ptrCourant); // Le pointeur pointe sur la liane pr�c�dente
    }                                          // Cette v�rification est n�cessaire puisque la jungle appel�e en param�tre pointe sur la liane ou est le singe, et non la premi�re.
    printf("\n########## JUNGLE ##########\n\n");
    while(!jungleVide(ptrCourant)) // Tant que la case point�e de la jungle n'est pas nulle, c'est-�-dire tant que le pointeur n'a pas parcouru toute la jungle
    {
        afficheLiane(*getLiane(ptrCourant), s); // On fait appel � la fonction d'affichage d'une liane
        ptrCourant = getNextLiane(ptrCourant); // Puis notre jungle pointe sur la liane suivante, et on rev�rifie la condition du while
    }
    printf("\n############################\n");
}

// Param�tres : Aucun
// R�sultat : Un singe
// Definition : Cette fonction permet d'initialiser un singe (Type T_singe) en fonction des choix de l'utilisateur
T_singe initSinge()
{
    T_singe singe; // Declaration du singe
    printf("\n########## INITIALISATION DU SINGE ##########");
    int id; // Declaration de l'ID du singe
    printf("\nSaisissez l'ID du singe (numero entre 1 et 50) : "); // On demande � l'utilisateur de saisir l'ID du singe
    scanf("%d", &id); // On r�cup�re la valeur entr�e par l'utilisateur
    singe.id = id; // On donne ainsi cette derni�re au singe cr�e

    char nom[10]; // Declaration d'une chaine de caract�re (nom du singe)
    printf("\nSaisissez le nom a attribuer au singe : "); // On demande � l'utilisateur de saisir le nom du singe
    scanf("%s", nom); // On r�cup�re le nom entr�e par l'utilisateur
    strcpy(singe.nom,nom); // On donne ainsi celui-ci au singe cr�e (besoin de la biblioth�que string.h pour strcpy)

    T_liste liste_pref; // Declaration d'une liste (entiers pr�f�r�s du singe)
    initListe(&liste_pref); // Initialisation de la liste � NULL pour le moment en appelant la fonction initListe
    int val = 0; // Declaration d'un entier val qui repr�sentera � chaque fois la valeur � ajouter � la liste

    while (val > -1) // Tant que l'entier val est strictement sup�rieur � -1
    {
        printf("\nSaisissez une valeur a ajouter a la liste du singe (-1 pour arreter) : "); // On demande � l'utilisateur de saisir une valeur � ajouter � la liste pr�f�r�e
        scanf("%d", &val); // On r�cup�re cette valeur
        if(val >= 0 && val <= 9) // Si la valeur est comprise entre 0 et 9
        {
            liste_pref = ajoutEnTete(liste_pref, val); // Alors elle est ajout�e � la liste pr�f�r�e en faisant appel � une fonction d'ajout en T�te (complexit� en temps meilleure qu'en fin)
        }                                              // Sinon il ne se passe rien
    }                                                  // Puis on rev�rifie la condition du while avec la valeur de val que l'utilisateur a entr�e. S'il entre -1 la demande de saisie s'arr�te
    singe.listeIntPreferes = liste_pref; // On donne la liste cr�ee au singe

    //printf("\n %d %s", id, nom);

    return singe; // Puis on retourne le singe initialis�
}

// Param�tres : Aucun
// R�sultat : Un singe
// Definition : Cette fonction permet d'initialiser un singe en appelant la fonction pr�c�dente et donne une esth�tique visuelle simple
T_singe choixSinge()
{
    printf("\n########## JEU DU SINGE ##########");
    printf("\nVous allez pouvoir saisir l'ID, le nom, ainsi que la liste d'entiers preferes de votre singe\n");

    T_singe singe = initSinge();
    printf("\nSinge cree !!!");
    return singe;
}

// Param�tres : Aucun
// R�sultat : Une jungle
// Definition : Cette fonction permet d'initialiser la jungle en appelant la g�n�ration de jungle, et permet une esth�tique visuelle
T_jungle creationJungle()
{
    printf("\nCreation de la jungle en cours");
    sleep(0.5); // Le programme attend une demi-seconde
    printf("."); // Affichage d'un point
    sleep(0.5);
    T_jungle jungle = genererJungle(); // Generation de la jungle
    printf(".");
    sleep(0.5);
    printf("."); // Cela donne un aspect r�el de chargement
    printf("\nJungle creee !!!");
    return jungle; // On retourne la jungle initialis�e
}

// Param�tres : Une jungle "jungle" et un pointeur de singe "singe"
// R�sultat : Un bool�en representant si le pointeur courant de la liane doit avancer d'une liane ou pas pour le prochain tour
// Definition : Cette fonction permet � l'utilisateur de choisir la direction que le singe doit emprunter selon les possibilit�s
bool choixDirection(T_jungle jungle, T_singe* singe)
{
    int numero_menu; // Declaration d'un entier qui sera chang� selon le choix de l'utilisateur pour entrer en param�tre de la fonction switch

    do // Do-while pour parcourir au minimum une fois la boucle et permettre de recommencer la boucle tant que la condition n'est pas v�rifi�e
    {
        printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
        afficheJungle(jungle, *singe); // Affiche l'etat actuel de la jungle

        printf("\nChoisissez parmi les propositions suivantes le traitement a effectuer (taper le numero)\n");
        printf("\n-----------------------------------------------------------\n");
        if (verifHaut(jungle,*singe)) printf("1/ Aller en haut\n"); // Affiche ou non les choix s'ils sont disponibles ou non pour le joueur
        if (verifFace(jungle,*singe)) printf("2/ Aller en face\n");
        if (verifBas(jungle,*singe)) printf("3/ Aller en bas\n");
        if (!verifTriLiane(jungle)) printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
        printf("5/ Sauter a l'eau\n");
        printf("-----------------------------------------------------------\n");

        printf("\nChoisissez un numero parmi les possibilites : \n");
        scanf("%d", &numero_menu);

        // Switch case permettant d'effectuer le choix de l'utilisateur en appelant la fonction correspondante
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
                triNextLiane(jungle);
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
    while(numero_menu < 1 && numero_menu > 5); // Verifie si le nombre rentre correspond a un choix possible
    return false;
}

// Param�tres : Une jungle "jungle" et un pointeur de singe "singe"
// R�sultat : Un bool�en representant si le pointeur courant de la liane doit avancer d'une liane ou pas pour le prochain tour
// Definition : Cette fonction permet d'avoir un mode automatique ou l'ordinateur joue tout seul au jeu
bool choixDirectionAuto(T_jungle jungle, T_singe* singe)
{
    int numero_menu; // Declaration d'un entier qui sera chang� selon le choix de l'utilisateur pour entrer en param�tre de la fonction switch

    printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
    afficheJungle(jungle, *singe); // Affiche l'etat actuel de la jungle

    printf("\nLes possibilites sont les suivantes\n");
    printf("\n-----------------------------------------------------------\n");
    if (verifHaut(jungle,*singe)) printf("1/ Aller en haut\n"); // Affiche ou non les choix s'ils sont disponibles ou non pour le joueur
    if (verifFace(jungle,*singe)) printf("2/ Aller en face\n");
    if (verifBas(jungle,*singe)) printf("3/ Aller en bas\n");
    if (!verifTriLiane(jungle)) printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
    printf("5/ Sauter a l'eau\n");
    printf("-----------------------------------------------------------\n");

    // Effet visuel permettant de montrer que l'ordinateur reflechit
    printf("\nChoix parmi les possibilites : \n");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    numero_menu = 5;

    // Choix de la direction prise par l'ordinateur
    if (verifHaut(jungle,*singe)) numero_menu = 1; // Le singe monte
    else if (verifFace(jungle,*singe)) numero_menu = 2; // Sinon il va en face
    else if (verifBas(jungle,*singe)) numero_menu = 3; // Sinon il descend
    else if (!verifTriLiane(jungle)) numero_menu = 4; // Sinon il invoque le tri
    else numero_menu = 5; // Et s'il ne peut aller nul part il saute dans l'eau

    // Switch case permettant d'effectuer le choix precedent
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
            triNextLiane(jungle);
            return false;
        default :
            printf("\nLe singe a saute a l'eau\n");
            sauterEau();
            break;
    }
    return false;
}

// Param�tres : Un booleen representant le mode de jeu
// R�sultat : Aucun
// Definition : Cette fonction permet d'initaliser le jeu (singe, jungle, apparition du singe sur la premiere liane) puis d'appeler la fonction du mode de jeu demande par l'utilisateur
void jouer(bool autoMode)
{
    T_singe singe = choixSinge(); // Initialise le singe
    T_jungle jungle = creationJungle(); // Initialise la jungle
    afficheJungle(jungle, singe); // Affiche une premiere fois la jungle sans le singe
    allerPremiereLiane(jungle, &singe); // Accroche le singe sur la premiere liane

    T_jungle jungleCourante = jungle; // Pointeur courant permettant de parcourir la jungle, le pointeur courant pointe vers la liane ou le singe est present
    bool doitAvancer = false; // booleen representant si le pointeur courant doit avancer d'une liane ou non en fonction du choix fait dans le jeu

    do // Do-while permettant de savoir si le singe est arrive a la derniere liane et donc de savoir si le jeu est termine ou non
    {
        if(autoMode) // If permettant d'appeler la fonction de jeu correspondant au mode de jeu choisi
        {
            doitAvancer = choixDirectionAuto(jungleCourante, &singe); // Fonction de choix de direction pour en mode automatique
        }
        else
        {
            doitAvancer = choixDirection(jungleCourante, &singe); // Fonction de choix de direction en demandant a l'utilisateur
        }

        if(doitAvancer) jungleCourante = getNextLiane(jungleCourante); // Fait avancer le poniteur courant si le choix precedent n'est pas le tri ou le saut dans l'eau
        clearConsole();
    }
    while(!verifFin(jungleCourante));

    printf("Vous avez gagne !\n");
    printf("Le singe a reussi a traverser la riviere !\n");

}

// Param�tres : Aucun
// R�sultat : Aucun
// Definition : Cette fonction permet de demander � l'utilisateur le mode de jeu qu'il souhaite
void choixTypeJeu()
{
    int numero_menu; // Numero representant le choix de l'utilisateur

    printf("\n########## JEU DU SINGE ##########");

    printf("\nSouhaitez vous jouer vous-meme ou lancer le mode automatique ? (taper le numero)\n");
    printf("\n-----------------------------------------------------------\n");
    printf("1/ Mode Manuel\n");
    printf("2/ Mode Automatique\n");
    printf("-----------------------------------------------------------\n");

    do // Do-while pour parcourir au minimum une fois la boucle et permettre de recommencer la boucle tant que la condition n'est pas v�rifi�e
    {
        printf("\nChoisissez un numero parmi les deux possibilites : \n");
        scanf("%d", &numero_menu);

        // Switch permettant d'appeler la fonction de jeu avec le mode correspondant en parametre
        switch(numero_menu)
        {
            case 1 :
                printf("\nVous avez choisi le mode manuel\n");
                jouer(false);
                break;
            case 2 :
                printf("\nVous avez choisi le mode automatique\n");
                jouer(true);
                break;
            default :
                printf("\nNumero non compris entre 1 et 2\n");
                break;
        }
    }
    while(numero_menu != 1 && numero_menu != 2);
}

