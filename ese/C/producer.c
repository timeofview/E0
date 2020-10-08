#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 256



int main(int argc, char* argv[]){ // preparazione programma
    int fd, readValues, bytes_to_write, written; char *file_out;
    char buf[MAX_STRING_LENGTH]; int righe, i; char riga[MAX_STRING_LENGTH];
    // fare controllo argomenti
    if (argc != 2) { perror(" numero di argomenti sbagliato …"); exit(EXIT_FAILURE);}
    // lettura #righe
    file_out = argv[1];
    gets (buf); // consumare il fine linea
    fd = open(file_out, O_WRONLY|O_CREAT|O_TRUNC, 00640);
    if (fd < 0){ 
        perror("P0: Impossibile creare/aprire il file"); exit(EXIT_FAILURE);
    }

    printf("Inserisci la nuova riga\n");
    gets (riga);
    while(riga!=NULL){
        
        /* la gets legge tutta la riga, separatori inclusi, e trasforma il fine
        linea in fine stringa */
        // aggiungo il fine linea
        riga[strlen(riga)+1]='\0';
        riga[strlen(riga)]='\n';
        written = write(fd, riga, strlen(riga)); // uso della primitiva
        if (written <= 0){ 
            perror("P0: errore nella scrittura sul file"); exit(2);
        }
        printf("Inserisci la nuova riga\n");
        gets (riga);
    }
    close(fd);
}
