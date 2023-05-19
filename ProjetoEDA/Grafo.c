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


int SalvarFicheiroGrafosBin(Vertice* head, char* nomeFicheiro){
	if (head == NULL)return 3;
	Vertice* aux = head;
	FILE* fp;
	fp = fopen(nomeFicheiro, "wb");
	if (fp == NULL)return 2;
	VerticeFicheiro auxFicheiro;
	while (aux != NULL) {
		auxFicheiro.cod = aux->cod;
		strcpy(auxFicheiro.cidade, aux->cidade);
		fwrite(&auxFicheiro, sizeof(VerticeFicheiro), 1, fp);
		if (aux->adjacente) {
			SalvarFicheiroAdjBin(aux->adjacente,);
		}
		aux = aux->proximo;
	}

	fclose(fp);
	return 1;
}
