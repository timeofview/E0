#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h> // Per isascii, isspace, ...
#include <sys/wait.h>


// Costanti 


#define MAX_STR 128
#define MAX_BUF 1024


// Prototipi funzioni


int getMode(int numArgs, char *args[]);
void controlloargs(int numArgs, char *args[], int mode);
int isText(char *filename);
void printUsage(char *programName);
void printfFileContent(int numArgs, char *args[]);
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
    mode = getMode(argc, argv); // SegFault
    
    printf("Mode = %d\n0: senza -s\n1: con -s\n", mode);
    
    // Controllo gli args ion base a "mode"
    controlloargs(argc, argv, mode);
    
    // Se non è stato passato il "-s"
    if(!mode)
        printfFileContent(argc, argv); // Stampo il contenuto dei file
    
    
    // Cerco la stringa nei file
    searchStringInFiles(argc, argv);
    
    printf("Programma terminato\n");
    
    
    return 0;
}

int getMode(int numArgs, char *args[]){ // SegFault
    
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
                
                exit(EXIT_FAILURE);
            }
        }
        
    }
    
    // Modalità 0
    return 0;
    
}


void controlloargs(int numArgs, char *args[], int mode){
    
    int i;
    
    
    // Se sono nella modalità con il "-s"
    if(mode){
        
        // Il minimo numero di args è 3: file1, -s, stringa
        if(numArgs-1 < 3){
            fprintf(stderr, "Errore: se viene dato il parametro 'stringaDaCercare', il numero minimo degli argomenti è 3!\n");
            printUsage(args[0]);
            
            exit(EXIT_FAILURE);
        }
        
        // Controllo che i file esistano e che siano di testo
        for(i=1; i<numArgs; i++){
            
            if(!isText(args[i])){
                fprintf(stderr, "Errore: %s è un file binario!\n", args[i]);
                exit(EXIT_FAILURE);
            }
            // Proseguo
        }
        
    }
    
    // Se non sono nella modalità con il "-s"
    if(numArgs-1 < 1){
            fprintf(stderr, "Errore: senza il parametro 'stringaDaCercare', il numero minimo degli argomenti è 1!\n");
            printUsage(args[0]);
            
            exit(EXIT_FAILURE);
        }
        
        // Controllo che i file esistano e che siano di testo
        for(i=1; i<numArgs; i++){
            
            if(!isText(args[i])){
                fprintf(stderr, "Errore: %s è un file binario!\n", args[i]);
                exit(EXIT_FAILURE);
            }
            // Proseguo
        }
    
    return;
    
}


int isText(char *filename) {
    
    int c;
    FILE *fp;
    
    fp = fopen(filename, "r");
    
    if (!fp) {
        fprintf(stderr, "Errore apertura file %s!\n", filename);
        
        exit(EXIT_FAILURE);
    }
    
    while ((c = fgetc(c) != EOF)) {
        if ((!isascii(c) || iscntrl(c)) && !isspace(c)) {
            printf("%s è un file binario!\n", filename);
            fclose(fp);
            
            return 0;
        }
    }
    printf("%s è un file di testo!\n", filename);
    fclose(fp);
    
    return 1;
    
    
}

void printUsage(char *programName){
    
    // mode = 0 indica che non c'è stato l'inserimento del "-s"
    // mode = 1 indica che c'è stato l'inserimento del "-s"
    
    printf("\nUtilizzo programma: %s file1, file2, ..., fileN [-s stringaDaCercare]\nI parametri tra parentesi quadre sono opzionali!\n", programName);
    
    return;
}

void printfFileContent(int numArgs, char *args[]){
    
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
        
        printf("\n ++ Nel file %s la stringa %s è stata trovata %d volte! ++\n", args[i], toFind, cnt);
        
        cnt = 0; // Azzero il contatore per il prossimo file
        fclose(fp);
    }
    
    return;
    
}

