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
    /*Cliente c1 = {"Joaquim" , "Braga", "123456789", 2500 };
    Cliente c2 = { "Maria", "Porto", "987654321", 3000 };
    clientes = addCliente(clientes, c1);
    clientes = addCliente(clientes, c2);
    MobilidadeE m1 = { 1500,M1,500, 1200, "12-AC-45","Braga" };
    MobilidadeE m2 = { 2000,M3,700, 1900, "69-TV-69","Porto" };

    Aluguer* a1 = CriarAluguer(&c1 , &m1, 1);
    Aluguer* a2 = CriarAluguer(&c2, &m2, 2);
    alugueres = AdicionarAluguerLista(alugueres, a1);
    alugueres = AdicionarAluguerLista(alugueres, a2);
   */
    /*AluguerLista* aluguerARemover = ProcurarAluguer(2, alugueres);
    alugueres = removerAluguerLista(aluguerARemover,alugueres);*/

    /*
    
    Aluguer* aluguer = CriarAluguer(&c1, &m1, alugueres);*/
   /* MostrarAluguer(aluguer);*/
    /*Vertice* v1 = CriaVertice("Lisboa",1);
    Vertice* v2 = CriaVertice("Porto", 2);
    Vertice* v3 = CriaVertice("Braga", 3);
    Vertice* v4 = CriaVertice("Coimbra", 4);
    Vertice* v5 = CriaVertice("Ponte Lima", 5);
    Vertice* v6 = CriaVertice("Barcelos", 6);
    grafo = AddVertice(grafo, v1);
    grafo = AddVertice(grafo, v2);
    grafo = AddVertice(grafo, v3);
    grafo = AddVertice(grafo, v4);
    grafo = AddVertice(grafo, v5);
    grafo = AddVertice(grafo, v6);
       
    Adj* a1 = CriaAdj(v1, v2, 10.0);
    Adj* a2 = CriaAdj(v1, v3, 25);
    Adj* a3 = CriaAdj(v1, v4, 50);
    Adj* a4 = CriaAdj(v3, v4, 15);
    Adj* a5 = CriaAdj(v4, v5, 5);
    Adj* a6 = CriaAdj(v5, v6, 30);
    Adj* a7 = CriaAdj(v2, v5, 7);
    InserirAdjVertice(grafo, a1);
    InserirAdjVertice(grafo, a2);
    InserirAdjVertice(grafo, a3);
    InserirAdjVertice(grafo, a4);
    InserirAdjVertice(grafo, a5);
    InserirAdjVertice(grafo, a6);
    InserirAdjVertice(grafo, a7);*/

    /*int t = SalvarFicheiroGrafosBin( grafo, "grafos.bin");
    printf("%d", t);*/
    //MostraGrafo(grafo);
    //int r = ExisteCaminho(grafo, 1, 6);
   // printf("%d", r);
    
   
 /*   Vertice* batata = NULL;
    batata= LerFicheiroGrafoBin(batata, "grafos.bin");
    MostraGrafo(batata);*/


   /* Gestores g1 = {1,"Rui","RuiSilvagmail.com", "benfica"};
    Gestores g2 = { 2,"Afonso","AfonsoSilvagmail.com", "Porto" };
    Gestores g3 = { 3,"Artur","ArturSilvagmail.com", "vsc" };
    Gestores g4 = { 4,"Luis","LuisSilvagmail.com", "estoril" };
    gestores = addGestor(gestores, g1);
    gestores = addGestor(gestores, g2);
    gestores = addGestor(gestores, g3);
    gestores = addGestor(gestores, g4);
    gestores = alterarGestores(gestores, 2, "Miguel", "MiguelSilva@email.com", "viseu");
    MostrarListaGestores(gestores);
    int r = SalvarFicheiroGestoresBin(gestores, "gestores.bin");
    printf("%d", r);*/

    meiosMobilidade = lerFicheiroMobilidadeBinario("meioMobilidade.bin");
    MostrarListaMeiosMobilidade(meiosMobilidade);
    meiosMobilidade = listarMeiosMobilidadePorLocalizacao(meiosMobilidade, "Porto");
    MostrarListaMeiosMobilidade(meiosMobilidade);

    return 0;
}


