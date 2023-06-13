#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

/*
 * Versione implementazione PILA con metodi utilizzando strutture collegate
 */

//la struttura
struct dato{
    int valore;
    struct dato* prec;
};

//funzione push
struct dato* push(struct dato* head, int val){

    //creo un appoggio
    struct dato* appoggio;

    //se la testa è NULL allora:
    if(head == NULL){
        //la alloco
        head = (struct dato*) malloc(sizeof(struct dato));
        if(head == NULL) exit(1);
        //la riempio
        head->valore = val;
        head->prec = NULL;
        //e la ritorno
        return head;
    }else {
        //altrimenti alloco l'appoggio e appiccico in coda la pila
        appoggio = (struct dato *) malloc(sizeof(struct dato));
        appoggio->valore = val;
        appoggio->prec = head;
        //poi lo ritorno
        return appoggio;
    }
}

//funzione pop
struct dato* pop(struct dato* head){
    //se testa è NULL allora ritorno NULL
    if(head == NULL) return NULL;
    //altrimenti creo un appoggio e mi salvo il primo elemento che andrà tagliato
    struct dato* appoggio = head;
    //la nuova testa diventa l'elemento precedente
    head = head->prec;
    //e libero appoggio
    free(appoggio);
    //ritorno la nuova testa
    return head;
}

//funzione stampa
void print(struct dato* head){
    if(head == NULL) printf("(null)\n");

    while(head!=NULL){
        printf("valore: %d\n", head->valore);
        head = head->prec;
    }
}

//funzione clear
struct dato* clear(struct dato* head){
    free(head);
    return NULL;
}

int main() {

    struct dato* testaDati = NULL; //testa della pila

    int n; //valore input utente
    int scelta=0; //scelta per lo switch
    bool run = true; //flag per il loop

    while(run){
        system("cls");
        //chiedo l'input
        print(testaDati);
        printf("\n\n[1]Esci\n[2]Push\n[3]Pop\n[4]Clear\n\n->");
        rewind(stdin);
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                //esci
                run = false;
                break;
            case 2:
                //push
                printf("\n\nInserisci il valore da inserire in cima:\n->");
                scanf("%d", &n);
                testaDati = push(testaDati, n);
                break;
            case 3:
                //pop
                testaDati = pop(testaDati);
                break;
            case 4:
                //clear
                testaDati = clear(testaDati);
                break;
            default:
                printf("\n\nInput non valido\n\n");
        }
        printf("\n\n");
        system("pause");
    }
    return 0;
}
