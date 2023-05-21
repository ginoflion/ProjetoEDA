/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   May 2023
 *********************************************************************/


#include "Aluguer.h";


Aluguer* CriarAluguer(ClienteLista* listaC, MobilidadeLista* listaA, AluguerLista* alugueres) {
    if (listaC == NULL || listaA == NULL) return NULL;

    if (!VerificarSaldoCliente(listaA->automovel.precoAluguer, &(listaC->cliente))) {
        return NULL;
    }

    Aluguer* aluguer = (Aluguer*)malloc(sizeof(Aluguer));
    if (aluguer == NULL) {
        return NULL;
    }

    aluguer->cliente = &(listaC->cliente);
    aluguer->automovel = &(listaA->automovel);

    ModificarSaldo(&(listaC->cliente), listaA->automovel.precoAluguer);

    alugueres = AdicionarAluguerLista(alugueres, aluguer);

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

void ModificarSaldo(Cliente* cliente, float valorAluguel) {
    if (cliente == NULL || valorAluguel <= 0) return;

    if (VerificarSaldoCliente(valorAluguel, cliente)) {
        cliente->saldo -= valorAluguel;
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

    printf("Cliente: %s\n", aluguer->cliente->nome);
    printf("NIF: %s\n", aluguer->cliente->nif);
    printf("Saldo Disponivel apos aluguer: %f\n", aluguer->cliente->saldo);
    printf("Tipo de Carro: %d\n", aluguer->automovel->tipo);
    printf("Matricula: %s\n", aluguer->automovel->matricula);
    printf("Autonomia: %f\n", aluguer->automovel->autonomia);
    printf("Bateria: %f\n", aluguer->automovel->bateria);

}