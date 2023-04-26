#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "kosaraju.h"
#include "dfs.h"

#define BUFFER 1000
#define SET 0
#define ADD 1

// |--------------------------------- Functions Declaration ---------------------------------|

void read_file(char* file, Graph** graph);

// |--------------------------------- Variables Declaration ---------------------------------|

int kosaraju_version;

// |--------------------------------- main ---------------------------------|


int main(int argc, char** argv) {
	
	Graph* graph = NULL;
	
	switch (argc) {
		
		case 2 :
			if (strcmp(argv[1], "-h") == 0|| strcmp(argv[1], "--help") == 0) {
				printf("[-] Usage:\n\t./file [number of Vertices] [number of Connections] #for random graphs.\nor\n");
				printf("\t./file [input file] #for file specified graphs\n");
			}
			
			else read_file(argv[1], &graph);
			
			break;
		
		case 3 :
			int numV = atoi(argv[1]);
			int numA = atoi(argv[2]);
			
			// Como estamos trabalhando com char, so podemos usar a -> z = 26 vertices maximos
			if (numV <= 0 || numA < 0) {
				printf("[-] Numero de vertices ou arestas nao suportado.\n\tEscolha um numero > 0\n\n");
				break;	
			}
			
			// Cria Grafo aleatorio para teste
			graph = generate_random_graph(numV, numA);
			
			break;
		
		
		default :
			printf("[-] Wrong usage. Use --help or -h for more information\n");
	}
	
	printGraph(graph);
	
	//(...)
}


// Interpreta o arquivo de entrada e retorna a versao do Kosaraju a ser usada
void read_file(char* file, Graph** graph_ptr){	
	
	Graph* graph = *graph_ptr;
	
	FILE* fp;
	fp = fopen (file, "rt");
	
	char* set;
	char* add;
	int index;
	
	int i = 0;
	while (!feof(fp)) {
		
		// SET or ADD (0 or 1)
		int opcao = -1;
		
		int string_size = 0;
		
		char line[BUFFER];
		fscanf(fp, "%s\n", &line);
		
		// Pegando o numero de vertices e iniciando o grafo
		if(i == 0) {
		
			int numV = atoi(line);
			graph = createGraph(numV);
		}
		
		int instruction = atoi(line);
		
		// Atoi vai retornar 0 caso haja char na string
		if (instruction == 1 || instruction == 2) kosaraju_version = instruction;
		
		else {
			// Significa que esta representa uma linha de instrucao de adicao de vertice
			
			// Achar o tamanho da string na linha para separar o valor do vertice da instrucao
			for (int j=0; j < BUFFER; j++) {
			
				if (line[j] == ':' || line[j] == ';') {
				
					string_size = j;
					
					if (line[j] == ':') opcao = SET;
					
					if (line[j] == ';') opcao = ADD;
					
					line[j] = '\0';
					
					break;
				}
			}
			
			// Agora line ate '\0' representa o valor do vertice, portanto ja temos o necessario para executar a instrucao
			char vertice_value[string_size+1];
			strcpy(vertice_value, line);
			
			if (opcao == SET) index = createVertice(graph, vertice_value);
			
			if (opcao == ADD) {

				No* dest = createNo(vertice_value);
				addAresta(graph, graph->ListaAdj[index], dest);
			}
		}

		i++;
	}
	
	fclose(fp);
	*graph_ptr = graph;
}
