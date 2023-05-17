/*****************************************************************//**
 * \file   Grafo.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h";


#pragma region Vertices


Vertice* CriaVertice(char* cidade, int cod) {
	Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
	if (novoVertice == NULL) {
		free(novoVertice);
		return novoVertice;
	}
	if (novoVertice == NULL) {
		return NULL;
	}
	novoVertice->cod = cod;
	strcpy(novoVertice->cidade, cidade);
	novoVertice->proximo = NULL;
	novoVertice->adjacente = NULL;
	return novoVertice;
}




Vertice* AddVertice(Vertice* head, Vertice* novo) {
	if (head== NULL) {
		head = novo;
		return head;
	}
	else {
		Vertice* aux = head;
		Vertice* anterior = aux;
		while (aux != NULL && aux->cod != novo->cod	) {
			anterior = aux;
			aux = aux->proximo;
		}
		if (aux==head) {
			novo->proximo = head;
			head = novo;
		}
		else {
			novo->proximo = aux;
			anterior->proximo = novo;
		}

		return head;
	}

}
void MostraGrafo(Vertice* head) {
	if (head == NULL) return;
	printf("V: %d - %s\n", head->cod, head->cidade);
	MostraGrafo(head->proximo);
	MostraAdjacencias(head->adjacente);
}

Vertice* ProcuraVertice(Vertice* head, int cod) {
	if (head == NULL) return NULL;
	if (head->cod == cod) {
		return head;
	}
	return ProcuraVertice(head->proximo, cod);
}
#pragma endregion

#pragma region Adjacentes

Adj* CriaAdj(int codOrigem, int codDestino, float distancia) {

	Adj* novaAdj = (Adj*)malloc(sizeof(Adj));
	if (novaAdj == NULL) {
		free(novaAdj);
		return novaAdj;
	}
	if (novaAdj == NULL) {
		return NULL;
	}

	novaAdj->codOrigem = codOrigem;
	novaAdj->codDestino = codDestino;
	novaAdj->distancia = distancia;
	novaAdj->proximo = NULL;
	return novaAdj;

}


Adj* InserirAdjVertice(Vertice* head, Adj* adj) {
	if (head == NULL)return NULL;
	Vertice* start = ProcuraVertice(head, adj->codOrigem);
	Vertice* destino = ProcuraVertice(head, adj->codDestino);

	if (start == NULL || destino == NULL)return NULL;
	Adj* novaAdj = CriaAdj(adj->codOrigem, adj->codDestino,adj->distancia);
	if (novaAdj == NULL)return NULL;
	if (start->adjacente == NULL) {
		start->adjacente = novaAdj;
	}
	else {
		novaAdj->proximo = start->adjacente;
		start->adjacente = novaAdj;
	}
	return start->adjacente;

}

void MostraAdjacencias(Adj* adj) {
	if (adj == NULL) return;
	printf("CodOrigem: %d \nCodDestino: %d \nDistancia: %.0f\n" , adj->codOrigem,adj->codDestino,adj->distancia);
	MostraAdjacencias(adj->proximo);
}
#pragma endregion 

int SalvarFicheiroGestoresBin(Vertice* grafo, char* ficheiro) {
	if (grafo == NULL || ficheiro == NULL) return 2;

	FILE* fp;
	fopen_s(&fp, ficheiro, "wb");
	if (fp == NULL) return 2;

	// Contar o número de vértices manualmente
	int numVertices = 0;
	Vertice* grafoAtual = grafo;
	while (grafoAtual != NULL) {
		numVertices++;
		grafoAtual = grafoAtual->proximo;
	}

	// Escrever o número de vértices no arquivo
	fwrite(&numVertices, sizeof(int), 1, fp);

	// Reiniciar o ponteiro para o início do grafo
	grafoAtual = grafo;

	// Escrever cada vértice no arquivo
	while (grafoAtual != NULL) {
		fwrite(grafoAtual, sizeof(Vertice), 1, fp);
		grafoAtual = grafoAtual->proximo;
	}

	fclose(fp);
	return 0;
}