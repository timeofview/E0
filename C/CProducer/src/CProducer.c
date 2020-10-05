#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGHT 256

int main(int argc, char* argv[]) {
    int fd, written,length;

    char buffer[MAX_STRING_LENGHT];
    char riga[MAX_STRING_LENGHT];
    char *file_out;
    //Controllo Parametri
    if (argc !=2){
        perror("SINTASSI ERRATA---> USO: NomeProgramma FileDoveScrivere ");
        exit(EXIT_FAILURE);
    }

    file_out = argv[1];
    fd = open(file_out,O_CREAT|O_WRONLY|O_APPEND, 0777); //volutamente dati tutti i permessi
    if(fd<0){
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    printf("Inserisci la nuova riga, (EOF o riga vuota per terminare) : \n");
    gets(buffer);
    while(strcmp(buffer, "EOF")!=0 && strcmp(buffer, "")!=0){
    	length = strlen(buffer);
    	buffer[length]='\n';
    	written = write(fd, buffer,length+1); // uso della primitiva
    	        if(written < 0){
    	            perror("errore nella scrittura nel file");
    	            close(fd);
    	            exit(EXIT_FAILURE);
    	        }
    	printf("Inserisci la nuova riga, (EOF o riga vuota per terminare) : \n");
    	gets(buffer);
        //read(1,buffer,MAX_STRING_LENGHT);
    }

    close(fd);
    printf("FINE PROGRAMMA....SPERO VI PIACCIA\n");

    return EXIT_SUCCESS;
}
