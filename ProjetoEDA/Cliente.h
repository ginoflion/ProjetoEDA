/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Structs e Funções para Cliente
 * 
 * \author Gonçalo Silva - a25970
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996
//bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define Nome 40
#define Morada 50
#define NIF 30


typedef struct Cliente {
	char nome[Nome];
	char morada[Morada];
	char nif[NIF];
	float saldo;

}Cliente;

typedef struct ClienteLista ClienteLista;
struct ClienteLista{
	Cliente cliente;
	ClienteLista* proximo;
};

ClienteLista* addCliente(ClienteLista* head, Cliente next);
ClienteLista* lerCliente(ClienteLista* head, int valor);
ClienteLista* removerCliente(ClienteLista* head, ClienteLista* next);
void MostrarListaClientes(ClienteLista* head);
int LerFicheiroClientes(ClienteLista** head, char* ficheiro);
int SalvarFicheiroClientes(ClienteLista* head, char* ficheiro);
int SalvarFicheiroClientesBin(ClienteLista* head, char* ficheiro);
ClienteLista* procuraClientes(ClienteLista* head, char* nif);
ClienteLista* alterarClientes(ClienteLista* head, float saldo, char* nome, char* morada, char* nif);
