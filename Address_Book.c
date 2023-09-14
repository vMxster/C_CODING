#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define PULISCI system("cls")
#define MAX_CONTATTI 1000
#define MAX_TESTO_RIGA 50

//funzione che mi aggiunge un nuovo contatto
int aggiungiContatto(char* nomi[MAX_CONTATTI], char* numeri[MAX_CONTATTI], char* nome, char* numero, int cont){
    //alloco la memoria di lunghezza della stringa + 1 (strlen non conta il carattere terminatore) * grandezza di char
    nomi[cont]=malloc((strlen(nome)+1) * sizeof(char));
    //e ci copio dentro il mio nome
    strcpy(nomi[cont], nome);

    //faccio la stessa cosa con il numero
    numeri[cont]=malloc((strlen(numero)+1) * sizeof(char));
    strcpy(numeri[cont], numero);

    //incremento la posizione alla cella successiva e la ritorno
    return ++cont;
}

//funzione che mi cerca esattamente cosa scrivo in input
void ricerca(char* nomi[MAX_CONTATTI], char* numeri[MAX_CONTATTI], char* temp){
    bool trovato=false; //flag che sbandiero appena trovo almeno un riscontro
    printf("Hai cercato %s:\n\n", temp);

    //ciclo prima l'array frastagliato dei nomi
    for(int i=0; i<MAX_CONTATTI; i++)
        if(nomi[i]!=NULL && !strcmp(nomi[i], temp)){
            //se trovo un riscontro allora lo stampo
            printf("Nome: %s\nNumero: %s\n\n", nomi[i], numeri[i]);
            trovato=true; //e lo sbandiero
        }
    /*
     * se ho trovato un riscontro mentre scorrevo i nomi allora di sicuro l'input non sarà compatibile con nessun numero
     * telefonico quindi salvo risorse e non lo faccio cercare anche nell'array frastagliato di numeri telefonici.
     * viceversa se non ho trovato un riscontro nei nomi allora ciò che ho cercato è un numero telefonico o non esiste.
     */

    if(!trovato){
        for(int i=0; i<MAX_CONTATTI; i++)
            if(numeri[i]!=NULL && !strcmp(numeri[i], temp)){
                printf("Nome: %s\nNumero: %s\n\n", nomi[i], numeri[i]);
                trovato=true;
            }
    }

    //se anche nei numeri non ho avuto riscontri allora ciò che ho cercato non esiste e lo comunico
    if(!trovato) printf("Nessun risultato.\n\n");
}

//funzione di ricerca migliore perché funziona anche con input parziale
void betterRicerca(char* nomi[MAX_CONTATTI], char* numeri[MAX_CONTATTI], char* temp){

    //A livello di algoritmo è identica a ricerca(), ho solo cambiato strcmp con strstr.
    bool trovato=false;
    printf("Hai cercato %s:\n\n", temp);
    for(int i=0; i<MAX_CONTATTI; i++)
        if(nomi[i]!=NULL && strstr(nomi[i], temp)){
            printf("Nome: %s\nNumero: %s\n\n", nomi[i], numeri[i]);
            trovato=true;
        }


    if(!trovato){
        for(int i=0; i<MAX_CONTATTI; i++)
            if(numeri[i]!=NULL && strstr(numeri[i], temp)){
                printf("Nome: %s\nNumero: %s\n\n", nomi[i], numeri[i]);
                trovato=true;
            }
    }
    if(!trovato) printf("Nessun risultato.\n\n");
}

//funzione che mi stampa tutta la rubrica
void stampaTutto(char* nomi[MAX_CONTATTI], char* numeri[MAX_CONTATTI]){
    //ciclo entrambi gli array frastagliati
    for(int i=0; i<MAX_CONTATTI; i++)
        //se il puntatore a char* in i non è null
        if(nomi[i]!=NULL && numeri[i]!=NULL){
            //stampo
            printf("[%d]:\nNome: %s\nNumero: %s\n\n", i, nomi[i], numeri[i]);
        }
}

void main() {

    int scelta = 0; // variabile che uso per lo switch principale
    char temp[MAX_TESTO_RIGA]; // stringa temporanea per la ricerca
    char *nomi[MAX_CONTATTI]; //array frastagliato dei nomi
    char *numeri[MAX_CONTATTI]; //array frastagliato dei numeri

    //li inizializzo a null tutti
    for(int i=0; i<MAX_CONTATTI; i++){
        nomi[i]=NULL;
        numeri[i]=NULL;
    }

    char tempNome[MAX_TESTO_RIGA]; // stringa temporanea nome per l'inserimento
    char tempNumero[MAX_TESTO_RIGA]; // stringa temporanea numero per l'inserimento
    int cont_rubrica=0; // posizione della rubrica. Mi serve per mettere nuovi contatti e lo aggiorno ogni volta che lo faccio

    while (true) { //ciclo all'infinito
        PULISCI;
        printf("[1]Nuovo Contatto [2]Ricerca [3]Ricerca Avanzata [4]Mostra Contatti [0]Esci\n->");
        rewind(stdin);
        scanf("%d", &scelta); //prendo in input la scelta dell'utente


        switch (scelta) {

            case 1: //aggiungi nuovo contatto
                printf("\nInserisci il nome:\n->");
                rewind(stdin);
                gets(tempNome);

                printf("\nInserisci il numero di %s:\n->", tempNome);
                rewind(stdin);
                gets(tempNumero);

                //controllo se sono pieno.
                if(cont_rubrica>=MAX_CONTATTI){
                    printf("\nRubrica piena!\n\n");
                }else{
                    //altrimenti aggiungo
                    cont_rubrica = aggiungiContatto(nomi, numeri, tempNome, tempNumero, cont_rubrica);
                }
                break;

            case 2: //ricerca esatta
                printf("Cerca contatto:\n->");
                rewind(stdin);
                gets(temp);

                PULISCI;

                ricerca(nomi, numeri, temp);

                system("pause");
                break;

            case 3: //ricerca "avanzata"
                printf("Cerca contatto:\n->");
                rewind(stdin);
                gets(temp);

                PULISCI;

                betterRicerca(nomi, numeri, temp);

                system("pause");
                break;

            case 4: //stampa tutta la rubrica
                PULISCI;
                stampaTutto(nomi, numeri);
                system("pause");
                break;

            case 0:
                exit(1); //chiudi il programma
        }
    }
}
