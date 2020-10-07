#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGHT 256
/////produttore File1 File2 FileN
int main(int argc, char* argv[]) {
    int n,trascritto, trascritto2;
    int fd[argc];
    char buffer[MAX_STRING_LENGHT];
    char *file_out[argc];
    char *token;
    //Controllo Parametri
    if (argc <2 || argc>10){
        perror("SINTASSI ERRATA---> USO: NomeProgramma FileDoveScrivere \n oppure numero di file inserito troppo elevato (Max 9)");
        exit(EXIT_FAILURE);
    }
    for(n=0; n<argc ; n++){
        fd[n]=-1;   // setto i file descriptor a -1 per controllare successivamente se sono stati aperti
    }

    do{
        printf("Inserisci la nuova riga, (EOF o riga vuota per terminare) : \n");
        gets(buffer);
        token= strtok(buffer, ":");
        if(token>"0" || token < "9"){
            n= atoi(token);
            token= strtok(NULL, "\0");
            fd[n-1]= open(argv[n], O_WRONLY | O_CREAT , 0777);
            trascritto = write(fd[n-1], token, strlen(token)); // uso della primitiva
            trascritto2 = write(fd[n-1], "\n", sizeof(char));
            if(trascritto < 0 || trascritto2<0){
                perror("errore nella scrittura nel file");
                exit(EXIT_FAILURE);
            }
        }else
        {
            printf("inserire un numero da uno a nove prima dei due punti");
        }
        
    }while(strcmp(buffer, "EOF")!=0 && strcmp(buffer, "")!=0);

    for(n=0; n<argc; n++){
        if(fd[n]!=-1){ // se il file è stato aperto allora lo chiudo;
            close(fd[n]);
        }
    }
    printf("FINE PROGRAMMA....SPERO VI PIACCIA\n");

    return EXIT_SUCCESS;
}
    