#ifndef LINKEDLIST_H 
#define LINKEDLIST_H

#include <stdint.h> 



typedef struct node {
	intptr_t data; 		// signed integer type which is guaranteed to be able to hold an address
	struct node *next;
} node;

typedef struct linkedList {
	node *head;		// the data present on this node
	node *tail;
} linkedList;

//prototypes of the functions that have to be implemented
linkedList* linkedList_generate();
void linkedList_free(linkedList* list);
void linkedList_addToFront(linkedList* list,intptr_t data);
void linkedList_addToEnd(linkedList* list,intptr_t data);
void linkedList_RemoveFromFront(linkedList* list);
void linkedList_RemoveFromEnd(linkedList* list);
void linkedList_print(linkedList* list);

//--tests -- 
void testList();
#endif