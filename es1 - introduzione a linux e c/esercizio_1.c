#include <stdio.h>
#include <string.h>
#include <ctype.h>

void stampaCategoria(int argc, char *argv[], char MP, char IN){
    int stampati = 0;
    
    for (int i=1; i<argc; i++){
        if (argv[i][0] == MP && argv[i][1] == IN){
            stampati = 1;
            for (int j=2; j<6; j++){
                printf("%c", argv[i][j]);
            }
            printf("\n");
        }
    }
    
    if (!stampati)
        printf("Non sono presenti voli per questa categoria\n");
    printf("\n");
}

int main (int argc, char *argv[]){

    if (argc>1){
        int tuttoConforme = 1;
        for (int i=1; i<argc; i++){
            if (strlen(argv[i])!=6 
                || (argv[i][0]!='M' && argv[i][0]!='P')
                || (argv[i][1]!='I' && argv[i][1]!='N')
                || !isdigit(argv[i][2]) || !isdigit(argv[i][3]) || !isdigit(argv[i][4]) || !isdigit(argv[i][5])
            ){
                tuttoConforme = 0;
                printf("Il programma presenta stringhe non conformi\n");
            }
        }
        
        if (tuttoConforme) {
            printf("Tutte le stringhe sono conformi\n\n");
            
            printf("Voli merci internazionali\n");
            stampaCategoria(argc, argv, 'M', 'I');
            
            printf("Voli merci nazionali\n");
            stampaCategoria(argc, argv, 'M', 'N');
            
            printf("Voli passeggeri internazionali\n");
            stampaCategoria(argc, argv, 'P', 'I');
            
            printf("Voli passeggeri nazionali\n");
            stampaCategoria(argc, argv, 'P', 'N');
        }
        
    }
    else {
        printf("Nessun volo passato come parametro\n");
    }
    
    return 0;
}
