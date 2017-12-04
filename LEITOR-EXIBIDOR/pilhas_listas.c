/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO PILHAS_LISTAS
 *  @{
 *  @ingroup MOD_PL
 *
 *  @file pilha.c
 *  @brief
 *            Implementa as funções de pilha.
 *
 * @author ALON MOTA        - MAT. 13/0005002
 * @author DANIEL MATIAS    - MAT. 12/0139804
 * @author GABRIEL TOLLINI  - MAT. 14/0020454
 * @author PAULO PASSOS     - MAT. 10/0118577
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

/**
 *  Descricao da funcao:
 *       Inicializa a pilha
 *
 *  @param  ePilha - Endereço do topo da pilha
 *
 */
void PL_inicializarPilha(ST_tpPilha **ePilha){
    *ePilha = NULL;
}

/**
 *  Descricao da funcao:
 *       Verifica se uma pilha esta vazia
 *
 *  @param  pPilha - Endereço do topo da pilha
 *
 *  @return       - 0 se a pilha nao esta vazia
 *                  1 se a pilha esta vazia
 */
int PL_pilhaVazia(ST_tpPilha *pPilha){
    return (pPilha == NULL);
}

/**
 *  Descricao da funcao:
 *       Retorna o elemento do topo da pilha
 *
 *  @param  pPilha - Endereço do topo da pilha
 *
 *  @return        - Endereço do valor no topo da pilha
 */
void *PL_topoPilha(ST_tpPilha *pPilha){
    return pPilha->dado;
}

/**
 *  Descricao da funcao:
 *       Insere elemento no topo da pilha
 *
 *  @param  ePilha   - Endereço do topo da pilha
 *  @param  dadoNovo - Novo elemento da pilha
 */
void PL_push(ST_tpPilha **ePilha, void *dadoNovo){
    ST_tpPilha *p1;
    
    if(*ePilha == NULL){
        p1 = malloc(sizeof(ST_tpPilha));
    }
    p1 = malloc(sizeof(ST_tpPilha));
    p1->dado = dadoNovo;
    p1->prox = *ePilha;
    *ePilha = p1;
}

/**
 *  Descricao da funcao:
 *       Retira um elemento do topo da pilha
 *
 *  @param    ePilha - Endereço do topo da pilha
 *
 *  @return   dado   - Endereço do elemento retirado do topo da pilha
 */
void *PL_pop(ST_tpPilha **ePilha){
    ST_tpPilha *p1;
    void *dado;
    p1 = *ePilha;
    *ePilha = p1->prox;
    dado = p1->dado;
    free(p1);
    
    return dado;
}
/*
 *  Descrição da função:
 *       Faz o Push na pilha de operandos
 *
 *  @param  pPilhaOperandos - Endereço da pilha de operandos
 *  @param  var - valor a ser adicionado na pilha de operandos 
 */

void PL_pushOperando(ST_tpOperandStack **pPilhaOperandos, ST_tpVariable var){
    ST_tpOperandStack *pAux = (ST_tpOperandStack*)malloc(sizeof(ST_tpOperandStack));
    
    pAux->next = NULL;
    pAux->variable = var;
    
    if(*pPilhaOperandos == NULL){
        *pPilhaOperandos = pAux;
    }
    else{
        pAux->next = *pPilhaOperandos;
        *pPilhaOperandos = pAux;
    }
}
/*
 *  Descrição da função:
 *       Faz o Pop na pilha de operandos
 *
 *  @param  pPilhaOperandos - Endereço da pilha de operandos
 *
 *  @return var - Valor removido da pilha
 */
ST_tpVariable *PL_popOperando(ST_tpOperandStack **pPilhaOperandos){
    ST_tpVariable *var;
    ST_tpOperandStack *pAux;
    
    var = malloc(sizeof(ST_tpVariable));
    
    // VERIFICAR COMO FAZER QUANDO A PILHA FOR VAZIA
    if (*pPilhaOperandos != NULL){
        var->tipo =  (*pPilhaOperandos)->variable.tipo;
        var->valor = (*pPilhaOperandos)->variable.valor;
        pAux =  *pPilhaOperandos;
        *pPilhaOperandos = (*pPilhaOperandos)->next;
        
        free(pAux);
        pAux = NULL;
        
        return var;
    }
    else{
        //printf("ERRO, PILHA VAZIA, NAO PODE RETORNAR VARIAVEL!");
        var->tipo = 0x99;
        return var;
    }
}
/*
 *  Descrição da função:
 *       Esvazia a pilha de operandos
 *
 *  @param  pPilhaOperandos - Endereço da pilha de operandos
 */
void PL_esvaziarPilhaOperandos(ST_tpOperandStack **pPilhaOperandos){
    while (*pPilhaOperandos != NULL) {
        PL_popOperando(pPilhaOperandos);
    }
}
/*
 *  Descrição da função:
 *       Esvazia a pilha de parâmetros
 *
 *  @param  pPilhaParametros - Endereço da pilha de parâmetros
 */

void PL_esvaziarPilhaParametros(ST_tpParameterStack**pPilhaParemetros ){
    while (*pPilhaParemetros != NULL) {
        PL_popParametro(pPilhaParemetros);
    }
}
/*
 *  Descrição da função:
 *       Faz o Push na pilha de parâmetros
 *
 *  @param  pPilhaParametros - Endereço da pilha de parâmetros
 *  @param  var - valor a ser adicionado na pilha de parâmetros 
 */
void PL_pushParametro(ST_tpParameterStack **pPilhaParametros, ST_tpVariable var){
    ST_tpParameterStack *pAux = (ST_tpParameterStack *)malloc(sizeof(ST_tpParameterStack));
    
    pAux->next      = NULL;
    pAux->variable  = var;
    
    if(*pPilhaParametros == NULL){
        *pPilhaParametros = pAux;
    }
    else{
        pAux->next = *pPilhaParametros;
        *pPilhaParametros = pAux;
    }
}

/*
 *  Descrição da função:
 *       Faz o Pop na pilha de parâmetros
 *
 *  @param  pPilhaParametros - Endereço da pilha de parâmetros
 *
 *  @return var - Valor removido da pilha
 */

ST_tpVariable *PL_popParametro(ST_tpParameterStack **pPilhaParametros){
    ST_tpVariable *var;
    ST_tpParameterStack *pAux;
    
    var = malloc(sizeof(ST_tpVariable));
    if (*pPilhaParametros != NULL){
        var->tipo = (*pPilhaParametros)->variable.tipo;
        var->valor = (*pPilhaParametros)->variable.valor;
        pAux = (*pPilhaParametros);
        (*pPilhaParametros) = (*pPilhaParametros)->next;
        pAux = NULL;
        free(pAux);
        return var;
    }
    else{
        //printf("ERRO, PILHA VAZIA, NAO PODE RETORNAR VARIAVEL!");
        var->tipo = 0x99;
        return var;
    }
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
 *  @param pClasse - Endereço da classe a ser inserida na JVM
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

/*
 *  Descrição da função:
 *       Insere uma classe no final da lista de Classes
 *
 *  @param  pClasses - Lista de Classes
 *  @param  pJvm - Java Virtual Machine, de se recebe a classe a ser adicionada
 */

void PL_inserirClasseFundo(ST_tpJVM *pJvm, ST_tpClassFile *pClasse){
    ST_tpClassFile *pAux = pJvm->methodArea->classFile;
    
    if(pAux == NULL){
        pClasse->prev = NULL;
        pClasse->next = NULL;
        pJvm->methodArea->classFile = pClasse;
    }
    else{
        while (pAux->next != NULL) {
            pAux = pAux->next;
        }
        pAux->next = pClasse;
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
 * @return NULL      - Se a Classe nao foi encontrado
 *         pAux      - Endereço da Classe econtrada
 *
 */
ST_tpClassFile *PL_buscarClasse(ST_tpJVM *pJVM, char *nomeClasse){
    ST_tpClassFile *pClasse;
    char *name;
    u2 nameIndex, thisClass;
    
    if(pJVM == NULL) return NULL;
    if (pJVM->methodArea == NULL) return NULL;
    if (pJVM->methodArea->classFile == NULL) return NULL;
    
    for(pClasse = pJVM->methodArea->classFile; pClasse != NULL; pClasse = pClasse->next){
        
        thisClass = pClasse->this_class;
        nameIndex = pClasse->constant_pool_table[thisClass - 1].info.Class.name_index;
        name = (char *) pClasse->constant_pool_table[nameIndex - 1].info.Utf8.bytes;
 
        if(strcmp(name, nomeClasse) == 0) return pClasse;
    }
    
    return NULL;
}


/**
* Retorna um pontero para um Objeto de classe
*
* @param pObjects   - Ponteiro para a pilha de Objetos do ObjectHeap
* @param nomeClasse - Nome da classe referente ao objeto a ser procurado
* @return NULL      - Se o objeto nao foi encontrado
*         pAux      - Endereço do objeto encontrado
**/
ST_tpObjectHeap *PL_buscaObjetoHeap(ST_tpObjectHeap *pObjects, char *nomeClasse){
 
    ST_tpObjectHeap *pAux;
    
    if(pObjects == NULL) return NULL;
    for(pAux = pObjects; pAux != NULL; pAux = pAux->next){
        if(strcmp(pAux->className, nomeClasse) == 0) return pAux;
    }
    return NULL;
}
/*
 *  Descrição da função:
 *       Busca, na pilha de Classes, uma Classe por seu nome
 *
 *  @param  pClasses - Lista de Classes
 *  @param  nomeClasse - Nome da Classe a ser procurada 
 *
 *  @return NULL - Se a classe não foi encontrada
 *          pAux - Endereço da classe encontrada
 */

ST_tpClassHeap *PL_buscaClassHeap(ST_tpClassHeap *pClasses, char *nomeClasse){

    ST_tpClassHeap *pAux;

    if(pClasses == NULL) return NULL;
    for(pAux = pClasses; pAux != NULL; pAux = pAux->next){
        if(strcmp(pAux->pClassName, nomeClasse) == 0) return pAux;
    }
    return NULL;
}










