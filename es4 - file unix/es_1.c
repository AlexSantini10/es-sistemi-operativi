#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

#define MAXN 1000

int debug = 1;

typedef struct{
    int tipo;
    int quant;
} operazione;

int main(int argc, char *argv[]){
    int fd;

    // Variabili nomi dei file
    char inputFileName[MAXN];
    char vendutiFileName[MAXN];
    char prodottiFileName[MAXN];

    // Controllo numero di argomenti
    if (argc != 4){
        printf("Numero di argomenti errato\n");
        exit(-1);
    }
    else {
        // Copia dei nomi dei file
        strcpy(inputFileName, argv[1]);
        strcpy(prodottiFileName, argv[2]);
        strcpy(vendutiFileName, argv[3]);

        // Check apertura file
        if ((fd=open(inputFileName, O_RDONLY))<0)
		{	perror("errore apertura F");
			exit(-2);
		}
    }

    int fdVenduti=creat(vendutiFileName, 0777);         // fd del file venduti
    int fdProdotti=creat(prodottiFileName, 0777);       // fd del file prodotti
    char temp[MAXN];                                    // stringa temporanea dei valori letti                              

    int valoreLettoAlMomento = 0;                       // contiene 0 se sto leggendo il primo intero della riga, 1 per il secondo e 2 per il tipo dell'operazione

    operazione tempOperazione;                          // variabile temporanea per l'operazione
    char tempTipo;                                      // variabile contenente il tipo dell'operazione

    char* div = ",\n";                                  // variabile contenente i caratteri per i quali dividere le stringhe

    read(fd, temp, MAXN);

    if (debug)
        printf("%s\n\n",temp);

    // token contiene la prima stringa
    char* token = strtok(temp, div); 

    // Ciclo di lettura
    while (token != NULL){
        printf("%s\n", token);

        if (valoreLettoAlMomento==0){
            // Primo intero, tipo di pezzo
            tempOperazione.tipo = atoi(token);

            valoreLettoAlMomento++;
        }
        else if (valoreLettoAlMomento==1){
            // Secondo intero, numero di pezzi
            tempOperazione.quant = atoi(token);

            valoreLettoAlMomento++;
        }
        else if (valoreLettoAlMomento==2){
            // Tipo di operazione, scrittura
            tempTipo = token[0];

            valoreLettoAlMomento=0;

            if (tempTipo == 'P'){
                if (debug)
                    printf("Scrivo i valori %d %d %c in prodotti\n", tempOperazione.tipo, tempOperazione.quant, tempTipo);

                write(fdProdotti, &tempOperazione, sizeof(operazione));
            }
            else {
                if (debug)
                    printf("Scrivo i valori %d %d %c in vendite\n", tempOperazione.tipo, tempOperazione.quant, tempTipo);

                write(fdVenduti, &tempOperazione, sizeof(operazione));
            }
        }

        token = strtok(NULL, div);
    }
    
    // Chiusura file
    close(fd);
    close(fdVenduti);
    close(fdProdotti);

    return 0;
}