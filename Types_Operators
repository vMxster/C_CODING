#include <stdio.h>
#include <math.h>

/* --- TESTO DEL PROGRAMMA ---
 * Scrivere un programma C che mostri l’utilizzo di tutti gli operatori studiati. Il programma deve inoltre mostrare
 * il comportamento scorretto che si ottiene utilizzando tipi non appropriati alla dimensione delle variabili, quello
 * che si ottiene usando più operatori con side effects all’interno della stessa istruzione, quello che si ottiene quando
 * le regole di conversione implicita sono applicate e quando si supera il range dei valori disponibili per un tipo di dato.
 * Il programma deve poi mostrare l’utilizzo di tutte le funzioni matematiche della libreria math.h.
 */



int main() {
    //dichiarazione variabili
    int A;
    int B;
    int C;

    //chiedo in input i valori delle variabili
    printf("inserisci il valore di A, B e C:\n->");
    scanf("%d %d %d", &A, &B, &C);

    //testo tutti gli operatori relazionali utilizzando l'operatore ternario "?"
    (A>B) ? printf("A e' maggiore di B\n\n") : printf("A non e' maggiore di B\n\n");

    (B<C) ? printf("B e' minore di C\n\n") : printf("B non e' minore di C\n\n");

    (A==B) ? printf("A e' uguale a B\n\n") : printf("A non e' uguale a B\n\n");

    (A!=C) ? printf("A e' diverso da C\n\n") : printf("A non e' diverso da C\n\n");

    (C>=B) ? printf("C e' maggiore o uguale di B\n\n") : printf("C non e' minore o uguale di B\n\n");

    (C<=A) ? printf("C e' minore o uguale ad A\n\n") : printf("C non e' minore o uguale ad A\n\n");

    //il comportamento scorretto che si ottiene utilizzando tipi non appropriati alla dimensione delle variabili
    short int D = 999999;
    printf("Ho assegnato alla mia variabile un tipo inadatto per contenerla, quindi il risultato e': %d", D);

    //il comportamento scorretto che si ottiene usando più operatori con side effects all’interno della stessa istruzione
    int X=3, Y=4;
    X=Y++;
    (X==Y) ? printf("questo non verra' stampato") : printf("\n\nquesto invece sara' stampato");
    X=++Y;
    (X==Y) ? printf("\n\nquesto verra' stampato") : printf("questo invece non sara' stampato");

    //il comportamento scorretto che si ottiene quando le regole di conversione implicita sono applicate
    int G;
    float M=1.2, H = 9.2;
    G=M*H; //G è un int, mettendoci dentro il risultato di una moltiplicazione tra float, si arrotonda all'unità, perdendo una porzione di dato.
    printf("\n\nValore di M: %d", G);

    //il comportamento scorretto che si ottiene quando si supera il range dei valori disponibili per un tipo di dato
    short int Z=20000;
    Z*=Z;
    printf("\n\nSupero il range di valori disponibili per lo short int: %d\n\n", Z);

    //operatori compatti
    int somma=31;
    somma+=23;
    printf("31+23 = %d\n\n", somma);

    //esempio di operatori bitwise
    int numero1 = 38;
    int numero2 = 26;
    int ris_or;
    ris_or = numero1 | numero2;
    printf("il risultato di %d OR %d vale %d\n\n", numero1, numero2, ris_or);

    //operatori logici
    int num1 = 5;
    // && == AND, entrambe le condizioni dell'if devono essere soddisfatte
    if(num1 < 10 && num1 > 3) printf("%d e' compreso nell'intervallo 3 - 10\n", num1);
    // || == OR, almeno una delle due condizioni deve essere soddisfatta. In questo caso l'ho negata con ! quindi
    // si traduce come "se num1 non è maggiore di 10 OR num1 non è minore di 3"
    if(!(num1 > 10 || num1 < 3)) printf("%d non e' maggiore di 10 e nemmeno minore di 3\n\n", num1);


    //operatori aritmetici
    //+ - / * %
    int var1, var2, ris;
    var1=73; var2=63;
    ris = var1+var2;
    printf("%d e' il risultato della somma.\n", ris);
    ris = var1-var2;
    printf("%d e' il risultato della sottrazione.\n", ris);
    ris = var1/var2;
    printf("%d e' il risultato della divisione.\n", ris);
    ris = var1*var2;
    printf("%d e' il risultato della moltiplicazione.\n", ris);
    ris = var1 % var2;
    printf("%d e' il resto della divisione.\n", ris);

    //funzioni di math.h
    double T = 251.46487;
    printf("\n\n%.5f alla seconda vale: %.5f,\n", T, pow(T,2)); //potenza
    printf("La radice quadrata di %.5f vale: %.5f\n", T, sqrt(T)); //radice quadrata
    printf("Il seno di %.5f vale: %.5f\n", T, sin(T)); //seno
    printf("Il coseno di %.5f vale: %.5f\n", T, cos(T)); //coseno
    printf("la tangente di %.5f vale: %.5f\n", T, tan(T)); //tangente
    printf("Il logaritmo in base 10 di %.5f vale: %.5f\n", T, log10(T)); //logaritmo


    return 0;
}
