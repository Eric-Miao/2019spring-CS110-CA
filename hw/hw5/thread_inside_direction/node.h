/*
 * File: node.h
 * 
 *   Declaration of a block cell node data structure and library functions
 *     manipulating the node. Feel free to add, remove, or modify these
 *     declarations to serve your algorithm.
 *  
 * Jose @ ShanghaiTech University
 *
 */

#ifndef _NODE_H_
#define _NODE_H_

/* 
 * Introduce the "bool" type. Though I really love C/C++, I would still say
 *   it is stupid for not even defining a standard "bool" type in ANSI C
 *   standard.
 *
 */
typedef int bool;
#define true  (1)
#define false (0)

/* 
 * Explicitly defines the four different node types.
 *   START: start point
 *   GOAL:  goal point
 *   WALL:  wall block, cannot step on / move across
 *   NONE:  normal blank point
 *
 */
typedef enum {START, GOAL, WALL, NONE} mark_t;

/* 
 * Structure of a block cell node.
 *
 */
typedef struct node_t
{
    int x;          /* X coordinate, starting from 0. */
    int y;          /* Y coordinate, starting from 0. */
    int Fgs;         /* A* g-score in front search. */
    int Ffs;         /* A* f-score in front search. */
    int Rgs;         /* A* g-score in reverse search. */
    int Rfs;         /* A* f-score in reverse search. */
    mark_t mark;    /* Node type. */
    int heap_idF;    /* Position on min front_heap, used by updating. */
    int heap_idR;
    bool reverse_flag; /*Has been discovered by reverse loop?*/
    bool opened;    /* Has been discovered? */
    bool closed;    /* Has been closed? */
    struct node_t *parentF;  /* Parent node along the forward path. */
    struct node_t *parentR;  /* Parent node along the reverse path. */
} node_t;

/* Function prototypes. */
node_t *node_init (int x, int y, mark_t mark);
void node_destroy (node_t *n);
bool node_lessF (node_t *n1, node_t *n2);
bool node_lessR (node_t *n1, node_t *n2);

#endif
