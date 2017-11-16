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
                             *PL_popOperando(&pFrame->operandStack));
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
        PL_pushParametro(&pFrame->parameterStack, *PL_popOperando(&pFrame->operandStack));
        count --;
    }
    if(!strcmp((const char *)pMethodName, "<init>")){
        return 1; // Significa um erro
    }
    
    pVar1 = &pFrame->parameterStack->variable;
    pTempHeap = pVar1->valor.obj_ref;
    
    strcpy(nomeClasseTemp, pTempHeap->className);
    
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
void FU_putstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    
    ST_tpVariable *var1, *var2;
    ST_tpCp_info *pCPInfo;
    ST_tpConstantPool *cpIndx;
    u1 parametro1, parametro2;
    u2 temp2Byte, index1, index2;
    ST_tpCONSTANT_Fieldref_info *pFieldref;
    char *nomeClasse, *nomeField, *descritorField;
    
    //var.tipo = 0x99; // inicializa variavel com valor arbitrario
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
    
    var2 = (ST_tpVariable *)malloc(sizeof(ST_tpVariable));
    var1 = (ST_tpVariable *)malloc(sizeof(ST_tpVariable));

    memcpy((void*) var1, PL_popOperando(&pFrame->operandStack), sizeof(ST_tpVariable));

    if(var1->tipo == JBOOL || var1->tipo == JBYTE || var1->tipo == JSHORT){
        if(var1->tipo == JBOOL) var2->valor.Int = var1->valor.Boolean;
        if(var1->tipo == JBYTE) var2->valor.Int = var1->valor.Byte;
        if(var1->tipo == JCHAR) var2->valor.Int = var1->valor.Char;
        if(var1->tipo == JSHORT) var2->valor.Int = var1->valor.Short;
        var2->tipo = JINT;
    }
    VM_armazenarVariavelNoFieldDaClasse(pJVM, pFrame, nomeClasse, nomeField, descritorField, *var2);
    //VM_armazenarValorStaticField(pJVM, nomeClasse, nomeField, descritorField, var1);
}
void FU_ldc(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    int tipo, i;
    u1 parametro1;
    ST_tpVariable var, var1, var2;
    ST_tpConstantPool *cpIndx;
    ST_tpCONSTANT_Utf8_info *pUTF8;
    ST_tpCONSTANT_Float_info *pFloat;
    ST_tpCONSTANT_String_info *pString;
    ST_tpCONSTANT_Integer_info *pInteger;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    cpIndx = &(pFrame->cp->constant_pool_table[parametro1 - 1].info);
    
    if (cpIndx->Integer.tag == CONSTANT_Integer ) {
        pInteger = (ST_tpCONSTANT_Integer_info *) cpIndx;
        var1.tipo = JINT;
        memcpy((void *)&var1.valor.Int, (void *)&pInteger->bytes, 4);
        PL_pushOperando(&pFrame->operandStack, var1);
    }
    else if (cpIndx->Float.tag == CONSTANT_Float){
        pFloat = (ST_tpCONSTANT_Float_info *) cpIndx;
        var1.tipo = JFLOAT;
        memcpy((void *)&var1.valor.Float, (void *)&pFloat->bytes, 4);
        PL_pushOperando(&pFrame->operandStack, var1);
        
    }
    else if (cpIndx->String.tag == CONSTANT_String) {
        
        char *nomeClasse =  "java/lang/String";
        
        pString = (ST_tpCONSTANT_String_info *) cpIndx;

        if(pString->StringObject == NULL){

            pUTF8 = (ST_tpCONSTANT_Utf8_info *) &(pFrame->cp->constant_pool_table[pString->string_index-1].info);
        
            tipo = T_CHAR;
            var1.tipo = JAREF;
        
            var1.valor.array_ref = VM_criarArray(tipo, "", pUTF8->length);
        
            for(i = 0; i < pUTF8->length; i++){
                VM_armazenarValorArray(var1.valor.array_ref, i, var1);
            }
        
            var2.valor.obj_ref = VM_criarObjeto(pJVM, pFrame->cp);
            VM_armazenarValorField(pJVM, nomeClasse, "value", "[C", var1, var2);
        
            var.valor.Int = 0;
            VM_armazenarValorField(pJVM, nomeClasse, "offset", "I", var, var2);
        
            var.valor.Int = i;
            VM_armazenarValorField(pJVM, nomeClasse, "count", "I", var, var2);
        
            pString->StringObject = (ST_tpObjectHeap *) var2.valor.obj_ref;
        
        }
        else{
            tipo = JREF;
            var2.valor.obj_ref = pString->StringObject;
        }
        PL_pushOperando(&pFrame->operandStack, var2);
    }
}

void FU_ldc2_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    
    int i;
    u2 temp2Byte;
    ST_tpConstantPool *cpIndx;
    ST_tpCONSTANT_Utf8_info *pUTF8;
    ST_tpCONSTANT_Long_info *pLong;
    u1 parametro1, parametro2, tipo;
    ST_tpCONSTANT_Double_info *pDouble;
    ST_tpCONSTANT_String_info *pString;
    ST_tpVariable var, var1, var2;
    
    cpIndx = malloc(sizeof(ST_tpConstantPool));
    
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    cpIndx = &(pFrame->cp->constant_pool_table[temp2Byte - 1].info);

    if(cpIndx->Long.tag == CONSTANT_Long){
        pLong             = (ST_tpCONSTANT_Long_info *)cpIndx;
        var2.valor.Long = pLong->high_bytes;
        var1.valor.Long = (var2.valor.Long << 32) | pLong->low_bytes;
        var1.tipo = JLONG;
        PL_pushOperando(&pFrame->operandStack, var1);
    }
    
    else if (cpIndx->Double.tag == CONSTANT_Double){
        pDouble             = (ST_tpCONSTANT_Double_info *)cpIndx;
        u8 aux = (u8)pDouble->high_bytes;
        aux <<= 32;
        aux |= pDouble->low_bytes;
        memcpy(&var1.valor.Double, &aux, sizeof(int64_t));
        var1.tipo = JDOUBLE;
        PL_pushOperando(&pFrame->operandStack, var1);
    }
    
    else if (cpIndx->String.tag == CONSTANT_String){
        
        char nomeField[] = "value";
        char descriptorField[] = "[C";
        char nomeClasse[] =  "java/lang/String";
        
        pString = (ST_tpCONSTANT_String_info *) cpIndx;
        if(pString->StringObject == NULL){
            pUTF8 = (ST_tpCONSTANT_Utf8_info *) &(pFrame->cp->constant_pool_table[pString->string_index-1].info);
            
            tipo = T_CHAR;
            var1.tipo = JREF;
            var1.valor.array_ref = VM_criarArray(tipo, "", pUTF8->length);
            
            for(i = 0; i < pUTF8->length; i++){
                VM_armazenarValorArray(var1.valor.array_ref, i, var1);
            }
            
            var2.valor.obj_ref  = VM_criarObjeto(pJVM, pFrame->cp);
            
            VM_armazenarValorField(pJVM, nomeClasse, nomeField, descriptorField, var1, var2);
            
            var.valor.Int = 0;
            strcpy(nomeField, "offset");
            strcpy(descriptorField, "I");
            VM_armazenarValorField(pJVM, nomeClasse, nomeField, descriptorField, var, var2);
            
            var.valor.Int = i;
            strcpy(nomeField, "count");
            strcpy(descriptorField, "I");
            VM_armazenarValorField(pJVM, nomeClasse, nomeField, descriptorField, var, var2);
            
            
            pString->StringObject = (ST_tpObjectHeap *) var2.valor.obj_ref;
        }
        
        else{
            tipo = JREF;
            var2.valor.obj_ref = pString->StringObject;
        }
        PL_pushOperando(&pFrame->operandStack, var2);
    }
}

void FU_dload_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = VM_recuperarVariavel(pFrame->localVariables, posicao);
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dstore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);
    
}

void FU_dadd(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var1.valor.Double + var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dsub(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var2.valor.Double - var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dmul(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var1.valor.Double * var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ddiv(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = var2.valor.Double / var1.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}
void FU_drem(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Double = fmod(var2.valor.Double, var1.valor.Double);
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}
void FU_dneg(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.valor.Double = -var.valor.Double;
    PL_pushOperando(&pFrame->operandStack, var);
}
            
ST_tpVariable FU_dreturn(ST_tpStackFrame *pFrame){
    ST_tpVariable varReturn;
    
    varReturn = *PL_popOperando(&pFrame->operandStack); // VERIFICAR SE *pVarReturn TEM * MESMO
    return varReturn;
}

void FU_return(ST_tpStackFrame *pFrame){
    PL_esvaziarPilhaOperandos(&pFrame->operandStack);
}
void FU_bipush(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    
    (*pc)++;
    memcpy(&var.valor.Byte, *pc, 1);
    var.valor.Int = var.valor.Byte;
    var.tipo = JINT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}
