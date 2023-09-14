#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

/* --- TESTO DEL PROGRAMMA ---
 * Scrivere un programma che legga da tastiera un testo terminato dal carattere # e poi stampi 
 * le statistiche relative al numero di spazi, al numero di caratteri di nuova linea, 
 * al numero di caratteri letti, al numero di quelli maiuscoli, etc. utilizzando almeno una 
 * volta tutte le funzioni dell’header ctype.h
*/

int main() {
	//INVIO 13
	char c;
	//contatori vari
	int caratteri=0;
	int upper_Case=0;
	int lower_Case=0;
	int numeri=0;
	int invio=0;
	int spazio=0;
	
	//ciclo finché c è diverso da '#'
	while(c!='#'){
		caratteri++; // conto i caratteri totali
		
		//leggo un carattere
		c = getch();
		
		//stampo ciò che metto in input
		if(c==13) printf("\n");
		printf("%c", c);
		
		//controllo e conto
		if(isdigit(c)) numeri++;
		if(isspace(c)) spazio++;
		if(isupper(c)) upper_Case++;
		if(islower(c)) lower_Case++;
		if(c==13) invio++;	
	}
	//stampo i risultati
    printf("\n\nNUMERI: %d\nSPAZI: %d\nMAIUSCOLE: %d\nMINUSCOLE: %d\nINVIO: %d\nCARATTERI: %d", numeri, spazio, upper_Case, lower_Case, invio, caratteri);
    return 0;

}
