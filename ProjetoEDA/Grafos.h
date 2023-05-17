/*****************************************************************//**
 * \file   Graphs.h
 * \brief  Header dos Grafos
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


typedef struct Vertice {
	int cod;
	char cidade[NomeCidade];
	struct Vertice* proximo;
	struct Adj* adjacente;
}Vertice;


typedef struct Adj {
	int codOrigem;
	int codDestino;
	float distancia;		
	struct Adj* proximo;
}Adj;





Vertice* CriaVertice(char* cidade, int cod);
Vertice* AddVertice(Vertice* head, Vertice* novo);
void MostraGrafo(Vertice* head);
void DestruirGrafo(Vertice* head);

Adj* CriaAdj(int codOrigem, int codDestino, float distancia);
Adj* InserirAdjVertice(Vertice* grafo, Adj* adj);
void MostraAdjacencias(Adj* adj);
