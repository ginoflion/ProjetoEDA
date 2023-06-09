/*****************************************************************//**
 * \file   Aluguer.h
 * \brief  Structs e Fun��es para Aluguer
 * 
 * \author Gon�alo Silva - a25970
 * \date   May 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

 //bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Grafos.h"
#include "Cliente.h"
#include "Mobilidade.h"

typedef struct Aluguer {
    int id;
	Cliente* cliente;
	MobilidadeE* automovel;
    Vertice* grafo;
}Aluguer;


typedef struct AluguerLista AluguerLista;
struct AluguerLista {
    Aluguer aluguer;
    AluguerLista* proximo;
    AluguerLista* anterior;
};

Aluguer* CriarAluguer(Cliente* cliente, MobilidadeE* meio,int id);
AluguerLista* AdicionarAluguerLista(AluguerLista* listaAlugueres, Aluguer* aluguer);
void MostrarAluguer(Aluguer* aluguer);
int SalvarFicheiroAlugueresBin(AluguerLista* head, char* ficheiro);
AluguerLista* lerFicheiroAlugueresBinario(char* nomeFicheiro);
void MostrarListaAlugueres(AluguerLista* listaAlugueres);
AluguerLista* removerAluguerLista(AluguerLista* aluguer, AluguerLista* listaAlugueres);
Aluguer* ProcurarAluguer(int id, AluguerLista* listaAlugueres);