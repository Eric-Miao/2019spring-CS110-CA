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
maze_t *maze;
heap_t *openset;
heap_t *openset_r;
node_t *n;
node_t *m;
node_t *curR;
node_t *cur;
int new_flag;

int direction;
/*
 * Entrance point. Time ticking will be performed on the whole procedure,
 *   including I/O. Parallelize and optimize as much as you can.
 *
 */
void
donothing(node_t *whateverinput){
    if(whateverinput!=NULL){}
    /*yeah, we do nothing here, yeah!*/
}


void*
loop_reverse() {
    printf("in the second thread.\n");
    m = fetch_neighbour(maze, curR, direction);
    new_flag = 1;

    if (m == NULL || m->mark == WALL || m->closed){
        new_flag = 0;    /* Not valid, or closed already. */
        return(void*)0;
    }
    if (m->opened && curR->Rgs + 1 >= m->Rgs) {
        new_flag = 0;    /* Old node met, not getting shorter. */
        return(void*)0;
    }
    /* Passing through CUR is the shortest way up to now. Update. */
    m->parentR = curR;
    m->Rgs = curR->Rgs + 1;
    m->Rfs = m->Rgs + heuristic(m, maze->start);
    if (!m->opened) {   /* New node discovered, add into heap. */
        m->opened = true;
        m->reverse_flag = true;
        heap_insertR(openset_r, m);
    } else              /* Updated old node. */
        heap_updateR(openset_r, m);
    return (void*)0;
}


void
forward_loop(){
    n = fetch_neighbour(maze, cur, direction);
    new_flag = 1;

    if (n == NULL || n->mark == WALL || n->closed) {
        new_flag = 0;   /* Not valid, or closed already. */
        return;
    }
    if (n->opened && cur->Fgs + 1 >= n->Fgs) {
        new_flag = 0;   /* Old node met, not getting shorter. */
        return;
    }
    /* Passing through CUR is the shortest way up to now. Update. */
    n->parentF = cur;
    n->Fgs = cur->Fgs + 1;
    n->Ffs = n->Fgs + heuristic(n, maze->goal);
    if (!n->opened) {   /* New node discovered, add into heap. */
        n->opened = true;
        heap_insertF(openset, n);
    } else{              /* Updated old node. */
        heap_updateF(openset, n);
    }
    return;
}

int
main (int argc, char *argv[]) {
    int err;
    int stop_flag;
    pthread_t temp;
    pthread_t *reverse_search = &temp;
    node_t *print_node;


    assert(argc == 2);  /* Must have given the source file name. */
    /* flag is here to indicate
    whether we have reached the stopping point
    0 ofr not stop, 1 for stop*/

    /* Initializations. */
    maze = maze_init(argv[1]);
    openset = heap_init();
    maze->start->Fgs = 0;
    maze->start->Ffs = heuristic(maze->start, maze->goal);
    heap_insertF(openset, maze->start);

    openset_r = heap_init();
    maze->goal->Rgs = 0;
    maze->goal->Rfs = heuristic(maze->start, maze->goal);
    heap_insertR(openset_r, maze->goal);

    /* Loop and repeatedly extracts the node with the highest f-score to
       process on. */
    while (openset->size > 0 && stop_flag!=1) {
        stop_flag=0;
        cur = heap_extractF(openset);
        if (cur->mark == GOAL)  /* Goal point reached. */
            break;
        cur->closed = true;

        curR = heap_extractR(openset_r);
        if (curR->mark == START)  /* Goal point reached. */
            break;
        curR->closed = true;
        /* Check all the neighbours. Since we are using a block maze, at most
           four neighbours on the four directions. */
        for (direction = 0; direction < 4; ++direction) {
            new_flag = 0;

            err = pthread_create(reverse_search, NULL, &loop_reverse, NULL);
            if (err != 0) printf("can't create thread\n");

            forward_loop();

            if (new_flag == 1 && n->opened && n->reverse_flag == true) {
                printf("\nf*****************k\n");
                printf("n->Rgs + n->Fgs = %d + %d = %d\n", n->Rgs, n->Fgs, n->Fgs + n->Rgs);
                printf("heap_F->Fgs+heap_R->Rgs = %d + %d = %d\n",
                       heap_extractF(openset)->Fgs, heap_extractR(openset_r)->Rgs,
                       heap_extractF(openset)->Fgs + heap_extractR(openset_r)->Rgs);
                printf("f*****************k\n\n");
                if ((heap_extractF(openset)->Fgs + heap_extractR(openset_r)->Rgs) >= (n->Rgs + n->Fgs)) {
                    printf("yes, criteria met\n");
                    print_node = n;
                    stop_flag=1;
                }
            }
        }

    }

    /* Print the steps back from loop_forward.*/
    /*n = maze->goal->parentF;
    n = print_node;
    while (n != NULL && n->mark != START) {
        maze_print_step(maze, n, 0); 0 for printing the way, 1 for reset
        n = n->parentF;
    }
    */
    /* Free resources and return. */

    donothing(print_node);
    heap_destroy(openset);
    maze_destroy(maze);
    printf("I am here before 2nd destroy.\n");
    heap_destroy(openset_r);
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
