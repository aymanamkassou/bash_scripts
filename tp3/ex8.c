// This program implements two command execution patterns: parallel and sequential execution 
// of 'who', 'ps', and 'ls -l' commands. The program takes a mode argument (-p for parallel, 
// -s for sequential). In parallel mode, it creates three child processes that run simultaneously, 
// while in sequential mode, each command waits for the previous one to finish. The program 
// uses fork() and execvp() for process creation and command execution, with appropriate 
// waiting mechanisms for each mode. Error handling is implemented for all system calls.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int executer_commande(char *commande, char *arg) {
    pid_t identifiant_processus = fork();
    
    if (identifiant_processus < 0) {
        perror("Échec du fork");
        return -1;
    }
    
    if (identifiant_processus == 0) {
        char *args[] = {commande, arg, NULL};
        execvp(commande, args);
        perror("Échec de l'exécution");
        exit(1);
    }
    
    return identifiant_processus;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "-p") != 0 && strcmp(argv[1], "-s") != 0)) {
        printf("Usage: %s [-p|-s]\n", argv[0]);
        printf("-p: exécution parallèle\n-s: exécution séquentielle\n");
        return 1;
    }

    int mode_parallele = (strcmp(argv[1], "-p") == 0);
    pid_t pid_who, pid_ps, pid_ls;

    if (mode_parallele) {
        pid_who = executer_commande("who", NULL);
        pid_ps = executer_commande("ps", NULL);
        pid_ls = executer_commande("ls", "-l");
        
        waitpid(pid_who, NULL, 0);
        waitpid(pid_ps, NULL, 0);
        waitpid(pid_ls, NULL, 0);
    } else {
        executer_commande("who", NULL);
        wait(NULL);
        executer_commande("ps", NULL);
        wait(NULL);
        executer_commande("ls", "-l");
        wait(NULL);
    }

    return 0;
}
