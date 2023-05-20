/*****************************************************************//**
 * \file   Aluguer.h
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
#include "Grafos.h";
#include "Cliente.h";
#include "Mobilidade.h";

typedef struct Aluguer {
	Cliente* cliente;
	MobilidadeE* automovel;
    Vertice* grafo;
}Aluguer;


typedef struct AluguerLista AluguerLista;
struct AluguerLista {
    Aluguer aluguer;
    AluguerLista* anterior;
    AluguerLista* proximo;
};

Aluguer* CriarAluguer(Cliente* cliente, MobilidadeE* automovel, AluguerLista* alugueres);
bool VerificarSaldoCliente(float valorAluguel, Cliente* cliente);
void ModificarSaldo(Cliente* cliente, float valorAluguel); 
AluguerLista* AdicionarAluguerLista(AluguerLista* listaAlugueres, Aluguer* aluguer);

