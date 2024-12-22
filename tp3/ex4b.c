// This program is similar to the previous one but uses execv() instead of execl(). The main 
// difference is that execv accepts an array of arguments rather than a variable number of 
// parameters. The program creates a child process to execute 'ps -l' while the parent waits 
// for completion. Arguments are prepared in an array format as required by execv. Error 
// handling is implemented for both fork and exec failures.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t identifiant_processus;
    int statut;
    char *arguments[] = {"ps", "-l", NULL};

    identifiant_processus = fork();
    
    if (identifiant_processus < 0) {
        perror("Échec du fork");
        exit(1);
    }
    
    if (identifiant_processus == 0) {
        execv("/bin/ps", arguments);
        perror("Échec de execv");
        exit(1);
    } else {
        wait(&statut);
        printf("Processus fils terminé avec le statut : %d\n", WEXITSTATUS(statut));
    }
    
    return 0;
}
