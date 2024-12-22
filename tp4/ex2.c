/* This program implements the shell command 'ps -uax | grep root | wc -l' using pipes and fork().
   It creates two pipes to connect three processes: first runs ps, second runs grep, and third runs wc.
   Each process redirects its input/output through the pipes as needed. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int tube_un[2], tube_deux[2];
    pid_t pid_un, pid_deux, pid_trois;

    pipe(tube_un);
    pipe(tube_deux);

    pid_un = fork();
    if (pid_un == 0) {
        close(tube_un[0]);
        dup2(tube_un[1], STDOUT_FILENO);
        close(tube_un[1]);
        close(tube_deux[0]);
        close(tube_deux[1]);
        execlp("ps", "ps", "-uax", NULL);
        exit(1);
    }

    pid_deux = fork();
    if (pid_deux == 0) {
        close(tube_un[1]);
        dup2(tube_un[0], STDIN_FILENO);
        close(tube_un[0]);
        close(tube_deux[0]);
        dup2(tube_deux[1], STDOUT_FILENO);
        close(tube_deux[1]);
        execlp("grep", "grep", "root", NULL);
        exit(1);
    }

    pid_trois = fork();
    if (pid_trois == 0) {
        close(tube_un[0]);
        close(tube_un[1]);
        close(tube_deux[1]);
        dup2(tube_deux[0], STDIN_FILENO);
        close(tube_deux[0]);
        execlp("wc", "wc", "-l", NULL);
        exit(1);
    }

    close(tube_un[0]);
    close(tube_un[1]);
    close(tube_deux[0]);
    close(tube_deux[1]);

    waitpid(pid_un, NULL, 0);
    waitpid(pid_deux, NULL, 0);
    waitpid(pid_trois, NULL, 0);

    return 0;
}
