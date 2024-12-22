// This program executes any command passed as command line arguments. It works by first 
// combining all arguments into a single command string. Then it creates a child process 
// using fork(). The child process uses execvp() to execute the command with its arguments, 
// while the parent process waits for completion. execvp() is used because it searches for 
// the command in PATH and accepts arguments as an array. The program includes error handling 
// for fork(), execvp(), and argument validation.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s commande [arguments...]\n", argv[0]);
        return 1;
    }

    pid_t identifiant_processus;
    int statut;

    identifiant_processus = fork();
    
    if (identifiant_processus < 0) {
        perror("Échec du fork");
        exit(1);
    }
    
    if (identifiant_processus == 0) {
        execvp(argv[1], &argv[1]);
        perror("Échec de l'exécution");
        exit(1);
    } else {
        wait(&statut);
    }
    
    return 0;
}
