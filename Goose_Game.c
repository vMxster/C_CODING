#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

/*  Domande.txt
 *  Film di Christopher Nolan del 2020:
 *  Qual e' la risposta alla domanda fondamentale sulla vita, l'universo e tutto quanto?
 *  In che anno Cristoforo Colombo ha scoperto l'America?
 *  In che anno e' finita la Seconda Guerra Mondiale?
 *  In che anno e' caduto il muro di Berlino?
 *  Anno in cui l'Italia entra in guerra durante la Prima Guerra Mondiale:
 *  Risposte.txt
 *  Tenet
 *  42
 *  1492
 *  1945
 *  1989
 *  1915
 */

/*
 * --- TESTO DELL'ESERCIZIO ---
 * Si scriva un programma C, adeguatamente commentato, per la generazione di partite del "Gioco dell'oca"
 * (Snakes & Ladders nella versione inglese). Il gioco consiste nel far competere più giocatori per il raggiungimento
 * della casella finale, avanzando di volta in volta tra caselle diverse tramite il tiro di un dado a 6 facce.
 *
 * Il programma non deve limitarsi a generare sempre lo stesso percorso (combinazione di caselle), ma ad ogni nuova
 * partita deve far corrispondere un diverso tabellone di gioco.
 *
 * Il programma deve implementare le seguenti caselle:
 *
 * oscale, che permettono di 'saltare' di X caselle in avanti, dove X è scelto dal programma; l'avanzamento non è
 * automatico, il giocatore deve rispondere correttamente a una domanda per poter utilizzare la scala;
 *
 * oscivoli, che permettono di indietreggiare di Y caselle, dove Y è scelto dal programma
 *
 * obuchi, che fanno saltare il turno successivo al giocatore.
 *
 * Il gioco deve gestire al massimo 5 giocatori, identificati da colori o numeri identificativi diversi.
 *
 * Si utilizzino le strutture per rappresentare giocatori e caselle.
 *
 * Si utilizzi una coda per gestire il turno dei giocatori.
 *
 * Si visualizzi il tabellone di gioco, con la posizione dei vari giocatori.
 *
 * Si utilizzino due file per la gestione del quiz delle scale: un file con le domande (una per riga) e un file con le
 * rispettive risposte;
 */

//costanti per la costruzione della mappa di gioco
#define N_OSCALE 5
#define N_OSCIVOLI 5
#define N_OBUCHI 5
#define N_NORMALI 25

//enum con tutti i tipi di casella
enum tipo{
    oscala,
    oscivolo,
    obuco,
    normale
};

//struttura casella
struct casella{
    int tipo; //tipo casella
    int nCasella; //numero della casella
    struct casella* next;
};

struct giocatore{
    char nome[20]; //nome giocatore
    int numero; //numero (usato anche per cambiare il colore)
    int pos; //posizione giocatore
    bool sonoNelBuco; //bool quando finisce in obuco
    struct giocatore* next;
};

//funzione colori
void cambiaColore(unsigned short int colore) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,colore);
}

//funzione per nascondere il cursore, per ora non c'è input richiesto quindi è più carino nasconderlo
void nascondiCursore(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO i;
    i.dwSize = 100;
    i.bVisible = FALSE;
    SetConsoleCursorInfo(h, &i);
}

//funzione che mi permette di spostare il cursore nel terminale usando una coppia di coordinate x e y
void spostaCursore(short int x, short int y) {
    COORD posizione = {x, y};
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, posizione);
}

//stampa base debug non serve al programma finito
void stampaCampoDebug(struct casella* head){
    while(head != NULL){
        printf("\nN = %d\nTipo = %d\n", head->nCasella, head->tipo);
        head = head->next;
    }
}

//stampa lista giocatori per debug, non server al programma finito
void stampaGiocatoriDebug(struct giocatore* head){
    while(head != NULL){
        printf("\nNome = %s, Colore = %d", head->nome, head->numero);
        head = head->next;
    }
}

//funzione che aggiunge una casella alla mappa, la uso quando la creo
struct casella* aggiungiCasella(struct casella* head, int tipo, int n){
    //creo un appoggio per scorrere la lista e la metto uguale alla testa
    struct casella* body = head;

    //se body quindi head è NULL allora significa che sto mettendo la prima casella, dunque alloco la testa
    if(body == NULL){
        head = (struct casella*) malloc(sizeof(struct casella));
        if(head == NULL) exit(1);
        body = head;

    //altrimenti
    }else{
        //scorro la lista finché non arrivo alla coda ed inserisco un nuovo figlio
        while(body->next != NULL) body = body->next;
        body->next = (struct casella*) malloc(sizeof(struct casella));
        if(body->next == NULL) exit(2);
        body = body->next;
    }

    //inizializzo il nuovo figlio appena appeso
    body->tipo = tipo;
    body->nCasella=n;
    body->next = NULL;

    //e ritorno il puntatore a testa
    return head;
}

//funzione che mi crea il campo di gioco
struct casella* generaCampo(struct casella* head){
    if(head != NULL) return NULL; //non dovrebbe mai essere diverso da null ma non si sa mai

    //variabili contatori
    int nCaselle = N_OBUCHI+N_OSCALE+N_OSCIVOLI+N_NORMALI;
    int n_obuchi = N_OBUCHI;
    int n_oscale = N_OSCALE;
    int n_oscivoli = N_OSCIVOLI;
    int n_normali = N_NORMALI;

    //variabili che uso per riempire ogni casella
    int r=0;
    int n=6;

    //faccio sì che le prime 5 caselle siano normali per convenienza
    for(int i=1 ; i<=5; i++){
        head = aggiungiCasella(head, normale, i);
        nCaselle--;
    }

    //ciclo finché non ho messo tutte le tot caselle
    while(nCaselle != 0){

        //faccio un random per decidere che casella mettere
        r = rand()%4+1;

        switch(r){

            /*
             * ovviamente il random potrebbe farmi mettere più caselle dello stesso tipo di quante ne possa
             * effettivamente mettere, quindi per ogni case controllo se ho finito le caselle da mettere.
             * Se le ho finite faccio continue e il loop riparte da capo, altrimenti piazzo e diminuisco il
             * rispettivo contatore
             */

            case 1:
                if(n_oscale == 0) continue;
                head = aggiungiCasella(head, oscala, n);
                n_oscale--;
                break;
            case 2:
                if(n_oscivoli == 0) continue;
                head = aggiungiCasella(head, oscivolo, n);
                n_oscivoli--;
                break;
            case 3:
                if(n_obuchi == 0) continue;
                head = aggiungiCasella(head, obuco, n);
                n_obuchi--;
                break;
            case 4:
                if(n_normali == 0) continue;
                head = aggiungiCasella(head, normale, n);
                n_normali--;
                break;
        }
        //alla fine diminuisco anche il numero totale di caselle
        nCaselle--;
        //incremento il contatore che uso per assegnare il numero alle caselle
        n++;
    }

    //ritorno puntatore a testa
    return head;
}

//funzione che mi inserisce un giocatore
struct giocatore* insGiocatore(struct giocatore* head, char* nome, int n){
    //creo un puntatore ausiliario per scorrere la lista e lo metto uguale a testa
    struct giocatore* body = head;

    //se body quindi testa è uguale a NULL allora significa che è il primo giocatore quindi alloco head
    if(body == NULL){
        head = (struct giocatore*) malloc(sizeof(struct giocatore));
        if(head == NULL) exit(1);
        body = head;

    //altrimenti
    }else{

        //scorro la lista finché non arrivo alla fine e appendo un nuovo figlio
        while(body->next != NULL) body = body->next;
        body->next = (struct giocatore*) malloc(sizeof(struct giocatore));
        if(body->next == NULL) exit(2);
        body = body->next;
    }

    //inizializzo i campi del figlio appena appeso
    strcpy(body->nome, nome);
    body->numero=n;
    body->pos = 1;
    body->sonoNelBuco = false;
    body->next = NULL;

    //e ritorno il puntatore a testa
    return head;
}

//funzione che mi stampa la legenda delle caselle
void stampaLegenda(){
    spostaCursore(80,0);
    printf("Legenda:");

    spostaCursore(80,2);
    cambiaColore(6);
    printf("Casella oScala");

    spostaCursore(80, 3);
    cambiaColore(9);
    printf("Casella oScivolo");

    spostaCursore(80, 4);
    cambiaColore(10);
    printf("Casella oBuco");

    spostaCursore(80, 5);
    cambiaColore(7);
    printf("Casella normale");
}

//funzione che mi mette in automatico in full screen, la uso appena runno il programma
void FullScreen_Plus(){
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

//stampa ufficiale dell'output
void betterStampaCampo(struct giocatore* headG, struct casella* headC, int turno){
    system("cls"); //pulisco il terminale
    stampaLegenda(); //stampo la legenda
    struct giocatore* bodyG = headG; //creo un appoggio per scorrere la lista
    int x = 0; //variabile x per lo spostaCursore()
    int contY=0; //variabile y per lo spostaCursore()
    int nGiocatoriAllaPosizione = 0; //contatore che mi conta quanti giocatori ci sono in una casella

    // stampo il turno
    spostaCursore(100, 2);
    printf("Turno %d", turno);

    //ciclo sulla lista caselle
    while(headC != NULL){
        bodyG = headG; //a ogni giro resetto il puntatore appoggio della lista giocatori

        //switcho sul tipo casella e cambio il colore per la stampa
        switch(headC->tipo){
            case oscala:
                cambiaColore(6);
                break;
            case oscivolo:
                cambiaColore(9);
                break;
            case obuco:
                cambiaColore(10);
                break;
            case normale:
                cambiaColore(7);
                break;
        }

        //sposto il cursore e stampo la casella
        spostaCursore(x,contY);
        printf("Casella %d", headC->nCasella);

        //e poi mi controllo se c'è un giocatore in questa casella

        int cont = 2;
        //ciclo la lista giocatori
        while(bodyG != NULL){
            spostaCursore(120, cont);
            printf("%s : %d", bodyG->nome, bodyG->pos);
            //se un giocatore è in questa posizione
            if(bodyG->pos == headC->nCasella){
                //aumento il contatore
                nGiocatoriAllaPosizione++;
                //cambio colore in base al giocatore e poi lo stampo
                cambiaColore(bodyG->numero);
                spostaCursore(x, contY+nGiocatoriAllaPosizione);
                printf("%s", bodyG->nome);
            }
            cont++;
            bodyG = bodyG->next;
        }

        //controlli per gestire le coordinate dello spostaCursore() in modo da stampare file da 10 caselle
        if(headC->nCasella%10 == 0){
            contY=0;
            x+=15;
        }else{
            contY+=6;
        }
        headC = headC->next;
    }
}

//funzione che mi controlla se qualcuno ha vinto
bool checkRun(struct giocatore* head){

    //puntatore appoggio per scorrere la lista
    struct giocatore* body = head;

    //variabile che conta il numero totale di caselle
    int totCaselle = N_OBUCHI+N_OSCALE+N_OSCIVOLI+N_NORMALI;

    //la lista giocatori non può essere NULL a questo punto, se lo è qualcosa è andato storto e chiudo
    if(body == NULL) exit(0);

    //ciclo sulla lista giocatori e controllo se c'è qualcuno che è all'ultima posizione
    while(body != NULL){
        if(body->pos == totCaselle) return false;
        body = body->next;
    }
    return true;
}

//funzione che mi legge da un file una riga
char* leggiRiga(FILE* fp){
    char* riga;
    riga = (char*) malloc(100*sizeof(char));
    char c = 'a';
    int cont = 0;
    while(c != '\n'){
        if(feof(fp) != 0) break;
        c = fgetc(fp);
        if(c != '\n') {
            riga[cont] = c;
            cont++;
        }
    }
    riga[cont] = '\0';
    return riga;
}

int main() {

    srand(time(NULL));

    //le liste
    struct giocatore* testaGiocatori = NULL;
    struct casella* testaCaselle = NULL;

    //i file
    FILE* domande = fopen("FileDomande.txt", "r");
    if(domande == NULL) exit(0);
    FILE* risposte = fopen("FileRisposte.txt", "r");
    if(risposte == NULL) exit(0);

    //variabili di sistema
    int nGiocatori;
    char nomeGiocatore[20];
    bool run = true;

    //variabile che conta il numero totale di caselle
    int totCaselle = N_OBUCHI+N_OSCALE+N_OSCIVOLI+N_NORMALI;

    FullScreen_Plus();
    nascondiCursore();

    //input utente, creo la lista giocatori. controllo che ci siano al max 5 giocatori ma almeno 1
    do{
        system("cls");
        printf("Quanti giocatori ci sono?\n->");
        scanf("%d", &nGiocatori);
    }while(nGiocatori<1 || nGiocatori>5);

    for(int i=1; i<=nGiocatori; i++){
        printf("\n\nGiocatore %d:\nNome:\n->", i);
        rewind(stdin);
        gets(nomeGiocatore);
        testaGiocatori = insGiocatore(testaGiocatori, nomeGiocatore, i);
    }

    //genero il campo
    testaCaselle = generaCampo(testaCaselle);

    system("cls");
    betterStampaCampo(testaGiocatori, testaCaselle, 0);

    //variabili del loop principale
    int turno = 0;
    struct giocatore* bodyG = testaGiocatori;
    struct casella* bodyC = testaCaselle;
    int dado;
    char* domanda;
    char* rispostaCorretta;
    char rispostaUtente[50];
    int salto;

    while(run){
        system("cls");
        betterStampaCampo(testaGiocatori, testaCaselle, turno);

        //controllo se il giocatore di questo turno è nel buco, se si vado avanti e gli resetto il bool
        if(bodyG->sonoNelBuco){
            bodyG->sonoNelBuco = false;
            if(bodyG->next != NULL){
                bodyG = bodyG->next;
            }else{
                bodyG = testaGiocatori;
            }
            continue;
        }

        //output grafico
        spostaCursore(80, 10);
        printf("Turno di %s", bodyG->nome);

        spostaCursore(80, 11);
        printf("Premi invio per tirare il dado:");

        system("pause > nul");

        //lancio il dado
        dado = rand()%6+1;
        spostaCursore(80, 12);
        printf("Lancio: %d", dado);

        //aumento la posizione del giocatore
        bodyG->pos = (bodyG->pos+dado > totCaselle) ? totCaselle : bodyG->pos+dado;

        system("pause > nul");
        system("cls");

        betterStampaCampo(testaGiocatori, testaCaselle, turno);

        //scorro la lista delle caselle e mi fermo alla casella su cui si trova il giocatore
        for(int i=0; i<(bodyG->pos-1); i++)
            bodyC = bodyC->next;

        //e poi switcho sul tipo di casella
        switch(bodyC->tipo){
            case oscala:
                //(rand() % (upper - lower + 1)) + lower
                salto = rand()% (4 - 1 + 1) +1; //faccio un random del salto in avanti tra 1 e 4
                spostaCursore(80, 15);
                printf("Per saltare avanti di %d, rispondi a questa domanda:", salto);

                /*
                 * devo leggere la domanda e la risposta, ma prima controllo per entrambi i
                 * file se sono arrivato alla fine. In tal caso riapro il file.
                 */

                if(feof(domande)) freopen("FileDomande.txt", "r", domande);
                domanda = leggiRiga(domande);
                if(feof(risposte)) freopen("FileRisposte.txt", "r", risposte);
                rispostaCorretta = leggiRiga(risposte);

                //metto la risposta utente e la risposta corretta a lowerCase così evito gli errori tipo "tenet" != "Tenet"
                for(int i = 0; i< strlen(rispostaCorretta); i++)
                    rispostaCorretta[i] = tolower(rispostaCorretta[i]);


                //output domanda e input risposta dell'utente
                spostaCursore(80, 16);
                printf("%s", domanda);
                spostaCursore(80, 17);
                printf("->");
                rewind(stdin);
                gets(rispostaUtente);

                for(int i = 0; i<strlen(rispostaUtente); i++)
                    rispostaUtente[i] = tolower(rispostaUtente[i]);


                /*
                 * controllo se la risposta dell'utente è corretta. Se è corretta aumento la sua posizione di salto,
                 * altrimenti non faccio niente.
                 * Se la pos del giocatore + salto è maggiore di totCaselle lo metto a totCaselle,
                 * altrimenti incremento semplicemente di salto
                 */
                if(!strcmp(rispostaUtente, rispostaCorretta)){
                    spostaCursore(80, 18);
                    printf("Risposta Corretta!! Avanzi di %d caselle", salto);
                    bodyG->pos = (bodyG->pos+salto > totCaselle) ? totCaselle : bodyG->pos+salto;
                }else{
                    spostaCursore(80, 18);
                    printf("Risposta errata!! la risposta corretta era %s", rispostaCorretta);
                }

                break;
            case oscivolo:
                //genero il salto indietro tra 1 e 4
                salto = rand()%4+1;
                spostaCursore(80,15);
                printf("%s vai indietro di %d caselle!!", bodyG->nome, salto);
                //decremento la pos del giocatore
                bodyG->pos -= salto;
                break;
            case obuco:
                spostaCursore(80, 15);
                printf("%s sei finito nel buco!!! Salti un turno", bodyG->nome);
                //se finisco nel buco alzo la flag
                bodyG->sonoNelBuco = true;
                break;
        }

        run = checkRun(testaGiocatori);

        //devo gestire il turno dei giocatori, quindi scorro in avanti se possibile nella lista giocatori.
        //se sono alla fine mi sposto in testa e riparto. Se il gioco è finito allora non lo faccio
        //così mi salvo il giocatore che ha vinto
        if(run){
            if(bodyG->next != NULL){
                bodyG = bodyG->next;
            }else{
                bodyG = testaGiocatori;
            }
        }

        // cose di fine loop. reset del puntatore caselle e incremento il turno
        spostaCursore(0,60);
        system("pause");
        turno++;
        bodyC = testaCaselle;
    }

    printf("\n\n");

    //output del vincitore e termine programma
    system("cls");
    spostaCursore(50, 25);
    printf("%s ha vinto!!!!", bodyG->nome);
    spostaCursore(80,27);
    system("pause");

    fclose(domande);
    fclose(risposte);
    free(testaGiocatori);
    free(testaCaselle);
    return 0;
}
