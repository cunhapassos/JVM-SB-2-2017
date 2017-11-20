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
#include <float.h>
#include "instrucoes.h"
#include "pilhas_listas.h"
#include <limits.h>

int FU_invokevirtual(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno){
    int count = 0;
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
        //char *nomeClasse = NULL, *nomeMetodo, *descritorMetodo;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte -1].info.Methodref.class_index;
    pNameAndTypeIndex     = pConstantPool[temp2Byte -1].info.Methodref.name_and_type_index;

    pClasseIndex          = pConstantPool[pClasseIndex - 1].info.Class.name_index;
    pClasseName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    pNomeMetodoIndex      = pConstantPool[pNameAndTypeIndex - 1].info.NameAndType.name_index;
    pDescritorMetodoIndex = pConstantPool[pNameAndTypeIndex - 1].info.NameAndType.descriptor_index;

    temp2Byte             = pNameAndTypeIndex;
    cpIndx                = &pConstantPool[pNomeMetodoIndex-1].info;
    nameTyperef           = (ST_tpCONSTANT_NameAndType_info *)malloc(sizeof(ST_tpCONSTANT_NameAndType_info));
    memcpy(nameTyperef, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_NameAndType_info));

    temp2Byte             = pNomeMetodoIndex;
    cpIndx                = &pConstantPool[temp2Byte-1].info;
    pMethodName           = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodName, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    temp2Byte             = pDescritorMetodoIndex;
    cpIndx                = &pConstantPool[temp2Byte-1].info;
    pMethodDescriptor     = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodDescriptor, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    count                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);
    count++;

    /* Retira todos os valores da pilha de operandos e passa para a pilha de parametros */
    while( count != 0 && pFrame->operandStack != NULL) {
        PL_pushParametro(&pFrame->parameterStack, *PL_popOperando(&pFrame->operandStack));
        count --;
    }
    if(!strcmp((const char *)pMethodName, "<init>")){
        return 1; // Significa um erro
    }

    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);

    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));

        if((pMetodoInfo->access_flags & ACC_ABSTRACT) == ACC_ABSTRACT){
            printf("\nERRO NA INSTRUCAO invokevirtual!\n");
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_STATIC) == ACC_STATIC){
            printf("\nERRO NA INSTRUCAO invokevirtual!\n");
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
                // EXECUTAR METODO NATIVO
            printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
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
int FU_invokespecial(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno){

    int count = 0;
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte -1].info.Methodref.class_index;
    pNameAndTypeIndex     = pConstantPool[temp2Byte -1].info.Methodref.name_and_type_index;

    pClasseIndex          = pConstantPool[pClasseIndex - 1].info.Class.name_index;
    pClasseName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    pNomeMetodoIndex      = pConstantPool[pNameAndTypeIndex - 1].info.NameAndType.name_index;
    pDescritorMetodoIndex = pConstantPool[pNameAndTypeIndex - 1].info.NameAndType.descriptor_index;

    temp2Byte             = pNameAndTypeIndex;
    cpIndx                = &pConstantPool[pNomeMetodoIndex-1].info;
    nameTyperef           = (ST_tpCONSTANT_NameAndType_info *)malloc(sizeof(ST_tpCONSTANT_NameAndType_info));
    memcpy(nameTyperef, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_NameAndType_info));
    
    temp2Byte             = pNomeMetodoIndex;
    cpIndx                = &pConstantPool[temp2Byte-1].info;
    pMethodName           = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodName, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));
    
    temp2Byte             = pDescritorMetodoIndex;
    cpIndx                = &pConstantPool[temp2Byte-1].info;
    pMethodDescriptor     = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodDescriptor, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));
    
    count                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);
    count++;
    
    /* Retira todos os valores da pilha de operandos e passa para a pilha de parametros */
    while( count != 0 && pFrame->operandStack != NULL) {
        PL_pushParametro(&pFrame->parameterStack, *PL_popOperando(&pFrame->operandStack));
        count --;
    }
    if(!strcmp((const char *)pMethodName, "<init>")){
        return 1; // Significa um erro
    }

    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);
    
    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));
        
        if((pMetodoInfo->access_flags & ACC_ABSTRACT) == ACC_ABSTRACT){
            printf("\nERRO NA INSTRUCAO invokespecial!\n");
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_STATIC) == ACC_STATIC){
            printf("\nERRO NA INSTRUCAO invokespecial!\n");
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
            // EXECUTAR METODO NATIVO
            printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
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

int FU_invokestatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc, ST_tpVariable **Retorno){
    int count = 0;
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte -1].info.Methodref.class_index;
    pNameAndTypeIndex     = pConstantPool[temp2Byte -1].info.Methodref.name_and_type_index;

    pClasseIndex          = pConstantPool[pClasseIndex - 1].info.Class.name_index;
    pClasseName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    pNomeMetodoIndex      = pConstantPool[pNameAndTypeIndex - 1].info.NameAndType.name_index;
    pDescritorMetodoIndex = pConstantPool[pNameAndTypeIndex - 1].info.NameAndType.descriptor_index;

    temp2Byte             = pNameAndTypeIndex;
    cpIndx                = &pConstantPool[pNomeMetodoIndex-1].info;
    nameTyperef           = (ST_tpCONSTANT_NameAndType_info *)malloc(sizeof(ST_tpCONSTANT_NameAndType_info));
    memcpy(nameTyperef, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_NameAndType_info));

    temp2Byte             = pNomeMetodoIndex;
    cpIndx                = &pConstantPool[temp2Byte-1].info;
    pMethodName           = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodName, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    temp2Byte             = pDescritorMetodoIndex;
    cpIndx                = &pConstantPool[temp2Byte-1].info;
    pMethodDescriptor     = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pMethodDescriptor, &(cpIndx->Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    count                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);
    count++;

    /* Retira todos os valores da pilha de operandos e passa para a pilha de parametros */
    while( count != 0 && pFrame->operandStack != NULL) {
        PL_pushParametro(&pFrame->parameterStack, *PL_popOperando(&pFrame->operandStack));
        count --;
    }

    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);

    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));

        if((pMetodoInfo->access_flags & ACC_STATIC) != ACC_STATIC){
            printf("\nERRO NA INSTRUCAO invokestatic!\n");
            return 1; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
                // EXECUTAR METODO NATIVO
            printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
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
        printf("ERRO NA INSTRUCAO invokestatic!");
        return 1; // ERRO
    }

    return 0;
}

int FU_retornaNumeroParametrosMetodo(ST_tpCONSTANT_Utf8_info *nome, ST_tpCONSTANT_Utf8_info *descricao){

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
    VM_armazenarValorStaticField(pJVM, nomeClasse, nomeField, descritorField, *var1);
    
}
void FU_sipush(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;
    
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var.tipo = JINT;
    var.valor.Int = (int)temp2Byte;
    PL_pushOperando(&pFrame->operandStack, var);
    
}
void FU_ldc(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **pc){
    int tipo, i;
    u1 parametro1;
    ST_tpVariable var, var1, var2;
    ST_tpObjectHeap *pObjeto;
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
                var.valor.Char = pUTF8->bytes[i];
                
                if ((var.valor.Char & 0xe0) == 0xe0) {
                    var.valor.Char = ((*(pUTF8->bytes) & 0xf) << 12) + ((*(pUTF8->bytes + 1) & 0x3f) << 6) + (*(pUTF8->bytes + 2) & 0x3f);
                    i += 2;
                }
                else if ((var.valor.Char & 0xc0) == 0xc0){
                    var.valor.Char = ((*(pUTF8->bytes) & 0x1f) << 12) + (*(pUTF8->bytes + 1) & 0x3f);
                }
                VM_armazenarValorArray(var1.valor.array_ref, i, var);
            }
        
            /* Verifica se objeto ja existe */
            pObjeto = PL_buscaObjetoHeap(pJVM->heap->objects, nomeClasse);
            if (pObjeto == NULL) {
                var2.valor.obj_ref = VM_alocarMemoriaHeapObjeto(pJVM, pFrame->cp);
            }
            else{
                var2.valor.obj_ref = pObjeto;
            }
            
            VM_armazenarValorField(pJVM, nomeClasse, "value", "[C", var1, var2);
        
           // var.valor.Int = 0;
           // VM_armazenarValorField(pJVM, nomeClasse, "offset", "I", var, var2);
        
           // var.valor.Int = i;
           // VM_armazenarValorField(pJVM, nomeClasse, "count", "I", var, var2);
        
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
    ST_tpObjectHeap *pObjeto;
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
            
            pObjeto  = VM_alocarMemoriaHeapObjeto(pJVM, pFrame->cp);
            if (pObjeto == NULL) {
                var2.valor.obj_ref = VM_alocarMemoriaHeapObjeto(pJVM, pFrame->cp);
            }
            else{
                var2.valor.obj_ref = pObjeto;
            }
            
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



void FU_return(ST_tpStackFrame *pFrame){
    //PL_esvaziarPilhaOperandos(&pFrame->operandStack);
}
void FU_bipush(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    
    (*pc)++;
    memcpy(&var.valor.Byte, *pc, 1);
    var.valor.Int = var.valor.Byte;
    var.tipo = JINT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_pushNull(ST_tpStackFrame *pFrame) {

    ST_tpVariable var;
    
    var.valor.obj_ref = 0;
    var.tipo = JREF;
    PL_pushOperando(&pFrame->operandStack, var);
}


                            
void FU_pushConstInt(ST_tpStackFrame *pFrame, int cte) {
    
    ST_tpVariable var;
    
    var.valor.Int = cte;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_pushConstLong(ST_tpStackFrame *pFrame, int64_t cte) {

    ST_tpVariable var;
    
    var.valor.Long = cte;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_pushConstFloat(ST_tpStackFrame *pFrame, float cte) {

    ST_tpVariable var;
    
    var.valor.Float = cte;
    var.tipo = JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);

}

void FU_pushConstDouble(ST_tpStackFrame *pFrame, double cte) {

    ST_tpVariable var;
    
    var.valor.Double = cte;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_iload(ST_tpStackFrame *pFrame, u1 **pc) {

    ST_tpVariable var;
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JINT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lload(ST_tpStackFrame *pFrame, u1 **pc) {

    ST_tpVariable var;
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JLONG;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fload(ST_tpStackFrame *pFrame, u1 **pc) {

    ST_tpVariable var;
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JFLOAT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}


void FU_dload(ST_tpStackFrame *pFrame, u1 **pc) {

    ST_tpVariable var;
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_aload(ST_tpStackFrame *pFrame, u1 **pc) {

    ST_tpVariable var;
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);

    var = VM_recuperarVariavel(pFrame->localVariables,  parametro1);
    
    var.tipo = JREF;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_iload_n(ST_tpStackFrame *pFrame, int index) {

    ST_tpVariable var;

    var = VM_recuperarVariavel(pFrame->localVariables,  index);
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lload_n(ST_tpStackFrame *pFrame, int index) {

    ST_tpVariable var;

    var = VM_recuperarVariavel(pFrame->localVariables,  index);
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}


void FU_fload_n(ST_tpStackFrame *pFrame, int index) {

    ST_tpVariable var;

    var = VM_recuperarVariavel(pFrame->localVariables,  index);
    var.tipo = JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dload_n(ST_tpStackFrame *pFrame, int index) {

    ST_tpVariable var;

    var = VM_recuperarVariavel(pFrame->localVariables,  index);
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_aload_n(ST_tpStackFrame *pFrame, int index) {

    ST_tpVariable var;

    var = VM_recuperarVariavel(pFrame->localVariables,  index);
    var.tipo = JREF;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_iaload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    val.tipo=JINT;
    
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_laload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    val.tipo=JLONG;
    
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_faload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    val.tipo=JFLOAT;
    
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_daload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    val.tipo=JDOUBLE;
    
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_aaload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    val.tipo=JAREF;
    
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_baload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    if (val.tipo==JBOOL){
        if(val.valor.Boolean<0)
            val.valor.Boolean=0-val.valor.Boolean;
        val.valor.Int=(int)val.valor.Boolean;}
    else{
        val.valor.Int=(int)val.valor.Byte;
    }

    val.tipo=JINT;
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_caload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    if (val.valor.Char<0)
        val.valor.Char=0-val.valor.Char;

    val.valor.Int=(int)val.valor.Char;
    val.tipo=JINT;
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_saload(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, val;
    var1   = *PL_popOperando(&pFrame->operandStack); // Index
    var2   = *PL_popOperando(&pFrame->operandStack); // Array reference

    val = VM_recuperarValorArray (var2.valor.array_ref , var1.valor.Int);
    val.valor.Int=(int)val.valor.Short;
    val.tipo=JINT;
    PL_pushOperando(&pFrame->operandStack, val);
}

void FU_istore(ST_tpStackFrame *pFrame, u1 **pc) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JINT;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_fstore(ST_tpStackFrame *pFrame, u1 **pc) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JFLOAT;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_lstore(ST_tpStackFrame *pFrame, u1 **pc) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JLONG;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_dstore(ST_tpStackFrame *pFrame, u1 **pc) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JDOUBLE;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_astore(ST_tpStackFrame *pFrame, u1 **pc) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JREF;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}

void FU_istore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);    
}

void FU_lstore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);
}

void FU_fstore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);
}

void FU_dstore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);
}

void FU_astore_n(ST_tpStackFrame *pFrame, int posicao){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    VM_armazenarVariavel(pFrame->localVariables, var, posicao);
}

void FU_iastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
        
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_lastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
        
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_fastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
        
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_dastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
        
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_aastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
        
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_bastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference

    if (var.valor.array_ref->type==JBOOL){
        var1.valor.Boolean=var1.valor.Int & 0x01;
    }
    else{
        var1.valor.Byte=var1.valor.Int & 0xff;
    }
        
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_castore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
        
    var1.valor.Int=0xffff & var1.valor.Char;    
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_sastore(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1   = *PL_popOperando(&pFrame->operandStack); // Val
    var2   = *PL_popOperando(&pFrame->operandStack); // Index
    var    = *PL_popOperando(&pFrame->operandStack); // Array reference
    
    var1.valor.Short=(short)var1.valor.Int;    
    VM_armazenarValorArray(var.valor.array_ref, var2.valor.Int, var1);
}

void FU_pop(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    var = *PL_popOperando(&pFrame->operandStack);
}

void FU_pop2(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    var = *PL_popOperando(&pFrame->operandStack);
    if (var.tipo!=JLONG && var.tipo!=JDOUBLE)
        var = *PL_popOperando(&pFrame->operandStack);
}

void FU_dup(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    var = *PL_popOperando(&pFrame->operandStack);
    PL_pushOperando(&pFrame->operandStack, var);
    PL_pushOperando(&pFrame->operandStack, var);

}

void FU_dup_x1(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    PL_pushOperando(&pFrame->operandStack, var1);
    PL_pushOperando(&pFrame->operandStack, var2);
    PL_pushOperando(&pFrame->operandStack, var1);
}

void FU_dup_x2(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    if (var2.tipo!=JLONG && var2.tipo!=JDOUBLE){
        ST_tpVariable var3=*PL_popOperando(&pFrame->operandStack);
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var3);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
    }
    else{
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
    }
}

void FU_dup2(ST_tpStackFrame *pFrame){
    ST_tpVariable var1; 
    var1 = *PL_popOperando(&pFrame->operandStack);
    if (var1.tipo!=JLONG && var1.tipo!=JDOUBLE){
        ST_tpVariable var2;
        var2 = *PL_popOperando(&pFrame->operandStack);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
    }
    else{
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var1);
    }
}

void FU_dup2_x1(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2; 
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    if (var1.tipo!=JLONG && var1.tipo!=JDOUBLE){
        ST_tpVariable var3;
        var3 = *PL_popOperando(&pFrame->operandStack);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var3);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
    }
    else{
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var2);    
        PL_pushOperando(&pFrame->operandStack, var1);
    }
}

void FU_dup2_x2(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2; 
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    if (var1.tipo!=JLONG && var1.tipo!=JDOUBLE && var2.tipo!=JLONG && var2.tipo!=JDOUBLE){
        ST_tpVariable var3;
        var3 = *PL_popOperando(&pFrame->operandStack);
        if (var3.tipo!=JLONG && var3.tipo!=JDOUBLE){
            ST_tpVariable var4 = *PL_popOperando(&pFrame->operandStack);    
            PL_pushOperando(&pFrame->operandStack, var2);
            PL_pushOperando(&pFrame->operandStack, var1);
            PL_pushOperando(&pFrame->operandStack, var4);
            PL_pushOperando(&pFrame->operandStack, var3);
            PL_pushOperando(&pFrame->operandStack, var2);
            PL_pushOperando(&pFrame->operandStack, var1);
        }
        else{
            PL_pushOperando(&pFrame->operandStack, var2);
            PL_pushOperando(&pFrame->operandStack, var1);
            PL_pushOperando(&pFrame->operandStack, var3);
            PL_pushOperando(&pFrame->operandStack, var2);
            PL_pushOperando(&pFrame->operandStack, var1);
        }}

    else if (var1.tipo==JLONG && var1.tipo==JDOUBLE){
        ST_tpVariable var3;
        var3 = *PL_popOperando(&pFrame->operandStack);
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var3);
        PL_pushOperando(&pFrame->operandStack, var2);
        PL_pushOperando(&pFrame->operandStack, var1);
    }        
    else{
        PL_pushOperando(&pFrame->operandStack, var1);
        PL_pushOperando(&pFrame->operandStack, var2);    
        PL_pushOperando(&pFrame->operandStack, var1);
    }
}

void FU_swap(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    PL_pushOperando(&pFrame->operandStack, var1);
    PL_pushOperando(&pFrame->operandStack, var2);
}

void FU_iadd(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Int = var1.valor.Int + var2.valor.Int;
    var.tipo=JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ladd(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Long = var1.valor.Long + var2.valor.Long;
    var.tipo=JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fadd(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var2, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Float = var1.valor.Float + var2.valor.Float;
    var.tipo=JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dadd(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Double = var1.valor.Double + var2.valor.Double;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_isub(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Int = var2.valor.Int - var1.valor.Int;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lsub(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Long = var2.valor.Long - var1.valor.Long;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fsub(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Float = var2.valor.Float - var1.valor.Float;
    var.tipo = JFLOAT;
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

void FU_imul(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Int = var1.valor.Int * var2.valor.Int;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lmul(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Long = var1.valor.Long * var2.valor.Long;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fmul(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Float = var1.valor.Float * var2.valor.Float;
    var.tipo = JFLOAT;
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

void FU_idiv(ST_tpStackFrame *pFrame){                                                        
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    if (var1.valor.Int==0){
        /* EXCESSÃO    ARITMÉTICA*/
    }
    else if (var2.valor.Int==INT_MIN && var1.valor.Int==-1){
        var.valor.Int=INT_MIN;
    }

    else{
        var.valor.Int=var2.valor.Int/var1.valor.Int;

    }
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ldiv(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
       if (var1.valor.Long==0){
        /* EXCESSÃO    ARITMÉTICA*/
    }
    else if (var2.valor.Long==LONG_MIN && var1.valor.Long==-1){
        var.valor.Long=LONG_MIN;
    }

    else{
        var.valor.Long=var2.valor.Long/var1.valor.Long;

    }
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fdiv(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Float = var2.valor.Float / var1.valor.Float;
    var.tipo = JFLOAT;
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

void FU_irem(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var1.valor.Int==0){
        /* EXCESSÃO    */
    }
    else if (var2.valor.Int==INT_MIN && var1.valor.Int==-1){
        var.valor.Int=0;
    }

    else{
        var.valor.Int=var2.valor.Int%var1.valor.Int;
    }
    var.tipo = JINT;

    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lrem(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    if (var1.valor.Long==0){
        /* EXCESSÃO    ARITMÉTICA*/
    }
    else if (var2.valor.Long==LONG_MIN && var1.valor.Long==-1){
        var.valor.Long=0;
    }

    else{
        var.valor.Long=var2.valor.Long%var1.valor.Long;

    }
    var.tipo = JLONG;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_frem(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    var.valor.Float = fmod(var2.valor.Double, var1.valor.Double);
    var.tipo = JFLOAT;
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

void FU_ineg(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.valor.Int = ~var.valor.Int+1;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lneg(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.valor.Long = ~var.valor.Long+1;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fneg(ST_tpStackFrame *pFrame){
    ST_tpVariable var;
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.valor.Float = -var.valor.Float;
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

void FU_lcmp(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var1.valor.Long == var2.valor.Long) {
        var.valor.Int = 0;
    }
    else if(var1.valor.Long > var2.valor.Long){
        var.valor.Int = -1;
    }
    else var.valor.Int = 1;

    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fcmpl(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (isnan(var1.valor.Float) || isnan(var2.valor.Float)) {
        var.valor.Int = -1;
    }
    else if(var1.valor.Float == var2.valor.Float){
        var.valor.Int = 0;
    }
    else if(var1.valor.Float > var2.valor.Float){
        var.valor.Int = -1;
    }
    else var.valor.Int = 1;

    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fcmpg(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (isnan(var1.valor.Float) || isnan(var2.valor.Float)) {
        var.valor.Int = 1;
    }
    else if(var1.valor.Float == var2.valor.Float){
        var.valor.Int = 0;
    }
    else if(var1.valor.Float > var2.valor.Float){
        var.valor.Int = -1;
    }
    else var.valor.Int = 1;

    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dcmpl(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (isnan(var1.valor.Double) || isnan(var2.valor.Double)) {
        var.valor.Int = -1;
    }
    else if(var1.valor.Double == var2.valor.Double){
        var.valor.Int = 0;
    }
    else if(var1.valor.Double > var2.valor.Double){
        var.valor.Int = -1;
    }
    else var.valor.Int = 1;

    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_dcmpg(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (isnan(var1.valor.Double) || isnan(var2.valor.Double)) {
        var.valor.Int = 1;
    }
    else if(var1.valor.Double == var2.valor.Double){
        var.valor.Int = 0;
    }
    else if(var1.valor.Double > var2.valor.Double){
        var.valor.Int = -1;
    }
    else var.valor.Int = 1;

    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ifeq(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int == 0) {
        *pc += (temp2Byte - 3);
    }
}

void FU_ifne(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int != 0) {
        *pc += (temp2Byte - 3);
    }
}

void FU_iflt(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int < 0) {
        *pc += (temp2Byte - 3);
    }
}

void FU_ifge(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int >= 0) {
        *pc += (temp2Byte - 3);
    }
}

void FU_ifgt(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int > 0) {
        *pc += (temp2Byte - 3);
    }
}

void FU_ifle(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int <= 0) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_icmpeq(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var1.valor.Int <= var2.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_icmpne(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var1.valor.Int != var2.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_icmplt(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int < var1.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_icmpge(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int >= var1.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_icmpgt(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int > var1.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_icmple(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int <= var1.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_if_acmpeq(ST_tpStackFrame *pFrame, u1 **pc){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    u2 temp2Byte;

    (*pc)++;
    memcpy(&parametro1, *pc, 1);
    (*pc)++;
    memcpy(&parametro2, *pc, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int == var1.valor.Int) {
        *pc += (temp2Byte - 3);
    }
}

void FU_i2l(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Long = (int64_t) var1.valor.Int;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_i2f(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Float = (float) var1.valor.Int;
    var.tipo = JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_i2d(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Double = (double) var1.valor.Int;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_l2i(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Int = (int) var1.valor.Long;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_l2f(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Float = (float) var1.valor.Long;
    var.tipo = JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_l2d(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Double = (double) var1.valor.Long;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_f2i(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    if (isnan(var1.valor.Float)) {
        var.valor.Int = 0;
    }
    else if (var1.valor.Float == -INFINITY) {
        var.valor.Int = INT_MIN;
    }
    else if (var1.valor.Float == INFINITY) {
        var.valor.Int = INT_MAX;
    }
    else {
        var.valor.Int = (int) var1.valor.Float;
    }
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_f2l(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    if (isnan(var1.valor.Float)) {
        var.valor.Long = 0;
    }
    else if (var1.valor.Float == -INFINITY) {
        var.valor.Long = LONG_MIN;
    }
    else if (var1.valor.Float == INFINITY) {
        var.valor.Long = LONG_MAX;
    }
    else {
        var.valor.Long = (int64_t) var1.valor.Float;
    }
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_f2d(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Double = (double) var1.valor.Float;
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_d2i(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    if (isnan(var1.valor.Double)) {
        var.valor.Int = 0;
    }
    else if (var1.valor.Double == -INFINITY) {
        var.valor.Int = INT_MIN;
    }
    else if (var1.valor.Double == INFINITY) {
        var.valor.Int = INT_MAX;
    }
    else {
        var.valor.Int = (int) var1.valor.Double;
    }
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_d2l(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    if (isnan(var1.valor.Double)) {
        var.valor.Long = 0;
    }
    else if (var1.valor.Double == -INFINITY) {
        var.valor.Long = LONG_MIN;
    }
    else if (var1.valor.Double == INFINITY) {
        var.valor.Long = LONG_MAX;
    }
    else {
        var.valor.Long = (int64_t) var1.valor.Double;
    }
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_d2f(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Float = (float) var1.valor.Double;
    var.tipo = JFLOAT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_i2b(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Byte = (char) var1.valor.Int;
    var1.valor.Int = (int) var.valor.Byte;
    var1.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var1);
}

void FU_i2c(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Char = (u2) var1.valor.Int;
    if (var.valor.Char < 0) {
        var.valor.Char = - var.valor.Char;
    }
    var1.valor.Int = (int) var.valor.Char;
    var1.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var1);
}

void FU_i2s(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Short = (short) var1.valor.Int;
    var1.valor.Int = (int) var.valor.Byte;
    var1.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var1);
}
