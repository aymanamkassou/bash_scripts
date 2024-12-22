// This program creates a child process that generates a random number between 0 and 100. 
// The child process uses the current time as a seed for the random number generator, 
// generates the number, and returns it as its exit code. The parent process waits for 
// the child to finish and then retrieves and displays the random number from the child's 
// exit status using WEXITSTATUS macro. Error handling is implemented for fork failures.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>

int main() {
    pid_t identifiant_processus = fork();
    int statut;

    if (identifiant_processus < 0) {
        perror("Échec du fork");
        exit(1);
    }

    if (identifiant_processus == 0) {
        srand(time(NULL));
        int nombre_aleatoire = rand() % 101;
        exit(nombre_aleatoire);
    } else {
        wait(&statut);
        if (WIFEXITED(statut)) {
            printf("Le fils a retourné: %d\n", WEXITSTATUS(statut));
        }
    }
    return 0;
}
