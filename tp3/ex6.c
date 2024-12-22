// This program uses the system() function to execute the 'cat' command on a file specified 
// as a command line argument. It first checks if a filename was provided as an argument. 
// If present, it constructs a command string combining 'cat' with the filename and executes 
// it using system(). The program includes error checking for both command line arguments 
// and system() execution. After displaying the file contents, it returns control to the user.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s nom_fichier\n", argv[0]);
        return 1;
    }

    char commande[256];
    snprintf(commande, sizeof(commande), "cat %s", argv[1]);
    
    int resultat = system(commande);
    
    if (resultat == -1) {
        perror("Échec de l'exécution de la commande");
        return 1;
    }

    return 0;
}
