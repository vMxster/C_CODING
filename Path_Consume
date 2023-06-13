#include <stdio.h>
#define cost 0.425 //dichiaro la costante che mi serve per la conversione

/* TESTO DEL PROGRAMMA
 * Scrivere un programma che chieda all'utente di inserire il numero di miglia percorse e il numero di galloni di
 * benzina consumati. Il programma deve poi calcolare e visualizzare il valore di miglia per gallone usando due cifre decimali.
 * Successivamente, il programma deve convertire il valore miglia per gallone in litri per 100 km, come si usa per
 * esprimere il consumo di carburante in Europa, e visualizzare il risultato, usando 3 cifre decimali. Usare costanti
 * simboliche per i due fattori di conversione. Commentare adeguatamente il programma.
 */

int main() {

    //inizializzo le variabili

    float mi, gal, consum, consum_kml, consum100km = 0;

    //acquisisco il valore di miglia
    printf("Inserire il numero di miglia: \n");
    scanf("%f", &mi);

    //acquisisco la quantità di galloni consumati
    printf("Inserire la qunatita' di galloni consumati: \n");
    scanf("%f", &gal);

    //calcolo il consumo in miglia/gallone e stampo a video
    consum = mi/gal;
    printf("\nConsumo in mi/gal %.2f", consum);

    //uso la costante per la conversione mi/gal a km/l
    consum_kml = consum*cost;

    //converto da km/l in l*100km
    consum100km = 100/consum_kml;
    printf("\n \nConsumo ogni 100km %.3f litri", consum100km);
    return 0;
}
