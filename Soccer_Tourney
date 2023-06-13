#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  Exam 25/01/2023 (Coding Course)
 */

/*
 * Input: partecipanti.txt
 *
 * Riga esempio:
 * m210 Wim 2 AO 6 Rga 0 Rom 5
 *
 * Elementi per riga:
 * id_giocatore, stringa di massimo 10 caratteri utili
 * n coppie di codice_torneo (stringa di massimo 3 caratteri utili) e livello_torneo (intero compreso tra 0 e 48, 0 indica nessun risultato (es. ritirato))
 */


#define L_ID 10
#define L_CODICE 3


struct Tornei{
    char codice_torneo[L_CODICE + 1];
    int livello_torneo;
    struct Tornei *next;
};


struct Giocatore{
    char id_giocatore[L_ID + 1];
    struct Tornei *elenco_tornei;
    struct Giocatore *next;
};


struct Giocatore * leggi_partecipanti(char *);
int iscritti_torneo(struct Giocatore *, char *);
int nuovi_iscritti_torneo(struct Giocatore *, char *);


int main() {
    struct Giocatore *lista_giocatori = NULL;
    int n_iscritti_Wim = 0, n_nuovi_iscritti_AO = 0;

    lista_giocatori = leggi_partecipanti("partecipanti.txt");
    n_iscritti_Wim = iscritti_torneo(lista_giocatori, "Wim");
    n_nuovi_iscritti_AO = nuovi_iscritti_torneo(lista_giocatori, "AO");
    return 0;
}


struct Giocatore * leggi_partecipanti(char *nome_file){
    FILE *file_partecipanti = fopen(nome_file, "r");
    struct Giocatore *lista = NULL;
    char controllo;

    if(file_partecipanti == NULL){
        printf("Errore - file partecipanti non trovato\n");
        return NULL;
    }
    while(!feof(file_partecipanti)){
        struct Giocatore *giocatore_new = malloc(sizeof(struct Giocatore));

        if(giocatore_new == NULL){
            printf("Errore - memoria piena\n");
            break;
        }
        for(int i = 0; i < sizeof (giocatore_new->id_giocatore); i++) (giocatore_new->id_giocatore)[i] = '\0';
        giocatore_new->elenco_tornei = NULL;
        fscanf(file_partecipanti, "%s", giocatore_new->id_giocatore);
        /*
         * Non so quanti tornei contiene la riga. Dunque, leggo la coppia di dati, poi un singolo carattere, fermandomi
         * quando quest'ultimo è un carattere di nuova linea.
         */
        controllo = (char)fgetc(file_partecipanti);
        while(controllo != '\n' && controllo != EOF){
            struct Tornei *tornei_new = malloc(sizeof(struct Tornei));
            struct Tornei *temp = giocatore_new->elenco_tornei, *prev = NULL;

            if(tornei_new == NULL){
                printf("Errore - memoria piena\n");
                break;
            }
            for(int i = 0; i < sizeof (tornei_new->codice_torneo); i++) (tornei_new->codice_torneo)[i] = '\0';
            tornei_new->livello_torneo = 0;
            tornei_new->next = NULL;
            fscanf(file_partecipanti, "%s %d", tornei_new->codice_torneo, &tornei_new->livello_torneo);
            /*
             * Devo mantenere la lista in ordine crescente. A ogni nuovo inserimento, controllo se la lista è già presente.
             * Se lo è, la scorro finché arrivo in fondo (puntatore a NULL) o il primo carattere del nuovo elemento viene
             * prima del primo carattere dell'elemento in lista.
             */
            while(temp != NULL){
                if(tornei_new->codice_torneo[0] < temp->codice_torneo[0]){
                    break;
                }
                /*
                 * In caso di uguaglianza, ripeto il medesimo controllo per il secondo carattere.
                 */
                if(tornei_new->codice_torneo[0] == temp->codice_torneo[0]){
                    if(tornei_new->codice_torneo[1] < temp->codice_torneo[1]){
                        break;
                    }
                    /*
                     * In caso di nuova uguaglianza, ripeto il medesimo controllo per il terzo carattere.
                     */
                    if(tornei_new->codice_torneo[1] == temp->codice_torneo[1]){
                        /*
                         * Mi fermo anche se il terzo carattere è identico; caso improbabile, poiché significa che le
                         * stringhe sono identiche, ovvero che lo stesso torneo è stato inserito più volte.
                         */
                        if(tornei_new->codice_torneo[2] <= temp->codice_torneo[2]){
                            break;
                        }
                    }
                }
                // Al termine di ogni giro, salvo l'elemento corrente in prec.
                prev = temp;
                temp = temp->next;
            }
            /*
             * All'uscita del ciclo, temp varrà NULL (lista vuota o torneo ultimo per ordine alfabetico) oppure
             * punterà a un torneo successivo a quello nuovo; il campo next del nuovo torneo dovrà quindi puntare a temp.
             */
            tornei_new->next = temp;
            /*
             * Se prev è diverso da NULL, l'inserimento avviene in mezzo alla lista, dunque il suo campo next dovrà
             * puntare al nuovo torneo.
             */
            if(prev != NULL){
                prev->next = tornei_new;
            }
            /*
             * In caso contrario, il nuovo torneo sarà il primo da inserire in lista (per ordine o perché la lista era
             * vuota); dunque, inserirò il nuovo torneo in testa.
             */
            else{
                giocatore_new->elenco_tornei = tornei_new;
            }
        }
        // Ogni nuovo giocatore è inserito in testa.
        giocatore_new->next = lista;
        lista = giocatore_new;
    }
    fclose(file_partecipanti);
    return lista;
}


int iscritti_torneo(struct Giocatore *lista_giocatori, char *id_torneo_cercato){
    int n_iscritti = 0;

    // Scorro la lista dei giocatori, controllandoli tutti.
    while(lista_giocatori != NULL){
        struct Tornei *temp = lista_giocatori->elenco_tornei;
        // Scorro l'elenco dei tornei di ciascun giocatore: se risulta iscritto al torneo, incremento il contatore e mi fermo.
        while(temp != NULL){
            if(strcmp(temp->codice_torneo, id_torneo_cercato) == 0){
                n_iscritti++;
                break;
            }
            temp = temp->next;
        }
        lista_giocatori = lista_giocatori->next;
    }
    return n_iscritti;
}


int nuovi_iscritti_torneo(struct Giocatore *lista_giocatori, char *id_torneo_cercato){
    int n_nuovi_iscritti = 0;

    // Scorro la lista dei giocatori, controllandoli tutti.
    while(lista_giocatori != NULL){
        struct Tornei *temp = lista_giocatori->elenco_tornei;
        // Scorro l'elenco dei tornei di ciascun giocatore; se risulta iscritto al torneo, mi fermo.
        while(temp != NULL){
            if(strcmp(temp->codice_torneo, id_torneo_cercato) == 0){
                break;
            }
            temp = temp->next;
        }
        // temp può rimanere NULL solo se il giocatore non è iscritto al torneo; in questo caso incremento il contatore.
        if(temp == NULL){
            n_nuovi_iscritti++;
        }
        lista_giocatori = lista_giocatori->next;
    }
    return n_nuovi_iscritti;
}
