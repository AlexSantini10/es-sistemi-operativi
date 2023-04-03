#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

#define MAXN 1000

int debug = 0;

void figlio(char fileName[], int fd_out, char car, int pipeFd[]){
    // Redirezione
    close(1);
    dup(fd_out);
    close(fd_out);

    char pipo[3] = {'^', car};
    execl("/bin/grep", "grep", pipo, fileName, (char*)0);
    perror("Execl fallita");
    exit(-1);
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Numero di argomenti errato\n");
        exit(-1);
    }

    int pipeFd[2];
    if (pipe(pipeFd) < 0){
        printf("Errore nell'apertura della pipe\n");
        exit(-3);
    }

    char fileName[MAXN], car;

    strcpy(fileName, argv[1]);
    car = argv[2][0];

    int pid = fork();

    if (pid == 0){
        // Processo figlio
        figlio(fileName, pipeFd[1], car, pipeFd);
    }   
    else {
        // Processo padre
        // Chiusura lato scrittura
        close(pipeFd[1]);

        // Redirezione
        close(0);
        dup(pipeFd[0]);
        close(pipeFd[0]);

        execl("/bin/wc", "wc", "-l", (char*)0);
    }

    return 0;
}