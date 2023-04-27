#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "linked_list.h"


// Vetores d[] e f[], marcando o tempo de descoberta (vertice cinza) e o tempo de finalizacao (vertice preto)
int* d;
int* f;
int* color;
int* pai;
int count;  // referente ao time no pseudo-codigo


void init_arrays(int graph_size) {

	// Alocando memoria
	d = (int*) malloc(sizeof(int)*graph_size);
	f = (int*) malloc(sizeof(int)*graph_size);
	color = (int*) malloc(sizeof(int)*graph_size);
	pai = (int*) malloc(sizeof(int)*graph_size);
	count = 0;
	
	// Preenchendo os vetores para DFS
	for (int i=0; i < graph->livre; i++) {
		color[i] = 0; // todos os vertices ficam brancos
		pai[i] = -1;  // todos os vertices "nao tem pai"
		d[i] = -1;
		f[i] = -1;
	}
}


void DFS(Graph* graph) {
	
	init_arrays(graph->numVertices);
	
	// Fazendo DFS em todos os vertices do grafo
	for (int i=0; i < graph->livre; i++) {
	
		if(color[i] == 0) DFS_Visit(graph, i);
	}
}


void DFS_Visit(Graph* graph, int indice_u, LinkedList* percorridos) {
	
	// Se o vertice ja estiver 'preto'
	if (color[indice_u] == 2) return NULL;
	
	// Mudar a cor do vertice 'u' para cinza
	color[indice_u] = 1;
	
	count++;
	d[indice_u] = count;
	
	// Percorrer por todos vertices 'v' adjacentes a 'u'
	No* v = graph->ListaAdj[indice_u]->proximo;
	while (v) {
		
		// Achar o indice correspondente do vertice 'v'
		int indice_v = getIndex(graph, v);
		
		if (color[indice_v] == 0) {
			pai[indice_v] = indice_u;
			DFS_Visit(graph, indice_v, percorridos);
		} 
		
		v = v->proximo;
	}
	
	// Mudar a cor do vertice 'u' para preto
	color[indice_u] = 2;
	push(percorridos, indice_u);
	
	count++;
	f[indice_u] = count;
}


LinkedList* ordenacao_topologica(Graph* graph) {

	/*
	1 - DFS no grafo
	2 - quando o vertice vira 'preto' insere numa lista ligada (mesmo o que pegar o f[] e na ordem crecente ir adicionando na lista)
	*/

	LinkedList* ordenacao = createList();
	
	DFS(graph);
	
	// Pegando o menor valor de f[] e adicionando na lista
	for (int i=0; i < graph->numVertices; i++) {
		
		int min = 0;
		
		for (int j=0; j < 26; j++) if (f[min] > f[j]) min = j;
		
		// Coloca numa lista ligada o indice do vertice ListaAdj[min]
		push(ordenacao, min);
		
		// Prevenir pegar o mesmo valor do anterior
		f[min] = -1;		
	}
	
	return ordenacao;
}


/* ---------------------- Kosaraju ---------------------- */


Graph* reverseGraph(Graph* graph) {

	// Criando novo grafo com o mesmo numero de vertices que o antigo
	Graph* new_graph = createGraph(graph->numVertices);
	
	for (int i=0; i < graph->numVertices; i++) {
	
		No* vertice = graph->ListaAdj[i];
		No* adjacente = vertice->proximo;
		
		// Caso tenha um vertice que nao possui arestas
		if (adjacente == NULL) createVertice(new_graph, vertice->valor);
		
		// Para cada vertice adjacente adicionar uma aresta reversa no novo grafo
		while(adjacente) {
			
			addAresta(new_graph, adjacente, vertice);
			adjacente = adjacente->proximo;
		}
	}
	
	return new_graph;
}


Graph* KosarajuV1(Graph* graph) {

	/*
	1 - Grafo transposto
	2 - DFS (pega a ordem) no grafo transposto
	3 - Aplica DFS no grafo original na ordem decrescente f[i]
	*/
	
	Graph* new_graph = createGraph(graph->numVertices);
	
	// 1:
	Graph* reversed = reverseGraph(graph);
	
	// 2:	
	DFS(reversed, pilha);
	
	// 3:
	
	// Resetando o vetor de cores do DFS
	for (int i=0; i < 26; i++) color[i] = 0; // todos os vertices ficam brancos
	
	// Pegando o maior valor e aplicando DFS
	for (int j=0; j < graph->numVertices; j++) {
		
		int max = 0;
		
		for (int i=0; i < 26; i++) if (f[max] < f[i]) max = i;
		
		
		
		LinkedList* componente = createList();
		
		DFS_Visit(graph, max, componente);
		
		// createVertice(new_graph, valor_componente);
		
		// Prevenir pegar o mesmo valor do anterior
		f[max] = -1;		
	}	
}


Graph* KosarajuV2(Graph* graph) {

	/*
	1 - DFS no grafo original (pegar a ordem)
	2 - Fazer o grafo transposto
	3 - aplicar DFS-Visit no grafo transposto na ordem
	*/
}


void Kosaraju(Graph* graph, int version) {

	if (version == 1) KosarajuV1(graph);
	if (version == 2) KosarajuV2(graph);
}

