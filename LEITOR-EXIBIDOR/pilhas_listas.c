/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *    Software Basico - Turma A
 *
 *  MODULO: PL_
 *  @file pilha.c
 *  @brief
 *            Descricao:  Implementa as funcoes de pilha.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @author DANIEL MATIAS
 * @author ALON MOTA
 *
 * @version 1.0
 * @since 30/10/2017
 *
 @}********************************************************************************/

#include <string.h>
#include "pilhas_listas.h"

/** ******************************************************************************
 *                      ESTRUTURAS E FUNCOES DE PILHA
 ** ******************************************************************************/

ST_tpOperandStack *PL_criarPilhaOperandos(){
    ST_tpOperandStack *pOperandStack;
    
    pOperandStack = (ST_tpOperandStack *) malloc(sizeof(ST_tpOperandStack));
    pOperandStack->next = NULL;
    return pOperandStack;
}

void PL_pushOperando(ST_tpOperandStack *pPilhaOperandos, ST_tpVariable var){
    ST_tpOperandStack *pAux = (ST_tpOperandStack*)malloc(sizeof(ST_tpOperandStack));
    
    pAux->next = NULL;
    pAux->variable = var;
    
    if(pPilhaOperandos == NULL){
        pPilhaOperandos = pAux;
    }
    else{
        pAux->next = pPilhaOperandos;
        pPilhaOperandos = pAux;
    }
}

ST_tpVariable PL_popOperando(ST_tpOperandStack *pPilhaOperandos){
    ST_tpVariable var;
    ST_tpOperandStack *pAux;
    
    // VERIFICAR COMO FAZER QUANDO A PILHA FOR VAZIA
    //if (pPilhaOperandos == NULL){
    
    var.tipo =  pPilhaOperandos->variable.tipo;
    var.valor = pPilhaOperandos->variable.valor;
    pAux =  pPilhaOperandos;
    pPilhaOperandos = pPilhaOperandos->next;
    
    free(pAux);
    pAux = NULL;
    
    return var;
}

ST_tpParameterStack *PL_criarPilhaParametros(){
    ST_tpParameterStack *pParameterStack;
    
    pParameterStack = (ST_tpParameterStack *) malloc(sizeof(ST_tpParameterStack));
    pParameterStack->next = NULL;
    return pParameterStack;
}

void PL_pushParametro(ST_tpParameterStack *pPilhaParametros, ST_tpVariable var){
    ST_tpParameterStack *pAux = (ST_tpParameterStack *)malloc(sizeof(ST_tpParameterStack));
    
    pAux->next      = NULL;
    pAux->variable  = var;
    
    if(pPilhaParametros == NULL){
        pPilhaParametros = pAux;
    }
    else{
        pAux->next = pPilhaParametros;
        pPilhaParametros = pAux;
    }
}

ST_tpVariable PL_popParametro(ST_tpParameterStack *pPilhaParametros){
    ST_tpVariable var;
    ST_tpParameterStack *pAux;
    
    var.tipo = pPilhaParametros->variable.tipo;
    var.valor = pPilhaParametros->variable.valor;
    
    pAux = pPilhaParametros;
    pPilhaParametros = pPilhaParametros->next;
    free(pAux);
    pAux = NULL;
    
    return var;
}
/** ******************************************************************************
 *                      ESTRUTURAS E FUNCOES DE LISTA
 ** ******************************************************************************/

/**
 *  Descricao da funcao:
 *           Insere classe carregada no topo da lista de classes carregadas da JVM
 *           A lista é uma lista eh duplamente encadeada de classes
 *
 *  @param pJvm    - Ponteiro para a JVM
 *  @param pClasse - Ponteiro para a classe a ser inserida na JVM
 * 
 */
void PL_inserirClasseTopo(ST_tpJVM *pJvm, ST_tpClassFile *pClasse){
    
    if(pJvm->methodArea->classFile == NULL){
        pClasse->prev = NULL;
        pClasse->next = NULL;
        pJvm->methodArea->classFile = pClasse;
    }
    else{
        pClasse->prev = NULL;
        pJvm->methodArea->classFile->prev = pClasse;
        pClasse->next = pJvm->methodArea->classFile;
        pJvm->methodArea->classFile = pClasse;
    }
}

/**
 *  Descricao da funcao:
 *           Remove classe do topo da lista de classes carregadas da JVM
 *           A lista é uma lista eh duplamente encadeada de classes
 *
 *  @param pJVM    - Ponteiro para a JVM
 *  @return 0 ou 1 - retorno de controle
 */
int PL_removerClasseTopo(ST_tpJVM *pJVM){
    ST_tpClassFile *pAux;
    
    if(pJVM->methodArea->classFile == NULL){
        return 0;
    }
    else if(pJVM->methodArea->classFile->next == NULL){
        free(pJVM->methodArea->classFile);
        pJVM->methodArea->classFile = NULL;
        return 1;
    }
    else{
        pAux = pJVM->methodArea->classFile;
        pJVM->methodArea->classFile = pJVM->methodArea->classFile->next;
        pJVM->methodArea->classFile->prev = NULL;
        free(pAux);
        pAux = NULL;
        return 1;
    }
    return 0;
}

/**
 *  Descricao da funcao:
 *           Busca uma classe na lista de classes carregadas da JVM
 *           A lista é uma lista duplamente encadeada de classes
 *
 *  @param pJVM         - Ponteiro para a JVM
 *  @param nomeClasse   - Nome da classe a ser procurada
 *
 */
ST_tpClassFile *PL_buscarClasse(ST_tpJVM *pJVM, char *nomeClasse){
    ST_tpClassFile *pClasse;
    char *name;
    u2 nameIndex;
    
    if(pJVM == NULL) return NULL;
    if (pJVM->methodArea == NULL) return NULL;
    if (pJVM->methodArea->classFile == NULL) return NULL;
    
    for(pClasse = pJVM->methodArea->classFile; pClasse != NULL; pClasse = pClasse->next){
        
        nameIndex = pClasse->constant_pool_table[pClasse->this_class-1].info.Class.name_index-1;
        name = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
        
        if(strcmp(name, nomeClasse) == 0) return pClasse;
    }
    
    return NULL;
}












