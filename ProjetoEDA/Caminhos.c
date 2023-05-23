/*****************************************************************//**
 * \file   Caminhos.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#include "Caminhos.h"

ListaCaminhos* CriarListaCaminhos(int vertice) {
	ListaCaminhos* novaListaCaminhos = (ListaCaminhos*)malloc(sizeof(ListaCaminhos));
	if (novaListaCaminhos == NULL) {
		free(novaListaCaminhos);
		return NULL;
	}
	novaListaCaminhos->caminho = NULL;
	novaListaCaminhos->distancia = Distancia;
	novaListaCaminhos->proximo = NULL;
	novaListaCaminhos->vertice = vertice;
	return novaListaCaminhos;
}

ListaCaminhos* adicionarCaminhoLista(ListaCaminhos* head, ListaCaminhos* caminho) {
	if (caminho == NULL) {
		free(caminho);
		return NULL;
	}
	caminho->proximo = NULL;

	if (head = NULL) {
		head = caminho;
		return head;
	}

	ListaCaminhos* ultimo = head;

	while (ultimo->proximo != NULL) {
		ultimo = ultimo->proximo;
	}
	ultimo->proximo = caminho;
	return head;
}

ListaCaminhos* procurarCaminhoLista(ListaCaminhos* head, int vertice){
	if (head = NULL)return NULL;

	ListaCaminhos* atual = head;

	while (atual != NULL) {
		if (atual->vertice == vertice)return atual;
		atual = atual->proximo;
	}
	return NULL;
}

Caminho* CriarCaminho(int vertice) {
	Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));

	if (novoCaminho == NULL) {
		free(novoCaminho);
		return NULL;
	}
	novoCaminho->vertice = vertice;
	novoCaminho->proximo = NULL;

	return novoCaminho;
}
