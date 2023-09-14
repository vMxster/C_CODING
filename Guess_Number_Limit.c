#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define PULISCI system("cls")

/* --- TESTO DEL PROGRAMMA ---
 * L’utente pensa ad un numero e il computer lo deve indovinare compiendo le seguenti operazioni.
 *
 * L’utente fissa un intervallo entro cui generare il valore da indovinare (min, max). Se i valori inseriti non rispettano
 * il vincolo 0<min≤max, l’operazione di lettura va ripetuta
 *
 * L’utente pensa ad un numero compreso tra min e max.
 *
 * Il programma cerca di indovinare la scelta dell’utente e propone un numero. A seconda della situazione l’utente deve
 * dire al programma se:
 *     - il numero da indovinare è più piccolo;
 *     - il numero da indovinare è più grande;
 *     - ha indovinato.
 *
 *      Scrivere una versione di programma in cui non c'è limite al numero di tentativi e scriverne un'altra in cui invece viene posto tale limite.
 *
 *      Il programma deve stampare il numero di tentativi.
 */

int main() {

    //dichiaro le mie variabili
    int min, max, tentativi;
    int x, scelta=0;
    int cont=0;
    bool indovinato = false;
    //inizializzo il seme per generare un numero random
    srand(time(NULL));

    //ciclo finché non ottengo dei valori accettabili per il range di valori
    do{
        (cont!=0) ? printf("Errore, input non accettabile, riprova (min max nTentativi):\n->") :
                    printf("Inserisci il valore minimo, il valore massimo ed il numero di tentativi:\n->");
        scanf("%d %d %d", &min, &max, &tentativi);
        fflush(stdin);
        cont++;
    }while(min<1 || min > max || tentativi<1); //continuo a ciclare finché: min < 1 OPPURE min > max OPPURE tentativi <1

    PULISCI; //pulisco il terminale

    printf("Ok, ora provo ad indovinare il tuo numero\n\n");

    cont=0; //riutilizzo il contatore che avevo già usato

    while(tentativi>0){ // ciclo finché i tentativi sono maggiori di 0

        //FORMULA number = (rand() % (upper - lower + 1)) + lower
        x = (rand() % (max - min + 1)) + min; //genero il numero random tra i valori "min" e "max" compresi

        printf("\n\nHo pensato a %d,\n\nRispetto a %d il numero da indovinare e':\n\n[1] Giusto [2] Piu' grande [3] Piu' piccolo\n\n", x, x);
        scanf("%d", &scelta);
        fflush(stdin);

        switch(scelta){ //faccio uno switch sulla variabile "scelta"

            case 1:{
                tentativi=0; // se vale 1 allora significa che ho indovinato e metto a 0 i tentativi
                indovinato = true; //visto che ho indovinato metto il booleano "indovinato" a true
                break;
            }

            case 2:{       // se vale 2 allora significa che rispetto a x il numero pensato dall'utente è più grande
                min=x+1;   // quindi rinnovo il valore minimo e lo metto a x+1 così elimino anche il numero appena uscito
                printf("\n\nIl nuovo intervallo e': %d - %d\n", min, max);
                break;
            }

            case 3:{       // se vale 3 allora significa che rispetto a x il numero pensato dall'utente è più piccolo
                max=x-1;   // quindi rinnovo il valore massimo e lo metto a x-1 così elimino anche il numero appena uscito
                printf("\n\nIl nuovo intervallo e': %d - %d\n", min, max);
                break;
            }

            default:{ //se l'input non è accettabile mando di default una stringa che lo avverte dell'errore e il ciclo continua
                printf("\nErrore, le scelte possibili sono [1]giusto [2]piu' grande [3]piu' piccolo\n");
            }
        }
        cont++;
        tentativi--;
    }

    /*
     * esco dal ciclo se indovino il numero oppure se termino i tentativi
     * in base a ciò scelgo l'output finale:
     */
    indovinato ? printf("\n\n\nHo indovinato il tuo numero con %d tentativi", cont) :
                 printf("\n\n\nHo terminato i tentativi, ho perso...");

    return 0;
}
