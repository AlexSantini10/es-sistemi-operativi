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

void figlio(char fileName[], char car, int pipeFd[]){
    // Chiusura lato lettura
    close(pipeFd[0]);

    int fd = open(fileName, O_RDONLY);

    if (fd == -1){
        printf("Errore nell'apertura del file\n");
        exit(-2);
    }

    char buf[MAXN];

    char *div = "\n";

    // Lettura del file per intero
    read(fd, buf, MAXN);

    if (debug)
        printf("%s\n\n\n", buf);

    // Divisione per righe
    char* token = strtok(buf, div);

    while(token != NULL){
        if (debug)
            printf("%s\n", token);

        // Controllo se la riga inizia per car
        if (token[0] == car){
            // Invio della riga a P0
            char daInviare[MAXN];
            strcpy(daInviare, token);
            strcat(daInviare, "\n");

            if (write(pipeFd[1], daInviare, strlen(daInviare)*sizeof(char)) == -1){
                printf("Errore nella scrittura in pipe\n");
                exit(-4);
            }
        }
        
        // Prossimo token
        token = strtok(NULL, div);
    }

    close(pipeFd[1]);
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
        figlio(fileName, car, pipeFd);
    }   
    else {
        // Processo padre
        // Chiusura lato scrittura
        close(pipeFd[1]);

        int contatoreRighe = 0;

        char st[MAXN];
        // Ricezione dati da P1
        while(read(pipeFd[0], st, MAXN*sizeof(char))>0){
            if (debug)
                printf("%s\n", st);

            // Divisione per \n
            for (int i=0; i<strlen(st); i++){
                if (st[i] == '\n'){
                    contatoreRighe++;
                }
            }

            strcpy(st, "");
        }

        printf("Righe contate: %d\n", contatoreRighe);
    }

    return 0;
}