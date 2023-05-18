/*****************************************************************//**
 * \file   MeiosMobilidade.c
 * \brief  Fun��es de Meios de Mobilidade
 * 
 * \author Gon�alo Silva - a25970
 * \date   March 2023
 *********************************************************************/
#include "Mobilidade.h"
#pragma once

/**
 * \brief Procura e retorna o meio de mobilidade na posi��o indicada pelo valor.
 * 
 * \param head Ponteiro para o primeiro elemento da lista de meios de mobilidade.
 * \param valor Valor inteiro que indica a posi��o do meio de mobilidade a ser retornado. 
 * \return meioAtual Ponteiro para o meio de mobilidade encontrado na posi��o indicada pelo valor.
 */
MobilidadeLista* lerMeioMobilidade(MobilidadeLista* head, int valor){
	if (head == NULL) {
		return NULL;
	}

	MobilidadeLista* meioAtual = head;
	int i = 0;
	while (i < valor) {
		meioAtual = meioAtual->proximo;
		i++;
	}
	return meioAtual;
}
/**
 * \brief Adiciona um novo meio � lista de meios.
 * 
 * \param head  A lista de meios existente.
 * \param next O meio a ser adicionado.
 * \return A lista de meios atualizada.
  */
 
MobilidadeLista* addMeioMobilidade(MobilidadeLista* head, MobilidadeE next){
	MobilidadeLista* novoMeio = (MobilidadeLista*)malloc(sizeof(MobilidadeLista));
	if (novoMeio == NULL) {
		free(novoMeio);
		return head;
	}
	novoMeio->automovel = next;
	novoMeio->proximo = NULL;
	if (head == NULL) {
		return novoMeio;
	}
	MobilidadeLista* ultimoMeio = head;
	while (ultimoMeio->proximo != NULL) {
		ultimoMeio = ultimoMeio->proximo;
	}
	ultimoMeio->proximo = novoMeio;
	return head;
}
/**
 * \brief Remove um meio da lista de meios de mobilidade.
 *	
 * 
 * \param head Ponteiro para a cabe�a da lista de meios.
 * \param next  O meios a ser removido.
 * \return O ponteiro para a cabe�a da lista de meios atualizado.
 */
MobilidadeLista* removerMeioMobilidade(MobilidadeLista* head, MobilidadeLista* next) {
	MobilidadeLista* aux = NULL;

	if (head == NULL) return head;

	if (head == next) {
		head = head->proximo;
	}
	else {
		aux = head;
		while (aux->proximo != NULL && aux->proximo != next) {
			aux = aux->proximo;
		}
		if (aux->proximo != NULL) {
			aux->proximo = next->proximo;
		}
	}

	free(next);
	return head;
}
/**
* \brief Print aos meios presentes numa lista
 * 
 * 
 * \param head O ponteiro para a cabe�a da lista ligada.
 */
void MostrarListaMeiosMobilidade(MobilidadeLista* head) {
	MobilidadeLista* aux = head;
	while (aux != NULL) {
		printf("Autonomia: %d\n", aux->automovel.autonomia);
		printf("Tipo de Transporte: %d\n", aux->automovel.tipo);
		printf("Matricula: %s\n", aux->automovel.matricula);
		printf("Localizacao: %s\n", aux->automovel.localizacao);
		printf("Preco de Aluguer: %.2f\n", aux->automovel.precoAluguer);
		printf("Carga de Bateria: %.2f\n", aux->automovel.bateria);
		aux = aux->proximo;
	}
}
/**
 * \brief L� um ficheiro de texto contendo a informa��o dos meios e adiciona-os � lista de meios de mobilidade.
 * 
 * \param head para a cabe�a da lista de gestores.
 * \param ficheiro  O nome do ficheiro de texto.
 * \return  Um c�digo de erro, sendo 1 para sucesso, -1 para erro na abertura do ficheiro e -2 para erro na aloca��o de mem�ria.
 */
int LerFicheiroMeioMobilidade(char* ficheiro) {
	MobilidadeE meioAtual = { 0 };
	FILE* fp;
	MobilidadeLista* head = NULL;

	fopen_s(&fp, ficheiro, "r");
	if (fp == NULL) return (-1);

	while (fscanf(fp, "%d;%[^;];%[^;];%f;%f;%d;\n", &meioAtual.autonomia, meioAtual.localizacao, meioAtual.matricula, &meioAtual.precoAluguer, &meioAtual.bateria, &meioAtual.tipo) == 6) {
		MobilidadeLista* novoMeio = addMeioMobilidade(head, meioAtual);
		if (novoMeio == NULL) {
			fclose(fp);
			return (-2);
		}
		head = novoMeio;
	}

	fclose(fp);
	return 1;
}


/**
 * \brief Salva a lista de gestores em ficheiro.
 * 
 * \param head Ponteiro para a cabe�a da lista de meios de mobilidade.
 * \param ficheiro  Nome do ficheiro para salvar a lista dos meios de mobilidade.
 * \return Um inteiro indicando o resultado da opera��o (1 se a opera��o foi bem sucedida, 2 se houve erro ao salvar o ficheiro, 3 se a lista de meios est� vazia).
 */
int SalvarFicheiroMeioMobilidade(MobilidadeLista* head, char* ficheiro) {
	if (head == NULL) return 3;

	MobilidadeLista* meioAtual = head;
	FILE* fp;
	fopen_s(&fp, ficheiro, "w");
	if (fp == NULL) return 2;

	while (meioAtual != NULL) {
		if (fprintf(fp, "%d;%s;%s;%f;%f;%d\n", meioAtual->automovel.autonomia, meioAtual->automovel.localizacao, meioAtual->automovel.matricula,
			meioAtual->automovel.precoAluguer,meioAtual->automovel.bateria, meioAtual->automovel.tipo) < 0) {
			fclose(fp);
			return 2;
		}
		meioAtual = meioAtual->proximo;
	}

	fclose(fp);
	return 1;
}
/**
 * \brief Salva a lista de gestores em ficheiro binario.
 * 
 * \param head Ponteiro para a cabe�a da lista de meios de mobilidade.
 * \param ficheiro  Nome do ficheiro para salvar a lista dos meios de mobilidade.
 * \return Um inteiro indicando o resultado da opera��o (1 se a opera��o foi bem sucedida, 2 se houve erro ao salvar o ficheiro, 3 se a lista de meios est� vazia).
 */
int SalvarFicheiroMeioMobilidadeBin(MobilidadeLista* head, char* ficheiro) {

	if (head == NULL) return 3;

	MobilidadeLista* meioAtual = head;

	FILE* fp;

	fopen_s(&fp, ficheiro, "wb");


	if (fp == NULL) return 2;

	do
	{
		fwrite(&(meioAtual->automovel), sizeof(MobilidadeE), 1, fp);

		meioAtual = meioAtual->proximo;
	} while (meioAtual != NULL);

	fclose(fp);
	return 1;
}
/**
 * \brief Procura um meio de mobilidade com base na sua matr�cula na lista de meios de mobilidade.
 * 
 * \param head  Ponteiro para a cabe�a da lista de meios de mobilidade;
 * \param matricula Matr�cula do meio de mobilidade a ser procurado.
 * \return O ponteiro para o meio de mobilidade encontrado ou NULL se n�o existir.
/
 */
MobilidadeLista* procuraMeioMobilidade(MobilidadeLista* head, char* matricula) {
	if (head == NULL) return NULL;
	MobilidadeLista* aux = head;
	while (aux != NULL) {
		if (strcmp(aux->automovel.matricula, matricula) == 0) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}
/**
 * \brief Altera as informa��es de um meio de mobilidade na lista de meios de mobilidade.
 * 
 * \param head Ponteiro para a cabe�a da lista de meios de mobilidade.
 * \param autonomia  A nova autonomia do meio de mobilidade.
 * \param tipo  O novo tipo do meio de mobilidade.
 * \param precoAluguer O novo pre�o de aluguer do meio de mobilidade. 
 * \param bateria A nova capacidade da bateria do meio de mobilidade.
 * \param matricula  A matr�cula do meio de mobilidade a ser alterado.
 * \param localizacao A nova localiza��o do meio de mobilidade.
 * \return O ponteiro para a cabe�a da lista de meios de mobilidade atualizado.
 */
MobilidadeLista* alterarMeioMobilidade(MobilidadeLista* head, int autonomia, TipoC tipo, float precoAluguer,float bateria, char* matricula, char* localizacao) {
	
	MobilidadeLista* aux = procuraMeioMobilidade(head, matricula);
	if (aux != NULL) {
		aux->automovel.autonomia = autonomia;
		aux->automovel.tipo = tipo;
		aux->automovel.precoAluguer = precoAluguer;
		strcpy(aux->automovel.localizacao ,localizacao);
		strcpy(aux->automovel.matricula,matricula);
	}
	return head;
}

MobilidadeLista* listarMeiosMobilidadePorAutonomia(MobilidadeLista* head) {
	if (head == NULL)return NULL;
	MobilidadeLista* aux=head;
	while (aux != NULL) {
		MobilidadeLista* atual = head;
		while (atual->proximo!=NULL) {
			if (atual->automovel.autonomia < atual->proximo->automovel.autonomia) {
				SwapMeioMobilidade(atual, atual->proximo);
			}
			atual = atual->proximo;
		}
		aux = aux->proximo;
	}
	return head;
}


MobilidadeLista* SwapMeioMobilidade(MobilidadeLista* transporte1, MobilidadeLista* transporte2) {
	MobilidadeE aux = transporte1->automovel;
	transporte1->automovel = transporte2->automovel;
	transporte2->automovel = aux;

}

MobilidadeLista* listarMeiosMobilidadePorLocalizacao(MobilidadeLista* head, char* localizacao) {
	
	if (head == NULL)return NULL;
	MobilidadeLista* ultimoAutomovel = NULL;
	MobilidadeLista* novaLista = NULL;
	MobilidadeLista* aux = head;
	while (aux != NULL) {
		if (strcmp(aux->automovel.localizacao, localizacao) == 0) {
			MobilidadeLista* novoAutomovel= (MobilidadeLista*)malloc(sizeof(MobilidadeLista));
			novoAutomovel->automovel = aux->automovel;
			novoAutomovel->proximo = NULL;

			if (novaLista == NULL) {
				novaLista = novoAutomovel;
				ultimoAutomovel = novaLista;
			}
			else {
				ultimoAutomovel->proximo = novoAutomovel;
				ultimoAutomovel = novoAutomovel;

			}
		}
		aux = aux->proximo;
	}
	return novaLista;
}


MobilidadeLista* lerFicheiroMobilidadeBinario(char* nomeFicheiro) {
	FILE* fp;
	MobilidadeLista* h = NULL;
	MobilidadeE aux;

	fp = fopen(nomeFicheiro, "rb");
	if (!fp) return NULL;

	while (fread(&aux, sizeof(MobilidadeE), 1, fp) > 0) {
		h = addMeioMobilidade(h, aux);
	}

	fclose(fp);
	return h;
}
