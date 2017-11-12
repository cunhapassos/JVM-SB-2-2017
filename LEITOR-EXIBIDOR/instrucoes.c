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


#include "instrucoes.h"

void FU_invokevirtual(ST_tpCp_info *pConstantPool, ST_tpThread *thread, u1 *pc){
    u1 parametro1, parametro2;
    u2 temp2Byte;
    pc++;
    memcpy(&parametro1, pc, 1);
    pc++;
    memcpy(&parametro2, pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    
    /// PAREI AQUI
}

void FU_dstore_n(ST_tpThread *thread, int posicao){
    ST_tpVariable var;
    
    var = PL_popOperando(thread->pJVMStack->operandStack);
    
    VM_armazenarVariavel(thread->pJVMStack->localVariables, var, posicao);
}

void FU_dload_n(ST_tpThread *thread, int posicao){
    ST_tpVariable var;
    
    var = VM_recuperarVariavel(thread->pJVMStack->localVariables, posicao);
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}

void FU_dadd(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(thread->pJVMStack->operandStack);
    var2 = PL_popOperando(thread->pJVMStack->operandStack);
    
    var.valor.Double = var1.valor.Double + var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}

void FU_dsub(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(thread->pJVMStack->operandStack);
    var2 = PL_popOperando(thread->pJVMStack->operandStack);
    
    var.valor.Double = var2.valor.Double - var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}

void FU_dmul(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(thread->pJVMStack->operandStack);
    var2 = PL_popOperando(thread->pJVMStack->operandStack);
    
    var.valor.Double = var1.valor.Double * var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}

void FU_ddiv(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(thread->pJVMStack->operandStack);
    var2 = PL_popOperando(thread->pJVMStack->operandStack);
    
    var.valor.Double = var2.valor.Double / var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}
void FU_drem(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(thread->pJVMStack->operandStack);
    var2 = PL_popOperando(thread->pJVMStack->operandStack);
    
    var.valor.Double = fmod(var2.valor.Double, var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}
void FU_dneg(ST_tpThread *thread){
    ST_tpVariable var;
    
    var = PL_popOperando(thread->pJVMStack->operandStack);
    var.valor.Double = -var.valor.Double;
    PL_pushOperando(thread->pJVMStack->operandStack, var);
}
            
void FU_dreturn(ST_tpThread *thread){
    ST_tpVariable *pVarReturn;
    
    *pVarReturn = PL_popOperando(thread->pJVMStack->operandStack);
    goto SairMetodo; // VERIFICAR ESSE GOTO E SE *pVarReturn TEM * MESMO
}
                            
