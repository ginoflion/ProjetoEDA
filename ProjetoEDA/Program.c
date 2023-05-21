/*****************************************************************//**
 * \file   Program.c
 * \brief  
 * 
 * \author Gonçalo Silva - a25970
 * \date   March 2023
 *********************************************************************/

#include "Cliente.h"
#include "Gestao.h"
#include "Mobilidade.h"
#include "Grafos.h"
#include "Aluguer.h"

//Teste das funçoes
int main() {
    
    ClienteLista* clientes = NULL;
    MobilidadeLista* meiosMobilidade = NULL;
    GestoresLista* gestores = NULL;
    Vertice* grafo =NULL;
    AluguerLista* alugueres = NULL;

    Cliente c1 = {"Joaquim" , "Braga", "123456789", 2500 };
    Cliente c2 = { "Maria", "Porto", "987654321", 3000 };
    clientes = addCliente(clientes, c1);
    clientes = addCliente(clientes, c2);
    MobilidadeE m1 = { 1500,M1,500, 1200, "12-AC-45","Braga" };
    MobilidadeE m2 = { 2000,M3,700, 1900, "69-TV-69","Porto" };
    meiosMobilidade = addMeioMobilidade(meiosMobilidade, m1);
    meiosMobilidade = addMeioMobilidade(meiosMobilidade, m2);

    ClienteLista* clienteEncontrado = procuraClientes(clientes, "123456789");
    MobilidadeLista* meioEncontrado = procuraMeioMobilidade(meiosMobilidade,"12-AC-45" );

    Aluguer* aluguer = CriarAluguer(clienteEncontrado, meioEncontrado, alugueres);
    MostrarAluguer(aluguer);
   

    // Procurar um cliente com base no número de NIF
    /*
    Aluguer* aluguer = CriarAluguer(c1, m1, alugueres);
    MostrarAluguer(aluguer);*/
    //Vertice* v1 = CriaVertice("Lisboa",1);
    //Vertice* v2 = CriaVertice("Porto",2);
    //Vertice* v3 = CriaVertice("Braga", 3);
    //grafo = AddVertice(grafo, v1);
    //grafo = AddVertice(grafo, v2);
    //grafo = AddVertice(grafo, v3);
    //   
    //Adj* adj = CriaAdj(1, 2, 10.0);
    //InserirAdjVertice(grafo, adj);
    //int t = SalvarFicheiroGrafosBin(grafo, "grafos.bin");
    //printf("%d", t);
    //MostraGrafo(grafo);

    //Vertice* novalista = lerFicheiroGrafosBin("grafos.bin");
    //MostraGrafo(novalista);


    return 0;
}


