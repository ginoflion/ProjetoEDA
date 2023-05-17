/*****************************************************************//**
 * \file   Gestao.h
 * \brief  Structs e Funções para Gestao
 * 
 * \author Gonçalo Silva - a25970
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

 //bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define N 30
#define E 50
#define P 50
typedef struct Gestores {
	 int id;
	 char nome[N];
	 char email[E];
	 char password[P];
}Gestores;

typedef struct GestoresLista GestoresLista;
struct GestoresLista {
	Gestores gestor;
	GestoresLista* proximo;
};


GestoresLista* addGestor(GestoresLista* head, Gestores next);
GestoresLista* lerGestor(GestoresLista* head, int valor);
GestoresLista* removerGestor(GestoresLista* head, GestoresLista *next);
void MostrarListaGestores(GestoresLista* head);
int LerFicheiroGestores(GestoresLista** head, char* ficheiro);
int SalvarFicheiroGestores(GestoresLista* head, char* ficheiro);
int SalvarFicheiroGestoresBin(GestoresLista* head, char* ficheiro);
GestoresLista* procuraGestores(GestoresLista* head, int* id);
GestoresLista* alterarGestores(GestoresLista* head, int id, char* nome, char* email, char* password);
GestoresLista* lerFicheiroGestoresBinario(char* nomeFicheiro);