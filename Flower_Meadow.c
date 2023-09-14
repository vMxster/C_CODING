#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define DIM 20
#define test(startpos, randompos) startpos>=randompos ? startpos-randompos : randompos-startpos
/*
 * --- TESTO ESERCIZIO ---
 * Prato fiorito.
 * Il gioco deve essere gestito tramite un menu a 3 scelte: gioca, imposta difficoltà (fra 1 e 5) ed esci.
 *
 * --- COMANDI ---
 * FRECCETTE PER SPOSTARSI
 * SPAZIO: BANDIERA
 * INVIO: SCOPRI
 * Q: ESCI DAL GIOCO
 */

//enum con tutti gli "stati" possibile delle caselle della matrice
enum stato{
    c0,
    c1,
    c2,
    c3,
    c4,
    c5,
    c6,
    c7,
    c8, // se è minore di 8 allora è una casella scoperta (c1 -> c8 indica il numero di bombe nei paraggi)
    flag_free, // se l'utonto ha messo la bandiera su una casella che non era bomba
    flag_mina, // se l'utente ha messo la bandiera su una casella che era bomba
    coperta, // se la casella non è ancora stata scoperta
    mina // se la casella è una mina
};

struct posizione{ //struct che utilizzo quando vado a cercare nelle 8 posizioni distanza 1 da una determinata cella (vedi codice successivo)
    int x;
    int y;
};

//funzione colori
void cambiaColore(unsigned short int colore) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,colore);
}

void stampaCampo(int campo[DIM][DIM], int x, int y){
    //ciclo la matrice
    for(int i=0; i<DIM; i++){
        for(int j=0; j<DIM; j++){
            //se la cella è scoperta
            if(campo[i][j]<=c8){
                //se la cella è scoperta ma ha 0 bombe vicino
                if(campo[i][j]==c0){
                    //se corrisponda alla casella su cui ho il cursore la evidenzio altrimenti stampo in colore base
                    if(i==x && j==y) cambiaColore(159);
                    printf("[ ]");
                    cambiaColore(7);
                    //altrimenti se la casella è scoperta ma ha almeno una bomba vicina
                } else {
                    //se corrisponda alla casella su cui ho il cursore la evidenzio altrimenti stampo in colore base
                    if(i==x && j==y) cambiaColore(159);
                    printf("[");

                    //metto come codice colore il numero di bombe vicine così da differenziare un pochino
                    cambiaColore(campo[i][j]);
                    printf("%d", campo[i][j]);

                    //se corrisponda alla casella su cui ho il cursore la evidenzio
                    if(i==x && j==y){
                        cambiaColore(159);
                        //altrimenti stampo in colore base
                    }else cambiaColore(7);
                    printf("]");
                }
            }
            //se la casella è una bandiera su una mina o una mina
            if(campo[i][j]==flag_free || campo[i][j]==flag_mina){
                if(i==x && j==y) cambiaColore(159); //stessa storia del cursore
                printf("[");

                cambiaColore(4); // rosso
                printf("F");

                //stessa storia del cursore
                if(i==x && j==y){
                    cambiaColore(159);
                }else cambiaColore(7);
                printf("]");
            }

            //se la casella è coperta o è una mina (coperta) stampo [O]
            if(campo[i][j]==coperta || campo[i][j]==mina){
                if(i==x && j==y) cambiaColore(159); // stessa storia del cursore
                printf("[");
                cambiaColore(7);
                printf("O");
                if(i==x && j==y){ //stessa storia del cursore
                    cambiaColore(159);
                }else cambiaColore(7);
                printf("]");
            }
            cambiaColore(7); //una volta finita la stampa rimetto il colore default (7 == bianco)
        }
        printf("\n");
    }
    printf("\n\n");
}

int contaBombeVicinoA(int campo[DIM][DIM], int x, int y){
    int bombe = 0; // cont di bombe
    int xTemp, yTemp; // coordinate temporanee
    //array di struct in cui ci metto le coordinate da sommare a quelle attuali così da andare in tutte e 8 le caselle vicine
    struct posizione pos[8] ={{1,0}, {1,1}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1}};
    //poi le ciclo e controllo
    for(int i=0; i<8; i++){
        xTemp = x+pos[i].x;
        yTemp = y+pos[i].y;
        //se sono all'interno della matrice
        if((xTemp>=0 && xTemp<DIM) && (yTemp>=0 && yTemp<DIM)){
            //controllo se la casella in questione è una mina o un flag mina, in tal caso aumento il contatore di bombe
            if(campo[xTemp][yTemp] == mina || campo[xTemp][yTemp] == flag_mina) bombe++;
        }
    }
    return bombe;
}

/*
void stampaDebug(int campo[DIM][DIM]){
    for(int i=0; i<DIM; i++){
        for(int j=0; j<DIM; j++){
            printf("[%d]", campo[i][j]);
        }
        printf("\n");
    }
}
*/


int scopriCasella(int campo[DIM][DIM], int x, int y){
    //se la casella è una mina il gioco finisce
    if(campo[x][y] == mina) return 0;
    //se la casella è coperta
    if(campo[x][y] == coperta){
        //struct con le 8 posizioni intorno che uso per la ricorsione
        struct posizione pos[8] ={{1,0}, {1,1}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1}};
        //scopro la casella e ci metto il numero di bombe vicino
        campo[x][y] = contaBombeVicinoA(campo, x, y);
        //se non ci sono bombe allora richiamo questa funzione per le 8 caselle attorno
        if(campo[x][y]==c0){
            //stessa meccanica della funzione contaBombeVicinoA
            int xTemp, yTemp;
            for(int i=0; i<8; i++){
                xTemp = x+pos[i].x;
                yTemp = y+pos[i].y;
                if((xTemp>=0 && xTemp<DIM) && (yTemp>=0 && yTemp<DIM)) {
                    if (campo[xTemp][yTemp] != mina) {
                        scopriCasella(campo, xTemp, yTemp);
                    }
                }
            }
        }
    }
    return 1;
}

void inizializzaGioco(int diff, int campoLogico[DIM][DIM], int x, int y){
    //in base alla difficoltà metto il numero di bombe
    int bombe = diff * 20;

    //inizializzo la matrice con tutte le caselle coperte
    for(int i=0; i<DIM; i++)
        for(int j=0; j<DIM; j++)
            campoLogico[i][j] = coperta;

    //e poi ci metto le bombe
    int i, j;
    while(bombe>0){
        i = rand()%DIM;
        j = rand()%DIM;
        //controllo con una macro che la distanza tra le caselle di start e la bomba random sia >1 e anche che non sia già una bomba
        if(campoLogico[i][j] != mina && test(x, i)>1 && test(y, j)>1){
            //altrimenti piazzo la mina e diminuisco il contatore
            campoLogico[i][j] = mina;
            bombe--;
        }
    }
}

//funzione che mi stampa la posizione delle bombe quando si perde
void stampaBombe(int campo[DIM][DIM]){
    //ciclo la matrice
    for(int i=0; i<DIM; i++){
        for(int j=0; j<DIM; j++){
            //se la casella è una mina o una bandiera sopra una mina
            if(campo[i][j]==mina || campo[i][j]==flag_mina){
                cambiaColore(4); // rosso
                printf("[*]");
                cambiaColore(7);
            }else{
                //altrimenti stampo una casella vuota
                printf("[ ]");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

//funzione che mi controlla la condizione di vittoria ad ogni ciclo
int checkWin(int campo[DIM][DIM], int diff){

    //se trovo una casella che è ancora coperta di sicuro non ho ancora vinto, quindi ritorno 1 e il loop continua
    for(int i=0; i<DIM; i++)
        for(int j=0; j<DIM; j++)
            if(campo[i][j] == coperta) return 1;


    // se non ho pià caselle coperte allora ritorno -1 (vittoria)
    return -1;
}

//funzione di sbandieramento
void mettiBandiera(int campo[DIM][DIM], int x, int y){
    //se è una mina metto un flag mina
    if(campo[x][y]==mina){
        campo[x][y]=flag_mina;
        //altrimenti se è un flag mina metto una mina
    }else if(campo[x][y]==flag_mina) campo[x][y]=mina;

    //se è coperta metto un flag free
    if(campo[x][y]==coperta){
        campo[x][y]=flag_free;
        //altrimenti se è flag free rimetto coperta
    } else if(campo[x][y]==flag_free) campo[x][y]= coperta;
}

void main() {

    int campoLogico[DIM][DIM]={0}; //matrice
    int scelta; // scelta ciclo principale
    int diff = 1; // difficoltà
    int tasto = 0; //tasto di input
    int run = 1; //condizione per far girare il ciclo del gioco
    int x=0,y=0; // coordinate

    srand(time(NULL));

    //ciclo finché il gioco non parte
    while(scelta!=1){

        system("cls");
        printf("[1]Gioca [2]Imposta difficolta' [3]Esci\n\n");
        rewind(stdin);
        scanf("%d", &scelta);


        switch(scelta){
            case 1:
                system("cls");
                stampaCampo(campoLogico, x ,y);
                //primo ciclo da cui esco quando inizializzo la matrice premendo invio su una casella
                while(tasto!=13){
                    tasto = getch();
                    /*
                    * sinistra = 75
                    * destra = 77
                    * sopra = 72
                    * sotto = 80
                    * spazio = 32
                    * invio = 13
                    */
                    switch(tasto){
                        case 75:
                            if(y>0) y--;
                            break;
                        case 77:
                            if(y<(DIM-1)) y++;
                            break;
                        case 72:
                            if(x>0) x--;
                            break;
                        case 80:
                            if(x<(DIM-1)) x++;
                            break;
                        case 13: // invio == inizializzo
                            inizializzaGioco(diff, campoLogico, x, y);
                            scopriCasella(campoLogico, x, y);
                            break;
                        case 113:
                            // Q == esco dal gioco mentre sto giocando
                            exit(1);
                            break;
                    }
                    system("cls");
                    stampaCampo(campoLogico, x ,y); // ad ogni ciclo stampo il campo così aggiorno il cursore
                    //printf("\n\n%d, %d", x, y);
                }

                //ciclo principale che va finché run rimane >0
                while(run>0){
                    tasto = getch(); //prendo un tasto in input
                    /*
                    * sinistra = 75
                    * destra = 77
                    * sopra = 72
                    * sotto = 80
                    * spazio = 32
                    * invio = 13
                    * q = 113
                    */
                    switch(tasto){
                        case 75:
                            if(y>0) y--;
                            break;
                        case 77:
                            if(y<(DIM-1)) y++;
                            break;
                        case 72:
                            if(x>0) x--;
                            break;
                        case 80:
                            if(x<(DIM-1)) x++;
                            break;
                        case 13:
                            //invio scopro la casella e aggiorno run
                            run = scopriCasella(campoLogico, x, y);
                            break;
                        case 32:
                            // spazio == metto una bandiera
                            mettiBandiera(campoLogico, x, y);
                            break;
                        case 113:
                            // Q == esco dal gioco mentre sto giocando
                            run = -2;
                            break;
                    }
                    system("cls");
                    stampaCampo(campoLogico, x ,y);
                    if(run>0)
                        run = checkWin(campoLogico, diff);
                    //printf("\n\n%d, %d", x, y);
                }

                //una volta uscito dal ciclo stampo il risultato a seconda del valore di run
                switch(run){
                    case 0:
                        //sconfitta
                        system("cls");
                        stampaBombe(campoLogico);
                        printf("\n\nHai perso\n\n");
                        break;
                    case -1:
                        //vittoria
                        printf("Hai vinto\n\n");
                        break;
                    case -2:
                        //uscita dal gioco in runtime
                        printf("Partita abbandonata\n\n");
                        break;
                }

                system("pause");
                break;
            case 2:
                //case scelta difficoltà
                do{
                    //finché non ottengo un input accettabile
                    system("cls");
                    printf("[1]20 bombe [2]40 bombe [3]60 bombe [4]80 bombe [5]100 bombe\n\n");
                    rewind(stdin);
                    scanf("%d", &diff);
                }while(diff<1 || diff>5);
                break;
            case 3:
                //case esci dal gioco
                exit(1);
            default:
                //default se l'input non triggera un case allora stampo input inaccettabile
                printf("\nInput invalido");
                system("pause");
        }
    }

}
