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

    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Server is running...\n");

    while (1) {
        if (msgrcv(msgid, &q, sizeof(q) - sizeof(long), 0, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        a.mtype = q.mtype;  
        a.sum = q.num1 + q.num2;

        if (msgsnd(msgid, &a, sizeof(a) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

}
 
