#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGHT 256
#define DELIM ":"
#define MAX_FILES 9
/////produttore File1 File2 FileN
//NumFile         1     2    N
//argv         argv[1]
//fd              0     1     N-1
int main(int argc, char* argv[]) {
    int n,trascritto, NumFiles;
    int fd[argc];
    char buffer[MAX_STRING_LENGHT];
    char *file_out[argc];
    char *token;
    //Controllo Parametri
    if (argc < 2 || argc>MAX_FILES+1){
        perror("SINTASSI ERRATA---> USO: NomeProgramma FileDoveScrivere \n oppure numero di file inserito troppo elevato (Max %d)", MAX_FILES);
        exit(EXIT_FAILURE);
    }

    NumFiles=argc-1;
    for(n=0; n<=NumFiles ; n++){
        fd[n]=-1;   // setto i file descriptor a -1 per controllare successivamente se sono stati aperti
    }

        printf("Inserisci la nuova riga, (EOF per terminare) : \n");
        gets(buffer);  // N  : riga
    while(strcmp(buffer, "EOF")!=0 ){
        
        
        token=strtok(buffer, DELIM);
        n=atoi(token);
        if(n > 0 && n <= NumFiles){
            if(fd[n-1]==-1){ // se il file non è stato mai aperto
                fd[n-1]= open(argv[n], O_CREAT | O_WRONLY | O_APPEND, 0777);
                if(fd[n-1]<0){
                    perror("IMPOSSIBILE APRIRE FILE-----terminazione del programma\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, "\0");
            token[strlen(token)+1] = "\0";
            token[strlen(token)] = "\n";
            trascritto = write(fd[n-1], token, strlen(token));
            if(trascritto<0){
                printf("Scrittura nel file %s non riuscita\n", argv[n]);
            }


        }else{
            printf("numero inserito non corretto oppure il carattere precedente i due punti non rappresenta un numero\n");
        }

        printf("Inserisci la nuova riga, (EOF per terminare) : \n");
        gets(buffer);  // N  : riga
    }
    

    for(n=0; n<argc; n++){
        if(fd[n]!=-1){ // se il file è stato aperto allora lo chiudo;
            close(fd[n]);
        }
    }
   

    return EXIT_SUCCESS;
}
    