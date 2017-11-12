/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *    Software Basico - Turma A
 *
 *  MODULO: ???
 *  @file instrucoes
 *  @brief
 *            Descricao: ????
 *
 * @author ALON MOTA     - MAT. 13/0005002
 * @author DANIEL MATIAS - MAT. 12/0139804
 * @author PAULO PASSOS  - MAT. 10/0118577
 *
 * @version 1.0
 * @since 11/11/17
 *
 @}********************************************************************************/


#ifndef instrucoes_h
#define instrucoes_h

#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "virtualMachine.h"



void FU_invokevirtual(ST_tpCp_info *pConstantPool, ST_tpThread *thread, u1 *pc);
void FU_dstore_n(ST_tpThread *thread, int posicao);

void FU_dload_n(ST_tpThread *thread, int posicao);

void FU_dadd(ST_tpThread *thread);

void FU_dsub(ST_tpThread *thread);

void FU_dmul(ST_tpThread *thread);

void FU_ddiv(ST_tpThread *thread);

void FU_drem(ST_tpThread *thread);

void FU_dneg(ST_tpThread *thread);

ST_tpVariable FU_dreturn(ST_tpThread *thread);

#endif /* instrucoes_h */
