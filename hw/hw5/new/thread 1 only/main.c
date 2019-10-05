/*
 * File: main.c
 * 
 *   Main body of A* path searching algorithm on a block maze. The maze is
 *     given in a source file, whose name is put as a command-line argument.
 *     Then it should perform an A* search on the maze and prints the steps
 *     along the computed shortest path back to the file.
 *
 *     * Heuristic function chosen as the "Manhattan Distance":
 *
 *         heuristic(n1, n2) = |n1.x - n2.x| + |n1.y - n2.y|
 *
 *     * The whole procedure, including I/O and computing, will be time-
 *         ticked. So you are allowed to modify and optimize everything in
 *         this file and in all the libraries, as long as it satisfies:
 *
 *         1. It performs an A* path searching algorithm on the given maze.
 *
 *         2. It computes one SHORTEST (exactly optimal) path and prints the
 *              steps along the shortest path back to file, just as the
 *              original version.
 *
 *         3. Compiles with the given "Makefile". That means we are using
 *              (and only manually using) "pthread" for parallelization.
 *              Further parallelization techniques, such as OpenMP and SSE,
 *              are not required (and not allowed).
 *
 *         4. If there are multiple shortest paths, any one of them will be
 *              accepted. Please make sure you only print exactly one valid
 *              path to the file.
 *  
 * Jose @ ShanghaiTech University
 *
 */
#include <pthread.h>
#include <stdlib.h>     /* NULL */
#include <assert.h>     /* assert */
#include "heap.h"
#include "node.h"
#include "maze.h"
#include "compass.h"    /* The heuristic. */

/* Local helper functions. */
static node_t *fetch_neighbour (maze_t *m, node_t *n, int direction);

/*
 * Entrance point. Time ticking will be performed on the whole procedure,
 *   including I/O. Parallelize and optimize as much as you can.
 *
 */

maze_t *maze;
heap_t *openset;
node_t *n;
heap_t *openset_r;
node_t *m;


void*
reverse_loop()
{    while (openset_r->size > 0) {
        int direction;
        node_t *cur = heap_extractR(openset_r);

        if (cur->mark == START)  /* Goal point reached. */
            break;

        cur->closed = true;

        /* Check all the neighbours. Since we are using a block maze, at most
           four neighbours on the four directions. */
        for (direction = 0; direction < 4; ++direction) {
            node_t *m = fetch_neighbour(maze, cur, direction);

            if (n == NULL || n->mark == WALL || n->closed)
                continue;   /* Not valid, or closed already. */

            if (n->opened && cur->Rgs + 1 >= n->Rgs)
                continue;   /* Old node met, not getting shorter. */

            /* Passing through CUR is the shortest way up to now. Update. */
            n->parentR = cur;
            n->Rgs = cur->Rgs + 1;
            n->Rfs = n->Rgs + heuristic(m, maze->start);
            if (!n->opened) {   /* New node discovered, add into heap. */
                n->opened = true;
                heap_insertR(openset_r, n);
            } else              /* Updated old node. */
                heap_updateR(openset_r, n);
        }
    }

    return (void*)0;
}

int
main (int argc, char *argv[])
{

    pthread_t thread;
    int err;

    assert(argc == 2);  /* Must have given the source file name. */

    /* Initializations. */
    maze = maze_init(argv[1]);
    openset = heap_init();
    maze->start->Fgs = 0;
    maze->start->Ffs = heuristic(maze->start, maze->goal);
    heap_insertF(openset, maze->start);

    maze = maze_init(argv[1]);
    openset_r = heap_init();
    maze->start->Rgs = 0;
    maze->start->Rfs = heuristic(maze->start, maze->goal);
    heap_insertR(openset_r, maze->goal);


    /* Loop and repeatedly extracts the node with the highest f-score to
       process on. */
    while (openset->size > 0) {
        int direction;
        node_t *cur = heap_extractF(openset);
        
        if (cur->mark == GOAL)  /* Goal point reached. */
            break;

        cur->closed = true;

        /* Check all the neighbours. Since we are using a block maze, at most
           four neighbours on the four directions. */
        for (direction = 0; direction < 4; ++direction) {
            node_t *n = fetch_neighbour(maze, cur, direction);
            
            if (n == NULL || n->mark == WALL || n->closed)
                continue;   /* Not valid, or closed already. */

            if (n->opened && cur->Fgs + 1 >= n->Fgs)
                continue;   /* Old node met, not getting shorter. */

            /* Passing through CUR is the shortest way up to now. Update. */
            n->parentF = cur;
            n->Fgs = cur->Fgs + 1;
            n->Ffs = n->Fgs + heuristic(n, maze->goal);
            if (!n->opened) {   /* New node discovered, add into heap. */
                n->opened = true;
                heap_insertF(openset, n);
            } else              /* Updated old node. */
                heap_updateF(openset, n);
        }
    }
    err = pthread_create(&thread,NULL,reverse_loop,NULL);
    if(err!=0) printf("fucking siliy problem occurred");

    /* Print the steps back. */
    n = maze->goal->parentF;
    while (n != NULL && n->mark != START) {
        maze_print_step(maze, n, 0);
        n = n->parentF;
    }
    /* Free resources and return. */
    heap_destroy(openset);
    maze_destroy(maze);
    return 0;
}

/*
 * Fetch the neighbour located at direction DIRECTION of node N, in the
 *   maze M. Returns pointer to the neighbour node.
 *
 */
static node_t *
fetch_neighbour (maze_t *m, node_t *n, int direction)
{
    switch (direction) {
        case 0: return maze_get_cell(m, n->x, n->y - 1);
        case 1: return maze_get_cell(m, n->x + 1, n->y);
        case 2: return maze_get_cell(m, n->x, n->y + 1);
        case 3: return maze_get_cell(m, n->x - 1, n->y);
    }
    return NULL;
}
