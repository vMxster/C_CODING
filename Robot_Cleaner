#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

/*
 * --- TESTO DELL'ESERCIZIO ---
 * Si scriva un programma C, adeguatamente commentato, che gestisca le funzionalità di Rob8, l'ultima versione di robot
 * domestico a breve disponibile sul mercato.

 * Il programma utilizza un vettore di strutture, ognuna delle quali memorizza le informazioni delle stanze della casa
 * (nome, larghezza, lunghezza, area, numero di ostacoli presenti, priorità di pulizia). Si definiscano le seguenti funzioni:
 *
 * robConnect() è la funzione per simulare la connessione a Rob8. Si visualizzi a schermo una finta barra di caricamento
 * con la percentuale 0-100% e si attenda il caricamento completo per le successive istruzioni.
 *
 * aggiungiStanza() aggiunge una nuova stanza, stampando un messaggio di errore se la stanza è già presente (individuata dal nome)
 * o se il vettore è pieno; la funzione deve inoltre assegnare alla stanza una priorità di pulizia scegliendo fra quelle disponibili.
 *
 * mostraInfoStanza(), dato il nome della stanza, stampare le informazioni della stessa oppure un messaggio di errore se
 * la stanza non è presente nel vettore.
 *
 * modificaStanza(), dato il nome della stanza, permettere la modifica delle sue informazioni
 *
 * calcolaPercorso() definisce la sequenza di stanze percorse dal robot, in base alla loro priorità.
 *
 * robDisconnect() visualizzerà l'avvenuta disconnessione dal robot.
 *
 * Le stanze nella memoria di Rob8 sono rappresentate tramite un vettore di NUM_STANZE elementi.
 *
 * Il programma deve gestire l'allocazione dinamica delle strutture usando la funzione malloc()
 */

//grandezza dell'array
#define NUM_STANZE 20

//struttura che uso per definire una stanza
struct stanza{
    char nomeStanza[30];
    int larghezzaStanza;
    int lunghezzaStanza;
    int areaStanza;
    int n_OstacoliStanza;
    int prioStanza;
};

//funzione colori
void cambiaColore(unsigned short int colore) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,colore);
}

//funzione che mi permette di spostare il cursore nel terminale usando una coppia di coordinate x e y
void spostaCursore(short int x, short int y) {
    COORD posizione = {x, y};
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, posizione);
}

//funzione per nascondere il cursore, per ora non c'è input richiesto quindi è più carino nasconderlo
void nascondiCursore(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO i;
    i.dwSize = 100;
    i.bVisible = FALSE;
    SetConsoleCursorInfo(h, &i);
}

//funzione grafica che mi fa il finto caricamento all'inizio
void robConnect(){
    //tempo da far aspettare in runtime
    int sleepTime=0;

    system("cls");

    //cambio il colore di tutto a 6 (giallo)
    cambiaColore(6);

    /*
     * uso spostaCursore per spostarmi in giro per il terminale per stampare caratteri così da avere un aspetto grafico
     * semi-decente.
    */

    spostaCursore(35, 5);
    printf("C O N N E S S I O N E    I N   C O R S O . . .\n\n");

    spostaCursore(78, 7);
    printf("] 100");

    spostaCursore(34, 7);
    printf("0 [");

    //41 rappresenta gli spazi tra la stampa   "0 ["   e   "] 100"
    for(int i=0; i<41; i++){
        //per ogni spazio aspetto un tempo tra 0 e mezzo secondo (500 ms)
        sleepTime = rand()%500;
        //e stampo un carattere "|"
        printf("|");
        _sleep(sleepTime);
    }

    //finito il "finto caricamento" stampo per un secondo e mezzo "connessione effettuata" e poi vado avanti
    spostaCursore(45, 10);
    printf("Connessione effettuata!\n\n");

    _sleep(1500);
}

//funzione che aggiunge una stanza all'array se possibile
int aggiungiStanza(struct stanza* listaStanze[NUM_STANZE], char* nome, int lun, int lar, int n_Ost, int prio){
    int cont=0; //mi conta il numero di puntatori a struct non nulli
    int pos=0; //mi serve per trovare il primo puntatore a struct non nullo così da metterci la nuova stanza

    //ciclo NUM_STANZE volte
    for(int i=0; i<NUM_STANZE; i++)
        //se il puntatore a struct in i è diverso da NULL
        if(listaStanze[i] != NULL){
            //incremento cont
            cont++;
            //e controllo se il nome della nuova stanza esiste già, se si esco con il codice -2
            if(!strcmp(listaStanze[i]->nomeStanza, nome)) return -2;
        }

    //se ho contato NUM_STANZE puntatori non nulli allora significa che ho finito i posto ed esco col codice -1
    if(cont==NUM_STANZE) return -1;

    //se non sono ancora uscito allora è tutto ok quindi procedo col trovare il primo posto disponibile
    while(listaStanze[pos] != NULL) pos++;

    //una volta trovato lo alloco con malloc e lo riempio
    listaStanze[pos] = (struct stanza*) malloc(sizeof(struct stanza));
    strcpy(listaStanze[pos]->nomeStanza, nome);
    listaStanze[pos]->lunghezzaStanza=lun;
    listaStanze[pos]->larghezzaStanza=lar;
    listaStanze[pos]->areaStanza=lun*lar;
    listaStanze[pos]->n_OstacoliStanza=n_Ost;
    listaStanze[pos]->prioStanza=prio;

    return pos;
}

//funzione che mi stampa tutte le informazioni di una stanza discriminata dal nome
void mostraInfoStanza(struct stanza* listaStanze[NUM_STANZE], char* nome){
    bool trovato = false; //bool che mi serve per vedere se trovo un riscontro

    for(int i=0; i<NUM_STANZE; i++)
        //se il puntatore a struct in i non è nullo e se il nome della stanza puntata è uguale o simile a quello preso in input
        if(listaStanze[i]!=NULL && strstr(listaStanze[i]->nomeStanza, nome)){
            //stampo le informazioni
            printf("Numero stanza: %d\n", i);
            printf("Nome stanza: %s\n", listaStanze[i]->nomeStanza);
            printf("Misure stanza: %d m x %d m   Area: %d m^2\n", listaStanze[i]->lunghezzaStanza, listaStanze[i]->larghezzaStanza, listaStanze[i]->areaStanza);
            printf("Numero ostacoli all'interno della stanza: %d\n", listaStanze[i]->n_OstacoliStanza);
            printf("Priorita' di pulizia: %d\n\n", listaStanze[i]->prioStanza);

            //e trovato diventa vero
            trovato=true;
        }

    //se non ho trovato niente allora lo dico
    if(!trovato) printf("Errore, stanza inesistente o nome stanza sbagliato!\n\n");
}

//funzione che mi calcola il percorso del robot discriminato dalla priorità di ogni stanza
void calcolaPercorso(struct stanza* listaStanze[NUM_STANZE]){
    printf("\n\n\n");
    //ciclo ogni livello di priorità (1 -> 4) estremi compresi
    for(int i=1; i<=4; i++){
        //ciclo l'array di puntatori a struct
        for(int j=0; j<NUM_STANZE; j++)
            //se il puntatore in j non è nullo e se la priorità della stanza puntata è uguale all'attuale i allora stampo il suo nome
            if(listaStanze[j] != NULL && listaStanze[j]->prioStanza == i) printf("Stanza: %s -> ", listaStanze[j]->nomeStanza);
        printf("\n");
    }
}

//funzione che modifica i dati di una stanza discriminata dal nome
void modificaStanza(struct stanza* listaStanze[NUM_STANZE], char* nome, int lun, int lar, int n_Ost, int prio){
    for(int i=0; i<NUM_STANZE; i++)
        //se il puntatore in i è diverso da NULL e se ho un riscontro tra il nome della stanza puntata e il nome preso in input
        if(listaStanze[i] != NULL && !strcmp(listaStanze[i]->nomeStanza, nome)){
            //allora ci copio i nuovi dati
            strcpy(listaStanze[i]->nomeStanza, nome);
            listaStanze[i]->lunghezzaStanza=lun;
            listaStanze[i]->larghezzaStanza=lar;
            listaStanze[i]->areaStanza=lun*lar;
            listaStanze[i]->n_OstacoliStanza=n_Ost;
            listaStanze[i]->prioStanza=prio;
        }
}

int main() {
    char scelta; // variabile per lo switch principale
    char tempNome[50]; // variabile temporanea per l'input del nome della stanza
    int tempLun, tempLar, tempN_Ost, tempPrio; // dati temporanei della nuova potenziale stanza
    int nStanza=0; // variabile che uso per manipolare il valore di ritorno di aggiungiStanza
    char azione; // variabile per lo switch interno al caso 3: modifica una stanza
    bool run = true; //booleano che mi fa girare il loop principale del programma
    struct stanza* listaStanze[NUM_STANZE]; // array di puntatori a struct di tipo stanza
    for(int i=0; i<NUM_STANZE; i++) listaStanze[i] = NULL; //all'inizio la lista è vuota quindi metto tutti i puntatori a NULL

    srand(time(NULL)); //seme per il random

    nascondiCursore(); //nascondo il cursore in modo da rendere migliore la grafica

    robConnect(); // falso caricamento

    while(run){ // inizio ciclo principale

        system("cls");
        printf("[1]Inserisci stanza [2]Cerca stanza [3]Modifica una stanza [4]Mostra percorso [5]Esci");
        rewind(stdin);
        scelta=getch();

        switch(scelta){
            case '1':
                //caso 1: aggiungi stanza

                system("cls");

                //prendo in input tutti i dati necessari per creare una nuova stanza
                printf("Inserisci il nome della stanza: ");
                rewind(stdin);
                gets(tempNome);

                printf("\n\nInserisci la lunghezza di %s:", tempNome);
                rewind(stdin);
                scanf("%d", &tempLun);

                printf("\n\nInserisci la larghezza di %s:", tempNome);
                rewind(stdin);
                scanf("%d", &tempLar);

                printf("\n\nInserisci il numero di ostacoli di %s:", tempNome);
                rewind(stdin);
                scanf("%d", &tempN_Ost);

                printf("\n\nInserisci la priorita' di %s: \n\nLegenda:\n[1]Molto Importante\n[2]Importante\n[3]Quasi Importante\n[4]Poco Importante\n\n->", tempNome);
                rewind(stdin);
                scanf("%d", &tempPrio);

                //e poi provo a crearla
                nStanza = aggiungiStanza(listaStanze, tempNome, tempLun, tempLar, tempN_Ost, tempPrio);

                //in base al valore di ritorno di aggiungiStanza, comunico l'esito dell'operazione.
                if(nStanza == -1) {
                    printf("\n\n\nErrore! Posto esaurito!\n\n");
                }else if(nStanza == -2){
                    printf("\n\n\nErrore! Stanza gia' inserita!\n\n");
                }else{
                    printf("\n\n\nStanza inserita con successo al posto %d", nStanza);
                }
                break;

            case '2':
                //caso 2: mostra informazioni stanza

                system("cls");

                printf("Inserisci il nome della stanza: ");
                rewind(stdin);
                gets(tempNome);
                printf("\n\n");

                mostraInfoStanza(listaStanze, tempNome);
                break;

            case '3':
                //caso 3: modifica stanza

                system("cls");

                printf("Inserisci il nome della stanza: ");
                rewind(stdin);
                gets(tempNome);

                //variabile temporanea che uso per vedere se la stanza che sto cercando esiste
                int temp=-1;

                for(int i=0; i<NUM_STANZE; i++)
                    if(listaStanze[i] != NULL && !strcmp(listaStanze[i]->nomeStanza, tempNome)){
                        printf("\n");
                        mostraInfoStanza(listaStanze, tempNome);
                        temp=i; //appena ho un riscontro mi salvo la posizione in caso voglia cancellare
                    }

                //se temp è rimasto -1 allora la stanza non esiste ed esco dal caso
                if(temp == -1){
                    printf("\n\nLa stanza non esiste o il nome e' sbagliato!");
                    break;
                }

                printf("\n\nCosa desideri fare?\n[1]Modifica dati stanza\n[2]Elimina stanza\n\n");
                rewind(stdin);
                azione = getch();

                //49 == '1', in tal caso richiedo tutti i dati e modifico
                if(azione == 49){
                    printf("\n\nInserisci il nome della stanza: ");
                    rewind(stdin);
                    gets(tempNome);

                    printf("\n\nInserisci la lunghezza di %s:", tempNome);
                    rewind(stdin);
                    scanf("%d", &tempLun);

                    printf("\n\nInserisci la larghezza di %s:", tempNome);
                    rewind(stdin);
                    scanf("%d", &tempLar);

                    printf("\n\nInserisci il numero di ostacoli di %s:", tempNome);
                    rewind(stdin);
                    scanf("%d", &tempN_Ost);

                    printf("\n\nInserisci la priorita' di %s: \n\nLegenda:\n[1]Molto Importante\n[2]Importante\n[3]Quasi Importante\n[4]Poco Importante\n\n->", tempNome);
                    rewind(stdin);
                    scanf("%d", &tempPrio);

                    modificaStanza(listaStanze, tempNome, tempLun, tempLar, tempN_Ost, tempPrio);
                }else if(azione == 50){ //50 = '2', altrimenti cancello la stanza puntata dal puntatore in posizione temp dell'array
                    free(listaStanze[temp]);
                    listaStanze[temp]=NULL; //e lo rimetto a NULL
                    printf("\n\nStanza eliminata dal registro!\n");
                }else{
                    //se l'input non è accettabile lo comunico e non faccio nulla
                    printf("Azione cancellata, ritorna al menu' e riprova!");
                }
                break;

            case '4':
                //caso 4: calcola il percorso in base alla priorità di ogni stanza

                calcolaPercorso(listaStanze);
                break;

            case '5':
                //caso 5: esco dal programma

                system("cls");
                printf("Disconnessione effettuata con successo!\n\n");
                run=false; //metto a false il bool su cui gira il loop
                break;

            default:
                puts("input non valido");
        }
        printf("\n\n\n");
        system("pause");
    }

    //una volta che esco dal loop principale libero la memoria presa.
    free(listaStanze);

    return 0;
}
