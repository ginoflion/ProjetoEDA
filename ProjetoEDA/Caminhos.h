/*****************************************************************//**
 * \file   Caminhos.h
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#pragma once
#pragma warning(disable : 4996)

 //bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define Distancia 200

typedef struct Caminho Caminho;
struct Caminho {
	int vertice;
	Caminho* proximo;
};

typedef struct ListaCaminhos ListaCaminhos;

struct ListaCaminhos {
	int vertice;
	int distancia;
	Caminho* caminho;
	ListaCaminhos* proximo;
};

ListaCaminhos* CriarListaCaminhos(int vertice);
ListaCaminhos* adicionarCaminhoLista(ListaCaminhos* head, ListaCaminhos* caminho);
ListaCaminhos* procurarCaminhoLista(ListaCaminhos* head, int vertice);
Caminho* CriarCaminho(int vertice);
//bool PushPath(Path** head, Path* sourcePath);
//bool PopPath(Path** head);
//Path* TopPath(Path* head);
//Path* CopyPath(Path* original);
//bool WipePaths(Path** head);
