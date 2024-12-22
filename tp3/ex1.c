// This program works by creating two child processes using fork(). The first child process 
// prints numbers 1-50, while the second child waits for the first child to complete using 
// waitpid before printing numbers 51-100. The parent process waits for both children to 
// finish. Each process flushes stdout after printing to ensure sequential output. Error 
// handling is implemented for fork failures.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t processus_fils1, processus_fils2;
    int statut;

    processus_fils1 = fork();
    if (processus_fils1 < 0) {
        perror("Échec du fork");
        exit(1);
    }
    
    if (processus_fils1 == 0) {
        for (int nombre = 1; nombre <= 50; nombre++) {
            printf("%d\n", nombre);
            fflush(stdout);
        }
        exit(0);
    } else {
        processus_fils2 = fork();
        if (processus_fils2 < 0) {
            perror("Échec du fork");
            exit(1);
        }
        
        if (processus_fils2 == 0) {
            waitpid(processus_fils1, &statut, 0);
            for (int nombre = 51; nombre <= 100; nombre++) {
                printf("%d\n", nombre);
                fflush(stdout);
            }
            exit(0);
        } else {
            waitpid(processus_fils1, &statut, 0);
            waitpid(processus_fils2, &statut, 0);
        }
    }
    return 0;
}
