#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

/*
 * Implementazione della PILA utilizzando un vettore dinamico
 */

int arguments = 0; //variabile globale che conta il numero di argomenti del vettore

int* push(int* vettore, int n){
    //se il vettore è NULL allora lo alloco per la prima volta con malloc
    if(vettore == NULL){
        vettore = (int*) malloc(sizeof(int));
        vettore[0] = n;
        arguments++;
    }else{
        //altrimenti uso realloc con grandezza precedente+1
        arguments++;
        vettore = realloc(vettore, arguments*sizeof(int));
        vettore[arguments-1] = n;
    }
    //ritorno il puntatore
    return vettore;
}

int* pop(int* vettore){
    //se il vettore è NULL oppure ha grandezza uno allora ritorno direttamente NULL
    if(vettore == NULL || arguments==1){
        arguments = 0;
        return NULL;
    }

    //altrimenti realloco a grandezza precedente-1
    arguments--;
    vettore = realloc(vettore, arguments*sizeof(int));

    return vettore;
}

void print(int* vettore){
    //funzione stampa, se è NULL stampa (null)
    if(vettore != NULL)
        for(int i=0; i<arguments; i++)
            printf("Valore %d = %d\n", i, vettore[i]);
    else printf("(null)\n");
}

int main() {

    int* vettore = NULL; //puntatore int per il vettore dinamico
    int scelta; //variabile per lo switch
    int n; //valore input utente
    bool run = true; //flag del loop while

    while(run){
        system("cls");
        print(vettore);

        //scelta azione e input
        printf("\n[1]Esci\n[2]Push\n[3]Pop\n[4]Clear\n\n->");
        rewind(stdin);
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                //esci
                run = false;
                break;
            case 2:
                //push
                printf("\n\nInserisci valore da inserire: ");
                rewind(stdin);
                scanf("%d", &n);
                vettore = push(vettore, n);
                break;
            case 3:
                //pop
                vettore = pop(vettore);
                break;
            case 4:
                //clear
                free(vettore);
                vettore = NULL;
                arguments = 0;
                break;
            default:
                printf("\n\nInput not valid\n\n");
        }
        printf("\n\n");
        system("pause");
    }
    return 0;
}
