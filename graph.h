#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 8
#define TRUE 1
#define FALSE 0

typedef char* Elemento;
typedef int boolean;

/*-----------------------------------Structs---------------------------------------------*/


typedef struct aux_no {

    Elemento valor;
    struct aux_no* proximo;
    
} No;


typedef struct Graph{

    int numVertices;
    No** ListaAdj;
    int livre;

} Graph;


/*-----------------------------------Functions---------------------------------------------*/


// Criar um novo Grafo vazio com V vertices
Graph* createGraph(int numVertices) {

    Graph* newGraph = (Graph*) malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;
    newGraph->ListaAdj = (No**) malloc(numVertices * sizeof(No*));
    newGraph->livre = 0;

    // Inicializar a Lista de Adj
    for (int i=0; i < numVertices; i++) {
        newGraph->ListaAdj[i] = NULL;
    }

    return newGraph;
}


// Criar um novo No para um Vertice na ListaAdj
No* createNo(Elemento valor) {

	No* newNo = (No*) malloc(sizeof(No));
	//newNo->valor = valor;
	newNo->valor = (char*) malloc(strlen(valor) + 1);
	strcpy(newNo->valor, valor);
	newNo->proximo = NULL;
	
	return newNo;
}


// Adiciona um Vertice no grafo e devolve seu indice na ListaAdj
int createVertice(Graph* graph, Elemento valor) {

	No* newVertice = createNo(valor);
	
	if (graph->numVertices > graph->livre) {
		graph->ListaAdj[graph->livre] = newVertice;
		graph->livre++;
		
		return (graph->livre - 1);
	}
	
	return -1;
}


// Pega o indice de certo vertice da ListaAdj de certo grafo
int getIndex(Graph* graph, No* no) {

	for (int i=0; i < graph->numVertices; i++) {
	
		if (graph->ListaAdj[i] == no) return i;
	}
	
	return -1;
}


void addAresta(Graph* graph, No* origem, No* destino) {

	No* newNo = createNo(destino->valor);
	int src = getIndex(graph, origem);
	
	// Adiciona o novo Vertice Adjacente no comeco da ListaAdj
	newNo->proximo = graph->ListaAdj[src]->proximo;
	graph->ListaAdj[src]->proximo = newNo;
}




// Verifica se ha uma aresta entre dois vertices
boolean hasAresta(Graph* graph, No* origem, No* destino) {

	No* p = origem->proximo;
	
	while(p) {
	
		if(p == destino) return TRUE;
		
		p = p->proximo;
	}
	
	return FALSE;
}


// Gerar Grafo direcionado aleatorio dado num de Vertices e Arestas sendo composto de valores inteiros
Graph* generate_random_graph(int numVertices, int numArestas) {

	Graph* new_graph = createGraph(numVertices);
	
	srand(time(0));
	
	// Preenchendo o grafo com vertices de valores aleatorios
	for (int i=0; i < numVertices; i++) {
		
		// Usuarios serao identificados por um numero de LENGTH digitos
		char random_value[LENGTH+1];
		random_value[LENGTH] = '\0';
		
		for (int k=0; k < LENGTH; k++) {
		
			// 0-9 em char representa 48 - 57
			int random_digit = rand() % 10 + 48;
			random_value[k] = (char) random_digit;
		}
				
		createVertice(new_graph, random_value);
	}
	
	// Escolhendo um Vertice aleatorio de saida e outro de entrada 
	for (int j=0; j < numArestas;) {
	
		int random_src = rand() % numVertices;
		int random_dest = rand() % numVertices;
		
		No* src = new_graph->ListaAdj[random_src];
		No* dest = new_graph->ListaAdj[random_dest];
		
		// Evitando varias arestas de mesmo destino e direcao
		if(hasAresta(new_graph, src, dest) == FALSE) {
			
			addAresta(new_graph, src, dest);
			j++;
		}
	}
	
	return new_graph;
}


/*-----------------------------------Print & Free---------------------------------------------*/


void freeGraph(Graph* graph){
	
	for (int i = 0; i < graph->numVertices; i++) {
	
		No* currentNo = graph->ListaAdj[i];
		
		while (currentNo) {
		
			No* tmp = currentNo;
			currentNo = currentNo->proximo;
			free(tmp);
		}
	}
    	
	free(graph->ListaAdj);
	free(graph);
}


void printGraph(Graph* graph) {
	
	if (graph) {
	
		printf("Grafo:\n");

		for (int i=0; i < graph->numVertices; i++) {
		
			No* currentNo = graph->ListaAdj[i];
			
			if (currentNo) {
			
				printf("\tVertice %s: ", currentNo->valor);
				currentNo = currentNo->proximo;
			}
			
			while(currentNo) {
				
				printf("%s -> ", currentNo->valor);
				currentNo = currentNo->proximo;
			}
			
			printf("NULL\n");
		}
		
		printf("\n");
	}
	
	else printf("Grafo aponta para NULL");
}
