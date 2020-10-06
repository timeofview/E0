#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Costanti 


#define MAX_STR 128
#define MAX_BUF 1024


// Prototipi funzioni


int getMode(int numArgs, char *args[]);
void controlloArgs(int numArgs, char *args[], int mode);
void printUsage(char *programName);
void printFileContent(int numArgs, char *args[]);
void searchStringInFiles(int numArgs, char *args[]);


/*
programma file1  file2, ..., fileN  -s stringaDaCercare
(nel caso di più stringhe si accetta solo la prima parola dopo "-s" )

Prende in Input:

    - da 1 a n nomi di file ;

    - una stringa da cercare sui vari file (optional) ;
    
Produce in Output:

    - se la stringa non è presente tra gli args - mostra a video il contenuto dei file ;

    - se la stringa è presente tra gli args - stampa a video:
      Nome file - righe in cui è presente la  stringa - ricorrenze nel file della stringa 
*/


// Sintassi:
// programma file1  file2, ..., fileN  -s stringaDaCercare
int main(int argc, char *argv[]) {
    
    // mode = 0 indica che non c'è stato l'inserimento del "-s"
    // mode = 1 indica che c'è stato l'inserimento del "-s"
    int mode;
    
    // Capisco in quale delle due modalità di funzionamento sono
    mode = getMode(argc, argv);
    
    printf("Mode = %d\n0: senza -s\n1: con -s\n", mode);
    
    // Controllo gli args ion base a "mode"
    controlloArgs(argc, argv, mode);
    
    // Se è stato passato il "-s"
    if(mode)
        searchStringInFiles(argc, argv);  // Cerco la stringa nei file
    else
        printFileContent(argc, argv); // Stampo il contenuto dei file
    
    
    printf("\nProgramma terminato!\n");
    
    return 0;
    
}

int getMode(int numArgs, char *args[]){
    
    int i;
    
    // Capisco in quale delle due modalità sono
    for(i=1; i<numArgs; i++){
        
        // Se ho trovato il "-s" e quest'ultimo si trova in posizione 2 o più
        // Ho messo posizione 2 o più perché nel caso con minor numero di argomenti
        // l'invocazione dovrebbe essere così:
        // programma file1 -s stringa
        // (Ovvero posizione 2)
        if(!strcmp(args[i], "-s")){
            
            if(i >= 2){
                
                 // Modalità 1
                return 1;
                
            }else{
                
                fprintf(stderr, "Errore nell'inserimento del parametro -s!\n");
                printUsage(args[0]); // Stampo come dovrebbe essere utilizzato il programma 
                
                exit(1);
            }
        }
        
    }
    
    // Modalità 0
    return 0;
    
}


void controlloArgs(int numArgs, char *args[], int mode){
    
    int i;
    FILE *fp;
    
    
    // Apro tutti i file per verificare se sono accessibili
    for(i=1; i<numArgs && strcmp(args[i], "-s")!=0 ; i++){
        
        fp = fopen(args[i], "r");
        
        if(!fp){
            fprintf(stderr, "Errore: non è stato possibile aprire il file '%s'!\n", args[i]); 
            
            exit(1);
        }
        
        fclose(fp);
    }
    
    
    // Se sono nella modalità con il "-s"
    if(mode){
        
        // Il minimo numero di args è 3: file1, -s, stringa
        if(numArgs-1 < 3){
            fprintf(stderr, "Errore: se viene dato il parametro 'stringaDaCercare', il numero minimo degli argomenti è 3!\n");
            printUsage(args[0]);
            
            exit(1);
        }
        
    }
    
    // Se non sono nella modalità con il "-s"
    if(numArgs-1 < 1){
        fprintf(stderr, "Errore: senza il parametro 'stringaDaCercare', il numero minimo degli argomenti è 1!\n");
        printUsage(args[0]);
        
        exit(1);
    }
        
    
    return;
    
}


void printUsage(char *programName){
    
    // mode = 0 indica che non c'è stato l'inserimento del "-s"
    // mode = 1 indica che c'è stato l'inserimento del "-s"
    
    printf("\nUtilizzo programma: %s file1, file2, ..., fileN [-s stringaDaCercare]\nI parametri tra parentesi quadre sono opzionali!\n", programName);
    
    return;
}

void printFileContent(int numArgs, char *args[]){
    
    int i, c;
    FILE *fp;
    
    for(i=1; i<numArgs; i++){
            
        fp = fopen(args[i], "r");
        
        if(i < numArgs)
            printf("\n ++ Contenuto file %s ++ \n", args[i]);

        while ((c = getc(fp)) != EOF)
            putchar(c);
        
        fclose(fp);

    }
    
    return;
    
}

void searchStringInFiles(int numArgs, char *args[]){
    
    char toFind[MAX_STR];
    char buffer[MAX_BUF];
    
    FILE *fp;
    int i, cnt = 0;
    
    
    // Ottengo la stringa da cercare
    for(i=1; i<numArgs; i++){
        
        if(!strcmp(args[i], "-s"))
            strcpy(toFind, args[++i]);
        
    }
    
    for(i=1; i<numArgs && strcmp(args[i], "-s")!=0 ; i++){

        fp = fopen(args[i], "r");
        
        while(fscanf(fp, "%s", buffer) == 1) {
            
            if(!strcmp(buffer, toFind))
                cnt++;
            
        }
        
        printf("\n ++ Nel file %s la stringa '%s' è stata trovata %d volte! ++\n", args[i], toFind, cnt);
        
        cnt = 0; // Azzero il contatore per il prossimo file
        fclose(fp);
    }
    
    return;
    
}
