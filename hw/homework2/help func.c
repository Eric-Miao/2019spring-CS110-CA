
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef DOUBLL_H
#define DOUBLL_H

/* Header file for a doubly linked list.The header elements of a list have a NULL poiter for data and 0 for size. */
typedef struct doubll_item doubll_item;

struct doubll_item
{
    /*start to construct the struct*/
    doubll_item *prev;
    doubll_item *next;
    void *data;
    size_t size;
    /*some basic items inside the struct*/
};
/* The doubly linked list. */
typedef struct doubll doubll;

/*start to create my doubll struct*/
struct doubll
{
    doubll_item head;
    doubll_item tail;
    size_t items;
    /*my struct finish defined */
};
/* Initialize doubly linked list.
   There will be no testcases that list is NULL. */
void list_init (doubll *list){
    /* to malloc some space for head and tail of the list*/
    list->items=0;
    /*initialize the property of head*/
    list->head.data=NULL;
    list->head.size=0;
    list->head.next=&list->tail;
    list->head.prev=NULL;
    /*initialize the property of tail*/
    list->tail.data=NULL;
    list->tail.size=0;
    list->tail.next=NULL;
    list->tail.prev=&list->head;
}
/*this is the function that will be called when there is a check_list macro.*/
#ifdef CHECK_LIST

static bool check_list(doubll *list, doubll_item *item){
    doubll_item* temp = list->head.next;
    /*run through the list, stop when we meet the item in the list, or meet the tail;*/
    while (temp!=&list->tail && temp!=item){
        temp = temp->next;
    }
    /*if temp==item, it means there is the item in the list, else doesn't;*/
    if(temp==item) return 1;
    else return 0;
}

#endif /*CHECK_LIST*/


/*to check each a time a function is called to check if list, tail, head does exit and tail
,head does hold a data not equal to NULL size > 0*/
static bool pre_check(doubll* list){
    /*below are the conditions TATATATATATATAT just so many of them*/
    if(list!=NULL && list->head.prev==NULL && list->head.next!=NULL && list->tail.next==NULL
       && list->tail.prev!=NULL && (int)list->items>=0
       && list->head.data==NULL && list->tail.data==NULL && (int)list->head.size>=0
       && (int)list->tail.size>=0) return 1;
        /*I will return next*/
    else return 0;
}
/*to check if the given list is connected*/
static bool connectivity(doubll* list){
    doubll_item* temp=list->head.next;
    int i, flag1, flag2;
    /*check if I can get to tail from head*/
    for(i = 0;i<(int)list->items && temp!=&list->tail && temp->next!=NULL; i++){
        temp=temp->next;
    }
    if (temp==&list->tail) flag1 = 1;
    /*check if I can get to head from tail*/
    temp = list->tail.prev;
    for(i = 0;i<(int)list->items && temp!=&list->head && temp->prev!=NULL; i++){
        temp=temp->prev;
    }
    /*only when both way are connected, then the list is connected.*/
    if(temp==&list->head) flag2 = 1;

    if(flag1==1 && flag2 ==1) return 1;
    else return 0;
}
/* For the following 3 functions, return NULL on error.*/
doubll_item *list_begin (doubll *list){
    if(!pre_check(list))  return NULL;
    if(list->head.next!=NULL) return list->head.next;
    else return NULL;
}
/* Return list's head. */
doubll_item *list_head (doubll *list){
    if(pre_check(list)) return &list->head;
    else return NULL;
}
/* Return list's tail. */
doubll_item *list_end (doubll *list){
    if(pre_check(list)) return &list->tail;
    else return NULL;
}
/* Return number of elements in a list.
   Return -1 on error. */
size_t list_size (doubll *list){
    if(pre_check(list)) return list->items;
    else return (size_t)-1;
}
/* Insert a new item in the list after the item item. The data is copied. The
   new item is returned. Returns NULL on error.
   If the marco CHECK_DLLIST is set your code has to check if the item item is
   actually member of the list. This check is slow...
   If the marco CHECK_DLLIST is not set your code shall not perform that check
   but rather run very fast. */
doubll_item *insert_list (doubll *list, doubll_item *item, void *data, size_t size){
    doubll_item *node;
    void* data_node;
    /*malloc a new space for the new node and check is malloc successfully;
    since *data is only a pointer, so we also have to malloc the space it points to.*/
    if(item == &list->tail) return NULL;
    /*you cannot insert after tail*/
    if(data == NULL) return NULL;
    if(!connectivity(list)) return NULL;
    if(size<=0) return NULL;
    if(!pre_check(list)) return NULL;
    /*Above r checking some basic failure*/
    if(item == NULL || item->next==NULL ) return NULL;
#ifdef CHECK_LIST
    /*when check_list returns 0, then no item, no where to insert.*/
    if(!check_list(list,item)) return NULL;
#endif /*CHECK_LIST*/
    /*first malloc a place to store the new node;*/
    node = (doubll_item*)malloc(sizeof(doubll_item));
    data_node = (void*)malloc(size);
    if (node == NULL || data_node==NULL){
        return NULL;
        /*to avoid the failure caused by malloc*/
    }
    else{
        /*if there is an item before item, insert as normal;*/
        node->data = data_node;
        node->size=size;
        memcpy(node->data,data,node->size);
        /*adjust the chain between the node;*/
        node->prev=item;
        node->next=item->next;
        /*in case item is tail or head*/
        if(item->next!=&list->tail) {item->next->prev=node;}
        else {
            list->tail.prev=node;
            node->next=&list->tail;
        }
        /*in case item is tail or head*/
        if(item!=&list->head) item->next=node;
        else {
            list->head.next=node;
            node->prev=&list->head;
        }
    }
    /*insertion means only more item in the list*/
    list->items++;
    return node;
}
/* Remove the item from the list and returns the next item. Returns NULL on error.*/
doubll_item *remove_item (doubll *list, doubll_item *item){
    if(item==&list->head||item==&list->tail) return NULL;
    /*this is to make sure I have enough comments*/
    if(!pre_check(list)) return NULL;
    if(!connectivity(list)) return NULL;
    /*Above r checking some basic failure*/
#ifdef CHECK_LIST
    /*when check_list returns 0, then no item, no where to insert.*/
    if(!check_list(list,item)) return NULL;
#endif /*CHECK_LIST*/
    if(item!=NULL && item->next!=NULL && item->prev!=NULL){
        /*only remove when its able to be removed*/
        doubll_item* ret = item->next;
        item->prev->next=item->next;
        item->next->prev=item->prev;
        /*since item and its data all have been malloced, so they both need to be freed*/
        free(item->data);
        free(item);
        /*this is to adjust the property of the list count.*/
        list->items--;
        /*since the "item" pointer is already freed, so to locate the next item,*/
        /*I use another variable on stack that will be freed automatically to store it.*/
        return ret;
    }
    else return NULL;

}

/* Purge all items from the list.
   There will be no testcases that list is NULL. */
void purge_list (doubll *list){
    doubll_item* iter=list->head.next;
    doubll_item* temp=iter;
    /*delete from the first item after head until we meet the tail;*/
    while(iter->next!=NULL){
        temp=iter;
        iter=iter->next;
        /*free both mallocation*/
        free(temp->data);
        free(temp);
    }
    /*reconnect head and tail;*/
    list->head.next=&list->tail;
    list->tail.prev=&list->head;
    /*reset the 'items' variable*/
    list->items = 0;
}

/* return true when a is less than b;*/

typedef bool list_less_func (const void *a, const void *b);

/*below is a help function which helps me do the swap in the sorting function.*/
static void swap(doubll_item *a, doubll_item *b){
    doubll_item *temp;
    void* temp_data;
    /*initialize the new object*/
    temp = (doubll_item*)malloc(sizeof(doubll_item));
    temp_data = malloc(a->size);
    temp->data=temp_data;
    temp->size=a->size;
    /*copy from a to temp, a brand new node;*/
    memcpy(temp->data,a->data,temp->size);
    *temp->next=*a->next;
    *temp->prev=*a->prev;
    /*fill b into a's place*/
    a->next->prev = b;
    a->prev->next = b;
    /*fill temp into b's place;*/
    b->next->prev = temp;
    b->prev->next = temp;
    /*adjust temp*/
    temp->next=b->next;
    temp->prev=b->prev;
    /*adjust b*/
    b->next = a->next;
    b->prev = a->prev;
    /*a is now out of the list, let's free it.*/
    free(a->data);
    free(a);
}
/* Sort the list in nondecreasing according to comparison function less.
   There will be no testcases that list or less is NULL. */
void sort_list (doubll *list, list_less_func *less){

    int size = (int)list->items;
    int i,j;/*iter*/
    doubll_item *temp1;
    /*temp1 is always now*/
    doubll_item *temp2;
    /*temp2 is the next.*/
    for (i=size-1;i>=1;i--){
        temp1=list->head.next;
        for(j=0;j<=i-1;j++){
            /*so now,temp2 is always the one after temp1;*/
            temp1=temp1->next;
            temp2=temp1->next;
            /*if temp1 is smaller, then no changed should be made*/
            if (less(temp2,temp1)){swap(temp1,temp2);}
            /*if swapped, then in the swap function, I actually swapped
             the data, size and position property of the two nodes,
             so that now temp1 does hold all the info that temp2 used to have
             that means it has already moved one step forward, no need to
             change again.
            */
        }
    }
}
#endif /* doubll.h */
//
//
//
//
///*below is a help function which helps me do the swap in the sorting function.*/
//static void swap(doubll_item *a, doubll_item *b){
//    /*copy from a to temp, a brand new node;*/
//    doubll_item* aprev = a->prev;
//    doubll_item* anext = a->next;
//    doubll_item* bprev = b->prev;
//    doubll_item* bnext = b->next;
//    /*now exchange the pointers of a*/
//    a->prev = bprev;
//    a->next = bnext;
//    bprev->next = a;
//    bnext->prev = a;
//    /*now exchange the pointers of b*/
//    b->prev = aprev;
//    b->next = anext;
//    aprev->next = b;
//    anext->prev = b;
//}

