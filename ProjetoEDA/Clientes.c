/*****************************************************************//**
 * \file   Clientes.c
 * \brief  Funções de Clientes
 * 
 * \author Gonçalo Silva - a25970
 * \date   March 2023
 *********************************************************************/
#include "Cliente.h"

 /**
  * \brief Procura e retorna o cliente na posição indicada pelo valor.
  *
  * \param head Ponteiro para o primeiro elemento da lista de clientes.
  * \param valor Valor inteiro que indica a posição do cliente a ser retornado.
  * \return clienteAtual Ponteiro para o cliente encontrado na posição indicada pelo valor.
  */
ClienteLista* lerCliente(ClienteLista* head, int valor) {
	
	if (head == NULL) {
		return NULL;
	}
	
	ClienteLista* clienteAtual = head;
	int i=0;
	while (i < valor) {
		clienteAtual=clienteAtual->proximo ;
		i++;
	}
	return clienteAtual;
}
/**
 * \brief Adiciona um novo cliente à lista de clientes.
 * 
 * \param head Ponteiro para o primeiro elemento da lista de clientes.
 * \param next O cliente a ser adicionado. 
 * \return O ponteiro para o primeiro elemento da lista atualizada.
 */

ClienteLista* addCliente(ClienteLista* head, Cliente next) {
	ClienteLista* novoCliente = (ClienteLista*)malloc(sizeof(ClienteLista));
	if (novoCliente == NULL) {
		free(novoCliente);
		return head;
	}
	novoCliente->cliente = next;
	novoCliente->proximo = NULL;
	if (head == NULL) {
		return novoCliente;
	}
	ClienteLista* ultimoCliente = head;
	while (ultimoCliente->proximo != NULL) {
		ultimoCliente = ultimoCliente->proximo;
	}
	ultimoCliente->proximo = novoCliente;
	return head;
}

/**
 * \brief Remove um cliente da lista de clientes.
 *
 * \param head Ponteiro para a cabeça da lista de clientes.
 * \param next NIF do cliente a ser removido.
 * \return O ponteiro para a cabeça da lista de clientes atualizado.
 */
ClienteLista* removerCliente(ClienteLista* head, ClienteLista* next) {
	ClienteLista* aux = NULL;

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
 * \brief Lê os clientes de um ficheiro e adiciona-os a uma lista ligada.
 *
 * \param head Ponteiro para a cabeça da lista ligada.
 * \param ficheiro Nome do ficheiro a ser lido.
 * \return Retorna 1 em caso de sucesso, -1 em caso de falha ao abrir o ficheiro,ou -2 em caso de falha ao alocar memória para um novo cliente.
 */
int LerFicheiroClientes( char* ficheiro) {
	Cliente clienteAtual = { 0 };
	FILE* fp;
	ClienteLista* head = NULL;

	fopen_s(&fp, ficheiro, "r");
	if (fp == NULL) return (-1);

	while (fscanf(fp, "%[^;];%[^;];%[^;];%f\n",
		clienteAtual.nome,  clienteAtual.morada, clienteAtual.nif, &clienteAtual.saldo) == 4)
	{
		ClienteLista* novoCliente = addCliente(head, clienteAtual);
		if (novoCliente == NULL) {
			fclose(fp);
			return (-2);
		}
		head = novoCliente;
	}

	fclose(fp);
	return 1;
}


/**
 * \brief Salva os dados dos clientes em um ficheiro.
 *
 * \param head Ponteiro para a cabeça da lista de clientes.
 * \param ficheiro O nome do arquivo para salvar os dados.
 * \return 1 se a operação foi bem sucedida, 2 se houve um erro ao abrir ou escrever no arquivo, 3 se a lista de clientes está vazia.
 */
int SalvarFicheiroClientes(ClienteLista* head, char* ficheiro) {
	if (head == NULL) return 3;

	ClienteLista* clienteAtual = head;
	FILE* fp;
	fopen_s(&fp, ficheiro, "w");
	if (fp == NULL) return 2;

	while (clienteAtual != NULL) {
		if (fprintf(fp, "%s;%s;%s;%f\n", clienteAtual->cliente.nome, clienteAtual->cliente.morada, clienteAtual->cliente.nif, clienteAtual->cliente.saldo) < 0) {
			fclose(fp);
			return 2;
		}
		clienteAtual = clienteAtual->proximo;
	}

	fclose(fp);
	return 1;
}
/**
 * \brief Salva os dados dos clientes em um ficheiro binario.
 *
 * \param head Ponteiro para a cabeça da lista de clientes.
 * \param ficheiro O nome do arquivo para salvar os dados.
 * \return 1 se a operação foi bem sucedida, 2 se houve um erro ao abrir ou escrever no arquivo, 3 se a lista de clientes está vazia.
 */
int SalvarFicheiroClientesBin(ClienteLista* head, char* ficheiro) {

	if (head == NULL) return 3;

	ClienteLista* clienteAtual = head;

	FILE* fp;

	fopen_s(&fp, ficheiro, "wb");

	
	if (fp== NULL) return 2;

	do
	{
		fwrite(&(clienteAtual->cliente), sizeof(Cliente), 1, fp);

		clienteAtual = clienteAtual->proximo;
	} while (clienteAtual != NULL);

	fclose(fp);
	return 1;
}
/**
*\brief Mostra as informações de cada cliente na lista ligada.
*
* \param head O ponteiro para a cabeça da lista ligada.
*/
void MostrarListaClientes(ClienteLista* head) {
	
	ClienteLista* aux = head;
	while (aux != NULL) {
		printf("Nome: %s\n", aux->cliente.nome);
		printf("Morada: %s\n", aux->cliente.morada);
		printf("NIF: %s\n", aux->cliente.nif);
		printf("Saldo: %.2f\n", aux->cliente.saldo);
		aux = aux->proximo;
	}
}
/**
 * \brief Procura um cliente na lista de clientes a partir do seu nif .
 * 
 * \param head Ponteiro para a cabeça da lista de clientes.
 * \param nif  Número de identificação fiscal do cliente a ser procurado.
 * \return O ponteiro para o nó da lista de clientes que contém o cliente procurado, ou NULL se não for encontrado.
 */
ClienteLista* procuraClientes(ClienteLista* head, char* nif) {
	if (head == NULL)return NULL;
	ClienteLista* aux = head;
	while (aux != NULL) {
		if (strcmp(aux->cliente.nif, nif) == 0) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
	
}
/**
 * \brief Altera os dados de um cliente existente na lista de clientes.
 * 
 * \param head Ponteiro para a cabeça da lista de clientes.
 * \param saldo Novo saldo do cliente
 * \param nome Novo nome do cliente
 * \param morada Nova morada do Cliente
 * \param nif NIF do cliente cujos dados sao alterados
 * \return Ponteiro para a cabeça da lista de clientes atualizado.
 */
ClienteLista* alterarClientes(ClienteLista* head, float saldo, char* nome, char* morada, char* nif) {
	ClienteLista* aux = procuraClientes(head, nif);
	if (aux != NULL) {
		aux->cliente.saldo = saldo;
		strcpy(aux->cliente.nome, nome);
		strcpy(aux->cliente.morada, morada);
		strcpy(aux->cliente.nif, nif);
	}
	return head;
}


ClienteLista* lerFicheiroClientesBinario(char* nomeFicheiro) {
	FILE* fp;
	ClienteLista* h = NULL;
	Cliente aux;

	fp = fopen(nomeFicheiro, "rb");
	if (!fp) return NULL;


	while (fread(&aux, sizeof(Cliente), 1, fp)>0) {
		h = addCliente(h, aux);
	}

	fclose(fp);
	return h;
}


Cliente* ModificarSaldo(Cliente* cliente, float valorAluguel) {
	if (cliente == NULL || valorAluguel <= 0) return;

	if (VerificarSaldoCliente(valorAluguel, cliente)) {
		cliente->saldo -= valorAluguel;
	}
	return cliente;
}