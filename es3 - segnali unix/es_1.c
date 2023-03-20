#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define MAXN 1000

int pid[MAXN];
char *com;

int debug = 1;

void handler_P1_SIGUSR1(int signum){
    // Handler del figlio P1 per il segnale SIGUSR1
    if (debug)
        printf("P1: Eseguo handler P1\n");
    execlp(com, ".", (char *) 0);
}

void figlioP1(){
    // Processo figlio P1
    signal(SIGUSR1, handler_P1_SIGUSR1);
    
    for (int i=0; 1; i++){
        printf("P1: %f\n", sqrt(i));
        sleep(1);
    }
}

void figlioP2(int pidP1){
    // Processo figlio P2
    sleep(3);
    
    if (getpid()%2==0){
        // Pari
        if (debug)
            printf("PARI\n");
        kill(getppid(), SIGUSR1);
    }
    else{
        // Dispari
        if (debug)
            printf("DISPARI\n");
        kill(pidP1, SIGUSR1);
    }
    
    exit(0);
}

void handler_P0_SIGUSR1(int signum){
    // Handler del processo padre P0 per il segnale SIGUSR1
    printf("P0: Finito!\n");
    
    kill(pid[0], SIGKILL);
    kill(pid[1], SIGKILL);
    printf("Figli terminati\n");
    exit(0);
}

void handler_P0_alarm(int signum){
    // Handler del processo padre P0 per il segnale SIGALRM
    printf("Timeout scaduto!\n");
    kill(pid[0], SIGUSR1);
    kill(pid[1], SIGUSR1);
    printf("Figli terminati\n");
    
    exit(0);
}

int main (int argc, char *argv[]){
    if (argc != 3){
        printf("Numero di argomenti errato\n");
        return -1;
    }
    
    com = argv[1];
    
    // Setup handler segnali
    signal(SIGUSR1, handler_P0_SIGUSR1);
    signal(SIGALRM, handler_P0_alarm);
    
    int t = atoi(argv[2]);
    
    // Fork processo P1
    pid[0] = fork();
    if (pid[0] == 0) figlioP1();
    else{
        // Fork processo P2
        pid[1] = fork();
        if (pid[1] == 0) figlioP2(pid[0]);
        else{
            // Setup timer
            alarm(t);
            // Processo padre
            for(int i=0; 1; i++){
                printf("P0: %f\n", pow(2, i));
                sleep(1);
            }
        }
    }
    
    return 0;
}
