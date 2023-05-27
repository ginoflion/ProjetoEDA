/*****************************************************************//**
 * \file   Grafo.c
 * \brief  Fun�oes dos Grafos
 * 
 * \author Gon�alo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h";


#pragma region Vertices
/**
 * \brief Cria um vertice.
 * 
 * \param cidade cidade para o novo Vertice
 * \param cod Codigo do novoVertice
 * \return novoVertice O novo vertice que ser� adicionado � lista de vertices
 */
Vertice* CriaVertice(char* cidade, int cod) {
	Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
	if (novoVertice == NULL) {
		free(novoVertice);
		return NULL;
	}
	if (novoVertice == NULL) {
		return NULL;
	}
	//Introdu��o da cidade e do c�digo no novo vert�c
	novoVertice->cod = cod;
	strcpy(novoVertice->cidade, cidade);
	novoVertice->proximo = NULL;
	novoVertice->adjacente = NULL;
	novoVertice->visitado = false;
	return novoVertice;
}

/**
 * \brief Adiciona o novo Vertice ao grafo
 * 
 * \param head Ponteiro para o in�cio do grafo
 * \param novo Ponteiro para o novo v�rtice que vai ser inserido no grafo
 * \return grafo com o novo v�rtice inserido
 */
Vertice* AddVertice(Vertice* head, Vertice* novo) {
	//Caso o grafo esteja vazio
	if (head== NULL) {
		head = novo;
		return head;
	}
	else {
		Vertice* aux = head;
		Vertice* anterior = aux;
		//Procura o v�rtice na lista
		while (aux != NULL && aux->cod != novo->cod	) {
			anterior = aux;
			aux = aux->proximo;
		}
		//Insere no in�cio da lista
		if (aux==head) {
			novo->proximo = head;
			head = novo;
		}
		//Insere no meio da lista
		else {
			novo->proximo = aux;
			anterior->proximo = novo;
		}

		return head;
	}

}

/**
 * \brief Procura um v�rtice no grafo pelo seu c�digo recursivo
 * 
 * \param head Ponteiro para o in�cio do grafo
 * \param cod codigo do vertice que vai ser procurado
 * \return head v�rtice encontrado
 */
Vertice* ProcuraVertice(Vertice* head, int cod) {
	if (head == NULL) return NULL;
	//caso o codigo do vertice seja o mesmo do codigo recebido nos parametros
	if (head->cod == cod) {
		return head;
	}
	//chamada recursiva da fun��o
	return ProcuraVertice(head->proximo, cod);
}

/**
 * \brief Contar os v�rtices inseridos no grafo
 * 
 * \param grafo Ponteiro para o in�cio do grafo
 * \return p Numero de v�rtices no grafo
 */
int ContarVertice(Vertice* grafo){

	int p = 0;
	Vertice* atual = grafo;

	while (atual != NULL) {
		p++;
		atual = atual->proximo;
	}

	return p;
}

/**
 * \brief Verifica se todos os vertices do grafo foram visitados
 * 
 * \param grafo Ponteiro para o in�cio do grafo
 * \return false grafo vazio
 * \return false caso nem todos os vertices tenham sido visitados
 * \return true se todos os vertices do grafo foram visitados
 */
bool TodosVerticesVisitados(Vertice* grafo) {
	if (grafo == NULL) return false;

	Vertice* atual = grafo;

	while (atual != NULL) {
		if (!atual->visitado) return false;
		atual = atual->proximo;
	}
	return true;
}
#pragma endregion

#pragma region Adjacentes
/**
 * \brief Cria uma nova adjac�ncia
 * 
 * \param codOrigem Ponteiro para o v�rtice origem
 * \param codDestino Ponteiro para o v�rtice destino
 * \param distancia dist�ncia entre os v�rtices
 * \return novaAdj a nova adjac�ncia
 */
Adj* CriaAdj(Vertice* codOrigem, Vertice* codDestino, float distancia) {
	if (codOrigem == NULL || codDestino == NULL)
		return NULL;

	Adj* novaAdj = (Adj*)malloc(sizeof(Adj));
	if (novaAdj == NULL) {
		return NULL;
	}
	//atribui��o dos valores � nova adjac�ncia
	novaAdj->codOrigem = codOrigem->cod;
	novaAdj->codDestino = codDestino->cod;
	novaAdj->distancia = distancia;
	novaAdj->proximo = NULL;
	novaAdj->vertice = codDestino;

	return novaAdj;
}

/**
 * \brief Mostrar adjac�ncias de forma recursiva
 * 
 * \param adj Ponteiro para a primeira adjacencia da lista
 */
void MostraAdjacencias(Adj* adj) {
	if (adj == NULL) return;
	printf("CodOrigem: %d \nCodDestino: %d \nDistancia: %.0f\n", adj->codOrigem, adj->codDestino, adj->distancia);
	//Mostrar as adjac�ncias que est�o inseridas no grafo
	MostraAdjacencias(adj->proximo);
}

/**
 * \brief Libertar a mem�ria alocada para a lista de adjac�ncias
 * 
 * \param adj Ponteiro para a primeira adjac�ncia da lista
 * \return a lista de adjacencias vazia
 */
Adj* DestruirAdj(Adj* adj) {
	if (adj == NULL)return NULL;
	Adj* atual = NULL;
	while (adj) {
		if (adj->proximo != NULL) {
			atual = adj->proximo;
		}
		free(adj);
		adj = atual;
		atual = NULL;
	}
	return adj;
}

/**
 * \brief Insere uma adjac�ncia no v�rtice
 * 
 * \param head Ponteiro para o inicio do grafo
 * \param adj a adjac�ncia a ser inserida 
 * \return Ponteiro para a nova adjacencia inserida
 */
Adj* InserirAdjVertice(Vertice* head, Adj* adj) {
	if (head == NULL)return NULL;
	//Procura os vertices de origem e destino no grafo
	Vertice* start = ProcuraVertice(head, adj->codOrigem);
	Vertice* destino = ProcuraVertice(head, adj->codDestino);

	if (start == NULL || destino == NULL)return NULL;
	//Criar a nova adjacencia
	Adj* novaAdj = CriaAdj(start, destino,adj->distancia);
	if (novaAdj == NULL)return NULL;
	//Insere a adjac�ncia no verticeOrigem
	if (start->adjacente == NULL) {
		start->adjacente = novaAdj;
	}
	else {
		novaAdj->proximo = start->adjacente;
		start->adjacente = novaAdj;
	}
	return start->adjacente;

}

#pragma endregion 


#pragma region Grafo
/**
 * \brief Mostra o grafo recursivamente
 *
 * \param head Ponteiro para o in�cio do grafo
 */
void MostraGrafo(Vertice* head) {
	if (head == NULL) return;
	printf("V: %d - %s\n", head->cod, head->cidade);
	MostraGrafo(head->proximo);
	MostraAdjacencias(head->adjacente);
}

/**
 * \brief Liberta a mem�ria alocada para o grafo
 * 
 * \param head Ponteiro para o in�cio do grafo
 * \return grafo vazio
 */
Vertice* DestruirGrafo(Vertice* head) {
	if (head == NULL)return NULL;
	
	Vertice* atual = NULL;
	while (head) {
		if (head->proximo != NULL) {
			atual = head->proximo;
		}
		head->adjacente = DestruirAdj(head->adjacente);
		free(head);
		head = atual;
		atual = NULL;
	}
	return head;
}

/**
 * \brief Guardar o grafo no ficheiro bin�rio
 * 
 * \param grafo Ponteiro para o in�cio do grafo
 * \param nomeFicheiro Nome do ficheiro a ser guardado
 * \return -1 caso o grafo esteja vazio
 * \return -2 se ocorrer um erro ao abrir o ficheiro
 * \return 1 caso o ficheiro tenha sido guardado com sucesso
 */
int SalvarFicheiroGrafosBin(Vertice* grafo, char* nomeFicheiro) {
	if (grafo == NULL)return -1;
	Vertice* verticeAtual = grafo;
	Adj* adjacenciaAtual = NULL;
	AdjFicheiro adjAtual = { 0 };

	FILE* fp;
	fopen_s(&fp, nomeFicheiro, "wb");

	if (fp == NULL)return -2;

	int numeroVertices = ContarVertice(grafo);

	fwrite(&numeroVertices, sizeof(int), 1, fp);

	// Escreve os c�digos dos v�rtices no ficheiro
	while (verticeAtual != NULL) {
		fwrite(&(verticeAtual->cod), sizeof(VerticeFicheiro), 1, fp);
		verticeAtual = verticeAtual->proximo;
	}
	// Muda o ponteiro para o in�cio do grafo
	verticeAtual = grafo;

	// Escreve as adjac�ncias no ficheiro
	while (verticeAtual != NULL) {
		Adj* adjacenciaAtual = verticeAtual->adjacente;
		while (adjacenciaAtual != NULL) {
			adjAtual.codOrigem = verticeAtual->cod;
			adjAtual.codDestino = adjacenciaAtual->codDestino;
			adjAtual.distancia = adjacenciaAtual->distancia;

			fwrite(&adjAtual, sizeof(adjAtual), 1, fp);
			adjacenciaAtual = adjacenciaAtual->proximo;
		}
		verticeAtual = verticeAtual->proximo;
	}
	fclose(fp);
	return 1;
}

/**
 * \brief L� um grafo apartir de um ficheiro binario
 * 
 * \param grafo Ponteiro para o in�cio do grafo.
 * \param nomeFicheiro Nome do ficheiro a ser lido.
 * \return ponteiro para o in�cio do grafo lido a partir do arquivo.
 */
Vertice* LerFicheiroGrafoBin(Vertice* grafo , char* nomeFicheiro) {

	
	FILE* fp;
	fopen_s(&fp, nomeFicheiro, "rb");


	if (fp == NULL) return -2;

	VerticeFicheiro verticeAtual;
	AdjFicheiro adjacenciaAtual;

	int numVertices =  0 ;

	//L� o n�mero de v�rtices no ficheiro
	fread(&numVertices, sizeof(int), 1, fp);
	if (numVertices <= 0) return 3;

	//Adicionar os v�rtices do ficheiro ao grafo
	for (int i = 0; i < numVertices; i++) {
		fread(&verticeAtual, sizeof(VerticeFicheiro), 1, fp);
		grafo=AddVertice(grafo, CriaVertice( verticeAtual.cidade, verticeAtual.cod));
		
	}
	//Adicionar as adjacencias do ficheiro ao grafo
	while (fread(&adjacenciaAtual, sizeof(AdjFicheiro), 1, fp) == 1) {
		//Cria a adjacencia usando os vertices correspondentes no grafo
		Adj* a1 = CriaAdj(ProcuraVertice(grafo, adjacenciaAtual.codOrigem), ProcuraVertice(grafo,adjacenciaAtual.codDestino), adjacenciaAtual.distancia);
		//Insere a adjacencia no vertice do grafo
		InserirAdjVertice(grafo, a1);
	}

	fclose(fp);
	return grafo;
}

/**
 * \brief Verifica se existe caminho entre dois v�rtices do grafo de forma recursiva
 * 
 * \param grafo Ponteiro para o in�cio do grafo.
 * \param codOrigem codigo do vertice origem
 * \param codDestino codigo do vertice destino
 * \return -1 caso o grafo seja nulo
 * \return 1 caso exista um caminho entre dois vertices
 * \return -2 caso n�o exista um caminho entre dois vertices
 */
int ExisteCaminho(Vertice* grafo, int codOrigem, int codDestino) {
	if (grafo == NULL)return -1;

	//se o codigo origem for igual ao codigo destino existe um caminho entre os dois vertices
	if (codOrigem == codDestino)return 1;

	Vertice* verticeAtual = ProcuraVertice(grafo, codOrigem);
	verticeAtual->visitado = true;

	Adj* adjacenciaAtual = verticeAtual->adjacente;

	while (adjacenciaAtual != NULL) {
		verticeAtual = adjacenciaAtual->vertice;
		// Verifica se o v�rtice atual j� foi visitado
		if (!verticeAtual->visitado) {
			//Recursividade para o pr�ximo v�rtice
			return ExisteCaminho(grafo, verticeAtual->cod, codDestino);
		}
		adjacenciaAtual=adjacenciaAtual->proximo;
	}
	return -2;

}

int LerFicheiroGrafoTXT(Vertice* grafo, char* nomeFicheiro) {

}

#pragma endregion