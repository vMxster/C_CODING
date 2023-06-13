#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

/*
 * --- TESTO DELL'ESERCIZIO ---
 * Si scriva un programma C, adeguatamente commentato, che gestisca un certo numero di studenti iscritti ad un corso
 * di laurea. Il programma utilizza un vettore di strutture, ognuna delle quali memorizza le informazioni di uno studente
 * (numero matricola, nome e cognome, anno di immatricolazione, piano di studi, …). Il programma utilizza inoltre un
 * vettore di strutture, ognuna delle quali memorizza le informazioni di un insegnamento (codice, descrizione, anno di
 * somministrazione, crediti, …). Il programma deve fornire la possibilità di:
 *
 * Aggiungere un nuovo studente, stampando un messaggio di errore se lo studente è già presente (individuato dalla matricola)
 * o se il vettore è pieno; la funzione deve inoltre assegnargli un piano di studi scegliendo fra gli insegnamenti disponibili.
 *
 * Dato il numero di matricola, stampare le informazioni dello studente oppure un messaggio di errore se la matricola
 * non è presente nel vettore
 *
 * Dato un numero di matricola, modificare le informazioni del piano di studi aggiungendo un voto oppure stampando un messaggio
 * di errore se la matricola non è presente nel vettore.
 *
 * Calcolare la media dei voti di tutti gli studenti che hanno completato il piano di studi pesata sul numero di crediti
 * di ogni insegnamento.
 *
 * Il piano di studi all’interno della struttura studente è un vettore di NUM_ESAMI elementi ognuno di tipo struttura
 * contenete il codice dell'insegnamento e il voto corrispondente (0 se non sostenuto).
 *
 * Modificare poi il programma in modo che il vettore di studenti venga allocato dinamicamente usando la funzione malloc().
 */

#define NUM_ESAMI 30
#define NUM_MATRICOLE 100

//struttura insegnamento
struct insegnamento{
    char codice[20]; //primary key (corso)
    char descrizione[50];
    char annoSomministrazione[20];
    int cfu;
};

//struttura esame
struct esame{
    char codice[20]; //foreign key (corso)
    int cfu;
    int voto;
};

//struttura studente
struct studente{
    char numeroMatricola[20];
    char nome[20];
    char cognome[20];
    char annoImmatricolazione[20];
    float mediaEsami;
    struct esame* esami[NUM_ESAMI];
};

/*
 * funzione che mi ritorna:
 * - vero se l'array di struct insegnamenti che sto scorrendo è completamente vuoto
 * - falso se c'è anche solo una voce
 */
bool insegnamentiIsEmpty(struct insegnamento* lista_ins[NUM_ESAMI]){
    for(int i=0; i<NUM_ESAMI; i++)
        if(lista_ins[i] != NULL)
            return false;

    return true;
}

//stessa cosa ma con array di struct esame
bool esamiIsEmpty(struct esame* lista_es[NUM_ESAMI]){
    for(int i=0; i<NUM_ESAMI; i++)
        if(lista_es[i] != NULL)
            return false;

    return true;
}

//funzione che mi stampa tutti i possibili corsi a cui posso iscrivermi
void stampaPianiStudi(struct insegnamento* lista_insegnamenti[NUM_ESAMI]){
    //ciclo per num esami la lista degli insegnamenti
    for(int i=0; i<NUM_ESAMI; i++)
        //se la lista in i non punta a null
        if(lista_insegnamenti[i] != NULL)
            //allora stampo
            printf("[%d]:\nCodice: %s\nDescrizione: %s\nAnno di somministrazione: %s\nCrediti: %d\n\n",
                   i, lista_insegnamenti[i]->codice, lista_insegnamenti[i]->descrizione, lista_insegnamenti[i]->annoSomministrazione, lista_insegnamenti[i]->cfu);
}

void stampaMatricole(struct studente* lista_matricole[NUM_MATRICOLE]){
    for(int i=0; i<NUM_MATRICOLE; i++)
        if(lista_matricole[i] != NULL)
            printf("[%d]:\nNumero Matricola: %s\nNome: %s\nCognome: %s\nAnno di immatricolazione: %s\n\n",
                   i, lista_matricole[i]->numeroMatricola, lista_matricole[i]->nome, lista_matricole[i]->cognome, lista_matricole[i]->annoImmatricolazione);
}

//funzione che mi aggiunge uno studente alla lista
int aggiungiStudente(struct studente* lista_Studenti[NUM_MATRICOLE], char* numero, char* nome, char* cognome, char* anno){
    //controllo se quel nunmero matricola è già stato inserito
    for(int i=0; i<NUM_MATRICOLE; i++)
        if(lista_Studenti[i] != NULL && !strcmp(lista_Studenti[i]->numeroMatricola, numero))
            //se si ritorno -1
            return -1;

    //vado a cercare il primo slot che punta a NULL
    int cont=0;
    while(lista_Studenti[cont] != NULL) cont++;

    // appena lo trovo alloco la memoria
    lista_Studenti[cont] = (struct studente*) malloc(sizeof(struct studente));

    //e inizializzo a null la lista degli esami della nuova matricola
    for(int i=0; i<NUM_ESAMI; i++)
        lista_Studenti[cont]->esami[i] = NULL;

    //dopodiché ci sbatto dentro tutte le info
    strcpy(lista_Studenti[cont]->numeroMatricola, numero);
    strcpy(lista_Studenti[cont]->nome, nome);
    strcpy(lista_Studenti[cont]->cognome, cognome);
    strcpy(lista_Studenti[cont]->annoImmatricolazione, anno);

    //e ritorno la posizione della lista in cui l'ho appena inserito
    return cont;
}

//funzione che chiamo una volta per ogni insegnamento che voglio aggiungere al piano di studi di una matricola
int assegnaEsameA(struct studente* stud, struct insegnamento* lista_Corsi[NUM_ESAMI], char* codice_esame){
    bool esiste = false;
    int temp = 0;

    //se lo studente ha già nell'array di esami l'esame che si vuole aggiungere allora ritorno -1
    for(int i=0; i<NUM_ESAMI; i++)
        if(stud->esami[i] != NULL && !strcmp(stud->esami[i]->codice, codice_esame))
            return -1;

    //controllo se esiste il corso che voglio assegnare
    for(int i=0; i<NUM_ESAMI; i++)
        if(lista_Corsi[i] != NULL && !strcmp(lista_Corsi[i]->codice, codice_esame)){
            //appena lo trovo flaggo ed esco da questo for
            esiste = true;
            temp = lista_Corsi[i]->cfu;
            break;
        }

    //se non esiste ritorno 2
    if(!esiste) return -2;

    //altrimenti continuo:

    int pos_esame = 0; //variabile temporanea che uso per spostarmi nella lista esami dello studente in posizione pos

    //la incremento finché non arrivo a una cella con un puntatore che punta a null
    while(stud->esami[pos_esame] != NULL) pos_esame++;

    //dopodiché alloco la memoria necessaria
    stud->esami[pos_esame] = (struct esame *) malloc(sizeof(struct esame));

    //e ci sbatto dentro le info dell'esame
    strcpy(stud->esami[pos_esame]->codice, codice_esame);
    stud->esami[pos_esame]->voto = 0;
    stud->esami[pos_esame]->cfu = temp;

    //ritorno la posizione in cui ho messo l'esame all'interno dell'array di puntatori esame della matricola
    return pos_esame;
}

//funzione che mi aggiunge un insegnamento
int aggiungiInsegnamento(struct insegnamento* lista_Corsi[NUM_ESAMI], char* codice, char* desc, char* anno, int cfu){

    //controllo se c'è già un insegnamento con quel codice
    for(int i=0; i<NUM_ESAMI; i++)
        if(lista_Corsi[i] != NULL && !strcmp(lista_Corsi[i]->codice, codice))
            return -1; //se si ritorno -1

    //altrimenti continuo e cerco la prima posizione libera
    int cont=0;
    while(lista_Corsi[cont]!=NULL) cont++;

    //appena la trovo alloco la memoria e la punto
    lista_Corsi[cont] = (struct insegnamento*) malloc(sizeof(struct insegnamento));
    if(lista_Corsi[cont] == NULL) return -1;

    //e poi la riempio con le info
    strcpy(lista_Corsi[cont]->codice, codice);
    strcpy(lista_Corsi[cont]->descrizione, desc);
    strcpy(lista_Corsi[cont]->annoSomministrazione, anno);
    lista_Corsi[cont]->cfu = cfu;

    //e ritorno la posizione dell'array che ho appena usato
    return cont;
}

//funzione che mi stampa una matricola discriminata dal numero matricola
int stampaMatricola(struct studente* lista_matricole[NUM_MATRICOLE], char* numero){
    //ciclo tutte le matricole
    for(int i=0; i<NUM_MATRICOLE; i++)
        //appena ho un riscontro
        if(lista_matricole[i] != NULL && !strcmp(lista_matricole[i]->numeroMatricola, numero)) {

            //stampo le info
            printf("\nNumero Matricola: %s\nNome: %s\nCognome: %s\nAnno immatricolazione: %s\nMedia esami: %.2f\n",
                   lista_matricole[i]->numeroMatricola, lista_matricole[i]->nome, lista_matricole[i]->cognome,
                   lista_matricole[i]->annoImmatricolazione, lista_matricole[i]->mediaEsami);

            //se l'array di esami della matricola è vuoto
            if(esamiIsEmpty(lista_matricole[i]->esami)){

                //lo stampo e ritorno 0 perché tutto è andato correttamente.
                printf("Questa matricola non ha ancora completato il piano di studi\n\n");
                return 0;
            }

            //altrimenti ciclo per num_esami l'array di esami della matricola

            for (int j = 0; j < NUM_ESAMI; j++)
                if(lista_matricole[i]->esami[j] != NULL){

                    //e per ogni esame ne stampo codice e voto (numerico se sostenuto stringa se non ancora sostenuto)
                    printf("\nEsame: %s\n", lista_matricole[i]->esami[j]->codice);

                    if(lista_matricole[i]->esami[j]->voto == 0){
                        printf("Non ancora sostenuto\n\n");
                    }else
                        printf("Voto: %d\n\n", lista_matricole[i]->esami[j]->voto);

                }

            return 0; //ritorno 0 quando ho correttamente stampato tutto
        }

    return -1; //ritorno -1 se non ho riscontri con il numero matricola dato
}

/*
 * funzione che calcola la media dei voti di una data matricola
 * ritorna 0 se ci sono ancora degli esami non sostenuti, quindi se il piano di studi non è finito
 * altrimenti ritorna la media dei voti
 *
 * Media ponderata = (voto esame1 x crediti esame1) + (voto esame2 x crediti esame2) + (voto esame3 x crediti esame3) /
 * numero crediti complessivo
 */
float calcolaMedia(struct studente* stud){
    float somma = 0.f;
    int i;
    float cont = 0.f;
    for(i=0; i<NUM_ESAMI; i++)
        if(stud->esami[i] != NULL)
            if(stud->esami[i]->voto == 0){
                return 0.f;
            }else {
                somma += (stud->esami[i]->voto * stud->esami[i]->cfu);
                cont += stud->esami[i]->cfu;
            }

    return somma/cont;
}

//funzione che mi aggiunge il voto ad un esame di una matricola a cui si è segnato
int aggiungiVoto(struct studente* lista_matricole[NUM_MATRICOLE], char* numero_m, char* codice_e, int voto){
    int media=0;

    //ciclo su num matricole e appena ho un riscontro con il numero matricola dato
    for(int i=0; i<NUM_MATRICOLE; i++)
        if(lista_matricole[i] != NULL && !strcmp(lista_matricole[i]->numeroMatricola, numero_m)) {

            //ciclo su num esami e se trovo anche qui un riscontro con il codice esame dato
            for(int j=0; j<NUM_ESAMI; j++)
                if(lista_matricole[i]->esami[j] != NULL && !strcmp(lista_matricole[i]->esami[j]->codice, codice_e)){

                    //allora modifico il voto
                    lista_matricole[i]->esami[j]->voto=voto;

                    lista_matricole[i]->mediaEsami = calcolaMedia(lista_matricole[i]);

                    return 0; // e ritorno 0: voto modificato con successo

                }

            return -2; //esame non trovato

        }

    return -1; //matricola non trovata
}

int main() {

    //array di puntatori di tipo struct studente inizializzati tutti a NULL
    struct studente* lista_Studenti[NUM_MATRICOLE];
    for(int i=0; i<NUM_MATRICOLE; i++) lista_Studenti[i] = NULL;

    //array di puntatori di tipo struct insegnamenti inizializzati tutti a NULL
    struct insegnamento* lista_Insegnamenti[NUM_ESAMI];
    for(int i=0; i<NUM_ESAMI; i++) lista_Insegnamenti[i] = NULL;

    bool run = true; // booleano per il ciclo principale
    int scelta; // variabile switch principale

    //variabili temporanee inserimento matricola
    char tempNome[50];
    char tempCognome[50];
    char tempNumMat[20];
    char tempAnnoIsc[20];

    //variabili temporanee inserimento corso
    char tempCodice[20];
    char tempDesc[50];
    char tempAnnoSomm[20];
    int tempCfu=0;

    //variabili temporanee inserimento esami in studente
    char tempCodEsami[500];
    char c;

    //variabili temporanee modifica voto
    short int tempVoto = 0;

    //variabili di stato
    int statoIscrizione;
    int statoAggiuntaCorso;
    int status;

    while(run){

        system("cls");
        printf("[1]Aggiungi matricola\n[2]Aggiungi insegnamento\n[3]Mostra matricola\n[4]Modifica voto matricola\n[5]Esci\n[6]Stampa tutte le matricole\n[7]Stampa insegnamenti\n\n->");
        rewind(stdin);
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                //inserimento matricola:
                system("cls");

                printf("N U O V A   M A T R I C O L A\n\n");

                //prendi in input tutte le info necessarie
                printf("Nome: ");
                rewind(stdin);
                gets(tempNome);

                printf("\n\nCognome: ");
                rewind(stdin);
                gets(tempCognome);

                printf("\n\nNumero Matricola: ");
                rewind(stdin);
                gets(tempNumMat);

                printf("\n\nAnno di iscrizione: ");
                rewind(stdin);
                gets(tempAnnoIsc);

                //e chiamo la funzione salvandomi il valore di ritorno in statoIscrizione
                statoIscrizione = aggiungiStudente(lista_Studenti, tempNumMat, tempNome, tempCognome, tempAnnoIsc);

                //e in base a quello stampo il risultato dell'operazione
                if(statoIscrizione == -1){
                    system("cls");
                    printf("\n\nAttenzione! Matricola già inserita!\n\n");
                    break;
                }else
                    printf("Matricola %s inserita con successo al posto %d\n\nCrea il tuo piano di studi:\n", tempNumMat, statoIscrizione);

                //se la lista di corsi è vuota allora termino qui l'inserimento
                if(insegnamentiIsEmpty(lista_Insegnamenti)){
                    printf("Nessun corso disponibile\n\n");
                }else{

                    //altrimenti stampo tutti i corsi accessibili
                    stampaPianiStudi(lista_Insegnamenti);

                    //e gli chiedo di inserire il codice dei corsi a cui vuole iscriversi separati dallo spazio
                    printf("Inserisci i codici dei corsi a cui desideri partecipare separati da spazio:\n\n->");
                    rewind(stdin);

                    do {
                        //il primo scanf è bloccante perché il buffer è vuoto
                        scanf("%s", tempCodEsami);
                        //lo scanf si ferma al primo spazio che trova

                        //faccio partire la funzione assegna esame salvandomi il valore di ritorno in status
                        status = assegnaEsameA(lista_Studenti[statoIscrizione], lista_Insegnamenti, tempCodEsami);

                        //se ritorno -2 allora l'esame non esiste, quindi lo comunico
                        if(status == -1) printf("\nEsame %s già inserito!\n\n", tempCodEsami);
                        if(status == -2) printf("\nEsame %s non esiste!\n\n", tempCodEsami);

                        //il buffer è ancora pieno, quindi getchar non è bloccante e va direttamente a leggere nel buffer
                        c = getchar();

                        //e cicla finché il getchar non legge il carattere invio
                    } while (c != '\n');

                }
                break;

            case 2:
                //aggiungi insegnamento

                system("cls");

                printf("C R E A   C O R S O\n\n");

                //prendo in input le info necessarie
                printf("Descrizione Corso: ");
                rewind(stdin);
                gets(tempDesc);

                printf("\n\nCodice Corso: ");
                rewind(stdin);
                gets(tempCodice);

                printf("\n\nAnno di somministrazione Corso: ");
                rewind(stdin);
                gets(tempAnnoSomm);

                printf("\n\nCrediti del Corso: ");
                rewind(stdin);
                scanf("%d", &tempCfu);

                //e chiamo la funzione aggiungiInsegnamento() su statoAggiuntaCorso
                statoAggiuntaCorso = aggiungiInsegnamento(lista_Insegnamenti, tempCodice, tempDesc, tempAnnoSomm, tempCfu);

                //in base al valore di ritorno stampo il risultato dell'operazione
                if(statoAggiuntaCorso == -1){
                    printf("\n\nErrore! Esiste gia' un corso con quel codice\n\n");
                }else{
                    printf("\n\nCorso %s aggiunto con successo\n\n", tempCodice);
                }

                break;

            case 3:
                //stampa matricola
                system("cls");

                printf("C E R C A   M A T R I C O L A\n\n");

                //prendo in input il numero matricola
                printf("Numero matricola da cercare: ");
                rewind(stdin);
                gets(tempNumMat);

                //mi salvo il valore di ritorno di stampaMatricola in status
                status = stampaMatricola(lista_Studenti, tempNumMat);

                //se ritorna -1 allora significa che non ha trovato niente
                if(status == -1) printf("\n\nMatricola %s inesistente\n\n", tempNumMat);
                break;

            case 4:
                //modificaVoto
                system("cls");

                printf("M O D I F I C A   V O T O\n\n");

                //prendo in input le info necessarie
                printf("Numero Matricola: ");
                rewind(stdin);
                gets(tempNumMat);

                printf("\n\nCodice Corso: ");
                rewind(stdin);
                gets(tempCodice);

                printf("\n\nVoto assegnato: ");
                rewind(stdin);
                scanf("%d", &tempVoto);

                //chiamo la funzione aggiungiVoto su status
                status = aggiungiVoto(lista_Studenti, tempNumMat, tempCodice, tempVoto);

                //in base al valore di ritorno comunico il risultato dell'operazione
                switch(status){
                    case 0:
                        printf("\nVoto inserito con successo\n\n");
                        break;
                    case -1:
                        printf("\nMatricola non trovata\n\n");
                        break;
                    case -2:
                        printf("\nEsame non trovato\n\n");
                        break;
                }
                break;

            case 5:
                //esco dal ciclo principale
                run = false;
                break;

            case 6:
                system("cls");
                stampaMatricole(lista_Studenti);
                break;

            case 7:
                system("cls");
                stampaPianiStudi(lista_Insegnamenti);
                break;

            default:
                printf("\n\nInput non accettabile\n\n");
        }
        system("pause");
    }
    return 0;
}
