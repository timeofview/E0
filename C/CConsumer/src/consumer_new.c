// Librerie
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


// Prototipi di funzioni

void waitChild();
void printUsage(char*);


// Sintassi:
// programma charDaFiltrare file1, file2, ..., fileN
// viene filtrato il contenuto dei file togliendone il carattere e si stampa il risultato
// su terminale
int main(int argc, char *argv[]) {
    
    int numFigli, i;
    int *pid;
    char c;
    FILE *fp;
    
    // Controllo argomenti
    if(argc-1 < 2){
        fprintf(stderr, "\nErrore: devi passare almeno 2 argomenti!\n");
        printUsage(argv[0]);
        
        exit(EXIT_FAILURE);
    }
    
    // Verifico che l'argomento in posizione 2 sia il carattere da filtrare 
    if(strlen(argv[1]) != 1){
        fprintf(stderr, "\nErrore: il primo argomento deve essere 'carattereDaCercare'!\n");
        printUsage(argv[0]);
        
        exit(EXIT_FAILURE);
    }
    
    // Ottengo il numero dei figli in base al numero dei file passati come argomento
    numFigli = argc - 2;
    
    // Alloco dinamicamente in base al numero dei figli
    pid = (int *)malloc(numFigli * sizeof(int));
    
    
    for(i=0; i<numFigli; i++){
        
        // Eseguo la fork
        pid[i] = fork();
        
        // Figli
        if(pid[i] == 0){
                
            // Apro i file e verifico che esistano
            fp = fopen(argv[i+2], "r");
            
            // Controllo che il file esista
            if(!fp){
                fprintf(stderr, "\n++ Figlio %d - Errore: il file '%s' non esiste!\n", i, argv[i+2]);
                
                exit(EXIT_FAILURE);
            }
            
            printf("\n++ Figlio P%d - File '%s' senza il carattere '%c' ++\n", i+1, argv[i+2], argv[1][0]);
            
            // Leggo tutto il file carattere per carattere 
            while ((c = getc(fp)) != EOF){
                
                // Se il carattere è uguale a quello passato come argomento 
                if(c != argv[1][0]){
                    
                    // Stampo a video il carattere
                    putchar(c); 
                }
            }
            
            fclose(fp);
            
            // Terminazione volontaria del figlio
            exit(EXIT_SUCCESS);
        
            
        }else if(pid[i] < 0){
            fprintf(stderr, "P0: Errore nella creazione del figlio P%d!", i+1);
            
            exit(EXIT_FAILURE);
        }
    }
    
    // Padre 
    
    // Rilascio pid dalla memoria
    free(pid);
    
    // P0 attende la terminazione dei figli
    for(i=0; i<numFigli; i++){
        waitChild();
    }
    
    
    return 0;
    
}




void waitChild() {
    
    int pid_terminated, status;
    pid_terminated = wait(&status);
    
    if (pid_terminated < 0)    {
        fprintf(stderr, "P0: errore in wait\n");
        exit(EXIT_FAILURE);
    }

    if(WIFEXITED(status)){
        
        printf("P0: terminazione volontaria del figlio %d con stato %d\n", pid_terminated, WEXITSTATUS(status));
        
        if (WEXITSTATUS(status) == EXIT_FAILURE){
            
            fprintf(stderr, "P0: errore nella terminazione del figlio %d\n", pid_terminated);
            exit(EXIT_FAILURE);
        }

    }else if (WIFSIGNALED(status)){
        
        fprintf(stderr, "P0: terminazione involontaria del figlio %d a causa del segnale %d\n", pid_terminated, WTERMSIG(status));
        exit(EXIT_FAILURE);
        
    }
    
}


void printUsage(char *programName){
    
    printf("\nUtilizzo programma:\n%s carattereDaFiltrare file1 file2 ... fileN\n", programName);
    
}
