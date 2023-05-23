/*****************************************************************//**
 * \file   Graphs.h
 * \brief  Header dos Grafos
 * 
 * \author Gon�alo Silva - a25970
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
}Adj;

typedef struct AdjFicheiro {
	int codOrigem;
	int codDestino;
	float distancia;
	
}AdjFicheiro;




Vertice* CriaVertice(char* cidade, int cod);
Vertice* AddVertice(Vertice* head, Vertice* novo);
void MostraGrafo(Vertice* head);
Vertice* DestruirGrafo(Vertice* head);
int SalvarFicheiroGrafosBin(Vertice* grafo, char* nomeFicheiro);
Vertice* lerFicheiroGrafosBin(char* nomeFicheiro);
int ContarVertice(Vertice* grafo);
Vertice* ProcuraVertice(Vertice* head, int cod);
Adj* CriaAdj(int codOrigem, int codDestino, float distancia);
Adj* InserirAdjVertice(Vertice* grafo, Adj* adj);
void MostraAdjacencias(Adj* adj);
Adj* DestruirAdj(Adj* adj);
//Ler Ficheiro Texto