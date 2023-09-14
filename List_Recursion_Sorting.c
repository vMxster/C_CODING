#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

struct dato{
    int valore;
    struct dato* next;
};

//sempre la stessa funzione di inserimento in coda
struct dato* init(struct dato* head, int val){

    struct dato* body = head;

    if(body==NULL){

        head = (struct dato*) malloc(sizeof(struct dato));
        if(head == NULL) exit(1);

        body = head;

    }else{

        while(body->next!=NULL)
            body=body->next;

        body->next = (struct dato*) malloc(sizeof(struct dato));
        if(body == NULL) exit(1);
        body = body->next;

    }

    body->valore = val;
    body->next = NULL;

    return head;
}

bool canContinue(struct dato* head){
    if(head == NULL) return false; //se testa è NULL ritorno false
    struct dato* body = head; // creo l'appoggio
    while(body->next!=NULL){
        //scorro la lista e appena trovo una coppia di valori non ordinati ritorno true
        if(body->valore>body->next->valore) return true;
        body = body->next;
    }
    //se esco dal ciclo allora non ho trovato niente e la lista è ordinata. ritorno false
    return false;
}

struct dato* ordina(struct dato* head){
    struct dato* appoggio = head; //appoggio per scorrere la lista
    int temp; //variabile temporanea che uso per lo scambio

    //finché trovo una coppia di celle adiacenti non ordinate continuo a far partire l'algoritmo di sorting
    while(canContinue(head)){
        while(appoggio->next != NULL) {
            //applico un bubble sort
            if (appoggio->valore > appoggio->next->valore) {
                temp = appoggio->valore;
                appoggio->valore = appoggio->next->valore;
                appoggio->next->valore = temp;
            }
            appoggio = appoggio->next;
        }
        appoggio = head;
    }
    return head;
}

//stampa ricorsiva
void print(struct dato* cella){
    if(cella == NULL) return;
    printf("valore: %d\n", cella->valore);
    print(cella->next);
}

int main() {
    struct dato* head = NULL; //testa della lista
    int val; //variabile temporanea per l'input

    srand(time(NULL)); //seme per il random

    //creo 10 elementi con valore random
    for(int i=0; i<10; i++){
        val = rand()%100+1;
        head = init(head, val);
    }

    print(head); // prima stampa: ordine casuale

    printf("\n\n\n");

    head = ordina(head); //riordino la lista

    print(head); //seconda stampa: lista ordinata

    struct dato* dummy = head; //appoggio

    //ora libero tutta la memoria
    while(head != NULL){
        head = head->next;
        free(dummy);
        dummy = head;
    }

    printf("\n");

    system("pause");
    return 0;
}
