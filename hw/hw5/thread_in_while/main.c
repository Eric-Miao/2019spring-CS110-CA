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
node_t *print_node;

int stop_flag;
int final_flag;

pthread_mutex_t g_mutex;

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
loop_reverse(){

    int direction;

    curR = heap_extractR(openset_r);

    if (curR->mark == START){  /* Goal point reached. */
        final_flag = 1;
        return (void*)0;
    }

    curR->closed = true;
    /* Check all the neighbours. Since we are using a block maze, at most
       four neighbours on the four directions. */
    for (direction = 0; direction < 4; ++direction) {
        node_t *m = fetch_neighbour(maze, curR, direction);

        if (m == NULL || m->mark == WALL || m->closed)
            continue;   /* Not valid, or closed already. */

        if (m->opened && curR->Rgs + 1 >= m->Rgs)
            continue;   /* Old node met, not getting shorter. */

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

    }
    return (void*)0;
}

void
forward_loop() {

    int direction;

    node_t *cur = heap_extractF(openset);



    if (cur->mark == GOAL){  /* Goal point reached. */
        final_flag = 1;
        return;
    }
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

        /*printf("X: %d Y: %d \n",n->x,n->y);*/

        if (!n->opened) {   /* New node discovered, add into heap. */
            n->opened = true;
            heap_insertF(openset, n);
            /*printf("New node.\n");*/
        } else{              /* Updated old node. */
            heap_updateF(openset, n);
            stop_flag=1;
            /*printf("Old node.\n");*/

        }
        if(n->opened&&n->reverse_flag==true){
/*
            printf("\nf*****************k\n");
            printf("n->Rgs + n->Fgs = %d + %d = %d\n",n->Rgs,n->Fgs,n->Fgs+n->Rgs);
            printf("heap_F->Fgs+heap_R->Rgs = %d + %d = %d\n",

                   openset->nodes[1]->Fgs,openset_r->nodes[1]->Rgs,
                   openset->nodes[1]->Fgs+openset_r->nodes[1]->Rgs);*/
            /*printf("f*****************k\n\n");*/
            if((openset->nodes[1]->Fgs+openset_r->nodes[1]->Rgs)>=(n->Rgs + n->Fgs)){
                /*printf("yes, criteria met\n");*/
                final_flag = 1;
                print_node = n;
                return;
            }
        }
        stop_flag=0;
    }
    print_node = maze->goal->parentF;
}

int
main (int argc, char *argv[])
{
    /*int err;

    pthread_t temp;

    pthread_t *reverse_search=&temp;*/

    pthread_mutex_init(&g_mutex, NULL);

    assert(argc == 2);  /* Must have given the source file name. */
    /* flag is here to indicate
    whether we have reached the stopping point
    0 ofr not stop, 1 for stop*/
    stop_flag = 0;
    final_flag = 0;
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


    while (openset->size > 0 && openset_r->size > 0 && final_flag == 0)
    {
        /*put the reverse loop in the second thread*/
        /*printf("I am here before second thread.\n");
        err = pthread_create(reverse_search,NULL,&loop_reverse,NULL);
        if (err != 0) printf("can't create thread\n");
        else printf("thread created\n");*/

        forward_loop();
    }

    /* Print the steps back from loop_forward.*/
    n = print_node;
    while (n != NULL && n->mark != START) {
        maze_print_step(maze, n, 0);
        n = n->parentF;
    }
    /* Free resources and return. */
    heap_destroy(openset);
    maze_destroy(maze);
    heap_destroy(openset_r);
    /*printf("I am here before 2nd destroy.\n");*/
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
