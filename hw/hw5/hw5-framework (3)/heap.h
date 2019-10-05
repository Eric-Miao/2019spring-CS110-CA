/*
 * File: heap.h
 * 
 *   Declaration of a min priority queue data structure and library functions
 *     manipulating the priority queue. Feel free to add, remove, or modify
 *     these declarations to serve your algorithm.
 *  
 * Jose @ ShanghaiTech University
 *
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include "node.h"

/* Define initial capacity to be 1000. */
#define INIT_CAPACITY 1000


/* 
 * Structure of a min prority queue (min heap) of cell nodes.
 *
 */
typedef struct heap_t
{
    node_t **nodes;     /* Array of node pointers. */
    int size;           /* Current size. */
    int capacity;       /* Temporary capacity. */
} heap_t;

/* Function prototypes. */
heap_t *heap_init (void);
void heap_destroy (heap_t *h);
void heap_insert (heap_t *h, node_t *n);
node_t *heap_extract (heap_t *h);
void heap_update (heap_t *h, node_t *n);

#endif
