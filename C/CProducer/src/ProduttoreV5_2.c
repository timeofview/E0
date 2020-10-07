#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGHT 256
#define DELIM ":"
#define MAX_FILES 9


//produttore File1 File2 FileN
//NumFile         1     2    N
//argv         argv[1]
//fd              0     1     N-1
//Formattazione Input> nLinea: messaggio

int main(int argc, char* argv[]) {
    int n,trascritto, NumFiles;
    int fd[argc];
    char buffer[MAX_STRING_LENGHT];
    char *file_out[argc];
    char *token;

    //Controllo Parametri
    if (argc < 2 || argc>MAX_FILES+1){
        printf("SINTASSI ERRATA---> USO: NomeProgramma FileDoveScrivere \n oppure numero di file inserito troppo elevato (Max %d)", MAX_FILES);
        exit(EXIT_FAILURE);
    }

    NumFiles=argc-1;

    //Setto i file descriptor a -1 per controllare successivamente se sono stati aperti
    for(n=0; n<NumFiles ; n++){
        fd[n]=-1;   
    }

    //Primo Input 
    printf("Inserisci la nuova riga, (EOF per terminare) : \n");

    //Ciclo di Input con terminatore EOF
    while( gets(buffer)!=NULL ){        

	//Cut stringa
        token=strtok(buffer, DELIM);

	//Check di Esistenza dell'indice
        if(token!=NULL){
	    
	    //Conversione indice in Intero
            n=atoi(token);

	    //Check di validità dell'indice
            if(n > 0 && n <= NumFiles){

		//Se il file non è stato mai aperto
                if(fd[n-1]==-1){
                    fd[n-1]= open(argv[n], O_CREAT | O_WRONLY | O_APPEND, 0777);
                    if(fd[n-1]<0){
                        perror("IMPOSSIBILE APRIRE FILE-----terminazione del programma\n");
                        exit(EXIT_FAILURE);
                }
            }

	    //Seleziono secondo token
            token = strtok(NULL, "\0");
	   
	    //Aggiungo terminatore stringa
            token[strlen(token)+1] = '\0';

	    //Aggiungo terminatore linea
            token[strlen(token)] = '\n';

	    //Scrittura
            trascritto = write(fd[n-1], token, strlen(token));

	    //Check esito scrittura
            if(trascritto<0){
                printf("Scrittura nel file %s non riuscita\n", argv[n]);
            }
        }
	else{
            printf("Numero inserito non corretto oppure il carattere precedente i due punti non rappresenta un numero\n");
        }
	}
	//Chiedo input
        printf("Inserisci la nuova riga, (EOF per terminare):\n");
    }
    
    //Ciclo di chiusura
    for(n=0; n<argc; n++){
	//Se ho aperto il file allora lo chiudo
        if(fd[n]!=-1){
            close(fd[n]);
        }
    }

    return EXIT_SUCCESS;
}
