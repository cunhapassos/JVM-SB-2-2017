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

int FU_invokespecial(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno);

void FU_getstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_putstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_ldc(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_ldc2_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_istore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_lstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_fstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_dstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_astore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_dadd(ST_tpStackFrame *pFrame);

void FU_dsub(ST_tpStackFrame *pFrame);

void FU_dmul(ST_tpStackFrame *pFrame);

void FU_ddiv(ST_tpStackFrame *pFrame);

void FU_drem(ST_tpStackFrame *pFrame);

void FU_dneg(ST_tpStackFrame *pFrame);

ST_tpVariable FU_dreturn(ST_tpStackFrame *pFrame );

void FU_bipush(ST_tpStackFrame *pFrame, u1 **pc);

void FU_pushNull(ST_tpStackFrame *pFrame);

void FU_pushConstInt(ST_tpStackFrame *pFrame, int cte);

void FU_pushConstFloat(ST_tpStackFrame *pFrame, float cte);

void FU_pushConstLong(ST_tpStackFrame *pFrame, int64_t cte);

void FU_pushConstDouble(ST_tpStackFrame *pFrame, double cte);

int isValidType(char t);

void FU_iload(ST_tpStackFrame *pFrame, u1 **pc);

void FU_lload(ST_tpStackFrame *pFrame, u1 **pc);

void FU_dload(ST_tpStackFrame *pFrame, u1 **pc);

void FU_fload(ST_tpStackFrame *pFrame, u1 **pc);

void FU_aload(ST_tpStackFrame *pFrame, u1 **pc);

void FU_iload_n(ST_tpStackFrame *pFrame, int index);

void FU_lload_n(ST_tpStackFrame *pFrame, int index);

void FU_fload_n(ST_tpStackFrame *pFrame, int index);

void FU_dload_n(ST_tpStackFrame *pFrame, int index);

void FU_aload_n(ST_tpStackFrame *pFrame, int index);

void FU_iaload(ST_tpStackFrame *pFrame);

void FU_laload(ST_tpStackFrame *pFrame);

void FU_faload(ST_tpStackFrame *pFrame);

void FU_daload(ST_tpStackFrame *pFrame);

void FU_aaload(ST_tpStackFrame *pFrame);

void FU_baload(ST_tpStackFrame *pFrame);

void FU_caload(ST_tpStackFrame *pFrame);

void FU_saload(ST_tpStackFrame *pFrame);

void FU_istore(ST_tpStackFrame *pFrame, u1 **pc);

void FU_fstore(ST_tpStackFrame *pFrame, u1 **pc);

void FU_lstore(ST_tpStackFrame *pFrame, u1 **pc);

void FU_dstore(ST_tpStackFrame *pFrame, u1 **pc);

void FU_astore(ST_tpStackFrame *pFrame, u1 **pc);

void FU_iastore(ST_tpStackFrame *pFrame);

void FU_lastore(ST_tpStackFrame *pFrame);

void FU_fastore(ST_tpStackFrame *pFrame);

void FU_dastore(ST_tpStackFrame *pFrame);

void FU_aastore(ST_tpStackFrame *pFrame);

void FU_bastore(ST_tpStackFrame *pFrame);

void FU_castore(ST_tpStackFrame *pFrame);

void FU_sastore(ST_tpStackFrame *pFrame);

void FU_pop(ST_tpStackFrame *pFrame);

void FU_pop2(ST_tpStackFrame *pFrame);

void FU_dup(ST_tpStackFrame *pFrame);

void FU_dup_x1(ST_tpStackFrame *pFrame);

void FU_dup_x2(ST_tpStackFrame *pFrame);

#endif /* instrucoes_h */
