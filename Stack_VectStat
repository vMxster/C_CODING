#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Versione programma pila con metodi usando un vettore statico
 */

#define MAX 10

int testa;

int* Push(int Pila[MAX], int n) {
    if(testa==MAX) //se ho raggiunto il limite dell'array non faccio niente
        printf("\nPila piena" );
    else //altrimenti inserisco il valore e incremento il contatore
        Pila[testa++]=n;

    return Pila;
}

void Pop(int Pila[MAX]) {
    if(testa==0) //se il contatore è 0 allora la pila è vuota
        printf("\n - Pila vuota" );
    else //altrimenti diminuisco il contatore
        testa--;
}

void Print(int Pila[MAX]) {
    if(testa==0)
        printf("\nPila vuota\n");
    else
        for(int i=testa-1;i>=0;i--) //parto dalla fine dell'array e torno indietro (FILO)
            printf("Valore %d = %d\n",i, Pila[i]);
}

int main(){
    int scelta; //variabile dello switch
    bool run = true; //bool per il ciclo while
    int Pila[MAX]; //array statico
    int val = 0; //valore di input

    while(run){
        system("cls");
        Print(Pila);
        printf("\n[1]Push\n[2]Pop\n[3]Clear\n[4]Esci\n\n->");
        rewind(stdin);
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                //Push
                printf("\nInserisci un valore ->");
                rewind(stdin);
                scanf("%d", &val);
                Push(Pila, val);
                break;
            case 2:
                //Pop
                Pop(Pila);
                break;
            case 3:
                //Clear
                testa=0;
                break;
            case 4:
                //Esci
                run = false;
                break;
        }
    }
    system("pause");
    return 0;
}
