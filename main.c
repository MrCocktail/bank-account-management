#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

struct Compte {
    int numero;
    char nomClient[30];
    char sexeClient[10];
    char dateCreation[13];
    char typeCompte[12];
    float solde;
};
struct Compte *pCompte;

struct node {
    struct Compte info;
    struct node *next;
};

struct node *first, *last;

// Functions Prototypes
struct Compte getAccountInfos();
struct Compte deleteFirstNode(struct node **last);
struct Compte deleteSecondNode(struct node *last);
struct Compte deleteNodeByAccNb();
struct Compte makeDeposit();
struct Compte makeWithdrawal();
struct Compte insertAfter();
void addToFirstNode(struct node **last, struct Compte newNode);
void addToSecondNode(struct node *last);
void addToLastNode(struct node *last);
void displayAccByType();
void displayWomenCurrentAcc();
void affichage(struct node *last);
char* getDate(); 

// Global
char date[30];
struct Compte newAccount;

void menu(){
    int userChoice;
    do {
        system("cls");
        puts("\n Veuillez choisir une option:\n\n 1.   Ajouter un Compte au premier noeud\n 2.   Ajouter un Compte au second noeud\n 3.   Ajouter un Compte au dernier noeud\n 4.   Suppression du dernier noeud\n 5.   Suppression du premier noeud\n 6.   Suppression d'un noeud intermediaire connaissant le numero du compte\n 7.   Faire un depot sur un compte donne\n 8.   Faire un retrait sur un compte donne\n 9.   Inserer un noeud intermediaire apres un compte dont on connait le numero\n 10.  Affichage des comptes d'un type donne (epargne ou courant)\n 11.  Affichage des filles proprietaires d'un compte courant\n 12.  Liste generale des comptes avec leurs soldes \n 0.   Quitter\n");
        scanf(" %d", &userChoice);
        switch (userChoice) {
            case 1:
                newAccount = getAccountInfos(); 
                addToFirstNode(&last, newAccount);
                // affichage(last);
                break;
            case 2:
                addToSecondNode(last);
                // affichage(last);
                break;
            case 3:
                addToLastNode(last);
                // affichage(last);
                break;
            case 4:
                deleteSecondNode(last);
                // affichage(last);
                break;
            case 5:
                deleteFirstNode(&last);
                // affichage(last);
                break;
            case 6:
                deleteNodeByAccNb();
                menu();
                break;
            case 7:
                makeDeposit();
                // affichage(last);
                break;
            case 8:
                makeWithdrawal();
                // affichage(last);
                break;
            case 9:
                insertAfter();
                menu();
                break;
            case 10:
                displayAccByType();
                break;
            case 11:
                displayWomenCurrentAcc();
                break;
            case 12:
                affichage(last);
                break;
            case 0: 
                printf("Session terminee\n");
                exit(0);
            default:
                printf("Option invalide\n");	    
                break;
        }
    } while (userChoice != 0);
}

char* getDate() {
    // char date[30];
    time_t current_time = time(NULL);
    if (current_time == ((time_t)-1)) {
        printf("Failed to obtain the current time.\n");
        return NULL; 
    }

    struct tm *local_time = localtime(&current_time);
    if (local_time == NULL) {
        fprintf(stderr, "Failed to convert the current time.\n");
        return NULL; 
    }

    strftime(date, sizeof(date), "%Y-%m-%d", local_time);
    return date; 
}

struct Compte getAccountInfos() {
    struct Compte compte; 
    int index;

    system("cls");
    printf("\n");
    puts(" Veuillez saisir les informations du compte\n");
    puts(" Numero: ");
    scanf(" %d", &compte.numero);
    getchar();
    puts(" Nom: ");
    fgets(compte.nomClient, sizeof(compte.nomClient), stdin);
    compte.nomClient[strcspn(compte.nomClient, "\n")] = 0; // Remove newline
    do {
        puts(" Sexe: (entrez 0 pour Femme ou 1 pour Homme) ");
        scanf(" %d", &index);
    } while (index != 0 && index != 1);
    if (index == 0) {
        strcpy(compte.sexeClient, "F");
    } else {
        strcpy(compte.sexeClient, "H");
    }

    // fgets(compte.sexeClient, sizeof(compte.sexeClient), stdin);
    // compte.sexeClient[strcspn(compte.sexeClient, "\n")] = 0;
    index = 99999;

    do {
        puts(" Type de Compte: (entrez 0 pour Courant ou 1 pour Epargne) ");
        scanf(" %d", &index);
    } while (index != 0 && index != 1);
    if (index == 0) {
        strcpy(compte.typeCompte, "Courant");
    } else {
        strcpy(compte.typeCompte, "Epargne");
    }
    // fgets(compte.typeCompte, sizeof(compte.typeCompte), stdin);
    // compte.typeCompte[strcspn(compte.typeCompte, "\n")] = 0;
    puts(" Solde: ");
    scanf(" %f", &compte.solde);

    char *date = getDate();
    if (date != NULL) {
        strcpy(compte.dateCreation, date);
    } else {
        strcpy(compte.dateCreation, "N/A"); // Handle date retrieval error
    }

    return compte;
}

void addToFirstNode(struct node **last, struct Compte newNode) {
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "Echec d'allocation de memoire.\n");
        exit(1);
    }
    temp->info = newNode; 
    temp->next = *last;
    *last = temp;
}
void addToSecondNode(struct node *last) {
    struct Compte newNode = getAccountInfos();
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "Echec d'allocation de memoire.\n");
        exit(1);
    } 
    else {
        if (last == NULL) {
            fprintf(stderr, "Operation impossible...");
            exit(1);
        } else {
            temp->info = newNode; 
            temp->next = last->next;
            last->next = temp;
        }
    }
}
void addToLastNode(struct node *last) {
    struct Compte newNode = getAccountInfos();
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "Echec d'allocation de memoire.\n");
        exit(1);
    } 
    else {
        if ((last == NULL) || (last->next == NULL)) {
            fprintf(stderr, "Operation impossible...");
            exit(1);
        } else {
            while (last->next != NULL) {
                last =  last->next;
            }
            temp->info = newNode; 
            temp->next = NULL;
            last->next = temp;
        }
    }
}

struct Compte deleteFirstNode(struct node **last) {
    struct node *temp;
    struct Compte acc;
    if (*last == NULL) {
        printf("Operation impossible...");
        exit(1);
    } else {
        temp = *last;
        *last = temp->next;
        acc = temp->info;
        free(temp);
        return acc;
    }
}

struct Compte deleteSecondNode(struct node *last) {
    struct node *temp;
    struct Compte acc;
    if ((last == NULL) || (last->next == NULL)) {
        printf("Operation impossible...");
        exit(1);
    } else {
        temp = last->next;
        last->next = temp->next;
        acc = temp->info;
        free(temp);
        return acc;
    }
}


struct Compte deleteNodeByAccNb() {
    int number;
    struct node *current = last;
    struct node *previous = NULL;
    struct Compte acc;

    system("cls");
    puts(" Entrez le numero du compte que vous voulez supprimer : ");
    scanf(" %d", &number);

    if (current == NULL) {
        printf(" Liste vide... Operation impossible.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    while (current != NULL && current->info.numero != number) {
        // printf(" Vérification du numero de compte : %d\n", current->info.numero);
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf(" Compte introuvable.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    acc = current->info;

    if (previous == NULL) {
        last = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Compte avec le numero %d supprime avec succes.\n", number);
    getch();
    return acc;
}

struct Compte makeDeposit() {
    int number;
    float amount;
    struct node *current = last;
    struct Compte acc;

    system("cls");
    puts(" Entrez le numero du compte : ");
    scanf(" %d", &number);
    puts(" Entrez le montant a ajouter sur le compte : ");
    scanf(" %f", &amount); // Correction ici pour lire un float.

    // Vérification si la liste est vide.
    if (current == NULL) {
        printf(" Liste vide... Operation impossible.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    // Recherche du compte avec le numéro donné.
    while (current != NULL && current->info.numero != number) {
        current = current->next;
    }

    // Si le compte n'est pas trouvé.
    if (current == NULL) {
        printf(" Compte non trouve.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    // Mise à jour du solde.
    current->info.solde += amount;
    acc = current->info;

    // Affichage du compte mis à jour.
    system("cls");
    printf("Depot sur le compte : %d effectue avec succes.\n", number);
    printf("Details du compte :\n\n");
    printf("%-10s %-25s %-5s %-10s %-15s %-20s\n", 
           "#", 
           "Nom", 
           "Sexe", 
           "Date", 
           "Type de Compte", 
           "Solde");
    printf("%-10d %-25s %-5s %-10s %-15s %f\n", 
           acc.numero, 
           acc.nomClient, 
           acc.sexeClient, 
           acc.dateCreation, 
           acc.typeCompte, 
           acc.solde);
    getch();
    return acc;
}

struct Compte makeWithdrawal() {
    int number;
    float amount;
    struct node *current = last;
    struct Compte acc;
    system("cls");
    puts(" Entrez le numéro du compte : ");
    scanf(" %d", &number);
    puts(" Entrez le montant a retirer sur le compte : ");
    scanf(" %f", &amount); // Correction ici pour lire un float.

    // Vérification si la liste est vide.
    if (current == NULL) {
        printf(" Liste vide... Operation impossible.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    // Recherche du compte avec le numéro donné.
    while (current != NULL && current->info.numero != number) {
        current = current->next;
    }

    // Si le compte n'est pas trouvé.
    if (current == NULL) {
        printf(" Compte non trouve.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    system("cls");
    // Mise à jour du solde.
    if (amount > current->info.solde) {
        printf("Erreur! Montant superieur a la balance disponible sur le compte\n");
        // acc = current->info;
    } else {
        current->info.solde -= amount;
        printf("Retrait sur le compte : %d effectue avec succes.\n", number);

    }
    acc = current->info;

    // Affichage du compte mis à jour.
    system("cls");
    printf("Details du compte :\n");
    printf("%-10s %-25s %-5s %-10s %-15s %-20s\n", 
           "#", 
           "Nom", 
           "Sexe", 
           "Date", 
           "Type de Compte", 
           "Solde");
    printf("%-10d %-25s %-5s %-10s %-15s %f\n", 
           acc.numero, 
           acc.nomClient, 
           acc.sexeClient, 
           acc.dateCreation, 
           acc.typeCompte, 
           acc.solde);
    getch();
    return acc;
}

struct Compte insertAfter() {
    int number;
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    struct Compte newNode = getAccountInfos();
    struct node *current = last;
    struct Compte acc;

    // Vérifiez si la liste est vide
    if (last == NULL) {
        printf("Liste vide... Opération impossible.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }
    puts("Entrez le numero du compte de reference : ");
    scanf(" %d", &number);

    if (temp == NULL) {
        fprintf(stderr, "Echec d'allocation de memoire.\n");
        getch();
        exit(1);
    }

    // Recherchez le compte de référence
    int found = 0; // Indicateur pour vérifier si le numéro est trouvé
    while ((current != NULL) && (current->info.numero != number)) {
        current = current->next;
    }
    if (current->info.numero == number) {
        found = 1;
    }
    // do {
    //     if (current->info.numero == number) {
    //         found = 1;
    //         break;
    //     }
    //     current = current->next;
    // } while (current != last->next); // Boucle dans une liste circulaire

    if (!found) {
        printf("Compte introuvable.\n");
        getch();
        memset(&acc, 0, sizeof(struct Compte));
        return acc;
    }

    // Insérez le nouveau nœud après le nœud de référence
    temp->info = newNode;
    temp->next = current->next;
    current->next = temp;

    // Mettez à jour `last` si le nouveau nœud est inséré après le dernier
    if (current == last) {
        last = temp;
    }
    if (current->next == temp && current == last) {
        temp->next = current;
        last = temp;
    }

    acc = temp->info;
    printf("Compte insere apres le compte %d avec succes.\n", number);
    getch();
    return acc;
}


void displayAccByType() {
    int number;
    struct node *current = last;
    system("cls");
    puts("Tapez 1 pour afficher tous les comptes courants\nTapez 2 pour afficher tous les comptes d'epargne");
    scanf(" %d", &number);

    if (current == NULL) {
        printf(" Liste vide... Operation impossible.\n");
        getch();
        return;
    }

    int found = 0; 

    if (number == 1) {
        printf(" Liste des comptes courants :\n");
        while (current != NULL) {
            if (strcmp(current->info.typeCompte, "Courant") == 0) {
                printf("%d %s %s %s %s %.2f\n", current->info.numero, current->info.nomClient, current->info.sexeClient, current->info.dateCreation, current->info.typeCompte, current->info.solde);
                found = 1;
            }
            current = current->next;
        }
    } else if (number == 2) {
        printf(" Liste des comptes d'epargne :\n");
        while (current != NULL) {
            if (strcmp(current->info.typeCompte, "Epargne") == 0) {
                printf("%d %s %s %s %s %.2f\n", current->info.numero, current->info.nomClient, current->info.sexeClient, current->info.dateCreation, current->info.typeCompte, current->info.solde);
                found = 1;
            }
            current = current->next;
        }
    } else {
        printf(" Choix invalide. Veuillez taper 1 ou 2.\n");
        getch();
        return;
    }

    if (!found) {
        printf(" Aucun compte trouve pour le type sélectionne.\n");
    }
    getch();
}

void displayWomenCurrentAcc() {
    struct node *current = last;
    int found = 0;
    system("cls");
    if (current == NULL) {
        printf("Liste vide... Operation impossible.\n");
        getch();
        return;
    }

    while (current != NULL) {
        if (strcmp(current->info.sexeClient, "F") == 0 && strcmp(current->info.typeCompte, "Courant") == 0) {
            printf("%d %s %s %s %s %.2f\n", current->info.numero, current->info.nomClient, current->info.sexeClient, current->info.dateCreation, current->info.typeCompte, current->info.solde);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("Aucun compte trouve.\n");
    }
    getch();
}


void affichage(struct node *last) {
    struct node *temp = last;
    system("cls");
    printf("\n");
    if (temp == NULL) {
        printf("%65s", "La liste est vide.\n");
    } else {
        printf("%65s", "Liste des comptes :");
        printf("\n\n");
        printf("%-12s %s", "", "------------------------------------------------------------------------------------\n");
        printf("%-12s %-10s %-25s %-5s %-10s %-15s %-20s\n", 
            "",
            "#", 
            "Nom", 
            "Sexe", 
            "Date", 
            "Type de Compte", 
            "Solde");
        printf("%-12s %s", "", "------------------------------------------------------------------------------------\n");
        while (temp != NULL) {
            printf("%-12s %-10d %-25s %-5s %-10s %-15s %f\n", 
                "",
                temp->info.numero, 
                temp->info.nomClient, 
                temp->info.sexeClient, 
                temp->info.dateCreation, 
                temp->info.typeCompte, 
                temp->info.solde);
            temp = temp->next;
        }
    }
    getch();
    menu();
}
// void affichage1(struct node *last) {
//     struct node *temp = last;
//     system("cls");
//     printf("\n");
    
//         printf("%65s", "Liste des comptes :");
//         printf("\n\n");
//         printf("%-12s %s", "", "------------------------------------------------------------------------------------\n");
//         printf("%-12s %-10s %-25s %-5s %-10s %-15s %-20s\n", 
//             "",
//             "#", 
//             "Nom", 
//             "Sexe", 
//             "Date", 
//             "Type de Compte", 
//             "Solde");
//         printf("%-12s %s", "", "------------------------------------------------------------------------------------\n");
//         // printf("------------------------------------------------------------------------------------\n");
//         // while (temp != NULL) {
//             printf("%-12s %-10d %-25s %-5s %-10s %-15s %f\n", 
//                 "",
//                 "temp->info.", 
//                 "temp->info.", 
//                 "temp", 
//                 "temp->info", 
//                 "temp->info.", 
//                 123.45);
//         // }
    
//     getch();
//     menu();
// }

int main() {
    menu();
    printf("\nSession terminee.\n");
    return 0;
}