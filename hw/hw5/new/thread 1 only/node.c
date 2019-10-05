/*
 * File: node.c
 * 
 *   Implementation of library functions manipulating a block cell node. Feel
 *     free to add, remove, or modify these library functions to serve your
 *     algorithm.
 *  
 * Jose @ ShanghaiTech University
 *
 */

#include <stdlib.h>     /* NULL, malloc, free */
#include <limits.h>     /* INT_MAX */
#include "node.h"

/* 
 * Initialize a node whose position is recorded at (X, Y) with type MARK.
 *   Returns the pointer to the new node.
 *
 */
node_t *
node_init (int x, int y, mark_t mark)
{
    node_t *n = malloc(sizeof(node_t));
    n->x = x;
    n->y = y;
    n->Fgs = INT_MAX;
    n->Ffs = INT_MAX;
    n->Rgs = INT_MAX;
    n->Rfs = INT_MAX;
    n->mark = mark;
    n->heap_idF = 0;
    n->heap_idR=0;
    n->reverse_flag = false;
    n->opened = false;
    n->closed = false;
    n->parentF = NULL;
    n->parentR = NULL;
    return n;
}

/* 
 * Delete the memory occupied by the node N.
 *
 */
void
node_destroy (node_t *n)
{
    free(n);
}

/* 
 * Defines the comparison method between nodes, that is, comparing their
 *   A* f-scores.
 *
 */
bool
node_lessF (node_t *n1, node_t *n2)
{
    return n1->Ffs < n2->Ffs;
}

bool
node_lessR (node_t *n1, node_t *n2)
{
    return n1->Rfs < n2->Rfs;
}
