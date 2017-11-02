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
void PL_inicializarPilha(PI_tpPilha **ePilha){
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
int PL_pilhaVazia(PI_tpPilha *pPilha){
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
void *PL_topoPilha(PI_tpPilha *pPilha){
    return pPilha->dado;
}

/**
 *  Descricao da funcao:
 *       Insere elemento no topo da pilha
 *
 *  @param  ePilha   - Ponteiro para a cabeça da pilha
 *  @param  dadoNovo - Novo elemento da pilha
 */
void PL_push(PI_tpPilha **ePilha, void *dadoNovo){
    PI_tpPilha *p1;
    
    p1 = malloc(sizeof(PI_tpPilha));
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
void *PL_pop(PI_tpPilha **ePilha){
    PI_tpPilha *p1;
    void *dado;
    p1 = *ePilha;
    *ePilha = p1->prox;
    dado = p1->dado;
    free(p1);
    
    return dado;
}

/** ******************************************************************************
 *                      ESTRUTURAS E FUNCOES DE LISTA
 ** ******************************************************************************/
