#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STR_LUN 200

/*
 * --- TESTO DELL'ESERCIZIO
 *
 * Scrivere un programma che simuli l’“effetto decriptazione dati” presentato nel 1992 nel film Sneakers.
 *
 * Il programma dovrà occuparsi di chiedere all’utente una stringa e di visualizzare in tempi successivi versioni
 * via via più simili alla stringa iniziale.
 */

//funzione colori
void setColor(unsigned short color) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,color);
}

int main() {
    char str1[STR_LUN]; //stringa originale

    bool running = true; //booleano per il ciclo principale

    printf("Scrivi qualcosa: \n->");
    gets(str1); // leggo la stringa di input

    srand(time(NULL)); // inizializzo il seme per il rand

    char str2[STR_LUN]; // stringa da decifrare

    //(rand() % (upper - lower + 1)) + lower;
    // (126-33+1) + 33;
    for(int i=0; i< strlen(str1); i++){ // inizializzo la stringa da decifrare
        if(str1[i]==' '){
            str2[i]=' '; // come nel video, dove trovo spazi metto spazi
        }else
            str2[i]=rand()%(126-33+1) + 33; //altrimenti metto un carattere random
    }

    while(running){
        puts(str1); // mi salvo in prima linea la stringa originale
        printf("\n\n");

        for(int i=0; i< strlen(str2); i++){ //ciclo la stringa da decifrare
            if(str2[i]!=str1[i])  // controllo se a pari valore di i, il carattere è diverso
                str2[i]=rand()%(126-33+1) + 33; // se si lo cambio con uno nuovo random

            if(str2[i]==str1[i]) { //se trovo un carattere che corrisponde lo evidenzio in blue (colore 2) e lo stampo
                setColor(1);
                putchar(str2[i]);
                setColor(7);
            }else
                putchar(str2[i]); //altrimenti lo stampo senza cambiare colore
        }

        if(strcmp(str1, str2)==0){ //se le stringhe sono congruenti metto a false la condizione di ciclo
            running = false;
        } else{ // altrimenti attendo 150 ms e pulisco il terminale
            _sleep(150);
            system("cls");
        }
    }
    printf("\n\n");
    system("pause");
    return 0;
}
