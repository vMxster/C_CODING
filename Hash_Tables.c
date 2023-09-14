/**
Hash Tables

Collisions handled by chaining collision lists
 **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **items;
    int size;
    int values_count;
} HashTable;

// This function maps an arbitrary integer k to a position in the array items of the hash table
unsigned long hash_function(const HashTable *h, unsigned long k);

// Transforms a sequence of characters into an unsigned integer
unsigned long encode(const char *key);

// Create a new hash table with size slot
HashTable *ht_create(int size);

// Empty the hash table
void ht_clear(HashTable *h);

// Frees up all memory occupied by the hash table
void ht_destroy(HashTable *h);

// Enter the pair (key, value) in the hash table
int ht_insert(HashTable *h, const char *key, int value);

// Returns the node containing the information associated with the key key
HashNode *ht_search(HashTable *h, const char *key);

// Removes the key and associated value from the hash table
int ht_delete(HashTable *h, const char *key);

// Returns the number of pairs (key, value) in the hash table
int ht_count(const HashTable *h);

// Print the contents of the hash table
void ht_print(const HashTable *h);


unsigned long hash_function(const HashTable *table, unsigned long k)
{
    assert(table != NULL);

    return k % table->size;
}

unsigned long encode(const char *key)
{
    int i;
    unsigned long s;

    assert(key != NULL);

    s = 0;
    // The following loop may cause an overflow; we ignore the problem by trusting that the value of the variable s will restart from the beginning
    for (i=0; key[i]; i++) {
        s += key[i];
    }
    return s;
}

// Returns true (notzero) if keys k1 and k2 are equal
static int keys_equal(const char *k1, const char *k2)
{
    assert(k1 != NULL);
    assert(k2 != NULL);

    return (0 == strcmp(k1, k2));
}

HashTable *ht_create(const int size)
{
    HashTable *h = (HashTable*)malloc(sizeof(*h));
    int i;

    assert(h != NULL);
    h->size = size;
    h->values_count = 0;
    h->items = (HashNode **) malloc(h->size * sizeof(*(h->items)));
    assert(h->items != NULL);
    for (i = 0; i < h->size; i++) {
        h->items[i] = NULL;
    }
    return h;
}

// Function that creates a new node for overflow lists
static HashNode *hashtable_new_node(const char *key, int value, HashNode *next)
{
    HashNode *item = (HashNode *) malloc(sizeof(HashNode));
    const int keylen = strlen(key);

    assert(item != NULL);
    item->key = (char*)malloc(keylen+1);
    assert(item->key != NULL);
    strcpy(item->key, key);
    item->next = next;
    item->value = value;
    return item;
}

// Frees the memory allocated for node n and corresponding key of the hash table.
static void free_node(HashNode *n)
{
    assert(n != NULL);

    free(n->key);
    free(n);
}

int ht_insert(HashTable *h, const char *key, int value)
{
    HashNode* slot;

    assert(h != NULL);

    slot = ht_search(h, key);
    if (slot != NULL) {
        slot->value = value;
        return 0;
    } else {
        const unsigned long index = hash_function(h, encode(key));
        h->items[index] = hashtable_new_node(key, value, h->items[index]);
        h->values_count++;
        return 1;
    }
}

HashNode* ht_search(HashTable *h, const char *key)
{
    unsigned long index;
    HashNode* item;

    assert(h != NULL);

    index = hash_function(h, encode(key));
    item = h->items[index];

    while ((item != NULL) && (!keys_equal(item->key, key))) {
        item = item->next;
    }
    return item;
}

int ht_delete(HashTable *h, const char *key)
{
    unsigned long index;
    HashNode *prev = NULL, *curr;

    assert(h != NULL);

    index = hash_function(h, encode(key));
    curr = h->items[index];

    while ((curr != NULL) && !keys_equal(curr->key, key)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return 0;
    } else {
        if (prev == NULL) {
            h->items[index] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free_node(curr);
        h->values_count--;
        return 1;
    }
}

void ht_clear(HashTable *h)
{
    int i;

    assert(h != NULL);

    for (i = 0; i < h->size; i++) {
        HashNode *current = h->items[i];
        while (current != NULL) {
            HashNode *next = current->next;
            free_node(current);
            current = next;
        }
        h->items[i] = NULL;
    }
    h->values_count = 0;
}

void ht_destroy(HashTable *h)
{
    assert(h != NULL);

    ht_clear(h);
    free(h->items);
    h->items = NULL;
    h->size = h->values_count = 0;
    free(h);
}

int ht_count(const HashTable *h)
{
    assert(h != NULL);
    return (h->values_count);
}

void ht_print(const HashTable *h)
{
    int i;
    assert(h != NULL);
    for (i=0; i<h->size; i++) {
        const HashNode* iter;
        printf("[%3d] ", i);
        for (iter = h->items[i]; iter != NULL; iter = iter->next) {
            printf("->(%s, %d)", iter->key, iter->value);
        }
        printf("\n");
    }
}
