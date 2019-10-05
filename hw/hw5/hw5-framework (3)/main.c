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
int
main (int argc, char *argv[])
{
    maze_t *maze;
    heap_t *openset;
    node_t *n;

    assert(argc == 2);  /* Must have given the source file name. */

    /* Initializations. */
    maze = maze_init(argv[1]);
    openset = heap_init();
    maze->start->gs = 0;
    maze->start->fs = heuristic(maze->start, maze->goal);
    heap_insert(openset, maze->start);

    /* Loop and repeatedly extracts the node with the highest f-score to
       process on. */
    while (openset->size > 0) {
        int direction;
        node_t *cur = heap_extract(openset);
        
        if (cur->mark == GOAL)  /* Goal point reached. */
            break;

        cur->closed = true;

        /* Check all the neighbours. Since we are using a block maze, at most
           four neighbours on the four directions. */
        for (direction = 0; direction < 4; ++direction) {
            node_t *n = fetch_neighbour(maze, cur, direction);
            
            if (n == NULL || n->mark == WALL || n->closed)
                continue;   /* Not valid, or closed already. */

            if (n->opened && cur->gs + 1 >= n->gs)
                continue;   /* Old node met, not getting shorter. */

            /* Passing through CUR is the shortest way up to now. Update. */
            n->parent = cur;
            n->gs = cur->gs + 1;
            n->fs = n->gs + heuristic(n, maze->goal);
            if (!n->opened) {   /* New node discovered, add into heap. */
                n->opened = true;
                heap_insert(openset, n);
            } else              /* Updated old node. */
                heap_update(openset, n);
        }
    }

    /* Print the steps back. */
    n = maze->goal->parent;
    while (n != NULL && n->mark != START) {
        maze_print_step(maze, n);
        n = n->parent;
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
