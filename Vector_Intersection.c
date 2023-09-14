#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define A_MAX 4
#define B_MAX 3

/* --- TESTO DELL'ESERCIZIO ---
 * Siano dati due vettori di interi di lunghezza differente. Scrivere un programma C che inserisca i valori da tastiera
 * e che lo faccia anche generandoli in maniera pseudo-casuale. Il programma deve poi generare un terzo vettore
 * contenente l’intersezione tra i due vettori di input. Implementare sia la variante in cui le ripetizioni di un elemento nei
 * vettori di input vengono riportate anche nel vettore risultato, sia quella in cui le ripetizioni non sono inserite nel risultato.
 * Implementare poi la generazione di un quarto vettore contenente l'unione dei due vettori di input. Il programma deve inoltre
 * stampare gli indirizzi di memoria occupati dagli elementi dei vettori e la loro dimensione totale in termini di numero di byte.
 */

void stampa(int* vettore, int l){
    int i;
    for(i=0; i<l; i++)
        printf("%d, ", vettore[i]);
    printf("\n");
}

bool esiste(int* vettore, int l, int x){
    for(int i=0; i<l; i++)
        if(vettore[i]==x) return true;
    return false;
}

int main() {
    int A[A_MAX]; int B[B_MAX];
    int A_RAND[A_MAX]; int B_RAND[B_MAX];
    int i;

    //inizializzazione pseudo-casuale:
    srand(time(NULL));

    printf("DUE VETTORI GENERATI RANDOM:\n");

    for(i=0; i<A_MAX; i++)
        A_RAND[i]=rand()%100+1; //riempio con valori da 1 a 100
    for(i=0; i<B_MAX; i++)
        B_RAND[i]=rand()%100+1; //riempio con valori da 1 a 100

        printf("Primo: ");
        stampa(A_RAND, A_MAX);
        printf("\nSecondo:");
        stampa(B_RAND, B_MAX);

    //inizializzazione da input:
    int appoggio;
    printf("\n\nPrimo Vettore:\n");
    for(i=0; i<A_MAX; i++){
        printf("\nInserisci il %d elemento:\n->", i+1);
        scanf("%d", &appoggio);
        A[i]=appoggio;
        fflush(stdin);
    }
    printf("\nSecondo Vettore:\n");
    for(i=0; i<B_MAX; i++){
        printf("\nInserisci il %d elemento:\n->", i+1);
        scanf("%d", &appoggio);
        B[i]=appoggio;
        fflush(stdin);
    }


    stampa(A, A_MAX);
    printf("\n\n\n");
    stampa(B, B_MAX);

    //intersezione di vett1 e vett2 - Variante senza ripetizioni:
    int j; int MIN; int C_cont=0;
    bool found;
    MIN = (A_MAX<B_MAX) ? A_MAX : B_MAX; //la grandezza dell'intersezione senza ripetizioni sarà minore o uguale al vettore più piccolo
    int C[MIN];

    printf("\n\nINTERSEZIONE SENZA RIPETIZIONI:\n");

    for(i=0; i<A_MAX; i++) {
        found=false;
        for (j = 0; j < B_MAX && !found; j++)
            if (A[i] == B[j]) found=true; //appena ho un riscontro positivo found diventa true altrimenti rimane false

        for(j=0; j<C_cont && found; j++) //se found == true allora ciclo per vedere se il valore è già presente
            if(A[i]==C[j]) found=false; // se è già presente found ritorna a false

        if(found) C[C_cont++]=A[i]; //altrimenti se non è presente lo metto e incremento il contatore dell'array finale
    }

    stampa(C, C_cont);

    //intersezione con ripetizioni
    printf("\n\nINTERSEZIONE CON RIPETIZIONI:\n");

    /*
     * Ho implementato un array appoggio in cui mi segno il numero della cella del secondo vettore che contiente il valore
     * risultato uguale a quello pescato dal primo. Una volta che ho finito di confrontarli tutti apro un ciclo for
     * che riempie il vettore risultato con i valori riscontrati.
     */
    int vett_app[A_MAX+B_MAX]; //vettore appoggio (dimensione per essere sicuro somma tra le dimensioni di A e B)
    int cont_v_app = 0; //conto quante volte metto un nuovo valore nell'array d'appoggio.
    int C_2[A_MAX+B_MAX]; //vettore finale in cui andrò mettere il risultato

    for(i=0; i<A_MAX; i++){ //ciclo principale
        found=false;
        for(j=0; j<B_MAX && !found; j++)
            // controllo se i due valori che pesco sono congruenti e se il numero di quella cella l'ho già segnato nell'appoggio
            if( (A[i] == B[j])  &&  !(esiste(vett_app, cont_v_app, j)) ){
                found=true; // se le condizioni sono rispettate metto found a true così passo al prossimo numero del primo array
                vett_app[cont_v_app]=j; //mi segno il numero della cella
                cont_v_app++; // incremento il contatore dell'array d'appoggio
            }
    }

    //ora devo solo riportare i valori nell'array finale
    for(i=0; i<cont_v_app; i++)
        C_2[i] = B[vett_app[i]];

    stampa(C_2, cont_v_app);

    //unione tra A e B:

    printf("\nUNIONE TRA A E B:\n\n");

    int C_3[A_MAX+B_MAX]; // l'unione per sicurezza la faccio grande tanto quanto la somma dei due vettori

    for(i=0; i<A_MAX; i++)
        C_3[i]=A[i];
    for(i=0; i<B_MAX; i++)
        C_3[i+A_MAX]=B[i];

    stampa(C_3, A_MAX+B_MAX);

    return 0;
}
