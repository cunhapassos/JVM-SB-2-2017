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

#include <math.h>
#include "instrucoes.h"
#include "pilhas_listas.h"

void FU_invokevirtual(ST_tpCp_info *pConstantPool, ST_tpThread *thread, u1 *pc){
    u1 parametro1, parametro2;
    u2 temp2Byte;
    ST_tpMethod_info *pMethodo;
    ST_tpConstantPool *cpIndx;
    ST_tpCONSTANT_Methodref_info *pMethodref;
    ST_tpCONSTANT_Class_info *pClassRef;
    ST_tpCONSTANT_Utf8_info *pClassName, *pMethodName, *pMethodDescriptor;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    

    pc++;
    memcpy(&parametro1, pc, 1);
    pc++;
    memcpy(&parametro2, pc, 1);
    
    temp2Byte = (parametro1 << 8) + parametro2;
    cpIndx = &pConstantPool[temp2Byte -1].info;
    pMethodref = (ST_tpCONSTANT_Methodref_info *)malloc(sizeof(ST_tpCONSTANT_Methodref_info));
    memcpy(pMethodref, &(cpIndx->Methodref), sizeof(ST_tpCONSTANT_Methodref_info));

    temp2Byte = pMethodref->class_index;
    cpIndx = &pConstantPool[temp2Byte-1].info;
    pClassRef = (ST_tpCONSTANT_Class_info *)malloc(sizeof(ST_tpCONSTANT_Class_info));
    memcpy(pClassRef, &(cpIndx->Class), sizeof(ST_tpCONSTANT_Class_info));

    temp2Byte = pClassRef->name_index;
    cpIndx = &pConstantPool[temp2Byte-1].info;
    pClassName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClassName, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    temp2Byte = pMethodref->name_and_type_index;
    cpIndx = &pConstantPool[temp2Byte-1].info;
    nameTyperef = (ST_tpCONSTANT_NameAndType_info *)malloc(sizeof(ST_tpCONSTANT_NameAndType_info));
    memcpy(nameTyperef, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_NameAndType_info));

    temp2Byte = nameTyperef->name_index;
    cpIndx = &pConstantPool[temp2Byte-1].info;
    pMethodName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodName, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    temp2Byte = nameTyperef->descriptor_index;
    cpIndx = &pConstantPool[temp2Byte-1].info;
    pMethodDescriptor = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodDescriptor, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    
    if(FU_resolveMethodo(pMethodName, pMethodDescriptor)) {

    }

    
    printf("Instrucao inacabada");
    pc++;
    
    /// PAREI AQUI
}


//TODO resolve method
int FU_resolveMethodo(ST_tpCONSTANT_Utf8_info *nome, ST_tpCONSTANT_Utf8_info *descricao){

    return 1;
}

void FU_getstatic( ST_tpThread *thread){
    u1 parametro1, parametro2;
    u2 temp2Byte;
    ST_tpConstantPool *cpIndx;
    ST_tpCONSTANT_Fieldref_info *pFieldref;
    
    thread->PC++;
    memcpy(&parametro1, thread->PC, 1);
    thread->PC++;
    memcpy(&parametro2, thread->PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    cpIndx = &thread->pJVMStack->cp->constant_pool_table[temp2Byte].info;
    pFieldref = (ST_tpCONSTANT_Fieldref_info *) malloc(sizeof(ST_tpCONSTANT_Fieldref_info));
    memcpy(pFieldref, cpIndx, sizeof(ST_tpCONSTANT_Fieldref_info));
    
}
void FU_ldc2_w(ST_tpCp_info *pConstantPool, ST_tpThread *thread){
    u1 parametro1, parametro2;
    u2 temp2Byte;
    ST_tpConstantPool *cpIndx;
    ST_tpVariable *pVar1, *pVar2;
    ST_tpCONSTANT_Long_info *pLong;
    ST_tpCONSTANT_String_info *pString;
    ST_tpCONSTANT_Utf8_info *pUTF8;
    ST_tpCONSTANT_Double_info *pDouble;
    
    pVar1 = malloc(sizeof(ST_tpVariable));
    pVar2 = malloc(sizeof(ST_tpVariable));
    cpIndx = malloc(sizeof(ST_tpConstantPool));
    
    thread->PC++;
    memcpy(&parametro1, thread->PC, 1);
    thread->PC++;
    memcpy(&parametro2, thread->PC, 1);
        pLong             = (ST_tpCONSTANT_Long_info *)cpIndx;
    temp2Byte = (parametro1 << 8) + parametro2;
    
    cpIndx = &pConstantPool[temp2Byte - 1].info;

    if(cpIndx->Long.tag == CONSTANT_Long){
        pLong             = (ST_tpCONSTANT_Long_info *)cpIndx;
        pVar2->valor.Long = pLong->high_bytes;
        pVar1->valor.Long = (pVar2->valor.Long << 32) | pLong->low_bytes;
        PL_pushOperando(&thread->pJVMStack->operandStack, *pVar1);
        
    }
    else if (cpIndx->Double.tag == CONSTANT_Double){
        pDouble             = (ST_tpCONSTANT_Double_info *)cpIndx;
        pVar2->valor.Double = pDouble->low_bytes;
        pVar1->valor.Double = ((u8)pVar2->valor.Double << 32 | pDouble->low_bytes);
        PL_pushOperando(&thread->pJVMStack->operandStack, *pVar1);
    }
    else if (cpIndx->Double.tag == CONSTANT_String){
        pString = (ST_tpCONSTANT_String_info *) cpIndx;
        cpIndx = &pConstantPool[pString->string_index-1].info;
        
        pUTF8 = (ST_tpCONSTANT_Utf8_info *) cpIndx;
        
    }

}

void FU_dload_n(ST_tpThread *thread, int posicao){
    ST_tpVariable var;
    
    var = VM_recuperarVariavel(thread->pJVMStack->localVariables, posicao);
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}

void FU_dadd(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&thread->pJVMStack->operandStack);
    var2 = PL_popOperando(&thread->pJVMStack->operandStack);
    
    var.valor.Double = var1.valor.Double + var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}

void FU_dsub(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&thread->pJVMStack->operandStack);
    var2 = PL_popOperando(&thread->pJVMStack->operandStack);
    
    var.valor.Double = var2.valor.Double - var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}

void FU_dmul(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&thread->pJVMStack->operandStack);
    var2 = PL_popOperando(&thread->pJVMStack->operandStack);
    
    var.valor.Double = var1.valor.Double * var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}

void FU_ddiv(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&thread->pJVMStack->operandStack);
    var2 = PL_popOperando(&thread->pJVMStack->operandStack);
    
    var.valor.Double = var2.valor.Double / var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}
void FU_drem(ST_tpThread *thread){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&thread->pJVMStack->operandStack);
    var2 = PL_popOperando(&thread->pJVMStack->operandStack);
    
    var.valor.Double = fmod(var2.valor.Double, var1.valor.Double);
    var.tipo = JDOUBLE;
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}
void FU_dneg(ST_tpThread *thread){
    ST_tpVariable var;
    
    var = PL_popOperando(&thread->pJVMStack->operandStack);
    var.valor.Double = -var.valor.Double;
    PL_pushOperando(&thread->pJVMStack->operandStack, var);
}
            
ST_tpVariable FU_dreturn(ST_tpThread *thread){
    ST_tpVariable varReturn;
    
    varReturn = PL_popOperando(&thread->pJVMStack->operandStack); // VERIFICAR SE *pVarReturn TEM * MESMO
    return varReturn;
} 
                            
