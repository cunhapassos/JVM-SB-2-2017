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

/**
 *  Descricao da funcao:
 *       Inicializa a pilha
 *
 *  @param  ePilha - Ponteiro para a cabeça da pilha
 *
 */
void PL_inicializarPilha(ST_tpPilha **ePilha){
    *ePilha = NULL;
}

/**
 *  Descricao da funcao:
 *       Verifica se uma pilha esta vazia
 *
 *  @param  pPilha - Ponteiro para a cabeça da pilha
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
 *  @param  pPilha - Ponteiro para a cabeça da pilha
 *
 *  @return       - ponteiro para o elemento do topo da pilha
 */
void *PL_topoPilha(ST_tpPilha *pPilha){
    return pPilha->dado;
}

/**
 *  Descricao da funcao:
 *       Insere elemento no topo da pilha
 *
 *  @param  ePilha   - Ponteiro para a cabeça da pilha
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
 *  @param  ePilha - Ponteiro para a cabeça da pilha
 *
 *  @return   dado - Ponteiro para o elemento retirado do topo da pilha
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
        printf("ERRO, PILHA VAZIA, NAO PODE RETORNAR VARIAVEL!");
        var->tipo = 0x99;
        return var;
    }
}

void PL_esvaziarPilhaOperandos(ST_tpOperandStack **pPilhaOperandos){
    while (*pPilhaOperandos != NULL) {
        PL_popOperando(pPilhaOperandos);
    }
}

void PL_esvaziarPilhaParametros(ST_tpParameterStack**pPilhaParemetros ){
    while (*pPilhaParemetros != NULL) {
        PL_popParametro(pPilhaParemetros);
    }
}

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
        printf("ERRO, PILHA VAZIA, NAO PODE RETORNAR VARIAVEL!");
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
 Retorna um pontero para um Objeto de classe

 @param pObjects   - Ponteiro para a pilha de Objetos do ObjectHeap
 @param nomeClasse - Nome da classe referente ao objeto a ser procurado
 @return NULL      - Se o objeto nao foi encontrado
         pAux      - Ponteiro para o objeto encontrado
 */
ST_tpObjectHeap *PL_buscaObjetoHeap(ST_tpObjectHeap *pObjects, char *nomeClasse){
 
    ST_tpObjectHeap *pAux;
    
    if(pObjects == NULL) return NULL;
    for(pAux = pObjects; pAux != NULL; pAux = pAux->next){
        if(strcmp(pAux->className, nomeClasse)) return pAux;
    }
    return NULL;
}










