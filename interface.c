#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "interface.h"
#include "liste.h"

// Paramètres : Aucun
// Résultat : Aucun
// Definition : Cette fonction permet de faire de l'espace dans la console et ainsi d'offrir une meilleure lisibilité
void clearConsole()
{
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }
}

// Paramètres : Une liane l, un singe s et un entier posX
// Résultat : Aucun
// Definition : Cette fonction permet d'afficher une liane en explicitant sa position en X
void afficheLiane(T_liane l, T_singe s, int posX)
{
    T_liane ptrCourant = l;        // Creation d'un pointeur copie de la liane en paramètre, afin de parcourir cette dernière.
    int posY = 0;                  // Initialise la position du pointeur courant
    while (!listeVide(ptrCourant)) // Tant que la case pointée de la liane n'est pas nulle, c'est-à-dire tant que le pointeur n'a pas parcouru toute la liane
    {
        if (posX == s.posX && posY == s.posY) // Si le singe est présent sur le point d'accroche de la case pointée de la liane
        {
            printf("-%c-", s.nom[0]); // Alors on affiche l'initiale du singe appelé en paramètre
        }
        else // Sinon
        {
            printf("-%d-", *getPtrData(ptrCourant)); // On affiche la valeur du point d'accroche de la liane
        }
        posY++;                                  // On incremente la hauteur actuelle de la case courante
        ptrCourant = getptrNextCell(ptrCourant); // Et on avance d'une case
    }
    printf("\n");
}

// Paramètres : Une jungle j et un singe s
// Résultat : Aucun
// Definition : Cette fonction permet d'afficher la jungle en appelant la fonction d'affichage d'une liane plusieurs fois
void afficheJungle(T_jungle j, T_singe s)
{
    T_jungle ptrCourant = j;                 // Creation d'un pointeur copie de la jungle en paramètre, afin de parcourir cette dernière.
    int posX = 0;                            // Initialisation de la position courante en X
    while (getPrecLiane(ptrCourant) != NULL) // On retourne au debut de la jungle pour l'afficher dans sa totalite
    {
        ptrCourant = getPrecLiane(ptrCourant);
    }
    printf("\n########## JUNGLE ##########\n\n");
    while (!jungleVide(ptrCourant)) // Tant que l'on a pas parcouru l'entierete de la jungle
    {
        afficheLiane(*getLiane(ptrCourant), s, posX); // On affiche la liane actuelle
        ptrCourant = getNextLiane(ptrCourant);        // Puis on avance sur la prochaine liane
        posX++;
    }
    printf("\n############################\n");
}

// Paramètres : Aucun
// Résultat : Un singe
// Definition : Cette fonction permet d'initialiser un singe (Type T_singe) en fonction des choix de l'utilisateur
T_singe initSinge()
{
    T_singe singe; // Declaration du singe
    printf("\n########## INITIALISATION DU SINGE ##########");
    int id; // Declaration de l'ID du singe
    printf("\nSaisissez l'ID du singe (numero entre 1 et 50) : ");
    scanf("%d", &id); // On assigne l'ID donne par l'utilisateur au singe
    singe.id = id;

    char nom[10]; // On demande a l'utilisateur le nom du singe et on l'affecte au singe
    printf("\nSaisissez le nom a attribuer au singe : ");
    scanf("%s", nom);
    strcpy(singe.nom, nom);

    // On initialise les coordonees du singe a -1 (X = 0 etant la premiere liane et Y = 0 etant la premiere case d'une liane)
    singe.posX = -1;
    singe.posY = -1;

    // On demande a l'utilisateur de rentrer les entiers de la liste preferes du singe
    T_liste liste_pref;
    initListe(&liste_pref);
    int val = 0;

    while (val > -1)
    {
        printf("\nSaisissez une valeur a ajouter a la liste du singe (-1 pour arreter) : ");
        scanf("%d", &val);
        if (val >= 0 && val <= 9)
        {
            liste_pref = ajoutEnFin(liste_pref, val); // On ajoute en fin de liste
        }
    }
    singe.listeIntPreferes = liste_pref; // On assigne la liste au singe

    //printf("\n %d %s", id, nom);

    return singe;
}

// Paramètres : Aucun
// Résultat : Un singe
// Definition : Cette fonction permet d'initialiser un singe en appelant la fonction précédente et donne une esthétique visuelle simple
T_singe choixSinge()
{
    printf("\n########## JEU DU SINGE ##########");
    printf("\nVous allez pouvoir saisir l'ID, le nom, ainsi que la liste d'entiers preferes de votre singe\n");

    T_singe singe = initSinge();
    printf("\nSinge cree !!!");
    return singe;
}

// Paramètres : Aucun
// Résultat : Une jungle
// Definition : Cette fonction permet d'initialiser la jungle en appelant la génération de jungle, et permet une esthétique visuelle
T_jungle creationJungle()
{
    printf("\nCreation de la jungle en cours");
    sleep(1);
    printf(".");
    sleep(1);
    T_jungle jungle = genererJungle();
    printf(".");
    sleep(1);
    printf("."); // DOnne un reel effet de charegment
    printf("\nJungle creee !!!");
    return jungle; // Retourne la jungle cree
}

// Paramètres : Une jungle "jungle" et un pointeur vers un singe "singe"
// Résultat : Un booléen representant si le pointeur courant de la liane doit avancer d'une liane ou pas pour le prochain tour
// Definition : Cette fonction permet à l'utilisateur de choisir la direction que le singe doit emprunter selon les possibilités
bool choixDirection(T_jungle jungle, T_singe *singe)
{
    int numero_menu; // Declaration d'un entier qui sera changé selon le choix de l'utilisateur pour entrer en paramètre de la fonction switch

    do // Do-while pour parcourir au minimum une fois la boucle et permettre de recommencer la boucle tant que la condition n'est pas vérifiée
    {
        printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
        afficheJungle(jungle, *singe);

        printf("\nChoisissez parmi les propositions suivantes le traitement a effectuer (taper le numero)\n");
        printf("\n-----------------------------------------------------------\n");
        if (verifHaut(jungle, *singe))
            printf("1/ Aller en haut\n");
        if (verifFace(jungle, *singe))
            printf("2/ Aller en face\n");
        if (verifBas(jungle, *singe))
            printf("3/ Aller en bas\n");
        printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
        printf("5/ Sauter a l'eau\n");
        printf("-----------------------------------------------------------\n");

        printf("\nChoisissez un numero parmi les possibilites : \n");
        scanf("%d", &numero_menu);

        // Switch case permettant d'effectuer le choix de l'utilisateur en appelant la fonction correspondante
        switch (numero_menu)
        {
        case 1:
            printf("\nVous avez choisi d'aller en haut\n");
            return allerEnHaut(jungle, singe);
        case 2:
            printf("\nVous avez choisi d'aller en face\n");
            return allerEnFace(jungle, singe);
        case 3:
            printf("\nVous avez choisi d'aller en bas\n");
            return allerEnBas(jungle, singe);
        case 4:
            printf("\nVous avez invoque le dieu DONKEY-KONG !!!\n");
            triLiane(jungle);
            return false;
        case 5:
            printf("\nVous avez choisi de sauter a l'eau\n");
            sauterEau();
            break;
        default:
            printf("\nVotre choix n'est pas valide, saisissez un numero entre 1 et 5\n");
            break;
        }
    } while (numero_menu < 1 && numero_menu > 5); // Verifie si le nombre rentre correspond a un choix possible
    return false;
}

// Paramètres : Une jungle "jungle" et un singe "singe"
// Résultat : Un booléen representant si le pointeur courant de la liane doit avancer d'une liane ou pas pour le prochain tour
// Definition : Cette fonction permet d'avoir un mode automatique ou l'ordinateur joue tout seul au jeu
bool choixDirectionAuto(T_jungle jungle, T_singe *singe)
{
    int numero_menu; // Declaration d'un entier qui sera changé selon le choix de l'utilisateur pour entrer en paramètre de la fonction switch

    do // Do-while pour parcourir au minimum une fois la boucle et permettre de recommencer la boucle tant que la condition n'est pas vérifiée
    {
        printf("\nVoici la jungle, l'initiale du singe represente sa position actuelle\n");
        afficheJungle(jungle, *singe); // Affiche l'etat actuelle de la jungle

        printf("\nLes possibilites sont les suivantes\n");
        printf("\n-----------------------------------------------------------\n");
        if (verifHaut(jungle, *singe))
            printf("1/ Aller en haut\n");
        if (verifFace(jungle, *singe))
            printf("2/ Aller en face\n");
        if (verifBas(jungle, *singe))
            printf("3/ Aller en bas\n");
        if (!verifTriLiane(jungle))
            printf("4/ Invocation dieu DONKEY-KONG (trier entiers liane suivante)\n");
        printf("5/ Sauter a l'eau\n");
        printf("-----------------------------------------------------------\n");

        // Effet visuel de chargement
        printf("\nChoix parmi les possibilites : \n");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".");
        numero_menu = 5;

        // Choix de la direction
        if (verifHaut(jungle, *singe))
            numero_menu = 1; // Le singe monte
        else if (verifFace(jungle, *singe))
            numero_menu = 2; // Sinon il va en face
        else if (verifBas(jungle, *singe))
            numero_menu = 3; // Sinon il descend
        else if (!verifTriLiane(jungle))
            numero_menu = 4; // Invocation du tri de la liste
        else
            numero_menu = 5; // Sinon il tombe dans l'eau

        // Appel de la fonction correspondante
        switch (numero_menu)
        {
        case 1:
            printf("\nLe singe est alle en haut\n");
            return allerEnHaut(jungle, singe);
        case 2:
            printf("\nLe singe est alle en face\n");
            return allerEnFace(jungle, singe);
        case 3:
            printf("\nLe singe est alle en bas\n");
            return allerEnBas(jungle, singe);
        case 4:
            printf("\nInvocation du dieu DONKEY-KONG !!!\n");
            triLiane(jungle);
            return false;
        case 5:
            printf("\nLe singe a saute a l'eau\n");
            sauterEau();
            break;
        default:
            printf("\nNumero non compris entre 1 et 5\n");
            break;
        }
    } while (numero_menu < 1 && numero_menu > 5);
    return false;
}

// Paramètres : Aucun
// Résultat : Aucun
// Definition : Cette fonction permet d'initaliser le jeu (singe, jungle, apparition du singe sur la premiere liane) puis d'appeler la fonction du mode de jeu demande par l'utilisateur
void jouer()
{
    T_singe singe = choixSinge();       // Initialise le singe
    T_jungle jungle = creationJungle(); // Initialise la jungle
    afficheJungle(jungle, singe);       // Affiche la jungle initiale
    allerPremiereLiane(jungle, &singe); // Et attace le singe surla premiere liane

    T_jungle jungleCourante = jungle; // Pointeur courant permettant de parcourir la jungle
    bool doitAvancer = false;         // booleen representant si le pointeur courant doit avancer d'une liane ou non en fonction du choix fait dans le jeu

    do // Do-while permettant de savoir si le singe est arrive a la derniere liane et donc de savoir si le jeu est termine ou non
    {
        doitAvancer = choixDirection(jungleCourante, &singe); // Choix de l'utilisateur
        if (doitAvancer)
            jungleCourante = getNextLiane(jungleCourante); // On avance seulement si le choix effectue necessite d'avancer
        clearConsole();
    } while (!verifFin(jungle, singe));

    printf("Vous avez gagne !\n");
    printf("Le singe a reussi a traverser la riviere !\n");
}

// Paramètres : Aucun
// Résultat : Aucun
// Definition : Cette fonction permet d'initaliser le jeu (singe, jungle, apparition du singe sur la premiere liane) puis d'appeler la fonction du mode de jeu automatique
void jouerAuto()
{
    T_singe singe = choixSinge();       // Initialise le singe
    T_jungle jungle = creationJungle(); // Initialise la jungle
    afficheJungle(jungle, singe);       // Affiche la jungle initiale
    allerPremiereLiane(jungle, &singe); // Et attace le singe surla premiere liane

    T_jungle jungleCourante = jungle; // Pointeur courant permettant de parcourir la jungle
    bool doitAvancer = false;         // booleen representant si le pointeur courant doit avancer d'une liane ou non en fonction du choix fait dans le jeu

    do // Do-while permettant de savoir si le singe est arrive a la derniere liane et donc de savoir si le jeu est termine ou non
    {
        doitAvancer = choixDirectionAuto(jungleCourante, &singe); // Choix de l'utilisateur
        if (doitAvancer)
            jungleCourante = getNextLiane(jungleCourante); // On avance seulement si le choix effectue necessite d'avancer
        clearConsole();
    } while (!verifFin(jungle, singe));

    printf("Vous avez gagne !\n");
    printf("Le singe a reussi a traverser la riviere !\n");
}

// Paramètres : Aucun
// Résultat : Aucun
// Definition : Cette fonction permet de demander à l'utilisateur le mode de jeu qu'il souhaite
void choixTypeJeu()
{
    int numero_menu; // Numero representant le choix de l'utilisateur

    printf("\n########## JEU DU SINGE ##########");

    printf("\nSouhaitez vous jouer vous-meme ou lancer le mode automatique ? (taper le numero)\n");
    printf("\n-----------------------------------------------------------\n");
    printf("1/ Mode Manuel\n");
    printf("2/ Mode Automatique\n");
    printf("-----------------------------------------------------------\n");

    do // Do-while pour parcourir au minimum une fois la boucle et permettre de recommencer la boucle tant que la condition n'est pas vérifiée
    {
        printf("\nChoisissez un numero parmi les deux possibilites : \n");
        scanf("%d", &numero_menu);

        // Switch permettant d'appeler la fonction de jeu avec le mode correspondant en parametre
        switch (numero_menu)
        {
        case 1:
            printf("\nVous avez choisi le mode manuel\n");
            jouer();
            break;
        case 2:
            printf("\nVous avez choisi le mode automatique\n");
            jouerAuto();
            break;
        default:
            printf("\nNumero non compris entre 1 et 2\n");
            break;
        }
    } while (numero_menu != 1 && numero_menu != 2);
}
