/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  Funções do Aluguer, que utilizam os clientes e os meios de mobilidade
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/


#include "Aluguer.h";

/**
 * \brief Função para criar um aluguer
 * 
 * \param cliente Ponteiro para o cliente que vai realizar o aluguer
 * \param meio Ponteiro para o meio de mobilidade que vai ser utilizado no aluguer
 * \param id id do aluguer
 * \return Ponteiro para o aluguer criado
 */
Aluguer* CriarAluguer(Cliente* cliente, MobilidadeE* meio, int id) {
    if (cliente == NULL || meio == NULL) return NULL;

    // Verifica se o cliente tem saldo suficiente para o aluguer
    if (!VerificarSaldoCliente(meio->precoAluguer, cliente)) {
        return NULL;
    }

    
    Aluguer* aluguer = (Aluguer*)malloc(sizeof(Aluguer));
    if (aluguer == NULL) {
        return NULL;
    }

    // Preenche os campos da estrutura de aluguer
    aluguer->id = id;
    aluguer->cliente = cliente;
    aluguer->automovel = meio;

    // Modifica o saldo do cliente, subtraindo o preço do aluguer
    ModificarSaldo(cliente, meio->precoAluguer);

    return aluguer;
}



/**
 * \brief Adicionar um aluguer à lista de alugueres
 * 
 * \param listaAlugueres Ponteiro para o início da lista de alugueres
 * \param aluguer ponteiro para o aluguer a ser adicionado à lista
 * \return lista de alugueres com o aluguer adicionado
 */
AluguerLista* AdicionarAluguerLista(AluguerLista* listaAlugueres, Aluguer* aluguer){
    if (aluguer == NULL) return listaAlugueres;

    //Cria um novo aluguer da lista de alugueres
    AluguerLista* novoAluguer = (AluguerLista*)malloc(sizeof(AluguerLista));
    if (novoAluguer == NULL) {
        return listaAlugueres;
    }

    // Preenche o novo aluguer com o aluguer para adicionar a lista
    novoAluguer->aluguer = *aluguer;
    novoAluguer->anterior = NULL;
    novoAluguer->proximo = NULL;

    //Verifica se a lista está vazia
    if (listaAlugueres == NULL) {
        listaAlugueres = novoAluguer;
    }
    else {
        //adiciona o aluguer após o ultimo aluguer da lista
        AluguerLista* ultimo = listaAlugueres;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }

        ultimo->proximo = novoAluguer;
        novoAluguer->anterior = ultimo;
    }

    return listaAlugueres;
}

/**
 * \brief Mostra os detalhes de um aluguer em específico
 * 
 * \param aluguer Ponteiro para o aluguer a ser mostrado
 */
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

/**
 * \brief Guarda a lista de alugueres no ficheiro binário
 * 
 * \param head Ponteiro para o inicio da lista de alugueres
 * \param ficheiro nome do ficheiro binario no qual seraõ guardados os dados
 * \return -2 caso a lista de alugueres esteja vazia
 * \return -1 caso exista algum problema a abrir o ficheiro
 * \return 1 caso os dados sejam guardados com sucesso
 */
int SalvarFicheiroAlugueresBin(AluguerLista* head, char* ficheiro) {
    if (head == NULL) return -2;

    FILE* fp;
    fopen_s(&fp, ficheiro, "wb");
    if (fp == NULL) return -1;

    AluguerLista* aluguerAtual = head;
    while (aluguerAtual != NULL) {
        fwrite(&(aluguerAtual->aluguer), sizeof(Aluguer), 1, fp);
        aluguerAtual = aluguerAtual->proximo;
    }

    fclose(fp);
    return 1;
}

/**
 * \brief Le o ficheiro de alugueres binário
 * 
 * \param nomeFicheiro nome do ficheiro a ser lido
 * \return  Lista de alugueres lidos do arquivo.
 */
AluguerLista* lerFicheiroAlugueresBinario(char* nomeFicheiro) {
    FILE* fp;
    AluguerLista* h = NULL;
    Aluguer aux;

    fp = fopen(nomeFicheiro, "rb");
    if (!fp) return NULL;

    // Lê cada aluger do ficheiro e adiciona à lista
    while (fread(&aux, sizeof(Aluguer), 1, fp) == 1) {
        Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
        if (!novoAluguer) {
            fclose(fp);
            return h;
        }
        // Copia o aluguer lido para o novo aluguer
        *novoAluguer = aux;
        // Adiciona o novo aluguer à lista de alugueres
        h = AdicionarAluguerLista(h, novoAluguer);
    }

    fclose(fp);
    return h;
}

/**
 * \brief Mostra a lista de alugueres
 * 
 * \param listaAlugueres Ponteiro para a lista de alugueres a ser mostrada
 */
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

/**
 * \brief Remove um aluguer da lista de alugueres.
 * 
 * \param aluguer Ponteiro para o aluguer a ser removido.
 * \param listaAlugueres Ponteiro para o início da lista de alugueres
 * \return  Ponteiro para a lista de alugueres atualizada
 */
AluguerLista* removerAluguerLista(AluguerLista* aluguer, AluguerLista* listaAlugueres) {
    if (listaAlugueres == NULL || aluguer == NULL) {
        return listaAlugueres;
    }

    // Verifica se o aluguer a ser removido é o primeiro aluguer da lista
    if (&(listaAlugueres->aluguer) == aluguer) {
        AluguerLista* novoHead = listaAlugueres->proximo;
        free(listaAlugueres);
        return novoHead;
    }

    AluguerLista* aux = listaAlugueres;
    while (aux != NULL && aux->proximo != NULL) {
        // Verifica se o aluguer a ser removido é o aluguer seguinte
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

/**
 * \brief Procura um aluguer da lista de alugueres utilizando o seu id
 * 
 * \param id codigo do aluguer a ser procurado
 * \param listaAlugueres Ponteiro para o inicio da lista de alugueres
 * \return Ponteiro para o aluguer encontrado
 * \return NULL caso o aluguer nao seja encontrado
 */
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

