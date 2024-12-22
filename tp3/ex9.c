// This program implements a basic shell interface that continuously prompts for commands 
// and executes them. It works by: 1) Displaying a prompt and reading user input, 2) Parsing 
// the input into command and arguments, 3) Creating a child process using fork(), 4) Using 
// execvp() in the child process to execute the command, 5) Parent process waits for command 
// completion before showing the next prompt. The shell supports basic command execution and 
// the 'exit' command to terminate. It includes input validation, command parsing, and error 
// handling for system calls.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAILLE_MAX_COMMANDE 1024
#define TAILLE_MAX_ARGS 64

void analyser_commande(char *ligne, char **arguments) {
    char *token = strtok(ligne, " \n\t");
    int i = 0;
    
    while (token != NULL && i < TAILLE_MAX_ARGS - 1) {
        arguments[i++] = token;
        token = strtok(NULL, " \n\t");
    }
    arguments[i] = NULL;
}

int main() {
    char ligne_commande[TAILLE_MAX_COMMANDE];
    char *arguments[TAILLE_MAX_ARGS];
    pid_t identifiant_processus;
    int statut;

    while (1) {
        printf("monshell> ");
        fflush(stdout);

        if (!fgets(ligne_commande, TAILLE_MAX_COMMANDE, stdin)) {
            break;
        }

        if (ligne_commande[0] == '\n') continue;

        analyser_commande(ligne_commande, arguments);

        if (arguments[0] == NULL) continue;

        if (strcmp(arguments[0], "exit") == 0) {
            break;
        }

        identifiant_processus = fork();
        
        if (identifiant_processus < 0) {
            perror("Échec du fork");
            continue;
        }
        
        if (identifiant_processus == 0) {
            execvp(arguments[0], arguments);
            perror("Échec de l'exécution");
            exit(1);
        } else {
            wait(&statut);
        }
    }

    printf("Au revoir!\n");
    return 0;
}
