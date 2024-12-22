// This program demonstrates the use of fork() and execl() to execute the 'ps -l' command. 
// After forking, the child process replaces its image with the 'ps' command using execl, 
// while the parent process waits for the child to complete and retrieves its exit status. 
// The program includes error handling for both fork and exec failures. The execl function 
// requires the full path to the ps command and passes '-l' as an argument.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t identifiant_processus;
    int statut;

    identifiant_processus = fork();
    
    if (identifiant_processus < 0) {
        perror("Échec du fork");
        exit(1);
    }
    
    if (identifiant_processus == 0) {
        execl("/bin/ps", "ps", "-l", NULL);
        perror("Échec de execl");
        exit(1);
    } else {
        wait(&statut);
        printf("Processus fils terminé avec le statut : %d\n", WEXITSTATUS(statut));
    }
    
    return 0;
}
