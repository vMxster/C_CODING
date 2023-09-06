/**
Shooting Stars Game
**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int board[3][3]; // board[i][j] = 0 indicates a black hole, 1 indicates a star

enum { BLACK_HOLE, STAR };

int nbor[9][3][3] = {
        {   {1, 1, 0}, 	// cell 0 with its neighborhood
                {1, 1, 0},
                {0, 0, 0}},

        {   {1, 1, 1}, 	// cell 1 with its neighborhood
                {0, 0, 0},
                {0, 0, 0}},

        {   {0, 1, 1}, 	// cell 2 with its neighborhood
                {0, 1, 1},
                {0, 0, 0}},

        {   {1, 0, 0}, 	// cell 3 with its neighborhood
                {1, 0, 0},
                {1, 0, 0}},

        {   {0, 1, 0}, 	// cell 4 with its neighborhood
                {1, 1, 1},
                {0, 1, 0}},

        {   {0, 0, 1}, 	// cell 5 with its neighborhood 	
                {0, 0, 1},
                {0, 0, 1}},

        {   {0, 0, 0}, 	// cell 6 with its neighborhood
                {1, 1, 0},
                {1, 1, 0}},

        {   {0, 0, 0}, 	// cell 7 with its neighborhood
                {0, 0, 0},
                {1, 1, 1}},

        {   {0, 0, 0}, 	// cell 8 with its neighborhood
                {0, 1, 1},
                {0, 1, 1}}
};

// Print the grid stored in the entire stars
void print_board( void ) {
    int i, j, idx = 0;
    printf("\n");
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (board[i][j] == BLACK_HOLE) {
                printf(". ");
            } else {
                printf("%d ", idx);
            }
            idx++;
        }
        printf("\n\n");
    }
    printf("\n");
}

typedef enum {INVALID=0, OK, WON, LOST, RESIGNED} Move;

void init_board( void ) {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            board[i][j] = (i == 1 && j == 1);
        }
    }
}

// Reverses the contents of the cell at position i,j
void inverti(int i, int j) {
    assert(i>=0 && i<3);
    assert(j>=0 && j<3);
    board[i][j] = 1 - board[i][j];
}

// returns true (notzero) if and only if the current configuration is the winning one
int won( void ) {

    /* è possibile determinare se la configurazione è quella vincente
     * usando una condizione booleana appropriata.*/

    static const int winning_conf[3][3] = {{1, 1, 1},
                                           {1, 0, 1},
                                           {1, 1, 1}};
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (board[i][j] != winning_conf[i][j])
                return 0;
        }
    }
    return 1;
}

// returns true (notzero) if and only if the current configuration is the losing one
int lost( void ) {
    int i, j;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (board[i][j] == STAR)
                return 0;
        }
    }
    return 1;
}

// It makes the star explode in the `k` position.
Move shoot(int k) {
    const int r = k/3; /* row */
    const int c = k%3; /* col */
    int i, j;

    if (k<0 || k>8)
        return INVALID;

    if (board[r][c] != STAR)
        return INVALID;

    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (nbor[k][i][j])
                inverti(i,j);
        }
    }

    if (won())
        return WON;
    else if (lost())
        return LOST;
    else
        return OK;
}

int main( void ) {
    Move outcome;
    init_board( );
    print_board( );
    do {
        int k;
        printf("Your move ( <0 to resign)? ");
        scanf("%d", &k);
        if ( k < 0 ) {
            outcome = RESIGNED;
        } else {
            outcome = shoot(k);
            if ( outcome == INVALID ) {
                printf("\nInvalid move\n");
            }
            print_board( );
        }
    } while (outcome == OK || outcome == INVALID);
    switch (outcome) {
        case WON:
            printf("You won!\n");
            break;
        case LOST:
            printf("You lost!\n");
            break;
        default:
            printf("Resigned!\n");
    }
    return EXIT_SUCCESS;
}
