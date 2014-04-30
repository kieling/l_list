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

void linkedList_ReverseList(linkedList* list){
	if (list->head == NULL)
		return ;
	
	node *aux = NULL; 

	/* Ex: 0   1->2->3
		aux = 0    next = 2  
		1->0  2->3
		aux = 1   next = 3
		2->1->0  3
		aux = 2   next = null
		3->-2->1->0 
	*/
	
	do {

		node *next = list->head->next; 
		list->head->next = aux;
		aux = list->head;
		list->head = next;

	} while (list->head != NULL);

	list->head = aux;
}

void linkedList_RemoveKth(linkedList* list, int element){
	if ((list->head == NULL) || (element == 0))
		return ; 

	int i = 0;
	node *aux = list->head;
	node *before; 

	if (element == 1)
	{
		list->head = list->head->next;
		free(aux);
		return ;
	}

	/*
		Ex: 1 -> 2 -> 3 
		aux = 2 
		aux->next = 3
		before = 1;
		free(aux) (2)
		before->next = 3 (1 -> 3)
	*/
	do
	{
		if (aux && aux->next){
			before = aux; 
			aux = aux->next;
			i++;
		}
		else{
			printf("List doesnt have that number of elements\n");	
			return ; 
		}
	} while(i < (element-1));

	before->next = aux->next; 

	free(aux);
}

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
	
	linkedList* num1 = linkedList_generate();
	linkedList_addToFront(num1,2);
	linkedList_addToFront(num1,1);
	linkedList_addToEnd(num1,3);
	linkedList_addToEnd(num1,4);
	linkedList_addToEnd(num1,6);
	//num: 1 -> 2 -> 3 -> 4
	printf("\nList:\n");
	linkedList_print(num1);

	
	printf("\nReverting list:\n");
	linkedList_ReverseList(num1);
	linkedList_print(num1);

	printf("Reverting back:\n");
	linkedList_ReverseList(num1);
	linkedList_print(num1);

	printf("\nTesting Kth remove:\n");

	printf("Removing the second element:\n");
	linkedList_RemoveKth(num1, 2);
	linkedList_print(num1);

	printf("Removing the first element:\n");
	linkedList_RemoveKth(num1, 1);
	linkedList_print(num1);

	printf("Removing the 4th element:\n");
	linkedList_RemoveKth(num1, 4);
	linkedList_print(num1);

	linkedList_free(num1);


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
