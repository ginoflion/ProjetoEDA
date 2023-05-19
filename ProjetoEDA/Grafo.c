/*****************************************************************//**
 * \file   Grafo.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h";


#pragma region Vertices


Vertice* CriaVertice(char* cidade, int cod) {
	Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
	if (novoVertice == NULL) {
		free(novoVertice);
		return novoVertice;
	}
	if (novoVertice == NULL) {
		return NULL;
	}
	novoVertice->cod = cod;
	strcpy(novoVertice->cidade, cidade);
	novoVertice->proximo = NULL;
	novoVertice->adjacente = NULL;
	return novoVertice;
}




Vertice* AddVertice(Vertice* head, Vertice* novo) {
	if (head== NULL) {
		head = novo;
		return head;
	}
	else {
		Vertice* aux = head;
		Vertice* anterior = aux;
		while (aux != NULL && aux->cod != novo->cod	) {
			anterior = aux;
			aux = aux->proximo;
		}
		if (aux==head) {
			novo->proximo = head;
			head = novo;
		}
		else {
			novo->proximo = aux;
			anterior->proximo = novo;
		}

		return head;
	}

}
void MostraGrafo(Vertice* head) {
	if (head == NULL) return;
	printf("V: %d - %s\n", head->cod, head->cidade);
	MostraGrafo(head->proximo);
	MostraAdjacencias(head->adjacente);
}

Vertice* ProcuraVertice(Vertice* head, int cod) {
	if (head == NULL) return NULL;
	if (head->cod == cod) {
		return head;
	}
	return ProcuraVertice(head->proximo, cod);
}
#pragma endregion

#pragma region Adjacentes

Adj* CriaAdj(int codOrigem, int codDestino, float distancia) {

	Adj* novaAdj = (Adj*)malloc(sizeof(Adj));
	if (novaAdj == NULL) {
		free(novaAdj);
		return novaAdj;
	}
	if (novaAdj == NULL) {
		return NULL;
	}

	novaAdj->codOrigem = codOrigem;
	novaAdj->codDestino = codDestino;
	novaAdj->distancia = distancia;
	novaAdj->proximo = NULL;
	return novaAdj;

}


Adj* InserirAdjVertice(Vertice* head, Adj* adj) {
	if (head == NULL)return NULL;
	Vertice* start = ProcuraVertice(head, adj->codOrigem);
	Vertice* destino = ProcuraVertice(head, adj->codDestino);

	if (start == NULL || destino == NULL)return NULL;
	Adj* novaAdj = CriaAdj(adj->codOrigem, adj->codDestino,adj->distancia);
	if (novaAdj == NULL)return NULL;
	if (start->adjacente == NULL) {
		start->adjacente = novaAdj;
	}
	else {
		novaAdj->proximo = start->adjacente;
		start->adjacente = novaAdj;
	}
	return start->adjacente;

}

void MostraAdjacencias(Adj* adj) {
	if (adj == NULL) return;
	printf("CodOrigem: %d \nCodDestino: %d \nDistancia: %.0f\n" , adj->codOrigem,adj->codDestino,adj->distancia);
	MostraAdjacencias(adj->proximo);
}
#pragma endregion 



Vertice* DestruirGrafo(Vertice* head) {
	if (head == NULL)return NULL;
	
	Vertice* atual = NULL;
	while (head) {
		if (head->proximo) {
			atual = head->proximo;
		}
		head->adjacente = DestruirAdj(head->adjacente);
		free(head);
		head = atual;
		atual = NULL;
	}
	return head;
}

Adj* DestruirAdj(Adj* adj){
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

int SalvarFicheiroGrafosBin(Vertice* grafo, char* nomeFicheiro) {
	if (grafo == NULL) return 3;
	Vertice* verticeAtual = grafo;
	VerticeFicheiro verticeFicheiro;
	Adj* adjAtual;
	AdjFicheiro adjAtualFicheiro;

	FILE* fp;
	fopen_s(&fp, nomeFicheiro, "wb");
	if (fp == NULL)return 2;

	int numeroVertices = ContarVertice(grafo);
	fwrite(&numeroVertices, sizeof(numeroVertices), 1, fp);

	while (verticeAtual != NULL) {
		strcpy(verticeFicheiro.cidade, verticeAtual->cidade);
		verticeFicheiro.cod = verticeAtual->cod;
		fwrite(&(verticeFicheiro), sizeof(VerticeFicheiro), 1, fp);
		verticeAtual = verticeAtual->proximo;
	}
	verticeAtual = grafo;
	while (verticeAtual != NULL) {
		Adj* adjAtual = verticeAtual->adjacente;
		while (adjAtual != NULL) {
			adjAtualFicheiro.codOrigem = verticeAtual->adjacente->codOrigem;
			adjAtualFicheiro.codDestino = verticeAtual->adjacente->codDestino;
			adjAtualFicheiro.distancia = verticeAtual->adjacente->distancia;
			fwrite(&adjAtualFicheiro,sizeof(adjAtualFicheiro),1,fp);
			adjAtual = adjAtual->proximo;

		}
		verticeAtual = verticeAtual->proximo;
	}
	fclose(fp);
	return 1;
}

Vertice* lerFicheiroGrafosBin(char* nomeFicheiro){
	FILE* fp = fopen(nomeFicheiro, "rb");

	
	if (fp == NULL) return NULL;

	VerticeFicheiro verticeAtualFicheiro;
	AdjFicheiro adjAtualFicheiro;

	Vertice* grafo = NULL;
	Vertice* verticeAtual = NULL;


	int numVertices = 0;

	fread(&numVertices, sizeof(int), 1, fp);

	if (numVertices <= 0) return;

	for (int i = 0; i < numVertices; i++) {

		if (fread(&verticeAtualFicheiro, sizeof(VerticeFicheiro), 1, fp)) {
			Vertice* novoVertice = CriaVertice(verticeAtualFicheiro.cidade, verticeAtualFicheiro.cod);
			
			grafo = AddVertice(grafo, novoVertice);
		}
	}

	while (fread(&adjAtualFicheiro, sizeof(AdjFicheiro), 1, fp) == 1) {

		Adj* novaAdjacencia = CriaAdj(adjAtualFicheiro.codOrigem, adjAtualFicheiro.codDestino, adjAtualFicheiro.distancia);

		verticeAtual = ProcuraVertice(grafo, novaAdjacencia->codOrigem);
		InserirAdjVertice(verticeAtual, novaAdjacencia);
	}

	fclose(fp);
	return grafo;
}



int ContarVertice(Vertice* grafo) {

	int p = 0;
	Vertice* atual = grafo;

	while (atual != NULL) {
		p++;
		atual = atual->proximo;
	}

	return p;
}







