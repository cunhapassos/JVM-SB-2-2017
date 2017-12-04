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

void FU_printString(ST_tpVariable *var){
    if (var->valor.array_ref != NULL) {
        for (int i = 0 ; i < var->valor.array_ref->length; i++) {
            switch (var->valor.array_ref->type) {
                case T_BOOLEAN:
                    printf("%s", (*(int*)(var->valor.array_ref->area+sizeof(char)*i) == 0) ? "FALSE" :"TRUE");
                    break;
                case T_CHAR:
                    printf("%c", *(char*)(var->valor.array_ref->area+sizeof(u2)*i));
                    break;
                case T_FLOAT:
                    printf("%f", *(float*)(var->valor.array_ref->area+sizeof(float)*i));
                    break;
                case T_DOUBLE:
                    printf("%lf", *(double*)(var->valor.array_ref->area+sizeof(double)*i));
                    break;
                case T_BYTE:
                    printf("%02X", *(int*)(var->valor.array_ref->area+sizeof(char)*i));
                    break;
                case T_SHORT:
                    printf("%d", *(short*)(var->valor.array_ref->area+sizeof(short int)*i));
                    break;
                case T_INT:
                    printf("%d", *(int*)(var->valor.array_ref->area+sizeof(int)*i));
                    break;
                case T_LONG:
                    printf("%ld", *(long*)(var->valor.array_ref->area+sizeof(__int64_t)*i));
                    break;
                case T_REF:
                    printf("Nao implementado!");
                    
                    //FU_printArray((ST_tpVariable*)(var->valor.array_ref->area));
                    break;
                case T_AREF:
                    printf("Nao implementado!");
                    break;
            }
        }
    }
   
}
static void print(ST_tpVariable *var) {
    switch (var->tipo) {
        case JBOOL:
            printf("%s \n", (var->valor.Boolean == 0) ? "FALSE" :"TRUE");
            break;
        case JBYTE:
            printf("%02X \n", var->valor.Byte);
            break;
        case JCHAR:
            printf("%c \n", var->valor.Char);
            break;
        case JSTRING:
                //printf("%s \n", var->valor.);
            break;
        case JSHORT:
            printf("%d \n", var->valor.Short);
            break;
        case JVOID:
            break;
        case JREF:
            if(!strcmp(var->valor.obj_ref->className, "java/lang/String")) {
                FU_printString(var->valor.obj_ref->field_area);
                printf("\n");
            }
            break;
        case JAREF:
            if(!strcmp(var->valor.obj_ref->className, "java/lang/String")) {
                FU_printString(var->valor.obj_ref->field_area);
                printf("\n");
            }
            break;
        case JINT:
            printf("%d \n", var->valor.Int);
            break;
        case JLONG:
            printf("%lld \n", (long long int)var->valor.Long);
            break;
        case JFLOAT:
            printf("%f \n", var->valor.Float);
            break;
        case JDOUBLE:
            printf("%lf \n", var->valor.Double);
            break;
        default:
            break;
    }
}

int FU_invokevirtual(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC, ST_tpVariable **Retorno){
    int count = 0;
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    ST_tpParameterStack *novaPilhaParametros = NULL;
        //char *nomeClasse = NULL, *nomeMetodo, *descritorMetodo;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;
    ST_tpVariable *var;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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

    ////printf(" %s %s\n", pMethodName->bytes, pMethodDescriptor->bytes);

    count                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);

    if(!strcmp((const char *)pMethodName->bytes, "<init>")){
    	printf("Erro metodo é init");
        return 2; // Significa um erro
    }

    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);
    
    if (pClassFile == NULL) {
        pClassFile = VM_carregarClasse((char *) pClasseName->bytes, pJVM);
    }
    
    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));

        if((pMetodoInfo->access_flags & ACC_ABSTRACT) == ACC_ABSTRACT){
            printf("\nERRO NA INSTRUCAO invokevirtual!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_STATIC) == ACC_STATIC){
            printf("\nERRO NA INSTRUCAO invokevirtual!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
                // EXECUTAR METODO NATIVO
            //printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
        }
        else{
            /* Retira valores da pilha de operandos e passa para a pilha de parametros */
            
            while( count != 0 && pFrame->operandStack != NULL) {
                PL_pushParametro(&novaPilhaParametros, *PL_popOperando(&pFrame->operandStack));
                count --;
            }
            if(strcmp((char *) (pMethodName->bytes), "println" ) == 0){
            	if((char)(pMethodDescriptor->bytes[1]) == ')'){
            		printf("\n");
            	} else {
            		var = PL_popParametro(&novaPilhaParametros);
            		print(var);
            	}
            }else{
                count++;
                while( count != 0 && pFrame->operandStack != NULL) {
                    PL_pushParametro(&novaPilhaParametros, *PL_popOperando(&pFrame->operandStack));
                    count --;
                }
                *Retorno = VM_executarMetodo(pJVM, pClassFile, novaPilhaParametros, pMetodoInfo);
            }
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
        return 2; // ERRO
    }

    return 0;
}

int FU_invokespecial(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC, ST_tpVariable **Retorno){

    int count = 0;
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    ST_tpParameterStack *novaPilhaParametros = NULL;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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
    
    ////printf(" %s %s\n", pMethodName->bytes, pMethodDescriptor->bytes);

    count                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);

    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);
    
    if (pClassFile == NULL) {
        pClassFile = VM_carregarClasse((char *) pClasseName->bytes, pJVM);
    }
    
    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));
        
        if((pMetodoInfo->access_flags & ACC_ABSTRACT) == ACC_ABSTRACT){
            printf("\nERRO NA INSTRUCAO invokespecial!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_STATIC) == ACC_STATIC){
            printf("\nERRO NA INSTRUCAO invokespecial!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
            // EXECUTAR METODO NATIVO
            //printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
        }
        else{
            /* Retira todos os valores da pilha de operandos e passa para a pilha de parametros */
            count++;
            while( count != 0 && pFrame->operandStack != NULL) {
                PL_pushParametro(&novaPilhaParametros, *PL_popOperando(&pFrame->operandStack));
                count --;
            }
            *Retorno = VM_executarMetodo(pJVM, pClassFile, novaPilhaParametros, pMetodoInfo);
            /*while (pFrame->parameterStack != NULL) {
                PL_pushOperando(&pFrame->operandStack, *PL_popParametro(&pFrame->parameterStack));
            }*/
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
        return 2; // ERRO
    }
    
    return 0;
}

int FU_invokestatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC, ST_tpVariable **Retorno){
    int count = 0;
    
    u1 parametro1, parametro2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpVariable *varTemp = NULL;
    ST_tpParameterStack *novaPilhaParametros = NULL;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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

    //printf(" %s %s\n", pMethodName->bytes, pMethodDescriptor->bytes);

    count                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);

    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);
    
    if (pClassFile == NULL) {
        pClassFile = VM_carregarClasse((char *) pClasseName->bytes, pJVM);
    }

    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));

        if((pMetodoInfo->access_flags & ACC_STATIC) != ACC_STATIC){
            printf("\nERRO NA INSTRUCAO invokestatic!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
            //printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
        }
        else{
            /* Retira todos os valores da pilha de operandos e passa para a pilha de parametros */
            while( count != 0 && pFrame->operandStack != NULL) {
                varTemp =  PL_popOperando(&pFrame->operandStack);
                PL_pushParametro(&novaPilhaParametros, *varTemp);
                count --;
            }
            
            *Retorno = VM_executarMetodo(pJVM, pClassFile, novaPilhaParametros, pMetodoInfo);
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
        return 2; // ERRO
    }

    return 0;
}

int FU_invokeinterface(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC, ST_tpVariable **Retorno){

    int aux = 0;
    u1 parametro1, parametro2, contador, byteExtra;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpMethod_info *pMetodoInfo;
    ST_tpCONSTANT_NameAndType_info *nameTyperef;
    ST_tpParameterStack *novaPilhaParametros = NULL;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL, *pMethodName, *pMethodDescriptor;
    u2 temp2Byte, pClasseIndex, pNameAndTypeIndex,pNomeMetodoIndex, pDescritorMetodoIndex;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    (*PC)++;
    memcpy(&contador, *PC, 1);
    (*PC)++;
    memcpy(&byteExtra, *PC, 1);
    
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
    
    //printf(" %s %s\n", pMethodName->bytes, pMethodDescriptor->bytes);

    aux                 = FU_retornaNumeroParametrosMetodo(pMethodName, pMethodDescriptor);
    
    if(!strcmp((const char *)pMethodName->bytes, "<init>")){
        return 1; // Significa um erro, goto saidaDoMetodo
    }
    
    pClassFile = PL_buscarClasse(pJVM, (char *) pClasseName->bytes);
    
    if (pClassFile == NULL) {
        pClassFile = VM_carregarClasse((char *) pClasseName->bytes, pJVM);
    }
    
    if(pClassFile != NULL){
        pMetodoInfo = VM_procurarMetodo(pClassFile, (char *) (pMethodDescriptor->bytes) , (char *) (pMethodName->bytes));
        
        if((pMetodoInfo->access_flags & ACC_ABSTRACT) == ACC_ABSTRACT){
            printf("\nERRO NA INSTRUCAO invokespecial!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_PUBLIC) != ACC_PUBLIC){
            printf("\nERRO NA INSTRUCAO invokespecial!\n");
            return 2; // ERRO
        }
        if((pMetodoInfo->access_flags & ACC_NATIVE) == ACC_NATIVE){
            // EXECUTAR METODO NATIVO
            //printf("\nWARNING! AQUI DEVERIA EXECUTAR UM METODO NATIVO!\n");
        }
        else{
            /* Retira todos os valores da pilha de operandos e passa para a pilha de parametros */
            while( aux != 0 && pFrame->operandStack != NULL) {
                PL_pushParametro(&novaPilhaParametros, *PL_popOperando(&pFrame->operandStack));
                aux --;
            }
            *Retorno = VM_executarMetodo(pJVM, pClassFile, novaPilhaParametros, pMetodoInfo);
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
        return 2; // ERRO
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

void FU_new(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    u1 parametro1, parametro2;
    u2 temp2Byte, pClasseIndex;
    ST_tpClassFile *pClassFile;
    ST_tpVariable *var;
    ST_tpCp_info *pConstantPool;
    ST_tpObjectHeap *pObjectHeap;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL;

    pClasseIndex = 1; // Inicializacao de variavel
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte -1].info.Class.name_index;
    
    pClasseName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));
    
    pClassFile = PL_buscarClasse(pJVM, (char *)pClasseName->bytes);
    if (pClassFile == NULL) {
        pClassFile = VM_carregarClasse((char *)pClasseName->bytes, pJVM);
    }
    pObjectHeap = VM_alocarMemoriaHeapObjeto(pJVM, pClassFile);
    
    var = (ST_tpVariable *)malloc(sizeof(ST_tpVariable));
    var->valor.obj_ref = pObjectHeap;
    var->tipo = JREF;
    
    PL_pushOperando(&pFrame->operandStack, *var);
    
}

void FU_newarray(ST_tpStackFrame *pFrame, u1 **PC){
    u1 parametro1;
    ST_tpVariable *var;
    ST_tpArrayHeap *pArray;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    var = PL_popOperando(&pFrame->operandStack);
    pArray = VM_criarArray(parametro1, "", var->valor.Int);
    var->valor.array_ref = pArray;
    
    PL_pushOperando(&pFrame->operandStack, *var);
    
}

void FU_anewarray(ST_tpStackFrame *pFrame, u1 **PC){
    
    ST_tpVariable *var;
    ST_tpArrayHeap *pArray;
    u1 parametro1, parametro2;
    u2 temp2Byte, pClasseIndex;
    ST_tpCp_info *pConstantPool;
    ST_tpCONSTANT_Utf8_info *pClasseName = NULL;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte - 1].info.Class.name_index;
    pClasseName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));
    
    var = PL_popOperando(&pFrame->operandStack);
    
    parametro1 = T_REF;
    pArray = VM_criarArray(parametro1, (char *)pClasseName->bytes, var->valor.Int);
    
    var->tipo = JAREF;
    var->valor.array_ref = pArray;
    
    PL_pushOperando(&pFrame->operandStack, *var);
    
}

void FU_arraylenght(ST_tpStackFrame *pFrame) {
    ST_tpVariable array_ref, size;
    
    array_ref = *PL_popOperando(&pFrame->operandStack);
    
    if (array_ref.tipo == JAREF) {
        if (array_ref.valor.array_ref == NULL) {
            //TODO lançar NullPointerException
        }
        else {
            size.valor.Int = array_ref.valor.array_ref->length;
            size.tipo = JINT;
            PL_pushOperando(&pFrame->operandStack, size);
        }
    }
}

void FU_athrow(ST_tpException_table *pExceptionTable, ST_tpClassFile *pClassFile ,ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable *var;
    
    var = PL_popOperando(&pFrame->operandStack);
    VM_executarThrow(pExceptionTable, pClassFile, *var,  PC, pFrame->operandStack);
}

void FU_checkcast(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    int flag = 0;
    char *nomeClasse;
    ST_tpVariable *var;
    u1 parametro1, parametro2;
    u2 temp2Byte, pClasseIndex;
    ST_tpClassFile *pClassFile;
    ST_tpCp_info *pConstantPool;
    ST_tpCONSTANT_Utf8_info *pClasseName1 = NULL;
    
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var = PL_popOperando(&pFrame->operandStack);
    
    if ((var->valor.obj_ref == 0)  && (var->tipo != JREF)) {
        PL_pushOperando(&pFrame->operandStack, *var);
    }
    else if ((var->valor.obj_ref == 0)  && (var->tipo != JAREF)){
        PL_pushOperando(&pFrame->operandStack, *var);
    }
    
    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte - 1].info.Class.name_index;
    pClasseName1 = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName1, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));
    
    if (var->tipo == JAREF) {
        if (!strcmp((char *) pClasseName1->bytes, "java/lang/object")) {
            flag = 1;
        }
    }
    else{
        nomeClasse = (char *)malloc(sizeof(char *) * strlen(var->valor.obj_ref->className));
        // Verificar se essa forma de fazer o malloc está certa
        strcpy(nomeClasse, var->valor.obj_ref->className);
        if (!strcmp((char *) pClasseName1->bytes, nomeClasse)) {
            flag = 1;
        }
        else{
            flag = 0;
            while (TRUE) {
                pClassFile = PL_buscarClasse(pJVM, nomeClasse);
                if (pClassFile == NULL) {
                    pClassFile = VM_carregarClasse(nomeClasse, pJVM);
                }
                if (pClassFile->super_class == 0) {
                    flag = 0;
                    break;
                }
                free(nomeClasse);
                nomeClasse = (char *)malloc(sizeof(char *) * strlen(pClassFile->nomeSuperClasse)); // Verificar se essa forma de fazer o malloc está certa
                strcpy(nomeClasse, pClassFile->nomeSuperClasse);
                if (!strcmp(nomeClasse, (char *) pClasseName1->bytes)){
                    flag = 1;
                    break;
                }
                flag = 0;
            }
        }
    }
    if (flag == 0) {
        // Exceção
    }
    else{
        PL_pushOperando(&pFrame->operandStack, *var);
    }
}

void FU_instanceof(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    int flag = 1;
    char *nomeClasse;
    ST_tpVariable *var, *var1;
    u1 parametro1, parametro2;
    u2 temp2Byte, pClasseIndex;
    ST_tpCp_info *pConstantPool;
    ST_tpCONSTANT_Utf8_info *pClasseName1 = NULL;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var = PL_popOperando(&pFrame->operandStack);
    
    if ((var->valor.obj_ref == 0)  && (var->tipo != JREF)) {
        flag = 0;
        var->tipo = JINT;
        PL_pushOperando(&pFrame->operandStack, *var);
    }
    else if ((var->valor.obj_ref == 0)  && (var->tipo != JAREF)){
        flag = 0;
        var->tipo = JINT;
        PL_pushOperando(&pFrame->operandStack, *var);
    }
    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseIndex          = pConstantPool[temp2Byte - 1].info.Class.name_index;
    pClasseName1 = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName1, &(pConstantPool[pClasseIndex - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));
    
    if (var->tipo == JREF) {
        nomeClasse = (char *)malloc(sizeof(char *) * strlen(var->valor.obj_ref->className));
        strcpy(nomeClasse, var->valor.obj_ref->className);
        // chamar funcao nao implementada
        //flag = VM_buscarInstanciaDeClasse((char *)pClasseName1->bytes, nomeClasse);
    }
    else{
        //flag = VM_buscarInstanciaDeArray((char *)pClasseName1->bytes, var);
    }
    var1 = (ST_tpVariable*) malloc(sizeof(ST_tpVariable));
    var1->tipo = JINT;
    var1->valor.Int = flag;
    PL_pushOperando(&pFrame->operandStack, *var1);
    
}

void FU_monitorenter(ST_tpStackFrame *pFrame){
    ST_tpVariable *var;
    
    var = PL_popOperando(&pFrame->operandStack);
    if (var->valor.obj_ref != 0) {
        //
    }
}

void FU_monitorexit(ST_tpStackFrame *pFrame){
    ST_tpVariable *var;
    
    var = PL_popOperando(&pFrame->operandStack);
    
    if (var->valor.obj_ref != 0) {
        //
    }
    
}

void FU_wide(ST_tpStackFrame *pFrame, u1 **PC){
    u1 parametro1, parametro2, parametro3, parametro4, parametro5;
    u2 temp2Byte;
    ST_tpVariable var, *var1 = NULL;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    switch (parametro1) {
        case 0x84:
            memcpy(&parametro2, (*PC)++, 1);
            memcpy(&parametro3, (*PC)++, 1);
            memcpy(&parametro4, (*PC)++, 1);
            memcpy(&parametro5, (*PC)++, 1);
            temp2Byte = parametro2 << 8 | parametro3;
            var = VM_recuperarVariavel(pFrame->localVariables, temp2Byte);
            var1->valor.Short = parametro4;
            var1->valor.Int = var1->valor.Short;
            var.valor.Int += var1->valor.Int;
            
            VM_armazenarVariavel(pFrame->localVariables, *var1, temp2Byte);
            break;
        case 0x19: //aload
        case 0x15://iload:
        case 0x16://lload;
        case 0x17://fload:
        case 0x18://dload:
            memcpy(&parametro2, (*PC)++, 1);
            memcpy(&parametro3, (*PC)++, 1);
            temp2Byte = parametro2 << 8 | parametro3;
            var = VM_recuperarVariavel(pFrame->localVariables, temp2Byte);
            PL_pushOperando(&pFrame->operandStack, var);
            break;
        case 0x3a://astore:
        case 0x36://istore:
        case 0x37://lstore:
        case 0x38://fstore:
        case 0x39://dstore:
            memcpy(&parametro2, (*PC)++, 1);
            memcpy(&parametro3, (*PC)++, 1);
            temp2Byte = parametro2 << 8 | parametro3;
            var = VM_recuperarVariavel(pFrame->localVariables, temp2Byte);
            PL_pushOperando(&pFrame->operandStack, var);
    }
}
void FU_multianewarray(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable *var, *var1 = NULL;
    u1 parametro1, parametro2, parametro3;
    ST_tpCp_info *pConstantPool;
    u4 *pClasseNameIndex;
    int16_t temp2Byte;
    ST_tpCONSTANT_Utf8_info* pClasseName;
    char *tem_ptr;
    
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    pConstantPool         = pFrame->cp->constant_pool_table;
    pClasseNameIndex          = &pConstantPool[temp2Byte -1].info.Class.name_index;
    
    pClasseName = (ST_tpCONSTANT_Utf8_info *)malloc(sizeof(ST_tpCONSTANT_Utf8_info));
    memcpy(pClasseName, &(pConstantPool[(int)(*pClasseNameIndex) - 1].info.Utf8), sizeof(ST_tpCONSTANT_Utf8_info));

    tem_ptr = strchr((char *)pClasseName->bytes, '[');
    tem_ptr++;

    (*PC)++;
    memcpy(&parametro3, *PC, 1);
    
    var1 = (ST_tpVariable*)malloc(sizeof(ST_tpVariable));
    var1->valor.array_ref = alocarMemoriaArrayMulti(tem_ptr, pFrame->operandStack, (int)parametro3);
    
    var1->tipo = JAREF;
    
    PL_pushOperando(&pFrame->operandStack, *var1);
}


void FU_ifnull(ST_tpStackFrame *pFrame, u1 **PC){

    ST_tpVariable *var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;


    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var = PL_popOperando(&pFrame->operandStack);
    
    if (var->valor.obj_ref == 0) {
        (*PC) += (temp2Byte - 3);
    }
}

void FU_ifnonnull(ST_tpStackFrame *pFrame, u1 **PC){
    
    ST_tpVariable *var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var = PL_popOperando(&pFrame->operandStack);
    
    if (var->valor.obj_ref == 0) {
        (*PC) += (temp2Byte - 3);
    }
}

void FU_goto_w(u1 **PC){

    u1 parametro1, parametro2, parametro3, parametro4;
    int32_t temp4Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    (*PC)++;
    memcpy(&parametro3, *PC, 1);
    (*PC)++;
    memcpy(&parametro4, *PC, 1);
    
    temp4Byte = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;
    (*PC) += (temp4Byte - 5);
}

void FU_jsr_w(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable *var = NULL;
    u1 parametro1, parametro2, parametro3, parametro4;
    int32_t temp4Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    (*PC)++;
    memcpy(&parametro3, *PC, 1);
    (*PC)++;
    memcpy(&parametro4, *PC, 1);
    
    temp4Byte = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;
    
    var->valor.retAddres = *((*PC));
    var->tipo = JRETADDRESS;
    
    PL_pushOperando(&pFrame->operandStack, *var);
    (*PC) += (temp4Byte - 5);
}

void FU_sipush(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var.tipo = JINT;
    var.valor.Int = (int)temp2Byte;
    PL_pushOperando(&pFrame->operandStack, var);
    
}
void FU_ldc(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    int tipo, i;
    u1 parametro1;
    ST_tpVariable var, var1, var2;
    ST_tpConstantPool *cpIndx;
    ST_tpClassFile *pClassFile;
    ST_tpCONSTANT_Utf8_info *pUTF8;
    ST_tpCONSTANT_Float_info *pFloat;
    ST_tpCONSTANT_String_info *pString;
    ST_tpCONSTANT_Integer_info *pInteger;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
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
            
            var2.tipo = JREF;
            /* Verifica se objeto ja existe */
            //pObjeto = PL_buscaObjetoHeap(pJVM->heap->objects, nomeClasse);
            //if (pObjeto == NULL) {
                pClassFile = VM_carregarClasse(nomeClasse, pJVM);
                var2.valor.obj_ref = VM_alocarMemoriaHeapObjeto(pJVM, pClassFile);
            //}
            //else{
            //    var2.valor.obj_ref = pObjeto;
            //}
            
            VM_armazenarValorField(pJVM, nomeClasse, "value", "[C", var1, var2);
        
            //var.valor.Int = 0;
            //VM_armazenarValorField(pJVM, nomeClasse, "offset", "I", var, var2);
        
            //var.valor.Int = i;
            //VM_armazenarValorField(pJVM, nomeClasse, "count", "I", var, var2);
        
            pString->StringObject = (ST_tpObjectHeap *) var2.valor.obj_ref;
        
        }
        else{
            var2.tipo = JREF;
            var2.valor.obj_ref = pString->StringObject;
        }
        PL_pushOperando(&pFrame->operandStack, var2);
    }
}

void FU_ldc_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    int tipo, i;
    u2 temp2Byte;
    ST_tpClassFile *pClassFile;
    u1 parametro1, parametro2;
    ST_tpVariable var, var1, var2;
    ST_tpConstantPool *cpIndx;
    ST_tpCONSTANT_Utf8_info *pUTF8;
    ST_tpCONSTANT_Float_info *pFloat;
    ST_tpCONSTANT_String_info *pString;
    ST_tpCONSTANT_Integer_info *pInteger;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    cpIndx = &(pFrame->cp->constant_pool_table[temp2Byte - 1].info);
    
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
            //pObjeto = PL_buscaObjetoHeap(pJVM->heap->objects, nomeClasse);
            //if (pObjeto == NULL) {
            	pClassFile = VM_carregarClasse(nomeClasse, pJVM);
            	var2.valor.obj_ref = VM_alocarMemoriaHeapObjeto(pJVM, pClassFile);
            //}
            //else{
            //    var2.valor.obj_ref = pObjeto;
            //}
            
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


void FU_ldc2_w(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    
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
    ST_tpClassFile *pClassFile;
    
    cpIndx = malloc(sizeof(ST_tpConstantPool));
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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
            	pClassFile = VM_carregarClasse(nomeClasse, pJVM);
            	var2.valor.obj_ref = VM_alocarMemoriaHeapObjeto(pJVM, pClassFile);
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



int FU_return(ST_tpStackFrame *pFrame){
    return 1;
}
void FU_bipush(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    
    (*PC)++;
    memcpy(&var.valor.Byte, *PC, 1);
    var.valor.Int = var.valor.Byte;
    var.tipo = JINT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_pushNull(ST_tpStackFrame *pFrame) {

    ST_tpVariable *var = (ST_tpVariable*) malloc(sizeof(ST_tpVariable));
    
    var->valor.obj_ref = 0;
    var->tipo = JREF;
    PL_pushOperando(&pFrame->operandStack, *var);
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

void FU_iload(ST_tpStackFrame *pFrame, u1 **PC) {

    ST_tpVariable var;
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JINT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lload(ST_tpStackFrame *pFrame, u1 **PC) {

    ST_tpVariable var;
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JLONG;
    
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_fload(ST_tpStackFrame *pFrame, u1 **PC) {

    ST_tpVariable var;
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JFLOAT;
    
    PL_pushOperando(&pFrame->operandStack, var);
}


void FU_dload(ST_tpStackFrame *pFrame, u1 **PC) {

    ST_tpVariable var;
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);

    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    var.tipo = JDOUBLE;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_aload(ST_tpStackFrame *pFrame, u1 **PC) {

    ST_tpVariable var;
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);

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
    //print(&val);
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

    val.valor.Int=(char)val.valor.Char;
    val.tipo=JCHAR;
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

void FU_istore(ST_tpStackFrame *pFrame, u1 **PC) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JINT;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_fstore(ST_tpStackFrame *pFrame, u1 **PC) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JFLOAT;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_lstore(ST_tpStackFrame *pFrame, u1 **PC) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JLONG;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_dstore(ST_tpStackFrame *pFrame, u1 **PC) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    var = *PL_popOperando(&pFrame->operandStack);
    var.tipo = JDOUBLE;
    VM_armazenarVariavel(pFrame->localVariables, var, parametro1);
    
}


void FU_astore(ST_tpStackFrame *pFrame, u1 **PC) {
    ST_tpVariable var;
    
    u1 parametro1;
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
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

void FU_ifeq(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int == 0) {
        *PC += (temp2Byte - 3);
    }
}

void FU_ifne(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int != 0) {
        *PC += (temp2Byte - 3);
    }
}

void FU_iflt(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int < 0) {
        *PC += (temp2Byte - 3);
    }
}

void FU_ifge(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int >= 0) {
        *PC += (temp2Byte - 3);
    }
}

void FU_ifgt(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int > 0) {
        *PC += (temp2Byte - 3);
    }
}

void FU_ifle(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var = *PL_popOperando(&pFrame->operandStack);

    if (var.valor.Int <= 0) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_icmpeq(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var1.valor.Int <= var2.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_icmpne(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var1.valor.Int != var2.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_icmplt(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int < var1.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_icmpge(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int >= var1.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_icmpgt(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int > var1.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_icmple(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int <= var1.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_acmpeq(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    if (var2.valor.Int == var1.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_if_acmpne(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var1, var2;
    u1 parametro1, parametro2;
    int16_t temp2Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    
    if (var2.valor.Int != var1.valor.Int) {
        *PC += (temp2Byte - 3);
    }
}

void FU_goto(ST_tpStackFrame *pFrame, u1 **PC){

    u1 parametro1, parametro2;
    int16_t temp2Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    (*PC) += (temp2Byte - 3);
}

void FU_jsr(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int16_t temp2Byte;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    temp2Byte = (parametro1 << 8) + parametro2;
    
    var.valor.retAddres = *((*PC));
    var.tipo = JRETADDRESS;
    
    PL_pushOperando(&pFrame->operandStack, var);
    *PC += (temp2Byte - 3);
}

void FU_ret(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    
    var = VM_recuperarVariavel(pFrame->localVariables, parametro1);
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
    var1.tipo = JBYTE;
    PL_pushOperando(&pFrame->operandStack, var1);
}

void FU_i2c(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Char = (u2) var1.valor.Int;
    if (var.valor.Char < 0) {
        var.valor.Char = 0 - var.valor.Char;
    }
    var.tipo = JCHAR;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_i2s(ST_tpStackFrame *pFrame){
    ST_tpVariable var1, var;
    var1 = *PL_popOperando(&pFrame->operandStack);
    var.valor.Short = (short) var1.valor.Int;
    
    var.tipo = JSHORT;
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

void FU_tableswitch(ST_tpStackFrame *pFrame, u1 **PC){
    u1 **tempPC = NULL, aux, parametro1, parametro2, parametro3, parametro4;
    int32_t valorDefalt, valorLow, valorHigh;
    ST_tpVariable var1, var2, var3;

    tempPC = PC;
    var1 = *PL_popOperando(&pFrame->operandStack);

    aux = 4 - (*(*PC) % 4);
    if (aux == 4) {
        aux = 0;
    }
    PC += aux;

    memcpy(&parametro1, (*PC)++, 1);
    memcpy(&parametro2, (*PC)++, 1);
    memcpy(&parametro3, (*PC)++, 1);
    memcpy(&parametro4, (*PC)++, 1);
    valorDefalt = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

    memcpy(&parametro1, (*PC)++, 1);
    memcpy(&parametro2, (*PC)++, 1);
    memcpy(&parametro3, (*PC)++, 1);
    memcpy(&parametro4, (*PC)++, 1);
    valorLow = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

    memcpy(&parametro1, (*PC)++, 1);
    memcpy(&parametro2, (*PC)++, 1);
    memcpy(&parametro3, (*PC)++, 1);
    memcpy(&parametro4, (*PC)++, 1);
    valorHigh = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

    if (var1.valor.Int > valorHigh || var1.valor.Int  < valorLow) {
        tempPC += (valorDefalt - 1);
        PC = tempPC;
    }
    else{
        var2.valor.Int = var1.valor.Int - valorLow;
        var3.valor.Int = var2.valor.Int * 4;
        PC += var3.valor.Int;
        memcpy(&parametro1, (*PC)++, 1);
        memcpy(&parametro2, (*PC)++, 1);
        memcpy(&parametro3, (*PC)++, 1);
        memcpy(&parametro4, (*PC)++, 1);

        var3.valor.Int = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;
        tempPC += (var3.valor.Int - 1);
        PC = tempPC;
    }
}

void FU_lookupswitch(ST_tpStackFrame *pFrame, u1 **PC){
    u1 **tempPC, aux, parametro1, parametro2, parametro3, parametro4;
    u4 valorDefalt, npairs, match, offset;
    ST_tpVariable var1;
    int controle;

    tempPC = PC;
    var1 = *PL_popOperando(&pFrame->operandStack);

    aux = 4 - (*(*PC) % 4);
    if (aux == 4) {
        aux = 0;
    }
    PC += aux;

    memcpy(&parametro1, (*PC)++, 1);
    memcpy(&parametro2, (*PC)++, 1);
    memcpy(&parametro3, (*PC)++, 1);
    memcpy(&parametro4, (*PC)++, 1);
    valorDefalt = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

    memcpy(&parametro1, (*PC)++, 1);
    memcpy(&parametro2, (*PC)++, 1);
    memcpy(&parametro3, (*PC)++, 1);
    memcpy(&parametro4, (*PC)++, 1);
    npairs = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

    controle = 0;
    for (int i = 0; i < npairs; i++) {
        memcpy(&parametro1, (*PC)++, 1);
        memcpy(&parametro2, (*PC)++, 1);
        memcpy(&parametro3, (*PC)++, 1);
        memcpy(&parametro4, (*PC)++, 1);
        match = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

        memcpy(&parametro1, (*PC)++, 1);
        memcpy(&parametro2, (*PC)++, 1);
        memcpy(&parametro3, (*PC)++, 1);
        memcpy(&parametro4, (*PC)++, 1);
        offset = (parametro1 << 24) | (parametro2 << 16) | (parametro3 << 8) | parametro4;

        if (var1.valor.Int == match) {
            tempPC += (offset - 1);
            PC = tempPC;
            aux = 1;
        }
    }
    if (controle == 0) {
        tempPC += (valorDefalt - 1);
        PC = tempPC;
    }
}

int FU_ireturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno){
    ST_tpVariable pTempRetorno;

    pTempRetorno = *PL_popOperando(&pFrame->operandStack);
    if(pTempRetorno.tipo == JBYTE){
        (*Retorno)->valor.Int = (int) pTempRetorno.valor.Byte;
    }
    else if (pTempRetorno.tipo == JBOOL){
        (*Retorno)->valor.Int = (int) pTempRetorno.valor.Boolean;
    }
    else if (pTempRetorno.tipo == JSHORT){
        (*Retorno)->valor.Int = (int) pTempRetorno.valor.Short;
    }
    else if (pTempRetorno.tipo == JCHAR){
        (*Retorno)->valor.Int = (int) pTempRetorno.valor.Char;
    }
    else if (pTempRetorno.tipo == JINT){
		(*Retorno)->valor.Int = (int) pTempRetorno.valor.Int;
	}
    (*Retorno)->tipo = JINT;
    return 1;
}

int FU_lreturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno){
    ST_tpVariable pTempRetorno;

    pTempRetorno = *PL_popOperando(&pFrame->operandStack);
    if(pTempRetorno.tipo == JINT){
        (*Retorno)->valor.Long = (int64_t) pTempRetorno.valor.Int;
    }
    else if (pTempRetorno.tipo == JSHORT){
        (*Retorno)->valor.Long = (int64_t) pTempRetorno.valor.Short;
    }else if (pTempRetorno.tipo == JFLOAT){
        (*Retorno)->valor.Long = (int64_t) pTempRetorno.valor.Float;
    }
    else if (pTempRetorno.tipo == JDOUBLE){
        (*Retorno)->valor.Long = (int64_t) pTempRetorno.valor.Double;
    }
    else if (pTempRetorno.tipo == JLONG){
		(*Retorno)->valor.Long = (int64_t) pTempRetorno.valor.Long;
    }


    (*Retorno)->tipo = JLONG;
    return 1;
}

int FU_freturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno){
    ST_tpVariable pTempRetorno;

    pTempRetorno = *PL_popOperando(&pFrame->operandStack);
    if(pTempRetorno.tipo == JDOUBLE){
        (*Retorno)->valor.Float = (float) pTempRetorno.valor.Double;
    }
    else if (pTempRetorno.tipo == JSHORT){
        (*Retorno)->valor.Float = (float) pTempRetorno.valor.Short;
    }
    else if (pTempRetorno.tipo == JINT){
        (*Retorno)->valor.Float = (float) pTempRetorno.valor.Int;
    }
    else if (pTempRetorno.tipo == JLONG){
        (*Retorno)->valor.Float = (float) pTempRetorno.valor.Long;
    }
    else if (pTempRetorno.tipo == JFLOAT){
		(*Retorno)->valor.Float = (float) pTempRetorno.valor.Float;
	}

    (*Retorno)->tipo = JFLOAT;
    return 1;
}

int FU_dreturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno){
    ST_tpVariable pTempRetorno;

    pTempRetorno = *PL_popOperando(&pFrame->operandStack);
    if(pTempRetorno.tipo == JFLOAT){
        (*Retorno)->valor.Double = (double) pTempRetorno.valor.Float;
    }
    else if (pTempRetorno.tipo == JSHORT){
        (*Retorno)->valor.Double = (double) pTempRetorno.valor.Short;
    }
    else if (pTempRetorno.tipo == JINT){
        (*Retorno)->valor.Double = (double) pTempRetorno.valor.Int;
    }
    else if (pTempRetorno.tipo == JLONG){
        (*Retorno)->valor.Double = (double) pTempRetorno.valor.Long;
    }
    else if (pTempRetorno.tipo == JDOUBLE){
		(*Retorno)->valor.Double = (double) pTempRetorno.valor.Double;
	}

    (*Retorno)->tipo = JDOUBLE;
    return 1;
}

int FU_areturn(ST_tpStackFrame *pFrame, ST_tpVariable **Retorno){
    *Retorno = PL_popOperando(&pFrame->operandStack);
    if ((*Retorno)->valor.obj_ref != 0) {
        (*Retorno)->valor.obj_ref->ref_count++;
        return 1;
    }
    return 1;
    // Sair do metodo
}

void FU_getstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){

    ST_tpVariable var;
    ST_tpCp_info *pCPInfo;
    ST_tpConstantPool *cpIndx;
    u1 parametro1, parametro2;
    u2 temp2Byte, index1, index2;
    ST_tpCONSTANT_Fieldref_info *pFieldref;
    char *nomeClasse, *nomeField, *descritorField;

    var.tipo = 0x99; // inicializa variavel com valor arbitrario
    pCPInfo = pFrame->cp->constant_pool_table;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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

void FU_putstatic(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){

    ST_tpVariable *var1, *var2;
    ST_tpCp_info *pCPInfo;
    ST_tpConstantPool *cpIndx;
    u1 parametro1, parametro2;
    u2 temp2Byte, index1, index2;
    ST_tpCONSTANT_Fieldref_info *pFieldref;
    char *nomeClasse, *nomeField, *descritorField;

        //var.tipo = 0x99; // inicializa variavel com valor arbitrario
    pCPInfo = pFrame->cp->constant_pool_table;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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
    // verificar se é melhor passar o var2 na chamda da função 
    VM_armazenarValorStaticField(pJVM, nomeClasse, nomeField, descritorField, *var1);

}
int FU_getfield(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){

    ST_tpVariable *var = NULL, *var1;
    ST_tpCp_info *pCPInfo;
    ST_tpConstantPool *cpIndx;
    u1 parametro1, parametro2;
    u2 temp2Byte, index1, index2;

    ST_tpCONSTANT_Fieldref_info *pFieldref;
    char *nomeClasse, *nomeField, *descritorField;

    //var->tipo = 0x99; // inicializa variavel com valor arbitrario
    pCPInfo = pFrame->cp->constant_pool_table;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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

    var1 = PL_popOperando(&pFrame->operandStack);

    var = VM_recuperarValorField(pJVM, nomeClasse, nomeField, descritorField, var1);
    if (var == NULL) {
        return 1;
    }
    else{
        PL_pushOperando(&pFrame->operandStack, *var);
        return 0;
    }
}

void FU_putfield(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, u1 **PC){
    
    ST_tpVariable *var1, *var2;
    ST_tpCp_info *pCPInfo;
    ST_tpConstantPool *cpIndx;
    u1 parametro1, parametro2;
    u2 temp2Byte, index1, index2;
    ST_tpCONSTANT_Fieldref_info *pFieldref;
    char *nomeClasse, *nomeField, *descritorField;
    
    //var.tipo = 0x99; // inicializa variavel com valor arbitrario
    pCPInfo = pFrame->cp->constant_pool_table;
    
    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
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
    memcpy((void*) var2, PL_popOperando(&pFrame->operandStack), sizeof(ST_tpVariable));
    
    if(var1->tipo == JBOOL || var1->tipo == JBYTE || var1->tipo == JSHORT){
        if(var1->tipo == JBOOL) var2->valor.Int = var1->valor.Boolean;
        if(var1->tipo == JBYTE) var2->valor.Int = var1->valor.Byte;
        if(var1->tipo == JCHAR) var2->valor.Int = var1->valor.Char;
        if(var1->tipo == JSHORT) var2->valor.Int = var1->valor.Short;
        var2->tipo = JINT;
    }
    VM_armazenarValorField(pJVM, nomeClasse, nomeField, descritorField, *var1, *var2);
    
}

void FU_ishl(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    u1 shift_amount;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    shift_amount = var1.valor.Int & 0x1F;
    var.valor.Int = var2.valor.Int << shift_amount;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lshl(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    u1 shift_amount;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    shift_amount = var1.valor.Int & 0x3F;
    var.valor.Long = var2.valor.Long << shift_amount;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);

}

void FU_ishr(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    u1 shift_amount;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    shift_amount = var1.valor.Int & 0x1F;
    var.valor.Int = var2.valor.Int >> shift_amount;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lshr(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    u1 shift_amount;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    shift_amount = var1.valor.Int & 0x3F;
    var.valor.Long = var2.valor.Long >> shift_amount;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_iushr(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    u1 shift_amount;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    shift_amount = var1.valor.Int & 0x1F;
    if (var2.valor.Int >=0) {
        var.valor.Int = var2.valor.Int >> shift_amount;
    }
    else {
        var.valor.Int = (var2.valor.Int >> shift_amount) + (2 << (~shift_amount & 0x1F));
    }
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lushr(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;
    u1 shift_amount;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);
    shift_amount = var1.valor.Int & 0x3F;
    if (var2.valor.Long >=0) {
        var.valor.Long = var2.valor.Int >> shift_amount;
    }
    else {
        var.valor.Long = (var2.valor.Long >> shift_amount) + (2 << (~shift_amount & 0x3F));
    }
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_iand(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    var.valor.Int = var1.valor.Int & var2.valor.Int ;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_land(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    var.valor.Long = var1.valor.Long & var2.valor.Long ;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ior(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    var.valor.Int = var1.valor.Int | var2.valor.Int ;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lor(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    var.valor.Long = var1.valor.Long | var2.valor.Long ;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_ixor(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    var.valor.Int = var1.valor.Int ^ var2.valor.Int ;
    var.tipo = JINT;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_lxor(ST_tpStackFrame *pFrame){
    ST_tpVariable var, var1, var2;

    var1 = *PL_popOperando(&pFrame->operandStack);
    var2 = *PL_popOperando(&pFrame->operandStack);

    var.valor.Long = var1.valor.Long ^ var2.valor.Long ;
    var.tipo = JLONG;
    PL_pushOperando(&pFrame->operandStack, var);
}

void FU_iinc(ST_tpStackFrame *pFrame, u1 **PC){
    ST_tpVariable var;
    u1 parametro1, parametro2;
    int8_t inc;

    (*PC)++;
    memcpy(&parametro1, *PC, 1);
    (*PC)++;
    memcpy(&parametro2, *PC, 1);
    
    var = VM_recuperarVariavel(pFrame->localVariables, (int) parametro1);
    inc = (int8_t) parametro2;
    var.valor.Int += (int) inc;
    VM_armazenarVariavel(pFrame->localVariables, var, (int) parametro1);
}

