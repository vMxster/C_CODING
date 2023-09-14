/**
Text formatting

Write a program that reads a text file and prints on the screen the
sequence of words in it so that each line has a
maximum length of Lmax characters. The value of Lmax and the name
of the text file are passed as parameters on the
command.

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define WORDLEN 1024 // Max Length Word

// Reads the next word from the file and stores it in s
int read_word(FILE *f, char *s)
{
    int i=0;
    int c;

    do {
        c = fgetc(f);
    } while (c != EOF && isspace(c));

    while (c != EOF && !isspace(c)) {
        assert(i < WORDLEN-1);
        s[i] = c;
        i++;
        c = fgetc(f);
    }
    s[i] = '\0';
    return i;
}

// Print long header line n
void header(int n)
{
    int i;

    for (i=1; i<=n; i++) {
        printf("%c", i%10 ? '-' : '|');
    }
    printf("\n");
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    int Lmax;
    char w[WORDLEN];
    int L=0;
    if (argc != 3) {
        fprintf(stderr, "Using: %s Lmax filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    Lmax = atoi(argv[1]);

    if (strcmp(argv[2], "-") != 0) {
        filein = fopen(argv[2], "r");
        if (filein == NULL) {
            fprintf(stderr, "Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    header(Lmax);
    while ( read_word(filein, w) > 0 ) {
        const int wlen = strlen(w);
        if (L + wlen <= Lmax) {
            printf("%s ", w);
        } else {
            printf("\n%s ", w);
            L = 0;
        }
        L += wlen + 1;
    }
    printf("\n");
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
