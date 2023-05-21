/*****************************************************************//**
 * \file   Mobilidade.h
 * \brief  Structs e Funções para Mobilidade
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
#define MATRICULA 15
#define LOCAL 40

typedef enum TipoC{
	M1,
	M2,
	M3
}TipoC;

typedef struct MobilidadeE{
	int autonomia;
	TipoC tipo;
	float precoAluguer;
    float bateria;
	char matricula[MATRICULA];
	char localizacao[LOCAL];
} MobilidadeE;


typedef struct MobilidadeLista MobilidadeLista;
struct MobilidadeLista {
	MobilidadeE automovel;
	MobilidadeLista* proximo;
};

MobilidadeLista* addMeioMobilidade(MobilidadeLista* head, MobilidadeE next);
MobilidadeLista* lerMeioMobilidade(MobilidadeLista* head, int valor);
MobilidadeLista* removerMeioMobilidade(MobilidadeLista* head, MobilidadeLista* next);
void MostrarListaMeiosMobilidade(MobilidadeLista* head);
int LerFicheiroMeioMobilidade(char* ficheiro);
int SalvarFicheiroMeioMobilidade(MobilidadeLista* head, char* ficheiro);
int SalvarFicheiroMeioMobilidadeBin(MobilidadeLista* head, char* ficheiro);
MobilidadeLista* procuraMeioMobilidade(MobilidadeLista* head, char* matricula);
MobilidadeLista* alterarMeioMobilidade(MobilidadeLista* head, int autonomia, TipoC tipo, float precoAluguer,float bateria , char* matricula, char* localizacao);
MobilidadeLista* listarMeiosMobilidadePorAutonomia(MobilidadeLista* head);
MobilidadeLista* TrocarMeioMobilidade(MobilidadeLista* transporte1, MobilidadeLista* transporte2);
MobilidadeLista* listarMeiosMobilidadePorLocalizacao(MobilidadeLista* head,char* localizacao );
MobilidadeLista* lerFicheiroMobilidadeBinario(char* nomeFicheiro);