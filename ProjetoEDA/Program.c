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
   
    
    MobilidadeE mobilidade1 = { 120, M1, 3.50, 90, "AA-11-22", "Lisboa" };
    MobilidadeE mobilidade2 = { 200, M2, 4.25, 120, "BB-33-44", "Porto" };
    MobilidadeE mobilidade3 = { 300, M3, 6.00, 150, "CC-55-66", "Funchal" };
    MobilidadeE mobilidade4 = { 300, M3, 6.00, 150, "CC-55-77", "Funchal" };
    meiosMobilidade = addMeioMobilidade(meiosMobilidade, mobilidade1);
    meiosMobilidade = addMeioMobilidade(meiosMobilidade, mobilidade2);
    meiosMobilidade = addMeioMobilidade(meiosMobilidade, mobilidade3);
    meiosMobilidade = addMeioMobilidade(meiosMobilidade, mobilidade4);
    meiosMobilidade = listarMeiosMobilidadePorLocalizacao(meiosMobilidade, "Funchal");
    MostrarListaMeiosMobilidade(meiosMobilidade);
    
    

    

  
    return 0;
}


