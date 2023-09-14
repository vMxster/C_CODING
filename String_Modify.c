#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

/*
 * --- TESTO DELL'ESERCIZIO ---
 * Scrivere un programma C che prenda da riga di comando una frase e stampi a video la frase così modificata.
 * Per ogni parola in ingresso:
 *
 * 1. Spostare la prima lettera alla fine.
 *
 * 2. Aggiungere le lettere "an" alla fine di ogni parola di tre lettere o meno, e "o" alla fine di ogni ALTRA parola.
 *
 * 3. Fare in modo che la nuova prima lettera della parola corrisponda al tipo (minuscola/maiuscola) della vecchia prima
 * lettera della parola. Rendete minuscola la lettera che è stata spostata, se non è la prima lettera. Non modificare il
 * tipo (minuscola/maiuscola) delle altre lettere.
 *
 * 4. Ogni carattere non isalpha deve rimanere inalterato.
 *
 * 5. Una parola si considera separata dalle altre quando c'è uno spazio bianco o un carattere non isalpha
 *
 * Ad esempio, data come input la frase:
 *
 * I *REALLY* like Yale's course-selection procedures.
 *
 * il programma deve stampare in output:
 *
 * Ian *EALLYro* ikelo Aleyo'san ourseco-electionso rocedurespo.
 */

#define MAX_PAROLA 1000

int altera(char* parola){

    //se la stringa è lunga 0 allora esco subito
    if(strlen(parola) == 0) return -1;

    //mi segno l'attuale prima lettera prima di cambiarla di posizione
    char tempChar = parola[0];

    //se la parola è lunga almeno 2 carattere
    if(strlen(parola)>1){

        //la prima lettera diventa l'ultima
        for(int k=1; k<= strlen(parola); k++){
            //mi son salvato la prima lettera, shifto tutto verso sinistra
            parola[k - 1] = parola[k];
        }
        //e poi la vecchia prima diventa l'ultima
        parola[strlen(parola)] = tempChar;

        //la nuova prima lettera deve essere dello stesso "tipo" della vecchia prima lettera
        parola[0] = (islower(tempChar)) ? tolower(parola[0]) : toupper(parola[0]);

        //la lettera spostata deve essere minuscola
        parola[strlen(parola)-1] = tolower(parola[strlen(parola)-1]);
    }

    //se la parola è lunga meno di 3 metto "an" alla fine, altrimenti "o" alla fine
    if(strlen(parola) > 3){
        strcat(parola, "o");
    }else{
        strcat(parola, "an");
    }

    return 0;
}

//funzione che mi legge una stringa
void leggiStringa(char *testo, int max_caratteri) {
    int ch;
    int i = 0;
    max_caratteri--;//necessario per gestire \0
    while ((ch = getchar()) != '\n' && i < max_caratteri) {
        testo[i] = ch;
        i++;
    }
    testo[i] = '\0';
}

int main() {

    char leggo[MAX_PAROLA];
    char parola[MAX_PAROLA+3]; //per assurdo se ho una parola lunga max_parola e la mando in esecuzione esco dal limite

    printf("Inserisi la frase da trasformare\n->");
    rewind(stdin);
    leggiStringa(leggo, MAX_PAROLA);

    printf("\n\n");

    int res = 0;

    int j=0;
    for(int i=0; i < strlen(leggo)+1; i++){

        //se sono arrivato al terminatore di stringa di "leggo" allora termino l'ultima stringa e mando in esecuzione.
        //al massimo è vuota.
        if(leggo[i] == '\0'){
            parola[j] = '\0';
            res = altera(parola);
            if(res == 0) printf("%s", parola);
            break;
        }

        //se leggo(i) è una lettera la inserisco dentro parola e aumento j
        if(isalpha(leggo[i])){
            parola[j] = leggo[i];
            j++;

        //altrimenti
        }else{

            //se leggo qualcosa che non è una lettera termino la parola e la mando in lavorazione.
            parola[j] = '\0';
            res = altera(parola);
            //una volta lavorata se tutto è andato bene la stampo
            if(res == 0) printf("%s", parola);
            // e poi stampo il carattere (non lettera) che ho letto che mi ha fatto terminare la parola
            printf("%c", leggo[i]);
            //e rimetto j a 0
            j=0;
        }
    }

    printf("\n\n");
    system("pause");

    return 0;
}
