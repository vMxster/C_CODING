/**
DFS
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Arch Structure
typedef struct Edge {
    int dst;
    struct Edge *next;
} Edge;

// Structure Graph
typedef struct {
    int n;              // Number of nodes
    int m;              // Number of arcs
    Edge **edges;       // Array of adjacency lists
    int *in_deg;        // Incoming nodes
    int *out_deg;       // Outgoing nodes
} Graph;

// Delete Graph
void graph_destroy(Graph *g);

// Pointer to the first arc of the node adjacency list v
Edge *graph_adj(const Graph *g, int v);

// Number Nodes
int graph_n_nodes(const Graph *g);

// Print Graph
void graph_print(const Graph *g);

// Create new graph by reading from file
Graph *graph_read_from_file(FILE *f);

// Predecessor to the list of fathers does not exist
const int NODE_UNDEF = -1;

typedef enum { WHITE, GREY, BLACK } Color; // Node colors

Graph *G;
int *p;         // Predecessor of i along the path from source to i
int t;          // Current time
int *discover;  // Initial time when node v was first visited
int *finish;    // Final time when all descendants of v were visited
Color *color;   // Node color v

// Recursive visitation of nodes reachable by u
void dfs_rec( int u )
{
    const Edge *e;

    assert( (u>=0) && (u<graph_n_nodes(G)) );

    t = t + 1;
    discover[u] = t;
    color[u] = GREY;

    for (e = graph_adj(G, u); e != NULL; e = e->next) {
        const int v = e->dst;
        if (color[v] == WHITE) {
            p[v] = u;
            dfs_rec(v);
        }
    }

    t = t + 1;
    finish[u] = t;
    color[u] = BLACK;
}

// Visit the graph in depth from all nodes
void dfs( void )
{
    const int n = graph_n_nodes(G);
    int v;

    t = 0;

    // Initialization
    for (v=0; v<n; v++) {
        p[v] = NODE_UNDEF;
        discover[v] = finish[v] = -1;
        color[v] = WHITE;
    }
    // Visit Grafo
    for (v=0; v<n; v++) {
        if (color[v] == WHITE) {
            dfs_rec(v);
        }
    }
}

// Print the predecessors of each node in the tree
void print_dfs( void )
{
    const int n = graph_n_nodes(G);
    int v;

    printf("     v |   p[v] | discover |   finish\n");
    printf("-------+--------+----------+----------\n");
    for (v=0; v<n; v++) {
        printf("%6d | %6d | %8d | %8d\n", v, p[v], discover[v], finish[v]);
    }
}

int main( int argc, char *argv[] )
{
    FILE *filein = stdin;
    int n;

    if (argc != 2) {
        fprintf(stderr, "Invoke the program with: %s file_grafo\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    G = graph_read_from_file(filein);
    n = graph_n_nodes(G);
    p = (int*)malloc( n * sizeof(*p) ); assert(p != NULL);
    discover = (int*)malloc( n * sizeof(*discover) ); assert(discover != NULL);
    finish = (int*)malloc( n * sizeof(*finish) ); assert(finish != NULL);
    color = (Color*)malloc( n * sizeof(*color) ); assert(color != NULL);
    dfs( );
    print_dfs( );
    graph_destroy(G);
    free(p);
    free(discover);
    free(finish);
    free(color);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
