#ifndef MESSAGES_H
#define MESSAGES_H

#include <sys/types.h>

#define MSG_KEY 1234  

struct question {
    long mtype;        
    int num1, num2;   
};

struct answer {
    long mtype;        
    int sum;          
};

#endif
