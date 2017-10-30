/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO PILHA
 *  @{
 *  @ingroup MOD_PI
 *
 *  @file pilha.h
 *  @brief
 *            Modulo de definicao: Modulo Pilha
 *            Define a assinatura de funcoes e estruturas de pilha
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @author DANIEL MATIAS
 * @author ALON MOTA
 *
 * @version 1.0
 * @since 30/10/2017
 *
 @}********************************************************************************/

#ifndef pilha_h
#define pilha_h

#include <stdio.h>
#include <stdlib.h>

typedef struct tpPilha{
    void *dado;
    struct tpPilha *prox;
}PI_tpPilha;

void PI_inicializarPilha(PI_tpPilha **ePilha);

int PI_pilhaVazia(PI_tpPilha *pPilha);

void *PI_topoPilha(PI_tpPilha *pPilha);

void PI_push(PI_tpPilha **ePilha, void *dadoNovo);

void *PI_pop(PI_tpPilha **ePilha);

#endif /* pilha_h */
