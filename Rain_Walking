/*
 *
 * Elaborato su Cammini Minimi data una Matrice Città, MAX 500 Righe e Colonne, dove 0 é un Marciapiede e 1-9 é un Palazzo.
 * Calcolare Cammino Minimo, Nodi Bagnati dalla Pioggia e Percorso( N= Nord, S= Sud, O= Ovest, E= Est )
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#define MAX_ROWS 501
#define MAX_COLS 501
#define INFINITY INT_MAX

/* Definizione della struttura Node per rappresentare un nodo nella coda a priorità */

typedef struct {
    int index;
    int distance;
} Node;

/* Definizione della struttura PriorityQueue per la coda a priorità */

typedef struct {
    Node* array;
    int capacity;
    int size;
} PriorityQueue;

/* Funzione per creare una coda a priorità */

PriorityQueue* createHeap(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    assert(queue != NULL);
    queue->array = (Node*)malloc(capacity * sizeof(Node));
    assert(queue->array != NULL);
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

/* Funzione per scambiare due nodi */

void swapNodes(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

/* Funzione per ripristinare la struttura di heap verso l'alto */

void heapifyUp(PriorityQueue* queue, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && queue->array[index].distance < queue->array[parent].distance) {
        swapNodes(&queue->array[index], &queue->array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

/* Funzione per ripristinare la struttura di heap verso il basso */

void heapifyDown(PriorityQueue* queue, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < queue->size && queue->array[leftChild].distance < queue->array[smallest].distance) {
        smallest = leftChild;
    }

    if (rightChild < queue->size && queue->array[rightChild].distance < queue->array[smallest].distance) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swapNodes(&queue->array[index], &queue->array[smallest]);
        heapifyDown(queue, smallest);
    }
}

/* Funzione per inserire un nodo nella coda a priorità */

void enqueue(PriorityQueue* queue, int index, int distance) {
    Node newNode;
    if (queue->size == queue->capacity) {
        printf("Priority queue is full.\n");
        return;
    }

    newNode.index = index;
    newNode.distance = distance;

    queue->array[queue->size] = newNode;
    queue->size++;

    heapifyUp(queue, queue->size - 1);
}

/* Funzione per estrarre il nodo con la distanza minima dalla coda a priorità */

Node dequeue(PriorityQueue* queue) {
    Node root;
    if (queue->size == 0) {
        Node emptyNode;
        printf("Priority queue is empty.\n");
        emptyNode.index = -1;
        emptyNode.distance = -1;
        return emptyNode;
    }

    root = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;

    heapifyDown(queue, 0);

    return root;
}

/* Funzione per trovare il percorso più breve utilizzando l'algoritmo di Dijkstra */

void ShortestPath(char city[][MAX_COLS], int rows, int cols) {

    /* Calcola il numero totale di nodi nella matrice */
    int numNodes = rows * cols;
    int i;
    int sourceIndex = 0;
    int destinationIndex = 0;
    PriorityQueue* queue;

    /* Allocazione di array per memorizzare le distanze e i genitori dei nodi */
    int* distances = (int*)malloc(numNodes * sizeof(int));
    int* parent = (int*)malloc(numNodes * sizeof(int));
    assert(distances != NULL);
    assert(parent != NULL);

    /* Inizializzazione delle distanze e dei genitori di tutti i nodi */
    for (i = 0; i < numNodes; i++) {
        distances[i] = INFINITY;
        parent[i] = -1;
    }

    /* Indice del nodo di origine e del nodo di destinazione */
    destinationIndex = numNodes - 1;
    distances[sourceIndex] = 0;

    /* Creazione della coda a priorità e inserimento del nodo di origine */
    queue = createHeap(numNodes);
    enqueue(queue, sourceIndex, 0);

    /* Esecuzione dell'algoritmo di Dijkstra */
    while (queue->size > 0) {
        Node minNode = dequeue(queue);
        int minIndex = minNode.index;

        /* Calcolo della riga e colonna corrispondenti all'indice del nodo */
        int currentNodeRow = minIndex / cols;
        int currentNodeCol = minIndex % cols;

        /* Ignora i nodi con una distanza superiore a quella attuale */
        if (minNode.distance > distances[minIndex]) {
            continue;
        }

        /* Interrompi l'esecuzione se è stato raggiunto il nodo di destinazione */
        if (minIndex == destinationIndex) {
            break;
        }

        /* Aggiornamento delle distanze e dei genitori dei nodi adiacenti */
        if (currentNodeRow > 0 && city[currentNodeRow - 1][currentNodeCol] == '0') {
            int adjIndex = minIndex - cols;
            int newDistance = distances[minIndex] + 1;
            if (newDistance < distances[adjIndex]) {
                distances[adjIndex] = newDistance;
                parent[adjIndex] = minIndex;
                enqueue(queue, adjIndex, newDistance);
            }
        }

        if (currentNodeRow < rows - 1 && city[currentNodeRow + 1][currentNodeCol] == '0') {
            int adjIndex = minIndex + cols;
            int newDistance = distances[minIndex] + 1;
            if (newDistance < distances[adjIndex]) {
                distances[adjIndex] = newDistance;
                parent[adjIndex] = minIndex;
                enqueue(queue, adjIndex, newDistance);
            }
        }

        if (currentNodeCol > 0 && city[currentNodeRow][currentNodeCol - 1] == '0') {
            int adjIndex = minIndex - 1;
            int newDistance = distances[minIndex] + 1;
            if (newDistance < distances[adjIndex]) {
                distances[adjIndex] = newDistance;
                parent[adjIndex] = minIndex;
                enqueue(queue, adjIndex, newDistance);
            }
        }

        if (currentNodeCol < cols - 1 && city[currentNodeRow][currentNodeCol + 1] == '0') {
            int adjIndex = minIndex + 1;
            int newDistance = distances[minIndex] + 1;
            if (newDistance < distances[adjIndex]) {
                distances[adjIndex] = newDistance;
                parent[adjIndex] = minIndex;
                enqueue(queue, adjIndex, newDistance);
            }
        }
    }

    /* Stampa del percorso più breve trovato */
    if (distances[destinationIndex] == INFINITY) {
        printf("-1 -1\n");  /* Percorso piu breve inesistente */
    } else {    /* Costruzione dei passi del percorso minimo utilizzando i genitori dei nodi e Individuazione dei nodi bagnati del percorso minimo */
        int d = distances[destinationIndex] + 1;
        int r = 1;
        int buildingHeight = 0;
        int currentIndex = destinationIndex;
        int pathIndex = d - 1;
        int currentNodeRow = 0;
        char* path = (char*)malloc(d * sizeof(char));
        assert(path != NULL);
        for (i = 0; i < d; i++) {
            path[i] = '\0';
        }

        while (currentIndex != sourceIndex) {
            int parentIndex = parent[currentIndex];
            int rowDiff = currentIndex / cols - parentIndex / cols;
            int colDiff = currentIndex % cols - parentIndex % cols;
            int nearestBuildingCol = -1;
            int distanceToBuilding = 0;
            int col = 0;

            if (rowDiff == -1 && colDiff == 0) {
                path[pathIndex] = 'N';
            } else if (rowDiff == 1 && colDiff == 0) {
                path[pathIndex] = 'S';
            } else if (rowDiff == 0 && colDiff == -1) {
                path[pathIndex] = 'O';
            } else if (rowDiff == 0 && colDiff == 1) {
                path[pathIndex] = 'E';
            }

            currentNodeRow = currentIndex / cols;

            for (col = currentIndex % cols - 1; col >= 0 && col >= currentIndex % cols - 9; col--) {
                if (city[currentNodeRow][col] != '0') {
                    nearestBuildingCol = col;
                    distanceToBuilding = (currentIndex % cols) - nearestBuildingCol;
                    buildingHeight = city[currentNodeRow][col] - '0';
                    if (buildingHeight >= distanceToBuilding ) {
                        break;
                    }
                    nearestBuildingCol = -1;
                }
            }
            if (nearestBuildingCol == -1) { r++; }

            pathIndex--;
            currentIndex = parentIndex;
        }
        printf("%d %d\n", d, r);
        for (i = 1; i < d; i++) {
            printf("%c", path[i]);
        }
        /* Deallocazione della memoria */
        free(path);
    }
    free(queue->array);
    free(queue);
    free(distances);
    free(parent);
}

int main( int argc, char *argv[] ) {
    int rows = 0;
    int cols = 0;
    int i;
    char city[MAX_ROWS][MAX_COLS] = {0};  /* Matrice dove memorizzare l'input */
    FILE* file = stdin;

    if (argc != 2) {
        fprintf(stderr, "Usa: %s inputfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "Impossibile Aprire %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    /* Legge rows e cols dal file */
    fscanf(file, "%d %d", &rows, &cols);

    /* Legge la matrice city dal file */
    for (i = 0; i < rows; i++) {
        fscanf(file, "%500s", city[i]);
    }

    /* Chiude il file */
    fclose(file);

    ShortestPath(city, rows, cols);

    return 0;
}
