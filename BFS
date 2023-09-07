/**
BFS
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Arch structure
typedef struct Edge {
    int src;
    int dst;
    struct Edge *next;
} Edge;

// Graph structure
typedef struct {
    int n;              // Numero nodi
    int m;              // Numero archi
    Edge **edges;       // Array di liste di adiacenza
    int *in_deg;        // Nodi entranti
    int *out_deg;       // Nodi uscenti
} Graph;

// Delete Graph
void graph_destroy(Graph *g);

// Pointer to the first arc of the node adjacency list v
Edge *graph_adj(const Graph *g, int v);

// Total nodes Graph
int graph_n_nodes(const Graph *g);

// Print Graph
void graph_print(const Graph *g);

// Create new graph by reading from file
Graph *graph_read_from_file(FILE *f);

typedef int ListInfo;

typedef struct ListNode {
    ListInfo val;
    struct ListNode *succ, *pred;
} ListNode;

typedef struct {
    int length;
    ListNode *sentinel;
} List;

// Create empty list
List *list_create( void );

// Delete list
void list_destroy(List *L);

// Returns true (notzero) if the list is empty
int list_is_empty(const List *L);

// Inserts a new node at the end of the list
void list_add_last(List *L, ListInfo k);

// Removes the first node in the list by returning value
ListInfo list_remove_first(List *L);

// Print list
void list_print(const List *L);

// Predecessor to the list of fathers does not exist
const int NODE_UNDEF = -1;

typedef enum { WHITE, GREY, BLACK } Color; // Node Colors

// Visit the amplitude graph
int bfs( const Graph *g,
         int s,  // Source Node
         int *d, // d[i] is the minimum distance of node i from the source node
         int *p  // p[i] is the predecessor of node i along the minimum path from s to i
)
{
    const int n = graph_n_nodes(g);
    List *q;
    int nvisited = 0;
    int i;
    Color *color = (Color*)malloc(n * sizeof(*color));

    assert(color != NULL);
    assert( (s>=0) && (s<n) );

    for (i=0; i<n; i++) {
        d[i] = -1;
        p[i] = NODE_UNDEF;
        color[i] = WHITE;
    }

    d[s] = 0;
    color[s] = GREY;
    q = list_create();
    list_add_last(q, s);

    while ( ! list_is_empty(q) ) {
        const int u = list_remove_first(q);
        const Edge *edge;
        nvisited++;
        for (edge = graph_adj(g, u); edge != NULL; edge = edge->next) {
            const int v = edge->dst;
            assert(u == edge->src);
            if (color[v] == WHITE) { // Unvisited node
                color[v] = GREY;
                d[v] = d[u] + 1;
                p[v] = u;
                list_add_last(q, v);
            }
        }
        color[u] = BLACK;
    }
    list_destroy(q);
    free(color);
    return nvisited;
}

// Print the minimum path from s to d
void print_path(int s, int d, const int *p)
{
    if (s == d)
        printf("%d", s);
    else if (p[d] < 0)
        printf("Unreachable");
    else {
        print_path(s, p[d], p);
        printf("->%d", d);
    }
}

// Print distance and paths of all nodes from source node
void print_bfs( const Graph *g, int src, const int *d, const int *p )
{
    const int n = graph_n_nodes(g);
    int v;

    assert(p != NULL);
    assert(d != NULL);

    printf("  src | dest | distance | path\n");
    printf("------+------+----------+-------------------------\n");
    for (v=0; v<n; v++) {
        printf(" %4d | %4d | %8d | ", src, v, d[v]);
        print_path(src, v, p);
        printf("\n");
    }
}

int main( int argc, char *argv[] )
{
    Graph *G;
    int nvisited;
    int *p, *d;
    FILE *filein = stdin;
    int src = 0, n;

    if (argc != 3) {
        fprintf(stderr, "Invoke the program with: %s src_node file_graph\n", argv[0]);
        return EXIT_FAILURE;
    }

    src = atoi(argv[1]);

    if (strcmp(argv[2], "-") != 0) {
        filein = fopen(argv[2], "r");
        if (filein == NULL) {
            fprintf(stderr, "Cannot open %s\n", argv[2]);
            return EXIT_FAILURE;
        }
    }

    G = graph_read_from_file(filein);
    n = graph_n_nodes(G);
    assert((src >= 0) && (src < n));
    p = (int*)malloc( n * sizeof(*p) ); assert(p != NULL);
    d = (int*)malloc( n * sizeof(*d) ); assert(d != NULL);
    nvisited = bfs(G, src, d, p);
    print_bfs(G, src, d, p);
    printf("# %d nodes on %d reachable from source %d\n", nvisited, n, src);
    graph_destroy(G);
    free(p);
    free(d);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
