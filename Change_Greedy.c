/**
The Problem of Change (Greedy)

Given t denominations of coins or banknotes T_0 in which we have infinite pieces of each
denomination, determine the minimum number of pieces to be used to
dispense a remainder R.

We have n coins or banknotes of
strictly positive integer values; the values are not necessarily ordered,
and multiple coins with the same value may exist.
Determine the minimum number of coins, among those on
available, that is necessary to use to dispense a given change R.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Comparison by Descending Sorting Coins
int compare_coins(const void *m1, const void *m2)
{
    const int v1 = *(const int*)m1;
    const int v2 = *(const int*)m2;
    if (v1 > v2)
        return -1;
    else if (v1 < v2)
        return 1;
    else
        return 0;
}

// Given n coins, it returns the minimum number of pieces needed to dispense a change R.
int resto(int R, int m[], int n)
{
    int *use = (int*)malloc(n * sizeof(*use));
    int n_coins = 0;
    int i;
    int da_erogare = R;

    assert(use != NULL);

    // Algo for Descending Sorting
    qsort(m, n, sizeof(*m), compare_coins);

    for (i=0; i<n; i++) {
        use[i] = 0;
    }

    for (i=0; i<n; i++) {
        if (da_erogare >= m[i]) {
            da_erogare -= m[i];
            use[i] = 1;
            n_coins++;
        }
    }

    if (da_erogare > 0) {
        printf("Remainder %d not dispensable with available coins\n", R);
        n_coins = -1;
    } else {
        int n_printed = 0; // control number of printed coins equal to n_coins
        printf("Remainder %d dispensable with %d coins:\n", R, n_coins);
        for (i=0; i<n; i++) {
            if (use[i]) {
                printf("%d ", m[i]);
                n_printed++;
            }
        }
        printf("\n");
        assert(n_coins == n_printed);
    }
    free(use);
    return n_coins;
}

int main( int argc, char *argv[] )
{
    int R, n, i;
    int *m;
    FILE *filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Invoke the program with: %s input_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    fscanf(filein, "%d %d", &R, &n);
    m = (int*)malloc(n * sizeof(*m));
    assert(m != NULL);
    for (i=0; i<n; i++) {
        if (1 != fscanf(filein, "%d", &m[i])) {
            fprintf(stderr, "Error during coin reading %d\n", i);
            return EXIT_FAILURE;
        }
    }

    resto(R, m, n);
    free(m);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
