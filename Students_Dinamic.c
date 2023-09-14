#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* --- TESTO DELL'ESERCIZIO ---
 * Modificare l’esercizio 2 della settimana 7 in modo che l’elenco di studenti sia gestito tramite vettore dinamico di
 * puntatori a vettori dinamici di studenti e che l’elenco degli insegnamenti sia gestito tramite vettore dinamico di
 * puntatori a vettori dinamici di insegnamenti.
 */

#define NUM_ESAMI 30

struct esame{
    char codice[20]; //foreign key (corso)
    int cfu;
    int voto;
};

struct studente{
    char numeroMatricola[20];
    char nome[20];
    char cognome[20];
    char annoImmatricolazione[20];
    float mediaEsami;
    struct esame* esami[NUM_ESAMI];
};

/*
 * La logica di base funziona così:
 * ho intenzione di occupare la minima porzione di memoria possibile e per farlo ho usato realloc() ogni volta che
 * volevo aggiungere qualcosa (insegnamento o studente).
 * realloc ogni volta mi ritorna la stessa porzione di memoria precedente aumentata però di quanto mi occupa un nuovo
 * puntatore a struct
 * Per usare la realloc però ho bisogno di sapere quanta è grande la porzione di memoria che ogni volta voglio ingrandire
 * quindi ho usato un'ulteriore struct (una per ogni tipo studente/insegnamento) che contiene appunto il mio vettore
 * dinamico di puntatori a vettori dinamici di struct e un contatore (count) che incrementa ogni volta che aggiungo qualcosa.
 */

struct arr_stud{
    struct studente **studenti;
    int count;
};

struct insegnamento{
    char codice[20]; //primary key (corso)
    char descrizione[50];
    char annoSomministrazione[20];
    int cfu;
};

struct arr_ins{
    struct insegnamento **insegnamenti;
    int count;
};


int aggiungiStudente(struct arr_stud* stud, char *nome, char* cognome, char* num, char* anno){

    for(int i =0; i<stud->count; i++)
        if(stud->studenti[i] != NULL && !strcmp(stud->studenti[i]->numeroMatricola, num))
            return -2; //controllo che lo studente che sto aggiungendo non esista gia'

    int i = stud->count; //variabile d'appoggio (si potrebbe usare direttamente stud->count)

    stud->count++;
    //rialloco la memoria
    stud->studenti = (struct studente**) realloc(stud->studenti, stud->count*sizeof(struct studente*));

    if(stud->studenti == NULL) return -1; //se fallisce la realloc();

    //ci appendo un nuovo puntatore a struct
    stud->studenti[i] = (struct studente*) malloc(sizeof(struct studente));
    strcpy(stud->studenti[i]->nome, nome);
    strcpy(stud->studenti[i]->cognome, cognome);
    strcpy(stud->studenti[i]->numeroMatricola, num);
    strcpy(stud->studenti[i]->annoImmatricolazione, anno);

    for(int j=0; j<NUM_ESAMI; j++)
        stud->studenti[i]->esami[j] = NULL;

    return i;
}

//funzione che mi aggiunge un insegnamento
int aggiungiInsegnamento(struct arr_ins* ins, char* codice, char* desc, char* anno, int cfu){

    for(int i=0; i<ins->count; i++)
        if(ins->insegnamenti[i] != NULL && !strcmp(ins->insegnamenti[i]->codice, codice))
            return -2;

    int i = ins->count;

    ins->count++;
    //rialloco
    ins->insegnamenti = (struct insegnamento**) realloc(ins->insegnamenti, ins->count*sizeof(struct insegnamento*));

    if(ins->insegnamenti == NULL) return -1;

    //e ci appendo un nuovo puntatore a struct insegnamento
    ins->insegnamenti[i] = (struct insegnamento*) malloc(sizeof(struct insegnamento));
    if(ins->insegnamenti[i] == NULL) return -1;

    strcpy(ins->insegnamenti[i]->codice, codice);
    strcpy(ins->insegnamenti[i]->descrizione, desc);
    strcpy(ins->insegnamenti[i]->annoSomministrazione, anno);
    ins->insegnamenti[i]->cfu = cfu;

    return i;
}

//funzione che mi stampa tutti i possibili corsi a cui posso iscrivermi
void stampaPianiStudi(struct arr_ins* ins){
    //ciclo per num esami la lista degli insegnamenti
    for(int i=0; i<ins->count; i++)
        //se la lista in i non punta a null
        if(ins->insegnamenti[i] != NULL)
            //allora stampo
            printf("[%d]:\nCodice: %s\nDescrizione: %s\nAnno di somministrazione: %s\nCrediti: %d\n\n",
                   i, ins->insegnamenti[i]->codice, ins->insegnamenti[i]->descrizione, ins->insegnamenti[i]->annoSomministrazione, ins->insegnamenti[i]->cfu);
}

//funzione che chiamo una volta per ogni insegnamento che voglio aggiungere al piano di studi di una matricola
int assegnaEsameA(struct studente* stud, struct arr_ins* ins, char* codice_esame){
    bool esiste = false;
    int temp = 0;

    //se lo studente ha già nell'array di esami l'esame che si vuole aggiungere allora ritorno -1
    for(int i=0; i<NUM_ESAMI; i++)
        if(stud->esami[i] != NULL && !strcmp(stud->esami[i]->codice, codice_esame))
            return -1;

    //controllo se esiste il corso che voglio assegnare
    for(int i=0; i<ins->count; i++)
        if(ins->insegnamenti[i] != NULL && !strcmp(ins->insegnamenti[i]->codice, codice_esame)){
            //appena lo trovo flaggo ed esco da questo for
            esiste = true;
            temp = ins->insegnamenti[i]->cfu;
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

//stessa cosa ma con array di struct esame
bool esamiIsEmpty(struct esame* lista_es[NUM_ESAMI]){
    for(int i=0; i<NUM_ESAMI; i++)
        if(lista_es[i] != NULL)
            return false;

    return true;
}

//funzione che mi stampa una matricola discriminata dal numero matricola
int stampaMatricola(struct arr_stud* stud, char* numero){
    //ciclo tutte le matricole
    for(int i=0; i<stud->count; i++)
        //appena ho un riscontro
        if(stud->studenti[i] != NULL && !strcmp(stud->studenti[i]->numeroMatricola, numero)) {

            //stampo le info
            printf("\nNumero Matricola: %s\nNome: %s\nCognome: %s\nAnno immatricolazione: %s\nMedia esami: %.2f\n",
                   stud->studenti[i]->numeroMatricola, stud->studenti[i]->nome, stud->studenti[i]->cognome,
                   stud->studenti[i]->annoImmatricolazione, stud->studenti[i]->mediaEsami);

            //se l'array di esami della matricola è vuoto
            if(esamiIsEmpty(stud->studenti[i]->esami)){

                //lo stampo e ritorno 0 perché tutto è andato correttamente.
                printf("Questa matricola non ha ancora completato il piano di studi\n\n");
                return 0;
            }

            //altrimenti ciclo per num_esami l'array di esami della matricola

            for (int j = 0; j < NUM_ESAMI; j++)
                if(stud->studenti[i]->esami[j] != NULL){

                    //e per ogni esame ne stampo codice e voto (numerico se sostenuto stringa se non ancora sostenuto)
                    printf("\nEsame: %s\n", stud->studenti[i]->esami[j]->codice);

                    if(stud->studenti[i]->esami[j]->voto == 0){
                        printf("Non ancora sostenuto\n\n");
                    }else
                        printf("Voto: %d\n\n", stud->studenti[i]->esami[j]->voto);

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
int aggiungiVoto(struct arr_stud* stud, char* numero_m, char* codice_e, int voto){
    int media=0;

    //ciclo su num matricole e appena ho un riscontro con il numero matricola dato
    for(int i=0; i<stud->count; i++)
        if(stud->studenti[i] != NULL && !strcmp(stud->studenti[i]->numeroMatricola, numero_m)) {

            //ciclo su num esami e se trovo anche qui un riscontro con il codice esame dato
            for(int j=0; j<NUM_ESAMI; j++)
                if(stud->studenti[i]->esami[j] != NULL && !strcmp(stud->studenti[i]->esami[j]->codice, codice_e)){

                    //allora modifico il voto
                    stud->studenti[i]->esami[j]->voto=voto;

                    stud->studenti[i]->mediaEsami = calcolaMedia(stud->studenti[i]);

                    return 0; // e ritorno 0: voto modificato con successo

                }

            return -2; //esame non trovato

        }

    return -1; //matricola non trovata
}

int main()
{
    //dichiaro le struct che contengono i vettori dinamici di puntatori a vettori dinamici di struct
    struct arr_stud matStudenti;

    struct arr_ins matInsegnamenti;

    //inizializzo il primo puntatore a puntatori di vettori dinamici di struct studente
    matStudenti.studenti = (struct studente **) malloc(sizeof(struct studente*));
    matStudenti.count = 0;

    //metto a NULL il primo puntatore a struct studenti del vettore puntato dal puntatore inizializzato prima
    matStudenti.studenti[0] = NULL;

    //inizializzo il primo puntatore a puntatori di vettori dinamici di struct insegnamento
    matInsegnamenti.insegnamenti = (struct insegnamento**) malloc(sizeof(struct insegnamento*));
    matInsegnamenti.count = 0;

    //metto a NULL il primo puntatore a struct insegnamenti del vettore puntato dal puntatore inizializzato prima
    matInsegnamenti.insegnamenti[0] = NULL;

    //variabile ritorno funzioni
    int status;

    //variabili di run del programma
    bool run = true;
    int scelta;

    //variabili temporanee inserimento dati matricola
    char num_mat[20];
    char nome[20];
    char cognome[20];
    char anno_imm[20];

    //variabili temporanee inserimento corso
    char tempCodice[20];
    char tempDesc[50];
    char tempAnnoSomm[20];
    int tempCfu=0;

    //variabile temporanea che mi tiene conto della posizione della matricola che sto inserendo
    int temp_pos=0;

    //variabili temporanee inserimento esami in studente
    char tempCodEsami[500];
    char c;

    //variabili per modificare il voto
    int voto;

    while(run){
        system("cls");
        printf("[1]Aggiungi matricola\n[2]Aggiungi insegnamento\n[3]Mostra matricola\n[4]Modifica voto matricola\n[5]Esci\n\n->");
        rewind(stdin);
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                //inserimento matricola
                system("cls");

                printf("I N S E R I S C I   M A T R I C O L A\n");

                printf("\nInserisci il numero matricola: ");
                rewind(stdin);
                gets(num_mat);

                printf("inserisci il nome: ");
                rewind(stdin);
                gets(nome);

                printf("inserisci il cognome: ");
                rewind(stdin);
                gets(cognome);

                printf("\nInserisci l'anno di immatricolazione': ");
                rewind(stdin);
                gets(anno_imm);

                //(struct arr_stud* stud, char *nome, char* cognome, char* num, char* anno)
                status = aggiungiStudente(&matStudenti, nome, cognome, num_mat, anno_imm);

                if(status == -1){
                    printf("\nErrore realloc()\n");
                    break;
                }else if(status == -2){
                    printf("\nErrore matricola gia' inserita\n");
                    break;
                }else{
                    printf("\nMatricola inserita con successo n. %d\n\n", status);
                    temp_pos = status;
                }


                if(matInsegnamenti.count == 0){
                    printf("\n\nNessun corso disponibile.\n\n");
                    break;
                }

                printf("\nCrea il tuo corso di studi\n\n");
                stampaPianiStudi(&matInsegnamenti);

                printf("Inserisci i codici dei corsi a cui desideri partecipare separati da spazio:\n\n->");
                rewind(stdin);

                do {
                    //il primo scanf è bloccante perché il buffer è vuoto
                    scanf("%s", tempCodEsami);
                    //lo scanf si ferma al primo spazio che trova

                    //faccio partire la funzione assegna esame salvandomi il valore di ritorno in status
                    status = assegnaEsameA(matStudenti.studenti[temp_pos], &matInsegnamenti, tempCodEsami);

                    //se ritorno -2 allora l'esame non esiste, quindi lo comunico
                    if(status == -1) printf("\nEsame %s già inserito!\n\n", tempCodEsami);
                    if(status == -2) printf("\nEsame %s non esiste!\n\n", tempCodEsami);

                    //il buffer è ancora pieno, quindi getchar non è bloccante e va direttamente a leggere nel buffer
                    c = getchar();

                    //e cicla finché il getchar non legge il carattere invio
                } while (c != '\n');

                break;

            case 2:
                //inserimento insegnamento
                system("cls");

                printf("I N S E R I S C I   C O R S O\n\n");

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
                status = aggiungiInsegnamento(&matInsegnamenti, tempCodice, tempDesc, tempAnnoSomm, tempCfu);

                if(status == -2){
                    printf("\nErrore: insegnamento gia' inserito\n");
                }else if(status == -1){
                    printf("\nErrore: realloc() non andata a buon fine.\n");
                }else
                    printf("\nInsegnamento inserito con successo!");

                break;

            case 3:
                //stampa matricola
                system("cls");

                printf("C E R C A   M A T R I C O L A\n\n");

                //prendo in input il numero matricola
                printf("Numero matricola da cercare: ");
                rewind(stdin);
                gets(num_mat);

                //mi salvo il valore di ritorno di stampaMatricola in status
                status = stampaMatricola(&matStudenti, num_mat);

                //se ritorna -1 allora significa che non ha trovato niente
                if(status == -1) printf("\n\nMatricola %s inesistente\n\n", num_mat);

                break;

            case 4:
                //modificaVoto
                system("cls");

                printf("M O D I F I C A   V O T O\n\n");

                //prendo in input le info necessarie
                printf("Numero Matricola: ");
                rewind(stdin);
                gets(num_mat);

                printf("\n\nCodice Corso: ");
                rewind(stdin);
                gets(tempCodice);

                printf("\n\nVoto assegnato: ");
                rewind(stdin);
                scanf("%d", &voto);

                //chiamo la funzione aggiungiVoto su status
                status = aggiungiVoto(&matStudenti, num_mat, tempCodice, voto);

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
                run = false;
                break;
            default:
                system("cls");
                printf("\ninput errato\n");
        }
        system("pause");
    }
    return 0;
}
