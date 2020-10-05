#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGHT 256

int main(int argc, char* argv[]) {
    int fd, trascritto, trascritto2;
    
    char buffer[MAX_STRING_LENGHT];
    char riga[MAX_STRING_LENGHT];
    char *file_out;
    //Controllo Parametri
    if (argc !=2){
        perror("SINTASSI ERRATA---> USO: NomeProgramma FileDoveScrivere ");
        exit(EXIT_FAILURE);
    }

    file_out = argv[1];
    fd = open(file_out,O_WRONLY  | O_CREAT, 0777); //volutamente dati tutti i permessi
    if(fd<0){
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }

    do{
        printf("Inserisci la nuova riga, (EOF o riga vuota per terminare) : \n");
        gets(buffer);
        trascritto = write(fd, buffer, strlen(buffer)); // uso della primitiva
        trascritto2 = write(fd, "\n", sizeof(char));
        if(trascritto < 0 || trascritto2<0){
            perror("errore nella scrittura nel file");
            exit(EXIT_FAILURE);
        }

    }while(strcmp(buffer, "EOF")!=0 && strcmp(buffer, "")!=0);

    close(fd);
    printf("FINE PROGRAMMA....SPERO VI PIACCIA\n");

    return EXIT_SUCCESS;
}
    