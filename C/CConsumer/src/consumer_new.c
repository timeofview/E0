#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Prototipi di funzioni

void printUsage(char*);


// Sintassi:
// programma charDaFiltrare file1, file2, ..., fileN
// viene filtrato il contenuto dei file togliendone il carattere e si stampa il risultato
// su terminale
int main(int argc, char *argv[]) {
    
    int i;
    char c;
    FILE *fp;
    
    // Controllo argomenti
    if(argc-1 < 2){
        fprintf(stderr, "\nErrore: devi passare almeno 2 argomenti!\n");
        printUsage(argv[0]);
        
        exit(1);
    }
    
    // Verifico che l'argomento in posizione 2 sia il carattere da filtrare 
    if(strlen(argv[1]) != 1){
        fprintf(stderr, "\nErrore: il primo argomento deve essere 'carattereDaCercare'!\n");
        printUsage(argv[0]);
        
        exit(1);
    }
    
    // Parto dall'argomento 2 perché da lì partono i vari file...
    for(i=2; i<argc; i++){
            
        // Apro tutti i file e verifico che esistano
        fp = fopen(argv[i], "r");
        
        // Controllo che il file esista
        if(!fp){
            fprintf(stderr, "\nErrore: il file '%s' non esiste!\n", argv[i]);
            
            exit(1);
        }
        
        printf("\n++ File '%s' senza il carattere '%c' ++\n", argv[i], argv[1][0]);
        
        // Leggo tutto il file carattere per carattere 
        while ((c = getc(fp)) != EOF){
            
            // Se il carattere è uguale a quello passato come argomento 
            if(c != argv[1][0]){
                
                // Stampo a video il carattere
                putchar(c); 
            }
        }
        
        fclose(fp);

    }
    
    
    printf("\nProgramma terminato!\n");
    
    return 0;
    
}


void printUsage(char *programName){
    
    printf("\nUtilizzo programma:\n%s carattereDaFiltrare file1 file2 ... fileN\n", programName);
    
}
