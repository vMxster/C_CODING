#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* --- TESTO ESERCIZIO ---
 * Indovina il continente:
 * In questo gioco, il computer visualizza una coppia di coordinate generata in maniera random sullo schermo per un
 * breve periodo di tempo.
 * Il giocatore deve indovinare a quale continente appartiene la coppia di coordinate generate;
 * fino a quando l'utente indovina il gioco prosegue con la generazione di una nuova coppia di coordinate.
 * L'obiettivo è quello di continuare il processo il più a lungo possibile.
 * Al termine del gioco il programma calcolerà un punteggio ottenuto quantomeno sulla base del numero di iterazioni
 * eseguite e inviterà il giocatore a giocare di nuovo.
 * N.B.: i margini che definiscono i confini dei vari continenti sono decisi da voi
 */

#define XY_MAX 100
int main() {
    //dichiaro le mie variabili
    int x, y, conta=0;
    int continenti;
    int input;
    char c;
    bool running=true;
    bool play=true;
    srand(time(NULL));
	do{
	    do {
	        //genero le coordinate random da stampare
	        //num = (rand() % (upper - lower + 1)) + lower;
	        x = rand() % XY_MAX + 1;
	        y = rand() % XY_MAX + 1;
	        printf("%d, %d", x, y);
	
	        sleep(2); //fermo il programma 2 secondi, dopodich頣ancello le coordinate e l'utente dovrࠩndovinare
	        system("cls");
	
	        //ciclo finché non ricevo un input accettabile
	        do {
	            printf("\n\nindovina continente, premere: [1] Europa, [2] Asia, [3] America, [4] Oceania, [5] Africa\n");
	            scanf("%d", &input);
	            if (input < 1 || input > 5) printf("\nInput non accettabile, riprova\n\n%d, %d", x, y);
	            fflush(stdin);
	        } while (input < 1 || input > 5);
	
	        /*
	         * Ho preso un piano (0,0) - (100,100) e l'ho diviso in 5 parti
	         * e a ciascuno ho assegnato un nome (Europa, America, Asia, Africa e Oceania.
	         */
	
	        //in base all'input verifico se la risposta è giusta
	        switch (input) {
	            case 1: {
	                //if((num-min)*(num-max) <= 0)
	                if ((x - 0) * (x - 50) <= 0)
	                    if ((y - 50) * (y - 100) <= 0) {
	                        continenti = 1;
	                        break;
	                    }
	            }
	                case 2: {
	                    //if((num-min)*(num-max) <= 0)
	                    if ((x - 50) * (x - 100) <= 0)
	                        if ((y - 50) * (y - 100) <= 0)
	                            continenti = 2;
	                    break;
	                }
	                case 3: {
	                    //if((num-min)*(num-max) <= 0)
	                    if ((x - 0) * (x - 50) <= 0)
	                        if ((y - 25) * (y - 50) <= 0)
	                            continenti = 3;
	                    break;
	                }
	                case 4: {
	                    //if((num-min)*(num-max) <= 0)
	                    if ((x - 50) * (x - 100) <= 0)
	                        if ((y - 25) * (y - 50) <= 0)
	                            continenti = 4;
	                    break;
	                }
	                case 5: {
	                    //if((num-min)*(num-max) <= 0)
	                    if ((x - 0) * (x - 100) <= 0)
	                        if ((y - 0) * (y - 25) <= 0)
	                            continenti = 5;
	                    break;
	                }
	                default: {
	                    printf("\nerrore, input non accettabile\n");
	                }
	            }
	
	                //se l'input era corretto aumento il punteggio
	                if (input == continenti) {
	                    conta++;
	                } else running = false; //altrimenti esco dal ciclo
	
	        }while (running);
	
	    //e stampo i risultati
	    printf("\n\npunteggio totale: %d", conta);
	    do{
	    	printf("\n\nVuoi continuare a giocare? [y]Si [n]No\n->");
	    	scanf("%c", &c);
	    	fflush(stdin);
		}while(c!='y' && c!='n');
		
		//se l'utente vuole continuare a giocare oppure no
		if(c == 'n') play=false;
		
		//resetto il punteggio
		conta=0;
		system("cls");
	    
	}while(play);
    return 0;
}
