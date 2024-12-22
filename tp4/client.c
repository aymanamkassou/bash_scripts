#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "message.h"

int main() {
    int msgid;
    struct question q;
    struct answer a;
    pid_t pid = getpid();

    msgid = msgget(MSG_KEY, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    q.mtype = pid;  
    printf("Enter two numbers: ");
    scanf("%d %d", &q.num1, &q.num2);

    if (msgsnd(msgid, &q, sizeof(q) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    if (msgrcv(msgid, &a, sizeof(a) - sizeof(long), pid, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("The sum is: %d\n", a.sum);

    return 0;
}
