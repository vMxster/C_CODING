/**
BST
 **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int BSTKey;

// Structure representing a node of the BST
typedef struct BSTNode {
    BSTKey key;
    struct BSTNode *parent, *left, *right;
} BSTNode;

// Structure representing a BST
typedef struct {
    BSTNode *root;
    int size;
} BST;

// Returns an empty BST
BST *bst_create( void );

// Empty BST
void bst_clear(BST *T);

// Delete BST
void bst_destroy(BST *T);

// Inserts the key into BST
void bst_insert(BST *T, BSTKey k);

// Returns the pointer to a node containing the key k
BSTNode *bst_search(const BST *T, BSTKey k);

// Delete node from BST
void bst_delete(BST *T, BSTNode *n);

// Returns the number of nodes in the BST
int bst_size(const BST *T);

// Returns true (notzero) if the tree is empty
int bst_is_empty(const BST *T);

// Returns the height of the BST
int bst_height(const BST *T);

// Print the contents of the BST
void bst_pretty_print(const BST *T);

// The functions bst_check() and bst_check_rec() are used to check whether BST structure is correct
static void bst_check_rec( const BST* T, const BSTNode *n )
{
    if (n != NULL) {
        if (n->left) {
            assert(n->left->key <= n->key);
            assert(n->left->parent == n);
            bst_check_rec(T, n->left);
        }
        if (n->right) {
            assert(n->right->key > n->key);
            assert(n->right->parent == n);
            bst_check_rec(T, n->right);
        }
    }
}

static void bst_check( const BST* T )
{
    if (T->root)
        assert(T->root->parent == NULL);
    bst_check_rec(T, T->root);
}

BST *bst_create( void )
{
    BST *T = (BST*)malloc(sizeof(*T));
    assert(T != NULL);

    T->root = NULL;
    T->size = 0;
    bst_check(T);
    return T;
}

// Recursive function that frees the memory used by node n and its descendants
static void bst_clear_rec(BSTNode *n)
{
    if (n != NULL) {
        bst_clear_rec(n->left);
        bst_clear_rec(n->right);
        free(n);
    }
}

void bst_clear(BST *T)
{
    assert(T != NULL);

    bst_clear_rec(T->root);
    T->root = NULL;
    T->size = 0;
    bst_check(T);
}

void bst_destroy(BST *T)
{
    bst_clear(T);
    free(T);
}

BSTNode *bst_search(const BST *T, BSTKey k)
{
    BSTNode *n;

    assert(T != NULL);

    n = T->root;
    while ((n != NULL) && (n->key != k)) {
        if (k < n->key)
            n = n->left;
        else
            n = n->right;
    }
    return n;
}

// Enter the key k in the subtree having n as the root
static BSTNode *bst_insert_rec(BSTNode *n, BSTNode *p, BSTKey k)
{
    if (n == NULL) {
        struct BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
        assert(node != NULL);
        node->key = k;
        node->parent = p;
        node->left = node->right = NULL;
        return node;
    } else {
        if (k <= n->key) {
            n->left = bst_insert_rec(n->left, n, k);
        } else {
            n->right = bst_insert_rec(n->right, n, k);
        }
        return n;
    }
}

void bst_insert(BST *T, BSTKey k)
{
    assert(T != NULL);

    T->root = bst_insert_rec(T->root, NULL, k);
    T->size++;
    bst_check(T);
}


// Returns the pointer to the node containing the minimum value of the subtree rooted in n.
static BSTNode *bst_minimum(BSTNode *n)
{
    assert(n != NULL);

    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}

// Replace node u with node v with its entire subtree
static void bst_transplant(BST *T, BSTNode *u, BSTNode *v)
{
    assert(T != NULL);
    assert(u != NULL);

    if (u->parent == NULL) {
        T->root = v;
    } else {
        if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// Returns the pointer to the successor of node n
static BSTNode *bst_successor(BSTNode *n)
{
    assert(n != NULL);

    if (n->right != NULL) {
        return bst_minimum(n->right);
    } else {
        BSTNode *p = n->parent;
        while ((p != NULL) && (n == p->right)) {
            n = p;
            p = p->parent;
        }
        return p;
    }
}


void bst_delete(BST *T, BSTNode *n)
{
    BSTNode *x;
    assert(T != NULL);
    assert(n != NULL);

    if (n->left == NULL && n->right == NULL)
        x = NULL;
    if (n->left == NULL && n->right != NULL)
        x = n->right;
    if (n->left != NULL && n->right == NULL)
        x = n->left;
    if (n->left != NULL && n->right != NULL) {
        x = bst_successor(n);
        n->key = x->key;
        bst_delete(T, x);
    } else {
        if (n->parent == NULL) {
            T->root = x;
        } else {
            if (n->parent->left == n) {
                n->parent->left = x;
            } else {
                n->parent->right = x;
            }
        }
        if (x != NULL)
            x->parent = n->parent;
        free(n);
        T->size--;
        bst_check(T);
    }
}

// Calculating Recursive Height
int bst_height_rec(const BSTNode *n)
{
    if (n == NULL) {
        return -1;
    } else {
        const int height_left = bst_height_rec(n->left);
        const int height_right = bst_height_rec(n->right);
        if (height_left > height_right)
            return 1 + height_left;
        else
            return 1 + height_right;
    }
}

int bst_height(const BST *T)
{
    assert(T != NULL);
    return bst_height_rec(T->root);
}

// Print the contents of the subtree rooted in node n
static void bst_print_rec( const BSTNode *n )
{
    printf("(");
    if (n != NULL) {
        printf("%d ", n->key);
        bst_print_rec(n->left);
        printf(" ");
        bst_print_rec(n->right);
    }
    printf(")");
}

void bst_print( const BST *T )
{
    assert(T != NULL);

    bst_print_rec(T->root);
    printf("\n");
}

// Prints the subtree rooted in node n that is at depth depth of the tree in which it is contained.
static void bst_pretty_print_rec( const BSTNode *n, int depth )
{
    if (n != NULL) {
        int i;
        bst_pretty_print_rec(n->right, depth+1);
        for (i=0; i<depth; i++) {
            printf("   ");
        }
        printf("%d\n", n->key);
        bst_pretty_print_rec(n->left, depth+1);
    }
}

void bst_pretty_print( const BST *T )
{
    assert(T != NULL);
    bst_pretty_print_rec(T->root, 0);
}

int bst_size(const BST *T)
{
    assert(T != NULL);

    return T->size;
}

int bst_is_empty(const BST *T)
{
    assert(T != NULL);

    return (T->root == NULL);
}
