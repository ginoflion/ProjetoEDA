/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  Funções do Aluguer, que utilizam os clientes e os meios de mobilidade
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/


#include "Aluguer.h";

/**
 * \brief Função para criar 
 * 
 * \param cliente
 * \param meio
 * \param id
 * \return 
 */
Aluguer* CriarAluguer(Cliente* cliente, MobilidadeE* meio, int id) {
    if (cliente == NULL || meio == NULL) return NULL;

    if (!VerificarSaldoCliente(meio->precoAluguer, cliente)) {
        return NULL;
    }

    Aluguer* aluguer = (Aluguer*)malloc(sizeof(Aluguer));
    if (aluguer == NULL) {
        return NULL;
    }

    aluguer->id = id;
    aluguer->cliente = cliente;
    aluguer->automovel = meio;

    ModificarSaldo(cliente, meio->precoAluguer);

    return aluguer;
}


bool VerificarSaldoCliente(float valorAluguel, Cliente* cliente) {
    if (valorAluguel < 0 || cliente == NULL) return false;

    if (cliente->saldo >= valorAluguel) {
        return true;
    }
    else {
        return false;
    }
}


AluguerLista* AdicionarAluguerLista(AluguerLista* listaAlugueres, Aluguer* aluguer){
    if (aluguer == NULL) return listaAlugueres;

    AluguerLista* novoAluguer = (AluguerLista*)malloc(sizeof(AluguerLista));
    if (novoAluguer == NULL) {
        return listaAlugueres;
    }

    novoAluguer->aluguer = *aluguer;
    novoAluguer->anterior = NULL;
    novoAluguer->proximo = NULL;

    if (listaAlugueres == NULL) {
       
        listaAlugueres = novoAluguer;
    }
    else {
        AluguerLista* ultimo = listaAlugueres;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }

       
        ultimo->proximo = novoAluguer;
        novoAluguer->anterior = ultimo;
    }

    return listaAlugueres;
}


void MostrarAluguer(Aluguer* aluguer) {
    if (aluguer == NULL) {
        printf("Aluguer inválido.\n");
        return;
    }

    printf("ID: %d\n", aluguer->id);
    printf("NIF: %s\n", aluguer->cliente->nif);
    printf("Saldo Disponivel apos aluguer: %f\n", aluguer->cliente->saldo);
    printf("Tipo de Carro: %d\n", aluguer->automovel->tipo);
    printf("Matricula: %s\n", aluguer->automovel->matricula);
    printf("Autonomia: %d\n", aluguer->automovel->autonomia);
    printf("Bateria: %f\n", aluguer->automovel->bateria);

}

int SalvarFicheiroAlugueresBin(AluguerLista* head, char* ficheiro) {
    if (head == NULL) return 3;

    FILE* fp;
    fopen_s(&fp, ficheiro, "wb");
    if (fp == NULL) return 2;

    AluguerLista* aluguerAtual = head;
    while (aluguerAtual != NULL) {
        fwrite(&(aluguerAtual->aluguer), sizeof(Aluguer), 1, fp);
        aluguerAtual = aluguerAtual->proximo;
    }

    fclose(fp);
    return 1;
}

AluguerLista* lerFicheiroAlugueresBinario(char* nomeFicheiro) {
    FILE* fp;
    AluguerLista* h = NULL;
    Aluguer aux;

    fp = fopen(nomeFicheiro, "rb");
    if (!fp) return NULL;

    while (fread(&aux, sizeof(Aluguer), 1, fp) == 1) {
        Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
        if (!novoAluguer) {
            fclose(fp);
            return h;
        }
        *novoAluguer = aux;
        h = AdicionarAluguerLista(h, novoAluguer);
    }

    fclose(fp);
    return h;
}

void MostrarListaAlugueres(AluguerLista* listaAlugueres) {
    if (listaAlugueres == NULL) {
        return;
    }

    AluguerLista* aluguerAtual = listaAlugueres;

    while (aluguerAtual != NULL) {
        Aluguer* aluguer = &(aluguerAtual->aluguer);

        printf("NIF: %s\n", aluguer->cliente->nif);
        printf("Saldo Disponivel apos aluguer: %f\n", aluguer->cliente->saldo);
        printf("Tipo de Carro: %d\n", aluguer->automovel->tipo);
        printf("Matricula: %s\n", aluguer->automovel->matricula);
        printf("Autonomia: %d\n", aluguer->automovel->autonomia);
        printf("Bateria: %f\n", aluguer->automovel->bateria);

        aluguerAtual = aluguerAtual->proximo;
    }
}

AluguerLista* removerAluguerLista(AluguerLista* aluguer, AluguerLista* listaAlugueres) {
    if (listaAlugueres == NULL || aluguer == NULL) {
        return listaAlugueres;
    }

    if (&(listaAlugueres->aluguer) == aluguer) {
        AluguerLista* novoHead = listaAlugueres->proximo;
        free(listaAlugueres);
        return novoHead;
    }

    AluguerLista* aux = listaAlugueres;
    while (aux != NULL && aux->proximo != NULL) {
        if (&(aux->proximo->aluguer) == aluguer) {
            AluguerLista* aluguerARemover = aux->proximo;
            aux->proximo = aux->proximo->proximo;
            free(aluguerARemover);
            return listaAlugueres;
        }
        aux = aux->proximo;
    }

    return listaAlugueres;
}

Aluguer* ProcurarAluguer(int id, AluguerLista* listaAlugueres) {
    if (listaAlugueres == NULL)return NULL;
    AluguerLista* aux = listaAlugueres;
    while (aux != NULL) {
        if (aux->aluguer.id == id) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}