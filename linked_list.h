#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


/* ------------------------ Struct ------------------------ */


typedef struct aux_node {

	int value;
	struct aux_node* next;
	
} Node;

typedef struct LinkedList {

	Node* primeiro;
	int tamanho;
	
} LinkedList;


/* ------------------------ Functions ------------------------ */


LinkedList* createList() {

	LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
	list->tamanho = 0;
	list->primeiro = NULL;
	
	return list;
}


void push(LinkedList* pilha, int valor) {
	
	// Pilha - First in First out (adicionar no inicio e remover no inicio)
	Node* newNo = (Node*) malloc(sizeof(Node));
	newNo->value = valor;
	
	newNo->next = pilha->primeiro;
	pilha->primeiro = newNo;
	
	pilha->tamanho++;	
}

char* pop(LinkedList* pilha) {
	
	// Pilha - First in First out (adicionar no inicio e remover no inicio)
	Node* tmp = pilha->primeiro;
	pilha->primeiro = tmp->next;
	
	int pop_value = tmp->value;
	pilha->tamanho--;
	free(tmp);
	
	return pop_value;
}


void printList(LinkedList* lista) {
	
	Node* p = lista->primeiro;
		
	while(p) {
	
		printf("%i -> ", p->value);
		p = p->next;
	}
	
	printf("NULL\n");
}


void freeList(LinkedList* lista) {
	
	Node* p = lista->primeiro;
	
	while(p) {
	
		Node* tmp = p;
		p = p->next;
		free(tmp);
	}
	
	free(lista);
}
