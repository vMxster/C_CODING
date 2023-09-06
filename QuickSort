/***
Quicksort
 ***/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define ARRAY_LEN(v) (sizeof(v)/sizeof(v[0]))

// Swap the contents of v[i] and v[j]
void swap(int *v, int i, int j)
{
    const int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

// Applies the partition to the subvector v and returns the position of the pivot
int partition(int *v, int start, int end)
{
    const int pivot = v[end];
    int i = (start - 1), j;

    for (j = start; j < end; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(v, i, j);
        }
    }

    swap(v, i+1, end);
    return i + 1;
}

// Sort the subvector v recursively
void quicksort(int *v, int start, int end)
{
    if (start < end) {
        const int split = partition(v, start, end);
        quicksort(v, start, split - 1);
        quicksort(v, split + 1, end);
    }
}

// Function to hide the implementation details of Quicksort.
void sort(int *v, int n)
{
    quicksort(v, 0, n-1);
}

void print_array(const int *v, int n)
{
    int i;

    printf("[ ");
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("]");
}

// Returns a random value between a and b
int randab(int a, int b)
{
    return a + rand() % (b-a+1);
}

// Permutes the contents of array v randomly
void random_shuffle(int *v, int n)
{
    int i;

    for (i=0; i<n-1; i++) {
        const int j = randab(i, n-1);
        const int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

int compare(const void *p1, const void *p2)
{
    const int v1 = *(const int*)p1;
    const int v2 = *(const int*)p2;
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

// Compare the contents of two arrays v1 and v2 of length n
int compare_vec(const int *v1, const int *v2, int n)
{
    int i;
    for (i=0; i<n; i++) {
        if (v1[i] != v2[i])
            return i;
    }
    return -1;
}

// Sort the array v of length n
int test(int *v, int n)
{
    int result;
    int *tmp = (int*)malloc(n * sizeof(*tmp));
    int diff;

    assert(tmp != NULL);
    memcpy(tmp, v, n*sizeof(*v));
    qsort(tmp, n, sizeof(*tmp), compare);
    sort(v, n);
    diff = compare_vec(v, tmp, n); // Compare my QuickSort with QuickSort already implemented in the library.
    if (diff < 0) {
        printf("Test OK \n");
        result = 1;
    } else {
        printf("Test FAILED: v[%d]=%d, expected=%d\n", diff, v[diff], tmp[diff]);
        result = 0;
    }
    free(tmp);
    return result;
}

int main( void )
{
    // Test Input
    int v1[] = {0, 8, 1, 7, 2, 6, 3, 5, 4};
    int v2[] = {0, 1, 0, 6, 10, 10, 0, 0, 1, 2, 5, 10, 9, 6, 2, 3, 3, 1, 7};
    int v3[] = {-1, -3, -2};
    int v4[] = {2, 2, 2};
    int v5[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    test(v1, ARRAY_LEN(v1));
    test(v2, ARRAY_LEN(v2));
    test(v3, ARRAY_LEN(v3));
    test(v4, ARRAY_LEN(v4));
    test(v5, ARRAY_LEN(v5));

    return EXIT_SUCCESS;
}
