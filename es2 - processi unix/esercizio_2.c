#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

# define MAXN 1000

void figlio(char dir_1[], char dir_2[], char file[]){
    int pid = getpid();
    // Debug
    //printf("\n%d", pid);
    
    char absFile1[MAXN];
    strcpy(absFile1, strcat(dir_1, file));
    
    char absFile2[MAXN];
    strcpy(absFile2, strcat(dir_2, file));
    
    // Debug
    //printf("\n%s %s\n", absFile1, absFile2);
    
    if (pid%2 == 0){
        // Copia
        execl("/bin/cp", "cp", absFile1, absFile2, (char *) 0);
        printf("%s copiato\n\n", file);
    }
    else {
        // Eliminazione
        execl("/bin/rm", "rm", absFile1, (char *) 0);
        printf("%s eliminato\n\n", file);
    }
    
    exit(0); 
}

int main (int argc, char *argv[]){
    srand(time(NULL));
    
    // Check inserimento nomi cartelle
    if (argc < 3){
        printf("Troppi argomenti mancanti");
        return -1;
    }
    
    // Variaibili per i nomi delle cartelle
    char dir_1[MAXN];
    char dir_2[MAXN];
    
    strcpy(dir_1, argv[1]);
    strcpy(dir_2, argv[2]);
    
    // Debug
    //printf("%s \n%s", dir_1, dir_2);
    
    // Array di stringhe per i nomi dei file
    char files[MAXN][MAXN];
    
    for (int i=3; i<argc; i++){
        strcpy(files[i-3], argv[i]);
        
        // Debug
        //printf("\n%s", files[i-3]);
    }
    
    // Creazione processi
    int processiTerminatiBene = 1;
    int pid[MAXN];
    for (int i=0; i<argc-3; i++) {
        pid[i] = fork();
        
        if (pid[i] == 0){
            // Processo figlio
            figlio(dir_1, dir_2, files[i]);
        }
        else {
            // Processo padre
            int status;
            int pid;
            
            pid = wait(&status);
            
            if (!WIFEXITED(status)){
                processiTerminatiBene = 0;
                
                printf("\nErrore nel processo con pid: %d\n", pid);
            }
                
        }
    }
    
    if (processiTerminatiBene){
        execl("/bin/ls", "ls", dir_2, (char *) 0);
    }

    
    
    return 0;
}
