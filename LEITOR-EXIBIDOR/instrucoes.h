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


int FU_resolveMethodo(ST_tpCONSTANT_Utf8_info *nome, ST_tpCONSTANT_Utf8_info *descricao);

void FU_invokevirtual(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_getstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_ldc2_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_dstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_dload_n(ST_tpStackFrame *pFrame, int posicao);

void FU_dadd(ST_tpStackFrame *pFrame);

void FU_dsub(ST_tpStackFrame *pFrame);

void FU_dmul(ST_tpStackFrame *pFrame);

void FU_ddiv(ST_tpStackFrame *pFrame);

void FU_drem(ST_tpStackFrame *pFrame);

void FU_dneg(ST_tpStackFrame *pFrame);

ST_tpVariable FU_dreturn(ST_tpStackFrame *pFrame );



int isValidType(char t);

#endif /* instrucoes_h */
