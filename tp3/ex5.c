// This program creates two child processes to execute 'ls -l' and 'ps -l' commands in parallel. 
// The parent process uses waitpid with WNOHANG option to check which child process finishes 
// first. It maintains the PIDs of both children and continuously checks their status until 
// one finishes. After detecting the first finished process, it waits for the other to 
// complete. The program includes comprehensive error handling for fork and exec operations.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t processus_ls, processus_ps;
    int statut;
    pid_t premier_termine;

    processus_ls = fork();
    
    if (processus_ls < 0) {
        perror("Échec du fork pour ls");
        exit(1);
    }
    
    if (processus_ls == 0) {
        execlp("ls", "ls", "-l", NULL);
        perror("Échec de execlp pour ls");
        exit(1);
    }

    processus_ps = fork();
    
    if (processus_ps < 0) {
        perror("Échec du fork pour ps");
        exit(1);
    }
    
    if (processus_ps == 0) {
        execlp("ps", "ps", "-l", NULL);
        perror("Échec de execlp pour ps");
        exit(1);
    }

    while (1) {
        premier_termine = waitpid(-1, &statut, WNOHANG);
        if (premier_termine > 0) {
            if (premier_termine == processus_ls) {
                printf("La commande ls a terminé en premier\n");
            } else {
                printf("La commande ps a terminé en premier\n");
            }
            break;
        }
    }

    wait(NULL);
    return 0;
}
