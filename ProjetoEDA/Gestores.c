/*****************************************************************//**
 * \file   Gestores.c
 * \brief  Funções de Gestores
 * 
 * \author Gonçalo Silva - a25970
 * \date   March 2023
 *********************************************************************/
#include "Gestao.h"

 /**
  * \brief Adiciona um novo gestor à lista de gestores.
  *
  * \param head A lista de gestores existente.
  * \param next O gestor a ser adicionado.
  * \return A lista de gestores atualizada.
  */
GestoresLista* addGestor(GestoresLista* head, Gestores next) {
	GestoresLista* novoGestor = (GestoresLista*)malloc(sizeof(GestoresLista));
	
	if (novoGestor == NULL) {
		free(novoGestor);
		return head;
	}
	novoGestor->gestor = next;
	novoGestor->proximo = NULL;
	if (head == NULL) {
		return novoGestor;
	}

	GestoresLista* ultimoGestor = head;
	while (ultimoGestor->proximo != NULL) {
		ultimoGestor = ultimoGestor->proximo;
	}
	ultimoGestor->proximo=novoGestor;
	return head;
}
/**
 * \brief Procura e retorna o gestor na posição indicada pelo valor.
 *
 * \param head Ponteiro para o primeiro elemento da lista de gestores.
 * \param valor Valor inteiro que indica a posição do gestor a ser retornado.
 * \return Ponteiro para o gestor encontrado na posição indicada pelo valor.
 */
GestoresLista* lerGestor(GestoresLista* head, int valor) {
	if (head == NULL)return NULL;
	GestoresLista* gestorAtual = head;
	int i = 0;
	while (i < valor) {
		gestorAtual = gestorAtual->proximo;
		i++;
	}
	return gestorAtual;
}
/**
 * \brief Remove um gestor da lista de gestores.
 *
 * \param head Ponteiro para a cabeça da lista de gestores.
 * \param next O gestor a ser removido.
 * \return O ponteiro para a cabeça da lista de gestores atualizado.
 */

GestoresLista* removerGestor(GestoresLista* head, GestoresLista *next) {
	
	GestoresLista* aux = NULL;
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
 * \brief Print a gestores presentes numa lista
 * 
 * \param head O ponteiro para a cabeça da lista ligada.
 */
void MostrarListaGestores(GestoresLista* head) {
	GestoresLista* aux = head;
	while (aux != NULL) {
		printf("Nome: %s\n", aux->gestor.nome);
		printf("Email: %s\n", aux->gestor.email);
		printf("Password: %s\n", aux->gestor.password);
		printf("ID: %d\n", aux->gestor.id);
		aux = aux->proximo;
	}
}
/**
 * \brief Lê um ficheiro de texto contendo a informação dos gestores e adiciona-os à lista de gestores.
 *
 * \param head Ponteiro para a cabeça da lista de gestores.
 * \param ficheiro O nome do ficheiro de texto.
 * \return Um código de erro, sendo 1 para sucesso, -1 para erro na abertura do ficheiro e -2 para erro na alocação de memória.
 */
int LerFicheiroGestores(GestoresLista** head, char* ficheiro) {
	Gestores gestorAtual = { 0 };
	FILE* fp;

	fopen_s(&fp, ficheiro, "r");
	if (fp == NULL) return (-1);

	while (fscanf(fp, "%d;%[^;];%[^;];%[^;\n]\n", &gestorAtual.id, gestorAtual.nome, gestorAtual.email, gestorAtual.password) == 4)

	{
		GestoresLista* novoGestor = addGestor(*head, gestorAtual);
		if (novoGestor == NULL) {
			fclose(fp);
			return (-2);
		}
		*head = novoGestor;
	}

	fclose(fp);
	return 1;
}
/**
 * \brief Salva a lista de gestores em ficheiro.
 * 
 * \param head Ponteiro para a cabeça da lista de gestores.
 * \param ficheiro  Nome do ficheiro para salvar a lista de gestores.
 * \return Um inteiro indicando o resultado da operação (1 se a operação foi bem sucedida, 2 se houve erro ao salvar o ficheiro, 3 se a lista de gestores está vazia).
 */
int SalvarFicheiroGestores(GestoresLista* head, char* ficheiro) {
	if (head == NULL) return 3;

	GestoresLista* gestorAtual = head;
	FILE* fp;
	fopen_s(&fp, ficheiro, "w");
	if (fp == NULL) return 2;

	while (gestorAtual != NULL) {
		if (fprintf(fp, "%d;%s;%s;%s\n", gestorAtual->gestor.id, gestorAtual->gestor.nome,gestorAtual->gestor.password, gestorAtual->gestor.email) < 0) {
			fclose(fp);
			return 2;
		}
		gestorAtual = gestorAtual->proximo;
	}

	fclose(fp);
	return 1;
}
/**
 * \brief Salva a lista de gestores em ficheiro binario.
 *
 * \param head Ponteiro para a cabeça da lista de gestores.
 * \param ficheiro  Nome do ficheiro para salvar a lista de gestores.
 * \return Um inteiro indicando o resultado da operação (1 se a operação foi bem sucedida, 2 se houve erro ao salvar o ficheiro, 3 se a lista de gestores está vazia).
 */
int SalvarFicheiroGestoresBin(GestoresLista* head, char* ficheiro) {
	if (head == NULL) return 3;

	GestoresLista* gestorAtual = head;

	FILE* fp;

	fopen_s(&fp, ficheiro, "wb");


	if (fp == NULL) return 2;

	do
	{
		fwrite(&(gestorAtual->gestor), sizeof(GestoresLista), 1, fp);

		gestorAtual = gestorAtual->proximo;
	} while (gestorAtual != NULL);

	fclose(fp);
	return 1;
}
/**
 * \brief Procura um gestor com um determinado ID na lista de gestores.
 * 
 * \param head Ponteiro para a cabeça da lista de gestores.
 * \param id O ID do gestor a ser procurado.
 * \return O ponteiro para o gestor encontrado ou NULL se não encontrado.
 */
GestoresLista* procuraGestores(GestoresLista* head, int id) {
	if (head == NULL || id<0)return NULL;
	GestoresLista* aux = head;
	while (aux != NULL) {
		if (aux->gestor.id==id) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}
/**
 * \brief Altera os dados de um gestor na lista de gestores.
 * 
 * \param head Ponteiro para a cabeça da lista de gestores.
 * \param id  O id do gestor a ser alterado.
 * \param nome O novo nome do gestor.
 * \param email O novo email do gestor.
 * \param password A nova password do gestor.
 * \return O ponteiro para a cabeça da lista de gestores atualizado.
 */
GestoresLista* alterarGestores(GestoresLista* head, int id, char* nome, char* email, char* password) {
	GestoresLista* aux = procuraGestores(head, id);
	if (aux != NULL) {
		aux->gestor.id=id;
		strcpy(aux->gestor.nome, nome);
		strcpy(aux->gestor.email, email);
		strcpy(aux->gestor.password, password);
	}
	return head;
}