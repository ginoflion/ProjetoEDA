/*****************************************************************//**
 * \file   Grafo.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h";


#pragma region Vertices
Vertice* CriaGrafo() {
	return NULL;
}

Vertice* CriaVertice(char cidade, int cod) {
	Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
	if (novoVertice == NULL) {
		free(novoVertice);
		return novoVertice;
	}
	if (novoVertice == NULL)return NULL;
	novoVertice->cod = cod;
	strcpy(novoVertice->cidade, cidade);
	novoVertice->proximo = NULL;
	novoVertice->adjacente = NULL;
}

Vertice* AddVertice(Vertice* head, Vertice* novo) {
	if (head== NULL) {
		head = novo;
		return head;
	}
	else {
		Vertice* aux = head;
		Vertice* anterior = aux;
		while (aux && aux->cod != novo->cod	) {
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
#pragma endregion

#pragma region Adjacentes
Adj* CriaAdj(int codOrigem,int codDestino, float distancia) {

	Adj* novaAdj = (Adj*)malloc(sizeof(Adj));
	if (novaAdj == NULL) {
		return NULL;
	}
	
	novaAdj->codOrigem = codOrigem;
	novaAdj->codDestino = codDestino;
	novaAdj->distancia = distancia;
	novaAdj->next = NULL;
	return novaAdj;

}
#pragma endregion 

