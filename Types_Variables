#include <stdio.h>
#include <limits.h>
#include <float.h>

/* TESTO DEL PROGRAMMA
 Scrivere un programma C che dichiari una variabile per ogni tipo studiato
 (usando anche i qualificatori short, long, signed e unsigned),
 ne stampi il valore e l’occupazione di memoria in byte. Utilizzare TUTTI gli argomenti della
 funzione printf() studiati e TUTTE le diverse varianti
 (modificatore, campoMinimo, precisione, modificatoreLunghezza).
 Per ogni chiamata alla funzione printf(), mostrare a video anche il numero di caratteri
 che quest’ultima ha stampato. Stampare inoltre il valore minimo e il valore massimo ammissibile
 per ogni tipo utilizzato. Commentare adeguatamente il programma.
*/

int main() {

    //dichiarazione e assegnazione variabili
    char a = 'L';
    signed char b = 'R';
    unsigned char c = 'W';
    int d = 10;
    short int e = 80;
    unsigned short int f = 42;
    unsigned int g = 17482;
    long int h = 235443;
    unsigned long int i = 89674534;
    float l = 675.54;
    double m = 34565.3452;
    long double n = 65454.244538;
    long long o = 95023;
    unsigned long long p = 19492;

    /*
     * Visto che la funzione printf ritorna l'int che equivale al numero di caratteri stampati quando viene chiamata,
     * ne innesto due in cui il primo serve solo a stampare l'int di ritorno del secondo (al suo interno).
     * Ho utilizzato questo metodo per tutti i tipi listati:
     */

    // CHAR - VARIANTE DI PRINTF %-10c
    printf("%d\n",
           printf("Nome Variabile: a, Tipo: %s, Valore: %-10c, Minimo: %d, Massimo: %d, Byte Occupati: %d, Caratteri Stampati: ", "char", a, CHAR_MIN, CHAR_MAX, sizeof(char)));

    // SIGNED CHAR - VARIANTE DI PRINTF %hhc
    printf("%d\n",
           printf("Nome Variabile: b, Tipo: %s, Valore: %hhc, Minimo: %d, Massimo: %d, Byte Occupati: %d, Caratteri Stampati: ", "signed char", b, SCHAR_MIN, SCHAR_MAX, sizeof(unsigned char)));

    // UNSIGNED CHAR - VARIANTE DI PRINTF %hhc
    printf("%d\n",
           printf("Nome Variabile: c, Tipo: %s, Valore: %hhc, Minimo: %d, Massimo: %u, Byte Occupati: %d, Caratteri Stampati: ", "unsigned char", c, 0, UCHAR_MAX, sizeof(unsigned char)));

    //INT - VARIANTE DI PRINTF %+10d
    printf("%d\n",
           printf("Nome Variabile: d, Tipo: %s, Valore: %+10d, Minimo: %d, Massimo: %d, Byte Occupati: %d, Caratteri Stampati: ", "int", d, INT_MIN, INT_MAX, sizeof(int)));

    //SHORT INT - VARIANTE DI PRINTF %3d
    printf("%d\n",
           printf("Nome Variabile: e, Tipo: %s, Valore: %3d, Minimo: %d, Massimo: %d, Byte Occupati: %d, Caratteri Stampati: ", "short int", e, SHRT_MIN, SHRT_MAX, sizeof(short int)));

    //UNSIGNED SHORT INT - VARIANTE DI PRINTF %hd
    printf("%d\n",
           printf("Nome Variabile: f, Tipo: %s, Valore: %hd, Minimo: %d, Massimo: %u, Byte Occupati: %d, Caratteri Stampati: ", "unsigned short int", f, 0, USHRT_MAX, sizeof(unsigned short int)));

    //UNSIGNED INT - VARIANTE DI PRINTF % u
    printf("%d\n",
           printf("Nome Variabile: g, Tipo: %s, Valore: % u, Minimo: %d, Massimo: %u, Byte Occupati: %d, Caratteri Stampati: ", "unsigned int", g, 0, UINT_MAX, sizeof(unsigned int)));

    //LONG INT - VARIANTE DI PRINTF %1d
    printf("%d\n",
           printf("Nome Variabile: h, Tipo: %s, Valore: %1d, Minimo: %d, Massimo: %d, Byte Occupati: %d, Caratteri Stampati: ", "long int", h, LONG_MIN, LONG_MAX, sizeof(long int)));

    //UNSIGNED LONG INT - VARIANTE DI PRINTF %lu
    printf("%d\n",
           printf("Nome Variabile: i, Tipo: %s, Valore: %lu, Minimo: %d, Massimo: %u, Byte Occupati: %d, Caratteri Stampati: ", "unsigned long int", i, 0, ULONG_MAX, sizeof(unsigned long int)));

    //FLOAT - VARIANTE DI PRINTF %0.2f
    printf("%d\n",
           printf("Nome Variabile: l, Tipo: %s, Valore: %0.2f, Minimo: %.2f, Massimo: %.2f, Byte Occupati: %d, Caratteri Stampati: ", "float", l, FLT_MIN, FLT_MAX, sizeof(float)));

    //DOUBLE - VARIANTE DI PRINTF %7.4f
    printf("%d\n",
           printf("Nome Variabile: m, Tipo: %s, Valore: %7.4f, Minimo: %e, Massimo: %e, Byte Occupati: %d, Caratteri Stampati: ", "double", m, DBL_MIN, DBL_MAX, sizeof(double)));

    //LONG DOUBLE - VARIANTE DI PRINTF %-9.5Lf
    printf("%d\n",
           printf("Nome Variabile: n, Tipo: %s, Valore: %-9.5Lf, Minimo: %Le, Massimo: %Le, Byte Occupati: %d, Caratteri Stampati: ", "long double", n, LDBL_MIN, LDBL_MAX, sizeof(long double)));

    //LONG LONG - VARIANTE DI PRINTF % lld
    printf("%d\n",
           printf("Nome Variabile: o, Tipo: %s, Valore: % lld, Minimo: %lld, Massimo: %lld, Byte Occupati: %d, Caratteri Stampati: ", "long long", o, LLONG_MIN, LLONG_MAX, sizeof(long long)));

    //UNSIGNED LONG LONG - VARIANTE DI PRINTF % llu
    printf("%d\n",
           printf("Nome Variabile: p, Tipo: %s, Valore: % llu, Minimo: %d, Massimo: %llu, Byte Occupati: %d, Caratteri Stampati: ", "unsigned long long", p, 0, ULLONG_MAX, sizeof(long long)));

    return 0;
}

