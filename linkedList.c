#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "assert.h"

linkedList* linkedList_generate(){
	return (linkedList*) malloc(sizeof(linkedList));
}

void linkedList_addToFront(linkedList* list,intptr_t data){
	node *newnode = (node*) malloc(sizeof(node));
	newnode->data = data;

	list->tail = list->head;
	list->head = newnode;
	list->head->next = list->tail;
}

void linkedList_addToEnd(linkedList* list,intptr_t data){
	node *newnode = (node*) malloc(sizeof(node));
	newnode->data = data;
	
	list->tail = list->head;

	while(list->tail->next != NULL)
		list->tail = list->tail->next;

	list->tail->next = newnode;
}

void linkedList_RemoveFromFront(linkedList* list){
	
	list->tail = list->head;	
	list->head = list->head->next;

	free(list->tail);
}

//note: This will have o(n) complexity
void linkedList_RemoveFromEnd(linkedList* list){
	
	list->tail = list->head;

	while(list->tail->next->next != NULL){
		free(list->tail->next);
	}
}


void linkedList_free(linkedList* list){
	list->tail = list->head;
	
	while (list->tail->next != NULL){
		list->tail = list->tail->next;
		list->head = list->tail;
		free(list->head);
	}
	free(list->tail);
}

void linkedList_print(linkedList* list){
	
	
}

//callenges:


// -- tests --
//	note: important to test for memory leaks also,
//  use valgrind
void testList(){
	linkedList* list = linkedList_generate();
	
	for(size_t s = 0;s < 20; s++){
		linkedList_addToFront(list,1);
	}
	
	for(size_t s = 0;s < 20; s++){
		linkedList_addToEnd(list,2);
	}
	linkedList_free(list); //check for memory leaks
	
	linkedList* num = linkedList_generate();
	linkedList_addToFront(num,2);
	linkedList_addToFront(num,1);
	linkedList_addToEnd(num,3);
	linkedList_addToEnd(num,4);
	//num: 1 -> 2 -> 3 -> 4
	
	node* tail = num->head;
	for(intptr_t i = 1;i<=4;i++){
		assert(tail->data == i);
		tail = tail->next;
	}
	
	linkedList_RemoveFromEnd(num);
	//num: 1 -> 2 -> 3
	tail = num->head;
	for(intptr_t i = 1;i<=3;i++){
		assert(tail->data == i);
		tail = tail->next;
	}
	
	linkedList_RemoveFromFront(num);
	//num: 2 -> 3
	tail = num->head;
	for(intptr_t i = 2;i<=3;i++){
		assert(tail->data == i);
		tail = tail->next;
	}
	
	linkedList_RemoveFromFront(num);
	linkedList_RemoveFromFront(num);
	assert(num->head == NULL);
	assert(num->tail == NULL);
	linkedList_free(num);
}

