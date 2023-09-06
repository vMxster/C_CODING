/**
Count the number of distinct words

Write a program that determines the total number of
words and the number of distinct words in it; no
distinguish between uppercase and lowercase letters.

Use Hash Functions to solve the problem

 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORDLEN 100

typedef struct {
    int size;
    int values_count;
} HashTable;

// Create a new hash table with size slot
HashTable *ht_create(int size);

// Frees up all memory occupied by the hash table
void ht_destroy(HashTable *h);

// Enter the pair (key, value) in the hash table.
int ht_insert(HashTable *h, const char *key, int value);

// Returns the number of (key, value) in the hash table
int ht_count(const HashTable *h);

// Print the contents of the hash table
void ht_print(const HashTable *h);


// Reads the next word from the file and stores it in the buffer s
int read_word(FILE *f, char *s)
{
    int i=0;
    int c;

    // Skip non-alphabetic characters
    do {
        c = fgetc(f);
    } while ((c != EOF) && !isalpha(c));

    while ((c != EOF) && isalpha(c) && (i < WORDLEN-1)) {
        s[i] = tolower(c);
        i++;
        c = fgetc(f);
    }
    s[i] = '\0';
    return i;
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    char w[WORDLEN]; // buffer for word reading
    int np = 0;
    HashTable *h;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s inputfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    h = ht_create(50000); // Arbitrary Hash Table Size
    while (read_word(filein, w)) {
        ht_insert(h, w, 1);
        printf("%s\n", w);
        np++;
    }
    printf("%d words, of which %d distinct\n", np, ht_count(h));
    ht_destroy(h);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
