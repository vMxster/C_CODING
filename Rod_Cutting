/**
Rod Cutting Problem

We have a rod of full length n, n < N, which
we can cut into shorter segments to resell at different prices
different. The allowable lengths are up to n, and we sell
respectively at prices up to p_n. We want to determine the maximum profit that is possible
obtain from cutting the rod.
The program reads input from a file whose name is to be specified on the
command line.

For Example:

Length i        1   2   3   4   5   6   7   8   9  10

Price p[i]      1   5   8   9  13  17  17  20  24  25

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 1000      // MAX length

/*
 * Although the use of global variables is considered (rightly) a bad programming practice,
 * the proposed solution uses them to simplify the interface of functions.
 */

double p[N];    // Selling price of a segment
int n;          // Length of the rod to be cut
double r[N];    // Maximum gain that can be obtained by cutting a long rod j
int s[N];       // Length of the last cut of the optimal solution of the problem P(j)

// Reads input from the file
void init(FILE *filein) {
    double val;
    p[0] = 0.0; /* p[0] non viene usato */
    n = 0;
    while (1 == fscanf(filein, "%lf", &val)) {
        n++;
        assert(n < N);
        p[n] = val;
    }
}

// Determines the solution to the Rod Cutting problem
double solve() {
    int i,j;

    for (i=0; i<=n; i++) {
        r[i] = 0.0;
        s[i] = 0;
    }

    for (j=1; j<=n; j++) {
        double max_earning = -1;
        for (i=1; i<=j; i++) {
            if (max_earning < p[i] + r[j-i]) {
                max_earning = p[i] + r[j-i];
                s[j] = i;
            }
        }
        r[j] = max_earning;
    }
    return r[n];
}

// Print the solution to the problem
void print() {
    int j;

    printf(" Length  Price\n");
    printf(" ------ --------\n");
    for (j=n; j>0; j -= s[j]) {
        printf("%6d %8.2f\n", s[j], p[s[j]]);
    }
    printf("Overall Gain: %.2f\n", r[n]);
}

double randab(double a, double b) {
    return (rand() / (double)RAND_MAX) * (b-a) + a;
}

void generate_input(int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%.2f\n", randab(2.0*(i+1), 4.0*(i+1)));
    }
}

int main( int argc, char *argv[] ) {
    FILE *filein = stdin;

    if (argc < 2) {
        fprintf(stderr, "Invoke the program with: %s input_file\n", argv[0]);
        return EXIT_FAILURE;
    } else if (argc > 2) {
        generate_input(atoi(argv[1]));
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    init( filein );
    solve();
    print();
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
