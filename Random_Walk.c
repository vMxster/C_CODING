#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

//grandezze matrice
#define MAX_X 10
#define MAX_Y 10

/* --- TESTO DELL'ESERCIZIO ---
 * Scrivete un programma che generi una “passeggiata aleatoria” (random walk) in un array bidimensionale di dimensione 10×10.
 * L’array sarà riempito di caratteri (inizialmente da punti). Il programma dovrà muoversi di elemento in elemento spostandosi
 * ogni volta di un passo in direzione su, giù, destra o sinistra. Gli elementi visitati andranno etichettati con le lettere
 * dalla A alla Z, nell’ordine in cui vengono visitati. E’ importante controllare ad ogni passo che la passeggiata non esca dall’array
 * e che non ritorni su posizioni già visitate. Quando si verifica una di queste condizioni, provare le altre direzioni.
 * Se tutte e quattro le direzioni sono bloccate, il programma deve terminare.
 *
 * --- ESEMPIO ---
 *
 * A . . . . . . . . .
 * B C D . . . . . . .
 * . F E . . . . . . .
 * H G . . . . . . . .
 * I . . . . . . . . .
 * J . . . . . . . Z .
 * K . . R S T U V Y .
 * L M P Q . . . W X .
 * . N O . . . . . . .
 * . . . . . . . . . .
 */

void stampa(char g[MAX_Y][MAX_X]){
    for(int i=0; i<MAX_Y; i++){
        for(int j=0; j<MAX_X; j++){
            printf("%c  ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void movimento(char g[MAX_Y][MAX_X], int scelta, int* x, int* y, char* letter) {
    switch(scelta){
        case 0:{ // destra
            g[*y][*x] = *letter;
            (*x)++;
            break;
        }
        case 1:{ // sinistra;
            g[*y][*x] = *letter;
            (*x)--;
            break;
        }
        case 2:{ // sopra
            g[*y][*x] = *letter;
            (*y)--;
            break;
        }
        case 3:{ //sotto
            g[*y][*x] = *letter;
            (*y)++;
            break;
        }
    }
    (*letter)++;
}

int main() {

    //array[righe][colonne]
    srand(time(NULL));
    int righe=0, colonne=0; // coordinate
    int* y = &righe; int* x = &colonne; // puntatori a coordinate
    char c = 'A'; // lettera d'inizio
    char* letter = &c; // puntatore alla lettera d'inizio

    char ground[MAX_Y][MAX_X]; // dichiaro il campo

    //inizializzo il campo
    for(int i=0; i<MAX_Y; i++)
        for(int j=0; j<MAX_X; j++)
            ground[i][j]='.';

    int move=0; // indicatore mossa
    bool acceptable=false; // booleano che mi indica se la mossa generata random è fattibile

    while(*letter<='Z'){ // ciclo finché non arrivo alla Z

        _sleep(1000); // aspetto 1 secondo dopo ogni passo
        acceptable=false; // rimetto il bool a false

        do{
            move = rand()%4; //genero una mossa casuale da ciclare finché non diventa accettabile

            switch(move){

                //per ogni mossa controllo se non esce dall'array e se non ci sono già stato
                case 0:{ // destra
                    if((*x+1)<MAX_X && ground[*y][(*x)+1] == '.') acceptable=true;
                    break;
                }

                case 1:{ // sinistra;
                    if((*x)-1>=0 && ground[*y][(*x)-1] == '.') acceptable=true;
                    break;
                }

                case 2:{ // sopra
                    if((*y)-1>=0 && ground[(*y)-1][*x] == '.') acceptable=true;
                    break;
                }

                case 3:{ // sotto
                    if((*y)+1<MAX_Y && ground[(*y)+1][*x] == '.') acceptable=true;
                    break;
                }
            }

            // controllo se tutte le direzioni sono bloccate:
            if( (ground[*y][(*x)+1] != '.')  &&  (ground[*y][(*x)-1] != '.')  &&  (ground[(*y)+1][*x] != '.')  && (ground[(*y)-1][*x] != '.')){

                //se le vie sono tutte bloccate metto l'ultima lettera sul punto su cui mi trovo ora
                ground[*y][*x]=*letter;

                printf("mossa successiva: X: %d - Y: %d - LETTERA: %c\n\n\n", *x, *y, *letter);  // stampa di debug per le mosse

                //faccio l'ultima stampa della mappa e metto anche la lettera a cui sono arrivato
                stampa(ground);

                //c'è la probabilità che sia arrivato proprio all'ultima lettera, in caso controllo se dare il game over oppure no
                if( !(*letter=='Z') )
                    printf("\n\nMi sono morso la coda, ero arrivato alla lettera %c", *letter);

                //termino il programma
                return 0;
            }
        }while(!acceptable); // appena trovo una mossa accettabile esco dal ciclo interno e la mando in esecuzione

        movimento(ground, move, x, y, letter);

        printf("mossa successiva: X: %d - Y: %d - MOSSA: %d - LETTERA: %c\n\n\n", *x, *y, move, *letter); // stampa di debug per le mosse

        //poi ristampo nuovamente la mappa aggiornata
        stampa(ground);
    }

    return 0;
}
