/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  MODULO: PL
 *  @file pilhas_listas.h
 *  @brief
 *            Descricao:  Definicao das funcoes de pilha.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @author DANIEL MATIAS
 * @author ALON MOTA
 *
 * @version 1.0
 * @since 30/10/2017
 *
 @}********************************************************************************/

#ifndef pilhas_listas_h
#define pilhas_listas_h

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

/** ******************************************************************************
 *                      ESTRUTURAS E FUNCOES DE PILHA
 ** ******************************************************************************/

ST_tpOperandStack *PL_criarPilhaOperandos(void);

void PL_pushOperando(ST_tpOperandStack *pPilhaOperandos, ST_tpVariable var);

ST_tpVariable PL_popOperando(ST_tpOperandStack *pPilhaOperandos);

ST_tpParameterStack *PL_criarPilhaParametros(void);

void PL_pushParametro(ST_tpParameterStack *pPilhaParametros, ST_tpVariable var);



/** ******************************************************************************
 *                      ESTRUTURAS E FUNCOES DE LISTA
 ** ******************************************************************************/

void PL_inserirClasseTopo(ST_tpJVM *pJvm, ST_tpClassFile *pClasse);

int PL_removerClasseTopo(ST_tpJVM *pJVM);

ST_tpClassFile *PL_buscarClasse(ST_tpJVM *pJVM, char *nomeClasse);

#endif /* pilhas_listas_h */
