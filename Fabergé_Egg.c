#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 10

/*
 * --- TESTO DELL'ESERCIZIO ---
 *
 * COME GENERARE UN UOVO DI FABERGE:
 *
 * Pickover usò come funzione la somma di due sinusoidi, una dipendente da x e l’altra da y, con stessa frequenza ma diverse fasi;
 * tenne fissa la griglia di punti sul piano cartesiano, facendo corrispondere direttamente i valori di j e i alle loro ascisse e
 * ordinate, rispettivamente.
 *
 * Per costruire i campioni di una di queste funzioni, procediamo così:
 *
 * prendiamo tre numeri “reali” (in virgola mobile): ω (la pulsazione) scelto a caso nell’intervallo [0.15, 0.80], φ e ψ (le fasi)
 * scelti, ancora casualmente, nell’intervallo [0.0, 1.0] (così suggerisce Pickover, ma si può usare [0, 2π]);
 *
 * per ogni i e j, calcoliamo Fji = sin(ω∙i + φ) + sin(ω∙j + ψ).
 * A questo punto scegliamo a caso un altro numero reale μ nell’intervallo [0.0, 20.0] e un numero intero β tra 128 e 256 e
 * infine calcoliamo m(i, j) = floor ((β + μ)∙(1.0 + Fji / 2.0)) mod β
 *
 * Otteniamo così una matrice m(i, j) di interi in [0, β − 1]; poi ripetiamo questi passi
 * altre due volte, per avere tre di queste matrici da usare come componenti per i tre colori di base dell’immagine finale.
 */

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

/*
 * funzione che mi stampa una matrice a partire da una x data.
 * visto che non ho ben compreso l'output finale del programma
 * mi sono limitato a colorare un segnaposto (in questo caso il carattere 0)
 * con la funzione cambiaColore: in base al valore della matrice in quella posizione, setColor
 * mi colora l'output che sto per fare.
 */
void stampaMat(int mat[MAX][MAX], int x){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            cambiaColore(mat[i][j]); //chiamo cambiaColore col valore calcolato della matrice in (i,j)
            spostaCursore(x+(j*2), i); //partendo dalla x data mi sposto verticalmente di i e orizzontalmente di x+(j*2)
            printf("O");
        }
    }
    cambiaColore(7); // finito di stampare rimetto il bianco come colore
}

void generaMatrice(int mat[MAX][MAX],float omega, float phi, float psi){
    float mi;
    short int beta;

    double temp;
    int temp2;

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            //Fji = sin(ω∙i + φ) + sin(ω∙j + ψ)
            temp= sin((omega*i)+phi) + sin((omega*j)+psi);

            //mi scelto nell’intervallo [0.0, 20.0]
            mi = (rand()%201)/10;

            //beta scelto tra 128 e 256
            beta = (rand()%(256 - 128 + 1))+128;

            //m(i, j) = floor ((β + μ)∙(1.0 + Fji / 2.0)) mod β
            temp2 = floor((beta+mi)*(1+temp/20));
            mat[i][j] = temp2%beta;
        }
    }
}

int main() {
    float omega; // pulsazione
    float phi; // fase 1
    float psi; // fase 2

    srand(time(NULL));

    //creo le tre matrici
    int mat1[MAX][MAX];
    int mat2[MAX][MAX];
    int mat3[MAX][MAX];

    //(rand() % (upper - lower + 1)) + lower;

    //omega scelto a caso nell’intervallo [0.15, 0.80]
    omega = ((rand()%(80-15+1))+15)/100;

    //fasi scelte nell’intervallo [0.0, 1.0]
    phi = (rand()%11)/10;
    psi = (rand()%11)/10;

    //inizializzo le matrici
    generaMatrice(mat1, omega, phi, psi);
    generaMatrice(mat2, omega, phi, psi);
    generaMatrice(mat3, omega, phi, psi);

    nascondiCursore(); //nascondo il cursore solo per un fattore estetico, pressoché inutile

    //stampo le matrici
    stampaMat(mat1,0);
    stampaMat(mat2, 20);
    stampaMat(mat3, 40);

    //riporto il cursore sotto la stampa
    spostaCursore(0, 20);

    system("pause");

    return 0;
}
