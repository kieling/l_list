#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "assert.h"

linkedList* linkedList_generate(){
	linkedList *aux = (linkedList*) malloc(sizeof(linkedList));

    if (aux == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }    

    aux->tail = NULL;
    aux->head = NULL;

	return aux;
}

void linkedList_addToFront(linkedList* list,intptr_t data){
	node *newnode = (node*) malloc(sizeof(node));
	newnode->data = data;
	newnode->next = NULL;

	if (!list->head)
	{
		list->head = newnode;	
		list->tail = newnode;
	}
	else{
		newnode->next = list->head;
		list->head = newnode;
	}
}

void linkedList_addToEnd(linkedList* list,intptr_t data){
	node *newnode = (node*) malloc(sizeof(node));
	newnode->data = data;
	newnode->next = NULL;

	if (!list->tail)
	{
		list->head = newnode;	
		list->tail = newnode;
	}
	else{
		list->tail->next = newnode;
		list->tail = newnode;	
	}

}

void linkedList_RemoveFromFront(linkedList* list){
	node *aux = list->head;

	if (list->head == NULL)
		return ; 

	if(list->head->next == NULL){
		free(aux);
		list->head = NULL;
		list->tail = NULL;
	} 
	else{
		list->head = list->head->next;
		free(aux);
	}

}

//note: This will have o(n) complexity
void linkedList_RemoveFromEnd(linkedList* list){
	node *aux = list->head;

	if (list->tail == NULL)
		return ; 

	if(list->head->next == NULL){
		free(aux);
		list->head = NULL;
		list->tail = NULL;
	} 
	else{		
		while(aux->next != list->tail)
			aux = aux->next;
		
		free(aux->next);
		list->tail = aux;
		list->tail->next = NULL;
	}
}


void linkedList_free(linkedList* list){	
	node *aux, *auxfree;
	aux = list->head;

	if(list->head != NULL)
	{
		while (aux->next != NULL){
			auxfree = aux;
			aux = aux->next;
			free(auxfree);
		}	
		free(aux);
	}

	free(list);
}

void linkedList_print(linkedList* list){
	node *aux = list->head;

	if (list->head == NULL)
		return;

	printf("List:\t");

	while(aux->next != NULL){
		printf("%ld\t", aux->data); 
		aux = aux->next;
	};
	printf("%ld\n", aux->data); 
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
	
	node* curr = num->head;
	for(intptr_t i = 1;i<=4;i++){
		assert(curr->data == i);
		curr = curr->next;
	}
	
	linkedList_RemoveFromEnd(num);
	//num: 1 -> 2 -> 3
	curr = num->head;
	for(intptr_t i = 1;i<=3;i++){
		assert(curr->data == i);
		curr = curr->next;
	}
	
	linkedList_RemoveFromFront(num);
	//num: 2 -> 3
	curr = num->head;
	for(intptr_t i = 2;i<=3;i++){
		assert(curr->data == i);
		curr = curr->next;
	}
	
	linkedList_RemoveFromFront(num);
	linkedList_RemoveFromFront(num);
	assert(num->head == NULL);
	assert(num->tail == NULL);
	linkedList_free(num);
}
