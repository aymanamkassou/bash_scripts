// This program demonstrates process information retrieval by creating a child process using 
// fork(). For both parent and child processes, it displays comprehensive process information 
// including process ID, parent process ID, real and effective user IDs, and group IDs. The 
// program first identifies whether it's running as parent or child, then retrieves and 
// displays all process characteristics using system calls. The parent process waits for the 
// child to complete before terminating.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main() {
    pid_t identifiant_processus = fork();

    if (identifiant_processus < 0) {
        perror("Échec du fork");
        exit(1);
    }

    printf("Type de processus: %s\n", 
           identifiant_processus == 0 ? "Fils" : "Père");
    printf("ID du processus: %d\n", getpid());
    printf("ID du processus père: %d\n", getppid());
    printf("UID réel: %d\n", getuid());
    printf("UID effectif: %d\n", geteuid());
    printf("GID réel: %d\n", getgid());
    printf("GID effectif: %d\n", getegid());
    printf("\n");

    if (identifiant_processus > 0) {
        wait(NULL);
    }

    return 0;
}
