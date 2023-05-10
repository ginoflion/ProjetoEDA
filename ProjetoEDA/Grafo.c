/*****************************************************************//**
 * \file   Grafo.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h";


#pragma region Vertices
/**
 * Inicialização do Grafo
 * 
 * \return 
 */
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
#pragma endregion

#pragma region Adjacentes
Adj* CriaAdj(int cod, float distancia) {
	Adj* novaAdj = (Adj*)malloc(sizeof(Adj));
	if (novaAdj == NULL) {
		free(novaAdj);
		return novaAdj;
	}
	if (novaAdj == NULL)return NULL;
	novaAdj->cod = cod;
	novaAdj->distancia = distancia;
	novaAdj->next = NULL;
	return novaAdj;
}
#pragma endregion 
