#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

# define MAXN 1000

void figlio(int ar[], int i, int n){
    int numeroDiConsegne = 0;
            
    for (int j=0; j<n; j++){
        if (ar[j] == i) numeroDiConsegne++;
    }
    
    // Debug
    //printf("INTERNO: Processo: %d -> Consegne: %d\n", i, numeroDiConsegne);
    
    exit(numeroDiConsegne);
}

int main (int argc, char *argv[]){
    srand(time(NULL));

    if (argc != 3){
        printf("Numero argomenti errato");
        return -1;
    }
        

    int n = atoi(argv[1]);
    int f = atoi(argv[2]);
    
    if (n < 0 || f < 0){
        printf("Numeri non validi");
        return -1;
    }
    
    int ar[n];
    for (int i=0; i<n; i++){
        int x = rand()%f;
        ar[i] = x;
    }
    
    printf("Array generato: \n");
    for (int i=0; i<n; i++){
        printf("%d\n", ar[i]);
    }
    
    int pid[MAXN];
    for (int i=0; i<n; i++){
        pid[i] = fork();
        
        if (pid[i] == 0){
            // Processo figlio
            figlio(ar, i, n);
        }
        else {
            // Processo padre
            int status;
            int pid;
            
            pid = wait(&status);
            
            // Divisione per uscita volontaria dal processo (shift a destra di 8 bit)
            status /= 256;
            
            printf("Processo: %d -> Consegne: %d\n", i, status);
        }
        
    }
    
    
    return 0;
}
