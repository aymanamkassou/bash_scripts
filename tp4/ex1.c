/*
This program creates two processes (parent and child) that print numbers from 1 to 100.
The child process prints odd numbers (1,3,5...) and the parent prints even numbers (2,4,6...).

How it works:
1. Program sets up signal handlers:
   - SIGUSR1 and SIGUSR2 are used for process synchronization
   - SIGCHLD prevents zombie processes
   - When SIGUSR1/SIGUSR2 is received, it sets signal_received flag to 1

2. After fork():
   - Child process starts first, prints odd number, signals parent (SIGUSR2), then waits
   - Parent process waits initially for child signal
   - Parent then prints even number, signals child (SIGUSR1), then waits
   - This cycle continues until all numbers are printed

3. Synchronization mechanism:
   - Each process uses signal_received flag to know when to proceed
   - After printing, process signals other process and waits for signal back
   - Small sleep (usleep) prevents CPU hogging while waiting
   - fflush ensures immediate output printing

4. Process termination:
   - Child exits after printing last odd number
   - Parent waits for child process to finish using wait()
   - SIGCHLD handler uses non-blocking waitpid to prevent zombies
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid_fils;
pid_t pid_pere;
int signal_received = 0;

void gestionnaire_sigchld(int signal) {
    int statut;
    waitpid(-1, &statut, WNOHANG);
}

void gestionnaire_sigusr(int signal) {
    signal_received = 1;
}

int main() {
    pid_pere = getpid();
    
    signal(SIGUSR1, gestionnaire_sigusr);
    signal(SIGUSR2, gestionnaire_sigusr);
    signal(SIGCHLD, gestionnaire_sigchld);

    pid_fils = fork();
    
    if (pid_fils == 0) {
        pid_pere = getppid();
        
        for (int nombre = 1; nombre <= 99; nombre += 2) {
            printf("%d\n", nombre);
            fflush(stdout);
            kill(pid_pere, SIGUSR2);
            
            signal_received = 0;
            while (!signal_received) {
                usleep(1000);
            }
        }
        exit(0);
    } else {
        signal_received = 0;
        while (!signal_received) {
            usleep(1000);
        }
        
        for (int nombre = 2; nombre <= 100; nombre += 2) {
            printf("%d\n", nombre);
            fflush(stdout);
            kill(pid_fils, SIGUSR1);
            
            signal_received = 0;
            while (!signal_received) {
                usleep(1000);
            }
        }
        
        wait(NULL);
    }
    
    return 0;
}
