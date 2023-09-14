#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

/*
 * --- TESTO DELL'ESERCIZIO ---
 * Realizzare un programma che gestisca la lista di tutti i libri letti in un anno. Per ognuno di essi, il programma
 * deve memorizzare una serie di informazioni, ad esempio il titolo, l’autore, l’anno di pubblicazione, la casa editrice,
 * la lunghezza, il genere, il codice identificativo, la valutazione. Il programma dovrà permettere di inserire un nuovo
 * libro, cancellarne uno, visualizzarli tutti, visualizzare solo quelli con una certa valutazione, …. Il programma deve
 * lavorare leggendo e scrivendo le informazioni da e su file. Consegnare un file .zip contente un progetto che comprenda
 * tutti i file necessari per testare il programma.
 */

/*
 * N.B
 * Se nel cancella libro l'utente inserisce una qualsiasi altra informazione che non è il codice il programma si sfasa,
 * confido nel buonsenso dell'utente. In caso si può risolvere andando a controllare il numero della riga in cui si trova
 * il codice e confrontarlo con n = n-7 finché n non è <7 e vedere se viene 1, poiché la riga dei codici è ogni 7 righe.
 */

#define MAX_RIGHE 500 //costante che uso come limite di lettura quando leggo tutte le righe del file.

//struttura libro
struct libro{
    char codice[20];
    char titolo[20];
    char autore[20];
    char annoPubblicazione[20];
    char casaEditrice[20];
    char lunghezza[10];
    char genere[50];
    char valutazione[10];
    struct libro* next;
};

//funzione che mi legge una riga dal file pointer e mi ritorna la stringa
char* leggiRiga(FILE* fp){
    char* riga; //definisco un puntatore char
    riga = (char*) malloc(40*sizeof(char)); //lo alloco
    char c = 'a'; //lo inizializzo a caso per evitare problemi
    int cont = 0; //contatore che uso per gestirmi la stringa quando la riempio

    //ciclo finché ciò che leggo è diverso da andata a capo
    while(c != '\n'){
        if(feof(fp) != 0) break; //se arrivo a fine file esco
        c = fgetc(fp); // leggo dal file

        //se cio che ho appena letto è diverso dai caratteri \n e EOF (\377)
        if(c != '\n' && c != EOF) {
            riga[cont] = c; //metto il char appena letto nella stringa alla posizione cont
            cont++; //e incremento il contatore
        }
    }
    riga[cont] = '\0'; //appena esco dal ciclo metto il carattere terminatore a fine stringa
    return riga; //e la ritorno
}

//funzione che mi inserisce un libro nella lista, l'inserimento su file lo faccio nel main
struct libro* insLib(struct libro* head, char* codice, char* titolo, char* autore, char* anno, char* editore, char* l, char* genere, char* val ) {
    struct libro* body = head; //creo l'appoggio

    //caso se la testa è null, quindi è il primo vagone che appendo
    if (body == NULL) {
        //allora alloco direttamente la testa
        head = (struct libro*) malloc(sizeof(struct libro));
        if (head == NULL)
            exit(1);
        body = head; //la metto uguale all'appoggio così dopo lo ritorno
    }

        //altrimenti se la lista non è vuota
    else {
        //la scorro
        while (body->next != NULL) {
            if(!strcmp(body->codice, codice)) return head;
            body = body->next;
        }
        //e in fondo ci appendo un nuovo figlio
        body->next = malloc(sizeof(struct libro));
        if (body->next == NULL)
            exit(1);
        body = body->next;
    }

    //in entrambi i casi ho una struttura da riempire, quindi lo riempio
    strcpy(body->codice, codice);
    strcpy(body->titolo, titolo);
    strcpy(body->autore, autore);
    strcpy(body->annoPubblicazione, anno);
    strcpy(body->casaEditrice, editore);
    strcpy(body->lunghezza, l);
    strcpy(body->genere, genere);
    strcpy(body->valutazione, val);

    body->next = NULL;

    //e ritorno la testa
    return head;
}

//funzione stampa
void stampaListaLibri(struct libro* head){
    //se la lista è vuota lo stampo
    if(head == NULL) printf("Lista vuota!!\n\n");
    //altrmenti creo l'appoggio, la scorro e nel mentre stampo tutto
    struct libro* body = head;
    while (body != NULL) {
        printf("Codice: %s\nTitolo: %s\nAutore: %s\nAnno di pubblicazione: %s\nEditore: %s\nLunghezza: %s\nGenere: %s\nValutazione: %s\n\n",
               body->codice, body->titolo, body->autore, body->annoPubblicazione, body->casaEditrice, body->lunghezza, body->genere, body->valutazione);

        body = body->next;
    }
}

//funzione che mi filtra i libri per la valutazione presa in input dall'utente
int cercaPerValutazione(struct libro* head, char* val){
    struct libro* body = head; //creo l'appoggio
    if(body == NULL) return -1; //se la lista è vuota ritorno -1
    //altrimenti scorro la lista e per ogni figlio
    while(body!=NULL){
        /*
         * controllo se la prima cifra della sua valutazione corrisponde alla prima cifra
         * della valutazione presa in input dall'utente.
         * esempio:
         * con input (7; 7.2; 7.42; ecc) posso vedere:
         * - libro 1: valutazione 7
         * - libro 2: valutazione 7.1
         * - libro 3: valutazione 7.93
         *
         * se stai leggendo qui allora buona fortuna per l'esame :D
         */
        if(body->valutazione[0]==val[0]){
            //poi stampo i risultati che matchano la mia richiesta
            printf("Codice: %s\nTitolo: %s\nAutore: %s\nAnno di pubblicazione: %s\nEditore: %s\nLunghezza: %s\nGenere: %s\nValutazione: %s\n\n",
                   body->codice, body->titolo, body->autore, body->annoPubblicazione, body->casaEditrice, body->lunghezza, body->genere, body->valutazione);
        }
        body=body->next;
    }
    return 0;
}

//funzione cancella libro
void cancellaLibro(struct libro* head, FILE* fp, char* code){
    fseek(fp, 0, SEEK_SET); //per sicurezza resetto il puntatore
    char* lines[MAX_RIGHE]; //vettore frastagliato di stringhe che mi serve per memorizzare il contenuto del file
    char* line; //stringa d'appoggio che uso per leggere riga per riga dal file
    int linesCount = 0; //contatore delle stringhe all'interno del vettore frastagliato lines

    //ciclo finché non arrivo alla fine del file
    while(!feof(fp)){
        line = leggiRiga(fp); // leggo la riga

        //controllo se corrisponde al codice del libro da cancellare
        if(!strcmp(line, code)){
            //se corrisponde allora salto 7 righe
            for(int i=0; i<7; i++)
                line = leggiRiga(fp);
            continue;
        }else{ //altrimenti
            //alloco una nuova stringa
            lines[linesCount] = (char*) malloc((strlen(line)+1)*sizeof(char));
            //e ci salvo la riga appena letta
            strcpy(lines[linesCount], line);
            //ed aumento il contatore
            linesCount++;
        }
    }
    //riapro il file in modalità write così che se esiste, cancella tutto il contenuto
    freopen("libri.txt", "w", fp);
    //e lo riempio con le righe che mi sono salvate che escludono le info sul libro che si è voluto cancellare
    for (int i = 0; i < linesCount; ++i) {
        //if else che mi serve per la corretta formattazione del file
        //l'ultimo elemento non deve andare a capo
        if(i==linesCount-1)
            fprintf(fp, "%s", lines[i]);
        else
            fprintf(fp, "%s\n", lines[i]);
    }
}

//funzione che mi aggiorna la lista dinamica di libri in runtime
struct libro* reloadList(FILE* booksPointer){

    //creo un nuovo puntatore
    struct libro* newHead = NULL;

    //riapro il file in mod. read e per sicurezza resetto il puntatore
    freopen("libri.txt", "r", booksPointer);
    fseek(booksPointer, 0, SEEK_SET);

    //variabili temporanee inserimento libro
    char* tempCodice;
    char* tempTitolo;
    char* tempAutore;
    char* tempAnno;
    char* tempEditore;
    char* tempLun;
    char* tempGenere;
    char* tempValutazione;

    while(!feof(booksPointer)){
        //leggo il codice
        tempCodice = leggiRiga(booksPointer);
        //leggo il titolo
        tempTitolo = leggiRiga(booksPointer);
        //leggo l'autore
        tempAutore = leggiRiga(booksPointer);
        //leggo l'anno di pubblicazione
        tempAnno = leggiRiga(booksPointer);
        //leggo l'editore
        tempEditore = leggiRiga(booksPointer);
        //leggo la lunghezza
        tempLun = leggiRiga(booksPointer);
        //leggo il genere
        tempGenere = leggiRiga(booksPointer);
        //leggo la valutazione
        tempValutazione = leggiRiga(booksPointer);

        //leggo tutte le info e appendo in lista
        newHead = insLib(newHead, tempCodice, tempTitolo, tempAutore, tempAnno, tempEditore, tempLun, tempGenere, tempValutazione);
    }
    //ritorno la nuova testa
    return newHead;
}

//funzione bool che mi controlla se il codice del libro che voglio inserire esiste già
bool esisteGia(struct libro* head, char* codice){
    if(head == NULL) return false; //se la lista è vuota ritorno false
    struct libro* body = head; //creo l'appoggio
    //scorro la lista
    while(body != NULL){
        //se ho un riscontro ritorno true
        if(!strcmp(body->codice, codice)) return true;
        body = body->next;
    }
    //se non ho ancora ritornato true, ritorno false perché non ho avuto nessun riscontro
    return false;
}

int main() {

    //testa della lista
    struct libro* head = NULL;

    //puntatore al file coi libri
    FILE* booksPointer = fopen("libri.txt", "r+");
    if(booksPointer == NULL) exit(0);

    bool run = true;
    int scelta = 0;
    int result = 0;

    //variabili temporanee inserimento libro
    char tempCodice[40];
    char tempTitolo[40];
    char tempAutore[40];
    char tempAnno[40];
    char tempEditore[40];
    char tempLun[40];
    char tempGenere[40];
    char tempValutazione[40];

    //carico tutti i libri presenti sul file prima di interfacciarmi con l'utente
    int len;
    fseek(booksPointer, 0, SEEK_END);
    len = ftell(booksPointer);
    fseek(booksPointer, 0, SEEK_SET);
    if(len>0)
        head = reloadList(booksPointer);


    while(run){
        system("cls");

        //chiedo l'input all'utente
        printf("[1]Inserisci libro\n[2]Cancella libro\n[3]Lista libri\n[4]Cerca per valutazione\n[5]Esci\n\n->");
        rewind(stdin);
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                system("cls");
                printf("I N S E R I M E N T O   L I B R O\n\n");

                printf("Codice Libro: ");
                rewind(stdin);
                gets(tempCodice);

                //se il libro con il codice appena preso non esiste allora continua a chiedere l'input
                if(!esisteGia(head, tempCodice)){
                    printf("\nTitolo del Libro: ");
                    rewind(stdin);
                    gets(tempTitolo);

                    printf("\nAutore del Libro: ");
                    rewind(stdin);
                    gets(tempAutore);

                    printf("\nAnno di pubblicazione: ");
                    rewind(stdin);
                    gets(tempAnno);

                    printf("\nCasa editrice: ");
                    rewind(stdin);
                    gets(tempEditore);

                    printf("\nNumero pagine: ");
                    rewind(stdin);
                    gets(tempLun);

                    printf("\nGenere Libro: ");
                    rewind(stdin);
                    gets(tempGenere);

                    printf("\nValutazione Libro: ");
                    rewind(stdin);
                    gets(tempValutazione);

                    //una volta raccolto tutto inserisco il libro
                    head = insLib(head, tempCodice, tempTitolo, tempAutore, tempAnno, tempEditore, tempLun, tempGenere, tempValutazione);

                    //metto il puntatore del file alla fine
                    freopen("libri.txt", "r+", booksPointer);
                    fseek(booksPointer, 0, SEEK_END);
                    //leggo la lunghezza
                    len = ftell(booksPointer);

                    //else if che mi servono per la corretta formattazione nel file, bisogna stare attenti alle andate a capo
                    if(len>0)
                        fprintf(booksPointer, "\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", tempCodice, tempTitolo, tempAutore, tempAnno, tempEditore, tempLun, tempGenere, tempValutazione);
                    else
                        fprintf(booksPointer, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", tempCodice, tempTitolo, tempAutore, tempAnno, tempEditore, tempLun, tempGenere, tempValutazione);

                }else printf("\n\nLibro gia' inserito\n\n"); //se un libro con quel codice esiste già allora lo dico
                break;

            case 2:
                system("cls");
                printf("C A N C E L L A   L I B R O");

                //chiedo il codice del libro da cancellare
                printf("\n\nCodice del Libro: ");
                rewind(stdin);
                gets(tempCodice);

                cancellaLibro(head, booksPointer, tempCodice);

                //metto il puntatore alla fine del file
                fseek(booksPointer, 0, SEEK_END);
                //leggo la lunghezza del file
                len = ftell(booksPointer);

                //se è maggiore di 0 allora c'è almeno un libro, per cui aggiorno la lista
                if(len>0)
                    head = reloadList(booksPointer);
                else //altrimenti se è 0 allora la lista è vuota e la metto a NULL
                    head = NULL;

                break;

            case 3:
                //case stampa lista libri
                system("cls");
                printf("L I S T A   L I B R I\n\n");
                stampaListaLibri(head);
                break;

            case 4:
                //case cerca per valutazione
                system("cls");
                printf("C E R C A   P E R   V A L U T A Z I O N E");
                printf("\n\nInserisci valutazione: ");
                rewind(stdin);
                gets(tempValutazione);
                result = cercaPerValutazione(head, tempValutazione);
                if(result == -1) printf("\nHEAD NULL ERROR\n\n");
                break;

            case 5:
                //case esci, metto run a false ed esco dal ciclo while
                run = false;
                break;
            default:
                printf("\n\nInput errato\n\n");
        }
        system("pause");
    }

    //chiudo il file e termino il programma
    fclose(booksPointer);

    return 0;
}
