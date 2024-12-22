#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* print_minuscules(void* arg) {
    for(char lettre = 'a'; lettre <= 'z'; lettre++) {
        printf("%c ", lettre);
    }
    return NULL;
}

void* print_majuscules(void* arg) {
    for(char lettre = 'A'; lettre <= 'Z'; lettre++) {
        printf("%c ", lettre);
    }
    return NULL;
}

void* ecrire_petit_nombres(void* arg) {
    FILE* fichier = (FILE*)arg;
    for(int nombre = 0; nombre <= 100000; nombre++) {
        fprintf(fichier, "%d\n", nombre);
    }
    return NULL;
}

void* ecrire_grand_nombres(void* arg) {
    FILE* fichier = (FILE*)arg;
    for(int nombre = 1000000; nombre <= 1100000; nombre++) {
        fprintf(fichier, "%d\n", nombre);
    }
    return NULL;
}

int variable_globale = 0;

void* incrementer_variable(void* arg) {
    int n = *((int*)arg);
    for(int i = 0; i < n; i++) {
        variable_globale++;
    }
    return NULL;
}

int main() {
    pthread_t thread_un, thread_deux;
    
    // Exercise 4.1
    pthread_create(&thread_un, NULL, print_minuscules, NULL);
    pthread_create(&thread_deux, NULL, print_majuscules, NULL);
    pthread_join(thread_un, NULL);
    pthread_join(thread_deux, NULL);
    printf("\n");

    // Exercise 4.2
    FILE* fichier = fopen("nombres.txt", "w");
    pthread_create(&thread_un, NULL, ecrire_petit_nombres, fichier);
    pthread_create(&thread_deux, NULL, ecrire_grand_nombres, fichier);
    pthread_join(thread_un, NULL);
    pthread_join(thread_deux, NULL);
    fclose(fichier);

    int n = 1000000;
    pthread_create(&thread_un, NULL, incrementer_variable, &n);
    pthread_create(&thread_deux, NULL, incrementer_variable, &n);
    pthread_join(thread_un, NULL);
    pthread_join(thread_deux, NULL);
    printf("Dernier valeur: %d (2 * N : %d)\n", variable_globale, 2 * n);

    return 0;
}
