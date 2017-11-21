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


int FU_retornaNumeroParametrosMetodo(ST_tpCONSTANT_Utf8_info *nome, ST_tpCONSTANT_Utf8_info *descricao);

int FU_invokevirtual(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno);

int FU_invokespecial(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno);

int FU_invokestatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno);

int FU_invokeinterface(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno);

// Implementar FU_invokedynamic

void FU_new(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_newarray(ST_tpStackFrame *pFrame, u1 **pc);

void FU_anewarray(ST_tpStackFrame *pFrame, u1 **pc);

void FU_arraylenght(ST_tpStackFrame *pFrame);

void FU_athrow(ST_tpStackFrame *pFrame);

void FU_checkcast(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_instanceof(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_getstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_putstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_sipush(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ldc(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_ldc2_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_istore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_lstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_fstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_dstore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_astore_n(ST_tpStackFrame *pFrame, int posicao);

void FU_return(ST_tpStackFrame *pFrame);

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

void FU_dup2(ST_tpStackFrame *pFrame);

void FU_dup2_x1(ST_tpStackFrame *pFrame);

void FU_dup2_x2(ST_tpStackFrame *pFrame);

void FU_swap(ST_tpStackFrame *pFrame);

void FU_iadd(ST_tpStackFrame *pFrame);

void FU_ladd(ST_tpStackFrame *pFrame);

void FU_fadd(ST_tpStackFrame *pFrame);

void FU_dadd(ST_tpStackFrame *pFrame);

void FU_isub(ST_tpStackFrame *pFrame);

void FU_lsub(ST_tpStackFrame *pFrame);

void FU_fsub(ST_tpStackFrame *pFrame);

void FU_dsub(ST_tpStackFrame *pFrame);

void FU_imul(ST_tpStackFrame *pFrame);

void FU_lmul(ST_tpStackFrame *pFrame);

void FU_fmul(ST_tpStackFrame *pFrame);

void FU_dmul(ST_tpStackFrame *pFrame);

void FU_idiv(ST_tpStackFrame *pFrame);

void FU_ldiv(ST_tpStackFrame *pFrame);

void FU_fdiv(ST_tpStackFrame *pFrame);

void FU_ddiv(ST_tpStackFrame *pFrame);

void FU_irem(ST_tpStackFrame *pFrame);

void FU_lrem(ST_tpStackFrame *pFrame);

void FU_frem(ST_tpStackFrame *pFrame);

void FU_drem(ST_tpStackFrame *pFrame);

void FU_ineg(ST_tpStackFrame *pFrame);

void FU_lneg(ST_tpStackFrame *pFrame);

void FU_fneg(ST_tpStackFrame *pFrame);

void FU_dneg(ST_tpStackFrame *pFrame);

void FU_lcmp(ST_tpStackFrame *pFrame);

void FU_fcmpl(ST_tpStackFrame *pFrame);

void FU_fcmpg(ST_tpStackFrame *pFrame);

void FU_dcmpl(ST_tpStackFrame *pFrame);

void FU_dcmpg(ST_tpStackFrame *pFrame);

void FU_ifeq(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ifne(ST_tpStackFrame *pFrame, u1 **pc);

void FU_iflt(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ifge(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ifgt(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ifle(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_icmpeq(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_icmpne(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_icmplt(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_icmpge(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_icmpgt(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_icmple(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_acmpeq(ST_tpStackFrame *pFrame, u1 **pc);

void FU_if_acmpne(ST_tpStackFrame *pFrame, u1 **pc);

void FU_goto(ST_tpStackFrame *pFrame, u1 **pc);

void FU_jsr(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ret(ST_tpStackFrame *pFrame, u1 **pc);

void FU_i2l(ST_tpStackFrame *pFrame);

void FU_i2f(ST_tpStackFrame *pFrame);

void FU_i2d(ST_tpStackFrame *pFrame);

void FU_l2i(ST_tpStackFrame *pFrame);

void FU_l2f(ST_tpStackFrame *pFrame);

void FU_l2d(ST_tpStackFrame *pFrame);

void FU_f2i(ST_tpStackFrame *pFrame);

void FU_f2l(ST_tpStackFrame *pFrame);

void FU_f2d(ST_tpStackFrame *pFrame);

void FU_d2i(ST_tpStackFrame *pFrame);

void FU_d2l(ST_tpStackFrame *pFrame);

void FU_d2f(ST_tpStackFrame *pFrame);

void FU_i2b(ST_tpStackFrame *pFrame);

void FU_i2c(ST_tpStackFrame *pFrame);

void FU_i2s(ST_tpStackFrame *pFrame);

void FU_tableswitch(ST_tpStackFrame *pFrame, u1 **pc);

void FU_lookupswitch(ST_tpStackFrame *pFrame, u1 **pc);

void FU_ireturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno);

void FU_lreturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno);

void FU_freturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno);

void FU_dreturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno);

void FU_areturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno);

void FU_getfield(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_putfield(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc);

void FU_ishl(ST_tpStackFrame *pFrame);

void FU_lshl(ST_tpStackFrame *pFrame);

void FU_ishr(ST_tpStackFrame *pFrame);

void FU_lshr(ST_tpStackFrame *pFrame);

void FU_iushr(ST_tpStackFrame *pFrame);

void FU_lushr(ST_tpStackFrame *pFrame);

void FU_iand(ST_tpStackFrame *pFrame);

void FU_land(ST_tpStackFrame *pFrame);

void FU_ior(ST_tpStackFrame *pFrame);

void FU_lor(ST_tpStackFrame *pFrame);

void FU_ixor(ST_tpStackFrame *pFrame);

void FU_lxor(ST_tpStackFrame *pFrame);



#endif /* instrucoes_h */
