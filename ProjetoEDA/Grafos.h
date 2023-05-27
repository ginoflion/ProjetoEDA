/*****************************************************************//**
 * \file   Graphs.h
 * \brief  Structs e Funções para Grafos
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NomeCidade 30
#define N 30;


typedef struct Vertice {
	int cod;
	char cidade[NomeCidade];
	struct Vertice* proximo;
	bool visitado;
	struct Adj* adjacente;
}Vertice;

typedef struct VerticeFicheiro {
	int cod;
	char cidade[NomeCidade];
}VerticeFicheiro;

typedef struct Adj {
	int codOrigem;
	int codDestino;
	float distancia;		
	struct Adj* proximo;
	struct Vertice* vertice;
}Adj;

typedef struct AdjFicheiro {
	int codOrigem;
	int codDestino;
	float distancia;
	
}AdjFicheiro;


#pragma region Vertice
Vertice* CriaVertice(char* cidade, int cod);
Vertice* AddVertice(Vertice* head, Vertice* novo);
Vertice* ProcuraVertice(Vertice* head, int cod);
int ContarVertice(Vertice* grafo);
bool TodosVerticesVisitados(Vertice* grafo);
#pragma endregion

#pragma region Grafo
void MostraGrafo(Vertice* head);
Vertice* DestruirGrafo(Vertice* head);
int SalvarFicheiroGrafosBin(Vertice* grafo, char* nomeFicheiro);
Vertice* LerFicheiroGrafoBin(Vertice* grafo, char* nomeFicheiro);
int ExisteCaminho(Vertice* grafo, int codOrigem, int codDestino);

#pragma endregion

#pragma region Adjacente
Adj* CriaAdj(Vertice* codOrigem, Vertice* codDestino, float distancia);
void MostraAdjacencias(Adj* adj);
Adj* DestruirAdj(Adj* adj);
Adj* InserirAdjVertice(Vertice* head, Adj* adj);
#pragma endregion
