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

void FU_invokevirtual(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    u1 parametro1, parametro2;
    u2 temp2Byte;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpConstantPool *cpIndx;
    ST_tpCONSTANT_Methodref_info *pMethodref;
    ST_tpCONSTANT_Class_info *pClassRef;
    ST_tpCONSTANT_Utf8_info *pClassName, *pMethodName, *pMethodDescriptor;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    int count = 0;
    
    pConstantPool = pFrame->cp->constant_pool_table;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    
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
    
    count = FU_resolveMethodo(pMethodName, pMethodDescriptor);
    count ++;

    if(count >= 0) {
        while( count != 0 && pFrame->operandStack != NULL) {
            PL_pushParametro(   &pFrame->parameterStack,
                                PL_popOperando(&pFrame->operandStack));
            count --;
        }

        pClassFile = PL_buscarClasse(pJVM, (char *) pClassName->bytes);


        //cria stack 

        //tenta criar methodo
    }
    (*pc)++;
}
int FU_invokespecial(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno){
    
    u2 temp2Byte;
    int count = 0;
    ST_tpVariable *pVar1;
    char *nomeClasseTemp = NULL;
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpObjectHeap *pTempHeap;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_Class_info *pClassRef;
    ST_tpCONSTANT_Methodref_info *pMethodref;
    ST_tpCONSTANT_Utf8_info *pMethodName, *pMethodDescriptor;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    
    
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    pConstantPool = pFrame->cp->constant_pool_table;
    cpIndx = &pConstantPool[temp2Byte -1].info;
    pMethodref = (ST_tpCONSTANT_Methodref_info *)malloc(sizeof(ST_tpCONSTANT_Methodref_info));
    memcpy(pMethodref, &(cpIndx->Methodref), sizeof(ST_tpCONSTANT_Methodref_info));
    
    temp2Byte = pMethodref->class_index;
    cpIndx = &pConstantPool[temp2Byte-1].info;
    pClassRef = (ST_tpCONSTANT_Class_info *)malloc(sizeof(ST_tpCONSTANT_Class_info));
    memcpy(pClassRef, &(cpIndx->Class), sizeof(ST_tpCONSTANT_Class_info));
    
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
    
    count = FU_resolveMethodo(pMethodName, pMethodDescriptor);
    //count ++;
    
    while( count != 0 && pFrame->operandStack != NULL) {
        PL_pushParametro(&pFrame->parameterStack, PL_popOperando(&pFrame->operandStack));
        count --;
    }
    if(!strcmp((const char *)pMethodName, "<init>")){
        return 1; // Significa um erro
    }
    
    pVar1 = &pFrame->parameterStack->variable;
    pTempHeap = pVar1->valor.obj_ref;
    
    strcpy(nomeClasseTemp, pTempHeap->classeName);
    
    pClassFile = PL_buscarClasse(pJVM, nomeClasseTemp);
    
    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));
        
        if((pMetodoInfo->access_flags & ACC_ABSTRACT) == ACC_ABSTRACT){
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_STATIC) == ACC_STATIC){
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
            // EXECUTAR METODO NATIVO
            
        }
        else{
            *Retorno = VM_executarMetodo(pJVM, pClassFile, pFrame->parameterStack, pMetodoInfo);
        }
        
        if((*Retorno)->tipo != JVOID ){
            PL_pushOperando(&pFrame->operandStack, *(*Retorno));
        }
        if ((*Retorno)->tipo == JAREF && (*Retorno)->valor.array_ref != 0) {
            ((*Retorno)->valor.array_ref)->ref_count --;
        }
        if((*Retorno)->tipo == JREF && (*Retorno)->valor.array_ref != 0){
            ((*Retorno)->valor.array_ref)->ref_count --;
        }
        // Ver caseo de excecoes
        //if()
    }
    else{
        return 1; // ERRO
    }
    
    return 0;
}
//TODO resolve method
int FU_resolveMethodo(ST_tpCONSTANT_Utf8_info *nome, ST_tpCONSTANT_Utf8_info *descricao){

    int params = 0, index = -1;
    char aux;

    do {
        index ++;
        aux = descricao->bytes[index];

        switch(aux) {
            case 'B': case 'C': case 'D': case 'F': case 'I': case 'J': case 'S': case 'Z':
                params ++;
            break;

            case 'L' :
                params ++;
                do {
                    index ++;
                    aux = descricao->bytes[index];
                } while(aux != ';');
            break;

            default: break;
        }

    } while (aux != ')');

    return params;
}

void FU_getstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    
    ST_tpVariable var;
    ST_tpCp_info *pCPInfo;
    ST_tpConstantPool *cpIndx;
    u1 parametro1, parametro2;
    u2 temp2Byte, index1, index2;
    ST_tpCONSTANT_Fieldref_info *pFieldref;
    char *nomeClasse, *nomeField, *descritorField;
    
    var.tipo = 0x99; // inicializa variavel com valor arbitrario
    pCPInfo = pFrame->cp->constant_pool_table;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    cpIndx = &pCPInfo[temp2Byte-1].info;
    
    pFieldref   = (ST_tpCONSTANT_Fieldref_info *) malloc(sizeof(ST_tpCONSTANT_Fieldref_info));
    memcpy(pFieldref, cpIndx, sizeof(ST_tpCONSTANT_Fieldref_info));
    
    index1      = pFieldref->class_index;
    index2      = pCPInfo[index1 - 1].info.Class.name_index;
    nomeClasse  = (char *)pCPInfo[index2 - 1].info.Utf8.bytes;
    
    index1 = pFieldref->name_and_type_index;
    index2 = pCPInfo[index1 - 1].info.NameAndType.name_index;
    nomeField = (char *) pCPInfo[index2 - 1].info.Utf8.bytes;
   
    index2 = pCPInfo[index1 - 1].info.NameAndType.descriptor_index;
    descritorField = (char *) pCPInfo[index2 - 1].info.Utf8.bytes;
    
    var = *VM_recuperarValorStaticField(pJVM, nomeClasse, nomeField, descritorField);
    
    PL_pushOperando(&pFrame->operandStack, var);

}
void FU_ldc2_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    
    int i;
    u2 temp2Byte;
    ST_tpObjectHeap *pObjRef;
    ST_tpConstantPool *cpIndx;
    ST_tpArrayHeap *pArrayRef;
    ST_tpCONSTANT_Utf8_info *pUTF8;
    ST_tpCONSTANT_Long_info *pLong;
    u1 parametro1, parametro2, tipo;
    ST_tpCONSTANT_Double_info *pDouble;
    ST_tpCONSTANT_String_info *pString;
    ST_tpVariable pVar, pVar1, pVar2;
    
    cpIndx = malloc(sizeof(ST_tpConstantPool));
    
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    cpIndx = &(pFrame->cp->constant_pool_table[temp2Byte - 1].info);

    if(cpIndx->Long.tag == CONSTANT_Long){
        pLong             = (ST_tpCONSTANT_Long_info *)cpIndx;
        pVar2.valor.Long = pLong->high_bytes;
        pVar1.valor.Long = (pVar2.valor.Long << 32) | pLong->low_bytes;
        pVar1.tipo = JLONG;
        PL_pushOperando(&pFrame->operandStack, pVar1);
    }
    
    else if (cpIndx->Double.tag == CONSTANT_Double){
        pDouble             = (ST_tpCONSTANT_Double_info *)cpIndx;
        u8 aux = (u8)pDouble->high_bytes;
        aux <<= 32;
        aux |= pDouble->low_bytes;
        memcpy(&pVar1.valor.Double, &aux, sizeof(int64_t));
        pVar1.tipo = JDOUBLE;
        PL_pushOperando(&pFrame->operandStack, pVar1);
    }
    
    else if (cpIndx->Double.tag == CONSTANT_String){
        
        char nomeField[] = "value";
        char descriptorField[] = "[C";
        char nomeClasse[] =  "java/lang/String";
        
        pString = (ST_tpCONSTANT_String_info *) cpIndx;
        if(pString->StringObject == NULL){
            cpIndx = &(pFrame->cp->constant_pool_table[pString->string_index-1].info);
            pUTF8 = (ST_tpCONSTANT_Utf8_info *) cpIndx;
            tipo = T_CHAR;
            
            pArrayRef = VM_criarArray(tipo, "", pUTF8->length);
            pVar1.tipo = JREF;
            pVar1.valor.array_ref = pArrayRef;
            
            for(i = 0; i < pUTF8->length; i++){
                VM_armazenarValorArray(pArrayRef, i, pVar1);
            }
            
            pObjRef = VM_criarObjeto(pJVM, pFrame->cp);
            pVar2.valor.obj_ref = pObjRef;
            
            VM_armazenarValorField(pJVM, nomeClasse, nomeField, descriptorField, pVar1, pVar2);
            
            pVar.valor.Int = 0;
            strcpy(nomeField, "offset");
            strcpy(descriptorField, "I");
            VM_armazenarValorField(pJVM, nomeClasse, nomeField, descriptorField, pVar, pVar2);
            
            pVar.valor.Int = i;
            strcpy(nomeField, "count");
            strcpy(descriptorField, "I");
            VM_armazenarValorField(pJVM, nomeClasse, nomeField, descriptorField, pVar, pVar2);
            
            
            pString->StringObject = (ST_tpObjectHeap *) pVar2.valor.obj_ref;
        }
        
        else{
            tipo = JREF;
            pVar2.valor.obj_ref = pString->StringObject;
        }
        PL_pushOperando(&pFrame->operandStack, pVar2);
    }
}

void FU_dload_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = VM_recuperarVariavel(pFrame->localVariables, posicao);
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dstore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);
    
}

void FU_dadd(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&pFrame->operandStack);
    var2 = PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var1.valor.Double + var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dsub(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&pFrame->operandStack);
    var2 = PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var2.valor.Double - var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dmul(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&pFrame->operandStack);
    var2 = PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var1.valor.Double * var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ddiv(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&pFrame->operandStack);
    var2 = PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var2.valor.Double / var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}
void FU_drem(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = PL_popOperando(&pFrame->operandStack);
    var2 = PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = fmod(var2.valor.Double, var1.valor.Double);
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}
void FU_dneg(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    
    var = PL_popOperando(&pFrame->operandStack);
    var.valor.Double = -var.valor.Double;
    PL_pushOperando(&pFrame->operandStack, var);
}
            
ST_tpVariable FU_dreturn(ST_tpStackFrame *pFrame){
    ST_tpVariable varReturn;
    
    varReturn = PL_popOperando(&pFrame->operandStack); // VERIFICAR SE *pVarReturn TEM * MESMO
    return varReturn;
} 

void FU_pushNull(ST_tpStackFrame *pFrame) {

    ST_tpVariable var;
    
    var.valor.obj_ref = 0,
    var.tipo = JREF;
    PL_pushOperando(&pFrame->operandStack, var);
}


                            
void FU_pushConstInt(ST_tpStackFrame *pFrame, int cte) {
    
    ST_tpVariable var;
    
    var.valor.Int = cte,
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_pushConstLong(ST_tpStackFrame *pFrame, int64_t cte) {

    ST_tpVariable var;
    
    var.valor.Long = cte,
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_pushConstFloat(ST_tpStackFrame *pFrame, float cte) {

    ST_tpVariable var;
    
    var.valor.Float = cte,
    var.tipo = JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);

}

void FU_pushConstDouble(ST_tpStackFrame *pFrame, double cte) {

    ST_tpVariable var;
    
    var.valor.Double = cte,
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}