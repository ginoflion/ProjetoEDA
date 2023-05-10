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


//Teste das funçoes
int main() {
    
    ClienteLista* clientes = NULL;
    MobilidadeLista* meiosMobilidade = NULL;
    GestoresLista* gestores = NULL;
   
    
    
    printf("%d" ,LerFicheiroClientes(&clientes, "clientes.txt"));
    printf("%d" ,LerFicheiroMeioMobilidade(&meiosMobilidade, "meiosMobilidade.txt"));
    printf("%d" ,LerFicheiroGestores(&gestores, "gestores.txt"));

   

    
    MostrarListaGestores(gestores);
    GestoresLista* gestorARemover = procuraGestores(gestores, 2);
    gestores= removerGestor(gestores, gestorARemover);
    MostrarListaGestores(gestores);
   

  
    return 0;
}


