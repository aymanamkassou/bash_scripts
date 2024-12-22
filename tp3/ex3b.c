// This program implements a parallel search algorithm using two processes. It divides an array 
// into two halves and searches for a value simultaneously in both halves using separate processes. 
// The parent process searches the first half while the child searches the second half. The search 
// function returns the index if the value is found, or -1 if not found. The child communicates 
// its result through its exit code (255 if not found, index if found). The parent process 
// combines results from both searches to determine the final outcome.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int rechercher_dans_tableau(int* tableau, int debut, int fin, int valeur) {
    for (int i = debut; i < fin; i++) {
        if (tableau[i] == valeur) {
            return i;
        }
    }
    return -1;
}

int main() {
    int tableau[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int longueur = 10;
    int valeur_recherchee = 7;
    int statut;
    pid_t identifiant_processus = fork();

    if (identifiant_processus < 0) {
        perror("Échec du fork");
        exit(1);
    }

    if (identifiant_processus == 0) {
        int resultat = rechercher_dans_tableau(tableau, longueur/2, longueur, valeur_recherchee);
        exit(resultat != -1 ? resultat : 255);
    } else {
        int resultat = rechercher_dans_tableau(tableau, 0, longueur/2, valeur_recherchee);
        wait(&statut);
        
        if (resultat != -1) {
            printf("Trouvé à l'index: %d\n", resultat);
        } else if (WEXITSTATUS(statut) != 255) {
            printf("Trouvé à l'index: %d\n", WEXITSTATUS(statut));
        } else {
            printf("Valeur non trouvée\n");
        }
    }

    return 0;
}
