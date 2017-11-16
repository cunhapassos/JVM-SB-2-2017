   /** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *    Software Basico - Turma A
 *
 *  MODULO: VM_
 *  @file virtualMachine
 *  @brief
 *            Descricao: Implementacao das estruturas de incicializacao da JVM
 *
 * @author ALON MOTA     - MAT. 13/0005002
 * @author DANIEL MATIAS - MAT. 12/0139804
 * @author PAULO PASSOS  - MAT. 10/0118577
 *
 * @version 1.0
 * @since 31/10/17
 *
 @}********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "leitor.h"
#include "pilhas_listas.h"
#include "virtualMachine.h"
#include "funcoes.h"


ST_tpMethodArea *VM_criarAreaMetodo(){
    ST_tpMethodArea *pAreaMetodo;
    
    pAreaMetodo = malloc(sizeof(ST_tpMethodArea));
    pAreaMetodo->classFile = NULL;
    
    return pAreaMetodo;
}

ST_tpHeap *VM_criarHeap(){
    ST_tpHeap *pHeap;
    
    pHeap = malloc(sizeof(ST_tpHeap));
    pHeap->array = NULL;
    pHeap->classes = NULL;
    pHeap->objects = NULL;
    
    return pHeap;
}

ST_tpThread *VM_criarThread(){
    ST_tpThread *pThread;
    
    pThread = malloc(sizeof(ST_tpThread));
    pThread->pJVMStack = NULL;
    pThread->PC = 0;
    
    return pThread;
}

ST_tpJVM *VM_criarJVM(){
    ST_tpJVM *pJvm;
    
    pJvm = malloc(sizeof(ST_tpJVM));
    pJvm->heap = VM_criarHeap();
    pJvm->methodArea = VM_criarAreaMetodo();
    pJvm->thread = VM_criarThread();
    
    return pJvm;
}

void VM_armazenarVariavel(ST_tpVariable *pVariaveisLocais, ST_tpVariable variavel, int posicao){
    memcpy((void *)(pVariaveisLocais + posicao), (void *) &variavel, sizeof(variavel));
    
    //printf("%lf", variavel.valor.Double);
    //printf("%lf", (pVariaveisLocais+posicao)->valor.Double);
}


ST_tpVariable VM_recuperarVariavel(ST_tpVariable *pVariaveisLocais, int posicao){
    ST_tpVariable varTemporaria;
    
    memcpy((void *)&varTemporaria, (void*)(pVariaveisLocais + posicao), sizeof(varTemporaria));
    
    return varTemporaria;
}


/**
 Cria um Frame para o metodo que sera executado e isere esse frame na pilha de
 frames da thread

 @param pJVMStack       - Pilha de Frames da thread
 @param pClasse         - Classe corrente do metodo
 @param pilhaParametros - Pilha de parametros que é passada para o metodo que sera executado
 @param maxStackSize    - Numero máximo de variaveis que pode ser colocadas na pilha de variaveis locais
 @return                - Retorna o Frame criado
 */
ST_tpStackFrame *VM_criarStackFrame(ST_tpStackFrame **pJVMStack, ST_tpClassFile *pClasse, ST_tpParameterStack *pilhaParametros, long maxStackSize){
    int i;
    ST_tpVariable varTemporaria;
    ST_tpStackFrame *pFrame;
    
    pFrame = (ST_tpStackFrame *) malloc(sizeof(ST_tpStackFrame));
    pFrame->cp              = pClasse;
    pFrame->next            = NULL;
    pFrame->operandStack    = NULL;
    pFrame->parameterStack  = NULL;
    pFrame->localVariables  = (ST_tpVariable *) malloc(sizeof(ST_tpVariable)*(maxStackSize));
    
    varTemporaria.tipo          = JREF;
    varTemporaria.valor.obj_ref = NULL;
    VM_armazenarVariavel(pFrame->localVariables, varTemporaria, 0);
    
    i = 0;
    while(pilhaParametros != NULL){
        varTemporaria = *PL_popParametro(&pilhaParametros);
        VM_armazenarVariavel(pFrame->localVariables, varTemporaria, i);
        i++;
        if(varTemporaria.tipo == JLONG || varTemporaria.tipo == JDOUBLE) i++;
    }
    
    if(*pJVMStack == NULL){
        *pJVMStack = pFrame;
    }
    else{
        pFrame->next = *pJVMStack;
        *pJVMStack    = pFrame;
    }
    
    return pFrame;
}

ST_tpVariable *VM_executarMetodo(ST_tpJVM *pJVM, ST_tpClassFile *pClasse, ST_tpParameterStack *pilhaParametros, ST_tpMethod_info *pMetodo){
    int i;
    u1* end;
    char *name;
    u2 nameIndex;
    ST_tpStackFrame *pFrame;
    ST_tpVariable *pRetorno;
    ST_tpCode_attribute *pCode;
    
    pRetorno = (ST_tpVariable*)malloc(sizeof(ST_tpVariable));
    pRetorno->tipo = 0;
    pRetorno->valor.Int = 0;
    pRetorno->valor.Long = 0;
    pRetorno->valor.Byte = 0;
    pRetorno->valor.Char = 0;
    pRetorno->valor.Short = 0;
    pRetorno->valor.Float = 0;
    pRetorno->valor.Double = 0;
    pRetorno->valor.Boolean = 0;
    pRetorno->valor.obj_ref = NULL;
    pRetorno->valor.array_ref = NULL;

    for(i = 0; i < pMetodo->attributes_count; i++){
        nameIndex = pMetodo->attributes[i].attribute_name_index-1;
        name = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
        
        if(strcmp(name, "Code") == 0){
            
            /* Cria uma Stack Frame */
            pFrame = VM_criarStackFrame(&(pJVM->thread->pJVMStack), pClasse, pilhaParametros,  ((ST_tpCode_attribute*)pMetodo->attributes[i].info)->max_stack);
            
            
            // EXECUTAR CODIGO
            /* Carregando codigos */
            pCode = (ST_tpCode_attribute *) malloc(sizeof(ST_tpCode_attribute));
            pCode->exception_table  = NULL;
            pCode->attribute_info   = NULL;
            pCode->code             = NULL;
            
            /* Ler informacoes do Atributo Code na sequencia da memoria */
            memset(pCode, 0, sizeof(ST_tpCode_attribute));/* Preenche os n (do tamanho de ST_tpCode_attribute) primeiros carcteres de pCode com 0 */
            memcpy((u1 *)&pCode->max_stack, (u2 *)&((ST_tpCode_attribute*) pMetodo->attributes->info)->max_stack, 2);
            memcpy((u1 *)&pCode->max_locals, (u2 *)&((ST_tpCode_attribute*) pMetodo->attributes->info)->max_locals, 2);
            memcpy((u1 *)&pCode->code_length, (u2 *)&((ST_tpCode_attribute*) pMetodo->attributes->info)->code_length, 4);
            
            pCode->code = (u1 *) malloc(pCode->code_length);
            memcpy((u1 *)pCode->code, (u1*)((ST_tpCode_attribute*)pMetodo->attributes->info)->code, pCode->code_length);
            memcpy((u2 *)&pCode->exception_table_length, (u2 *)&((ST_tpCode_attribute*) pMetodo->attributes->info)->exception_table_length , 2);
            
            
            if(pCode->exception_table_length != 0){
                ST_tpException_table *pExeptionTable = ((ST_tpCode_attribute*) pMetodo->attributes->info)->exception_table;
                pCode->exception_table = (ST_tpException_table *) malloc(pCode->exception_table_length * sizeof(ST_tpException_table));
                
                for(int k = 0; k < pCode->exception_table_length; k++){
                    memcpy((u1 *)&pCode->exception_table[i].end_pc , (u1 *)&pExeptionTable[i].end_pc, 2);
                    memcpy((u1 *)&pCode->exception_table[i].start_pc , (u1 *)&pExeptionTable[i].start_pc, 2);
                    memcpy((u1 *)&pCode->exception_table[i].handler_pc , (u1 *)&pExeptionTable[i].handler_pc, 2);
                    memcpy((u1 *)&pCode->exception_table[i].catch_type , (u1 *)&pExeptionTable[i].catch_type, 2);
                }
            }
            else{
                pCode->exception_table = NULL;
            }
            
            memcpy((u1 *)&pCode->attributes_count, (u2 *)&((ST_tpCode_attribute*) pMetodo->attributes->info)->attributes_count, 2);
            
            pCode->attribute_info = (ST_tpAttribute_info *) malloc(pCode->attributes_count); // VERIFICAR SE TEM A MULTIPLICACAO MESMO?
            
            pJVM->thread->PC = (u1 *)pCode->code;
            end = pJVM->thread->PC + pCode->code_length;
            while(pJVM->thread->PC < end){
                IT_executaInstrucao(pJVM, pFrame, &pRetorno); // VERIFICAR ONDE EXECUTA AS EXCESSOES
                pJVM->thread->PC++;
            }

            //CRIA ESSA FUNCAO
           // limparFrame(pJVM->thread->pJVMStack->localVariables);
            // VERIFICAR COMO FAZER O RETORNO DA FUNCAO
        }
    }
    return pRetorno;
}

ST_tpMethod_info *VM_procurarMetodo(ST_tpClassFile *pClassFile, char *descritorMetodo, char *nomeMetodo) {
    char *name, *descritor;
    u2 nameIndex, descritorIndex;
    
    for(int i = 0; i < pClassFile->methods_count; i++){
        nameIndex = pClassFile->method_info_table[i].name_index-1;
        descritorIndex = pClassFile->method_info_table[i].descriptor_index-1;
        name = (char *) pClassFile->constant_pool_table[nameIndex].info.Utf8.bytes;
        descritor = (char *)  pClassFile->constant_pool_table[descritorIndex].info.Utf8.bytes;
        
        if(strcmp(name, nomeMetodo) == 0 && strcmp(descritor, descritorMetodo) == 0){ // VERIFICAR SOBRE A FLAG DE ACESSO
            return &pClassFile->method_info_table[i];    
        }
    }
    return NULL;
}
u1 *VM_retornaNomeSuperClasse(ST_tpClassFile *pClassFile){
    u1 *superClasseString;
    u2 classNameIndex;
    u2 superClassIndex;
    
    superClassIndex     = pClassFile->super_class;
    classNameIndex      = pClassFile->constant_pool_table[superClassIndex -1].info.Class.name_index;
    superClasseString   = (u1 *)pClassFile->constant_pool_table[classNameIndex - 1].info.Utf8.bytes;
    
    return superClasseString;
}

u1 *VM_retornarNomeClasse(ST_tpClassFile *pClassFile){
    u1 *classeString;
    u2 classNameIndex;
    u2 classIndex;
    
    classIndex      = pClassFile->this_class;
    classNameIndex  = pClassFile->constant_pool_table[classIndex -1].info.Class.name_index;
    classeString   = (u1 *)pClassFile->constant_pool_table[classNameIndex - 1].info.Utf8.bytes;
    
    return classeString;
}
ST_tpObjectHeap *VM_criarObjeto(ST_tpJVM *pJVM, ST_tpClassFile *pClassFile){
    int maxVariaveis;
    ST_tpClassFile *pAuxClassFile1, *pAuxClassFile2;
    u1 *nome;
    
    ST_tpObjectHeap *pObjeto = (ST_tpObjectHeap *)malloc(sizeof(ST_tpObjectHeap));
    
    pAuxClassFile1 = pClassFile;
    maxVariaveis = pClassFile->fields_count;
    
    while(pAuxClassFile1->super_class != 0 ){
        nome = VM_retornaNomeSuperClasse(pClassFile);
        /* Verifica se a SuperClasse esta carregada */
        pAuxClassFile2 = PL_buscarClasse(pJVM, (char *) nome);
        
        /* Se nao estiver carragada, carrega */
        if(pAuxClassFile2 == NULL){
            
            
            pAuxClassFile2 = LE_carregarClasse((char *)nome);
            if(pAuxClassFile2 != NULL){
                PL_inserirClasseTopo(pJVM, pAuxClassFile2);
                //VM_alocarMemoriaHeapClasse(pJVM, pAuxClassFile2->nomeClasse);
            }
            else{
                printf("ERRO AO CARREGAR CLASSE");
                return NULL;
            }
            maxVariaveis += pAuxClassFile2->fields_count;
            pAuxClassFile1 = pAuxClassFile2;
        }
    }
    //ATENCAO NA ESTA COMPLETO: Acrescenntar os outros valores de ST_tpFieldHeap
    pObjeto->field_area = (ST_tpFieldHeap *)malloc(sizeof(ST_tpFieldHeap) * (maxVariaveis + 1));
    pObjeto->className = malloc(sizeof(pClassFile->nomeClasse));
    memcpy((void*)pObjeto->className, (void*)pClassFile->nomeClasse, sizeof(pClassFile->nomeClasse));
    pObjeto->thread = pJVM->thread;
    pObjeto->max_no_var = maxVariaveis;
    pObjeto->ref_count = 0;
    pObjeto->next = NULL;
    
    if(pJVM->heap->objects == NULL){
        pJVM->heap->objects = pObjeto;
    }
    else{
        pObjeto->next = pJVM->heap->objects;
        pJVM->heap->objects = pObjeto;
    }
    
    return pObjeto;
}
ST_tpArrayHeap *VM_criarArray(u1 tipo, char *nomeClasse, int tamanho){
    ST_tpArrayHeap *pArray = ( ST_tpArrayHeap *) malloc(sizeof( ST_tpArrayHeap)); // VERIFICAR SE EH PRECISO MULTIPLICAR POR TAMANHO
    
    switch (tipo) {
        case T_BOOLEAN:
            pArray->area = calloc(tamanho, sizeof(u1));
            break;
        case T_CHAR:
            pArray->area = calloc(tamanho, sizeof(u2));
            break;
        case T_FLOAT:
            pArray->area = calloc(tamanho, sizeof(float));
            break;
        case T_DOUBLE:
            pArray->area = calloc(tamanho, sizeof(double));
            break;
        case T_BYTE:
            pArray->area = calloc(tamanho, sizeof(u1));
            break;
        case T_SHORT:
            pArray->area = calloc(tamanho, sizeof(short));
            break;
        case T_INT:
            pArray->area = calloc(tamanho, sizeof(int));
            break;
        case T_LONG:
            pArray->area = calloc(tamanho, sizeof(long));
            break;
        case T_REF:
            pArray->area = calloc(tamanho, sizeof(ST_tpObjectHeap));
            break;
        case T_AREF:
            pArray->area = calloc(tamanho, sizeof(ST_tpObjectHeap));
            break;
    }
    pArray->length = tamanho;
    pArray->type = tipo;
    pArray->ref_count = 0;
    
    return pArray;
    
}
void VM_armazenarValorArray(ST_tpArrayHeap *pArray, int posicao, ST_tpVariable variavel){
    u2 *pChar;
    int *pInt;
    float *pFloat;
    double *pDouble;
    __int64_t *pLong;
    short int *pShort;
    char *pByte, *pBoolean;
    ST_tpObjectHeap *pObjRef;
    ST_tpArrayHeap *pArrayRef;

    
    switch (pArray->type) {
        case T_BYTE:
            pByte  = (char*)pArray->area;
            pByte += posicao;
            memcpy((void *)pByte, (void *)&variavel.valor.Byte, sizeof(variavel.valor.Byte));
            break;
        case T_LONG:
            pLong  = (__int64_t *)pArray->area;
            pLong += posicao;
            memcpy((void *)pLong, (void *)&variavel.valor.Long, sizeof(variavel.valor.Long));
            break;
        case T_BOOLEAN:
            pBoolean  = (char*) pArray->area;
            pBoolean += posicao;
            memcpy((void *)pBoolean, (void *)&variavel.valor.Boolean, sizeof(variavel.valor.Boolean));
            break;
        case T_CHAR:
            pChar  = (u2*)pArray->area;
            pChar += posicao;
            memcpy((void *)pChar, (void *)&variavel.valor.Char, sizeof(variavel.valor.Char));
            break;
        case T_SHORT:
            pShort  = (short int  *)pArray->area;
            pShort += posicao;
            memcpy((void *)pShort, (void *)&variavel.valor.Short, sizeof(variavel.valor.Short));
            break;
        case T_FLOAT:
            pFloat  = (float *)pArray->area;
            pFloat += posicao;
            memcpy((void *)pFloat, (void *)&variavel.valor.Float, sizeof(variavel.valor.Float));
            break;
        case T_INT:
            pInt  = (int *)pArray->area;
            pInt += posicao;
            memcpy((void *)pInt, (void *)&variavel.valor.Int, sizeof(variavel.valor.Int));
            break;
        case T_DOUBLE:
            pDouble  = (double *)pArray->area;
            pDouble += posicao;
            memcpy((void *)pDouble, (void *)&variavel.valor.Double, sizeof(variavel.valor.Double));
            break;
        case T_REF:
            pObjRef  = (ST_tpObjectHeap *)pArray->area;
            pObjRef += posicao;
            memcpy((void *)pObjRef, (void *)&variavel.valor.obj_ref, sizeof(variavel.valor.obj_ref));
            break;
        case T_AREF:
            pArrayRef  = (ST_tpArrayHeap *)pArray->area;
            pArrayRef += posicao;
            memcpy((void *)pArrayRef, (void *)&variavel.valor.array_ref, sizeof(variavel.valor.array_ref));
            break;
    }
}


ST_tpVariable VM_recuperarValorArray(ST_tpArrayHeap *pArrayHeap, int posicao){
    
    u2 *pChar;
    int *pInt;
    float *pFloat;
    double *pDouble;
    __int64_t *pLong;
    short int *pShort;
    char *pByte, *pBoolean;
    ST_tpObjectHeap *pObjRef;
    ST_tpArrayHeap *pArrayRef;
    ST_tpVariable var;
    
    var.tipo = 0x99; // Inicia variavel com valor qualquer
    
    switch (pArrayHeap->type) {
        case T_BYTE:
            pByte  = (char*)pArrayHeap->area;
            pByte += posicao;
            var.tipo = JBYTE;
            memcpy((void *)&var, (void *)pByte , sizeof(pByte));
            break;
        case T_LONG:
            pLong  = (__int64_t *)pArrayHeap->area;
            pLong += posicao;
            var.tipo = JLONG;
            memcpy((void *)&var, (void *)pLong, sizeof(pLong));
            break;
        case T_BOOLEAN:
            pBoolean  = (char*) pArrayHeap->area;
            pBoolean += posicao;
            var.tipo = JBOOL;
            memcpy((void *)&var, (void *)pBoolean, sizeof(pBoolean));
            break;
        case T_CHAR:
            pChar  = (u2*)pArrayHeap->area;
            pChar += posicao;
            var.tipo = JCHAR;
            memcpy((void *)&var, (void *)pChar, sizeof(pChar));
            break;
        case T_SHORT:
            pShort  = (short int  *)pArrayHeap->area;
            pShort += posicao;
            var.tipo = JSHORT;
            memcpy((void *)&var, (void *)pShort, sizeof(pShort));
            break;
        case T_FLOAT:
            pFloat  = (float *)pArrayHeap->area;
            pFloat += posicao;
            var.tipo = JFLOAT;
            memcpy((void *)&var, (void *)pFloat, sizeof(pFloat));
            break;
        case T_INT:
            pInt  = (int *)pArrayHeap->area;
            pInt += posicao;
            memcpy((void *)&var, (void *)pInt, sizeof(pInt));
            var.tipo = JINT;
            break;
        case T_DOUBLE:
            pDouble  = (double *)pArrayHeap->area;
            pDouble += posicao;
            var.tipo = JDOUBLE;
            memcpy((void *)&var, (void *)pDouble, sizeof(pDouble));
            break;
        case T_REF:
            pObjRef  = (ST_tpObjectHeap *)pArrayHeap->area;
            pObjRef += posicao;
            var.tipo = JREF;
            memcpy((void *)&var, (void *)pObjRef, sizeof(pObjRef));
            break;
        case T_AREF:
            pArrayRef  = (ST_tpArrayHeap *)pArrayHeap->area;
            pArrayRef += posicao;
            var.tipo = JAREF;
            memcpy((void *)&var, (void *)pArrayRef, sizeof(pArrayRef));
            break;
    }
    return var;
}

void *VM_armazenarValorField(ST_tpJVM *pJVM, char *nomeClasse, char *pFieldName, char *pFieldDescriptor, ST_tpVariable var, ST_tpVariable objRef){
    int i = 0;
    char *string;
    ST_tpField_info *pField;
    ST_tpClassFile *pClassFile;
    ST_tpObjectHeap *pHeap;


    if(objRef.valor.obj_ref == 0){
        return NULL; // Lancar um erro
    }
    
    while (TRUE) {
        pClassFile = PL_buscarClasse(pJVM, nomeClasse);
        if(pClassFile == NULL){
            pClassFile = LE_carregarClasse((char*)nomeClasse);
            if (pClassFile == NULL) {
                printf("ERRO AO CARREGAR CLASSE!");
                return NULL;
            }
            else{
                PL_inserirClasseTopo(pJVM, pClassFile);
                VM_alocarMemoriaHeapClasse(pJVM, pClassFile->nomeClasse);
            }
        }
        pField = pClassFile->field_info_table;
        while (pField != NULL) {
            string = (char *)(pClassFile->constant_pool_table[pField->name_index - 1].info.Utf8.bytes);
            
            if(strcmp(string, pFieldName) == 0){
                i++;
                pField = pField->next;
                continue;
            }
            
            string = (char *)pClassFile->constant_pool_table[pField->descriptor_index-1].info.Utf8.bytes;
            if(strcmp(string, pFieldDescriptor) == 0){
                i++;
                pField = pField->next;
                continue;
            }
            if((pField->access_flags & ACC_STATIC) == ACC_STATIC){
                pField = pField->next;
                continue;
            }
            break;
        }
        if(NULL == pField){
            if(pClassFile->super_class == 0){
                break;
            }
            else{
                //strcpy(temp_class_name, pClassFile->super_class_name);
            }
        }
        else{
            break;
        }
    }
    if(pField == NULL){
        return NULL;
    }
    pHeap = (ST_tpObjectHeap *)objRef.valor.obj_ref;
    memcpy((pHeap->field_area + i), &var, sizeof(var));
    
    return pHeap;
}

void *VM_recuperarValorField(ST_tpJVM *pJVM, char *nomeClasse, char *pFieldName, char *pFieldDescriptor, ST_tpVariable *var, ST_tpVariable objRef){
    int i = 0;
    char *string;
    ST_tpField_info *pField;
    ST_tpClassFile *pClassFile;
    ST_tpObjectHeap *pHeap;
    
    
    if(objRef.valor.obj_ref == 0){
        return NULL; // Lancar um erro
    }
    
    while (TRUE) {
        pClassFile = PL_buscarClasse(pJVM, nomeClasse);
        if(pClassFile == NULL){
            pClassFile = LE_carregarClasse((char *)nomeClasse);
            if (pClassFile == NULL) {
                printf("ERRO AO CARREGAR CLASSE!");
                return NULL;
            }
            else{
                PL_inserirClasseTopo(pJVM, pClassFile);
                VM_alocarMemoriaHeapClasse(pJVM, pClassFile->nomeClasse);
            }
        }

        pField = pClassFile->field_info_table;
        while (pField != NULL) {
            string = (char *)(pClassFile->constant_pool_table[pField->name_index - 1].info.Utf8.bytes);
            
            if(strcmp(string, pFieldName) == 0){
                i++;
                pField = pField->next;
                continue;
            }
            
            string = (char *)pClassFile->constant_pool_table[pField->descriptor_index-1].info.Utf8.bytes;
            if(strcmp(string, pFieldDescriptor) == 0){
                i++;
                pField = pField->next;
                continue;
            }
            if((pField->access_flags & ACC_STATIC) == ACC_STATIC){
                pField = pField->next;
                continue;
            }
            break;
        }
        if(NULL == pField){
            if(pClassFile->super_class == 0){
                break;
            }
            else{
                //strcpy(temp_class_name, pClassFile->super_class_name);
            }
        }
        else{
            break;
        }
    }
    if(pField == NULL){
        return NULL;
    }
    pHeap = (ST_tpObjectHeap *)objRef.valor.obj_ref;
    memcpy(var, (pHeap->field_area + i), sizeof(ST_tpVariable));
    
    return var;
}

void *VM_alocarMemoriaHeapClasse(ST_tpJVM *pJVM, char *pClassName){
    
    int maxStaticVar = 0;
    char *pNomeClasse;
    ST_tpClassHeap *pClassHeap;
    ST_tpField_info *pFieldTable;
    ST_tpClassFile *pClassFile1, *pClassFile2;
    
    pClassFile1 = PL_buscarClasse(pJVM, pClassName);
    
    while(TRUE){
        pFieldTable = pClassFile1->field_info_table;
        for (int i = 0 ; i < pClassFile1->fields_count; i++) {
            if((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC){
                maxStaticVar++;
            }
            pFieldTable = pFieldTable->next;
        }
        if (pClassFile1->super_class == 0) {
            break;
        }
        
        pNomeClasse = (char *)malloc(strlen(pClassFile1->nomeSuperClasse)+2);
        strcpy(pNomeClasse, pClassFile1->nomeSuperClasse);
        //strcat(pNomeClasse, ".class");
        
        pClassFile2 = PL_buscarClasse(pJVM, pNomeClasse);
    
        if (pClassFile2 == NULL) {
            pClassFile2 = LE_carregarClasse((char *)pNomeClasse);
            if (pClassFile2 == NULL) {
                /* A classe não foi carregada */
                printf("ERRO AO CARREGAR CLASSE!");
                return NULL;
            }
            else{
                PL_inserirClasseTopo(pJVM, pClassFile2);
                VM_alocarMemoriaHeapClasse(pJVM, pClassFile2->nomeClasse);
            }
        }
        pClassFile1 = pClassFile2;
    }
    pClassHeap = (ST_tpClassHeap *)malloc(sizeof(ST_tpClassHeap));
    pClassHeap->pClassName = (char *)malloc(strlen(pClassName)+2);
    strcpy(pClassHeap->pClassName, pClassName);
    
    //ATENCAO NA ESTA COMPLETO: Acrescenntar os outros valores de ST_tpFieldHeap
    pClassHeap->field_area = (ST_tpFieldHeap *)malloc(sizeof(ST_tpFieldHeap) * (maxStaticVar + 1));
    pClassHeap->next = NULL;
    
    if(pJVM->heap->classes == NULL){
        pJVM->heap->classes = pClassHeap;
    }
    else{
        pClassHeap->next = pJVM->heap->classes;
        pJVM->heap->classes = pClassHeap;
    }
    
    return pClassHeap;
}
/*
void VM_carregarHeapClass(ST_tpJVM *pJVM, char *pClassName){
    char *pNomeClasse, *nameField, *descritorField;
    ST_tpClassFile *pClassFile1;
    ST_tpVariable var;
    ST_tpField_info *pFieldTable = NULL;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);
    strcpy(pNomeClasse, pClassName);
    pClassFile1 = PL_buscarClasse(pJVM, pNomeClasse);
    pFieldTable = pClassFile1->field_info_table;
    while (pFieldTable != NULL) {
        nameField      = (char *)pClassFile1->constant_pool_table[pFieldTable->name_index- 1].info.Utf8.bytes;
        descritorField = (char *)pClassFile1->constant_pool_table[pFieldTable->descriptor_index - 1].info.Utf8.bytes;
        // CRIAR FUNCAO resolver descritor
        
        VM_armazenarValorStaticField(pJVM, pClassName, nameField, descritorField, <#ST_tpVariable var#>)
    }
    
    
} */
/*
ST_tpVariable VM_resolveField(ST_tpCONSTANT_Utf8_info *decritorFieldUtf8){
    char aux;
    ST_tpVariable var;
    
    for (int i = 0; i < decritorFieldUtf8->length; i++) {
        aux = decritorFieldUtf8->bytes[i];
        switch (aux) {
            case 'B':
                var.tipo = JBYTE;
                break;
                
            default:
                break;
        }
    }
} */

void VM_armazenarVariavelNoFieldDaClasse(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, char *pClassName, char *pFieldName, char *pFieldDescritor,ST_tpVariable var){
    
    ST_tpFieldHeap *pFieldHeap;
    ST_tpClassFile *pClassFile;
    ST_tpClassHeap *pClassHeap, *pAux;
    ST_tpField_info *pFieldTable = NULL;
    char *pNameField, *pDescriptorField;
    
    pClassFile = PL_buscarClasse(pJVM, pClassName);
    if(pClassFile == NULL){
        pClassFile = LE_carregarClasse(pClassName);
        if (pClassFile != NULL) {
            PL_inserirClasseTopo(pJVM, pClassFile);
        }
        else{
            printf("ERRO AO CARREGAR CLASSE!");
        }
    }
    pFieldTable = pClassFile->field_info_table;

    pFieldHeap = (ST_tpFieldHeap *)malloc(sizeof(ST_tpFieldHeap));
    pFieldHeap->nameField       = malloc(sizeof(pFieldName));
    pFieldHeap->decritorField   = malloc(sizeof(pFieldDescritor));
    memcpy((void*)pFieldHeap->decritorField, (void*)pFieldDescritor, sizeof(pFieldDescritor));
    strcpy(pFieldHeap->nameField, pFieldName);
    pFieldHeap->var             = &var;
    
    /* Recuperar acesse flag do field */
    while (pFieldTable != NULL) {
        
        pNameField       = (char *) pClassFile->constant_pool_table[pFieldTable->name_index - 1].info.Utf8.bytes;
        pDescriptorField = (char *) pClassFile->constant_pool_table[pFieldTable->descriptor_index-1].info.Utf8.bytes;
        
        if (strcmp(pNameField, pFieldName) == 0 && strcmp(pDescriptorField, pFieldDescritor) == 0) {
            pFieldHeap->access_flags =  pFieldTable->access_flags;
            break;
        }
        pFieldTable = pFieldTable->next;
    }
    
    pAux = pJVM->heap->classes;
    
    if (pAux == NULL){
        pClassHeap = (ST_tpClassHeap *)malloc(sizeof(ST_tpClassHeap));
        pClassHeap->pClassName = (char *)malloc(sizeof(pClassName));
        
        memcpy((void*)pClassHeap->pClassName, (void*)pClassName, sizeof(pClassName));
        pClassHeap->field_area  = pFieldHeap;
        pClassHeap->next        = NULL;
        pJVM->heap->classes = pClassHeap;
    }
    
    else{
        while (pAux != NULL) {
            if(strcmp(pAux->pClassName, pClassName) == 0) break;
            pAux = pAux->next;
        }
        if (pAux == NULL) {
            pClassHeap = (ST_tpClassHeap *)malloc(sizeof(ST_tpClassHeap));
            pClassHeap->pClassName = (char *)malloc(sizeof(pClassName));
            
            memcpy((void*)pClassHeap->pClassName, (void*)pClassName, sizeof(pClassName));
            pClassHeap->field_area  = pFieldHeap;
            pClassHeap->next        = (pJVM->heap->classes);
            pJVM->heap->classes     = pClassHeap;
        }
        else{
            pFieldHeap->next = pAux->field_area;
            pAux->field_area = pFieldHeap;
        }
    }
}
/*
void *VM_armazenarValorStaticField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescritor, ST_tpVariable var){
    int i = 0;
    char *pNomeClasse;
    ST_tpClassFile *pClassFile1;
    ST_tpClassHeap *pClassHeap;
    ST_tpField_info *pFieldTable = NULL;
    char *pNameField, *pDescriptorField;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);
    
    strcpy(pNomeClasse, pClassName);
    
    while (TRUE) {
        pClassFile1 = PL_buscarClasse(pJVM, pNomeClasse);
        if (pClassFile1 == NULL) {
            pClassFile1 = LE_carregarClasse((char *)pNomeClasse);
            if (pClassFile1 == NULL) {
                printf("ERRO AO CARREGAR CLASSE!");
                return NULL;
            }
            else{
                PL_inserirClasseTopo(pJVM, pClassFile1);
                //VM_alocarMemoriaHeapClasse(pJVM, pClassFile1->nomeClasse);
            }
            
        }
        pFieldTable = pClassFile1->field_info_table;
        
        while (pFieldTable != NULL) {
            pNameField = (char *) pClassFile1->constant_pool_table[pFieldTable->name_index-1].info.Utf8.bytes;
            if (strcmp(pNameField, pFieldName) == 0) {
                if ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC) i++;
                pFieldTable = pFieldTable->next;
                continue;
            }
            pDescriptorField = (char *) pClassFile1->constant_pool_table[pFieldTable->descriptor_index-1].info.Utf8.bytes;
            if (strcmp(pDescriptorField, pFieldDescritor)) {
                if ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC) i++;
                pFieldTable = pFieldTable->next;
                continue;
            }
            if ((pFieldTable->access_flags & ACC_STATIC) != ACC_STATIC){
                pFieldTable = pFieldTable->next;
                continue;
            }
            break;
        }
        if (pFieldTable != NULL) {
            break;
        }
        if (pClassFile1->super_class == 0) {
            return NULL;
        }
        else{
            strcpy(pNomeClasse, pClassFile1->nomeSuperClasse);
        }
    }
    
    pClassHeap = pJVM->heap->classes;
    while (pClassHeap != NULL) {
        if (!(strcmp(pClassHeap->pClassName, pClassName))) break;
        pClassHeap = pClassHeap->next;
    }
    memcpy(pClassHeap->field_area + i, &var, sizeof(var));
    
    return pJVM->heap->classes;
    
}
*/
ST_tpVariable  *VM_recuperarValorStaticField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescritor){
    int i = 0;
    ST_tpVariable *var = NULL;
    char *pNomeClasse;
    ST_tpClassFile *pClassFile1;
    ST_tpClassHeap *pClassHeap;
    ST_tpField_info *pFieldTable = NULL;
    char *pNameField, *pDescriptorField;
    
    //var->tipo = 0x99;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);
    
    strcpy(pNomeClasse, pClassName);
    
    while (TRUE) {
        pClassFile1 = PL_buscarClasse(pJVM, (char *)pNomeClasse);
        if (pClassFile1 == NULL) {
            pClassFile1 = LE_carregarClasse((char *)pNomeClasse);
            if (pClassFile1 == NULL) {
                return var;
            }
            else{
                PL_inserirClasseTopo(pJVM, pClassFile1);
                VM_alocarMemoriaHeapClasse(pJVM, pClassFile1->nomeClasse);
            }
            pFieldTable = pClassFile1->field_info_table;
        }
        
        while (pFieldTable != NULL) {
            
            pNameField = (char *) pClassFile1->constant_pool_table[pFieldTable->name_index - 1].info.Utf8.bytes;
            if (strcmp(pNameField, pFieldName) == 0) {
                if ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC) i++;
                pFieldTable = pFieldTable->next;
                continue;
            }
            pDescriptorField = (char *) pClassFile1->constant_pool_table[pFieldTable->descriptor_index - 1].info.Utf8.bytes;
            if (strcmp(pDescriptorField, pFieldDescritor)) {
                if ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC) i++;
                pFieldTable = pFieldTable->next;
                continue;
            }
            if ((pFieldTable->access_flags & ACC_STATIC) != ACC_STATIC){
                pFieldTable = pFieldTable->next;
                continue;
            }
            break;
        }
        if (pFieldTable != NULL) {
            break;
        }
        if (pClassFile1->super_class == 0) {
            return var;
        }
        else{
            strcpy(pNomeClasse, pClassFile1->nomeSuperClasse);
        }
    }
    
    pClassHeap = pJVM->heap->classes;
    while (pClassHeap != NULL) {
        if (!(strcmp(pClassHeap->pClassName, pClassName))) break;
        pClassHeap = pClassHeap->next;
    }
    memcpy(var, pClassHeap->field_area + i, sizeof(ST_tpVariable));
    
    return var;
    
}
ST_tpJVM *VM_exucutarJVM(int numeroClasses, char *nomeClasses[]){
    int i, flag1, flag2;

    ST_tpJVM *pJVM;
    ST_tpClassFile *pClasse;
    ST_tpMethod_info *pMetodo;
    
    /* Cria a maquina virtual, a area de metodos, o heap e uma thread*/
    pJVM = VM_criarJVM();
    
    
    /* Carregando classes na JVM */
    for(i = 0; i < numeroClasses; i++){
        ST_tpClassFile *pClasse= LE_carregarClasse(nomeClasses[i]);
        if(pClasse != NULL){
            /* Insere classe carregada na lista de classes carregadas da JVM */
            PL_inserirClasseTopo(pJVM, pClasse);
            //VM_alocarMemoriaHeapClasse(pJVM, pClasse->nomeClasse);
        }
        else{
            printf("ERRO AO CARREGAR CLASSE!");
        }
    }
    flag1 = 0;
    flag2 = 0;
    /* Procurando a primeira classe que tem o main */
    for(pClasse = pJVM->methodArea->classFile; pClasse != NULL; pClasse = pClasse->next){
        
        //pMetodo = VM_procurarMetodo( pClasse, "()V", "<init>");
        //pMetodo = VM_procurarMetodo( pClasse, "([Ljava/lang/String;)V", "main");
        pMetodo = VM_procurarMetodo( pClasse, "()V", "<clinit>");
        if (pMetodo != NULL){
            
            /* Cria Objeto e insere no topo da lista de objeto do Heap */
            /*pObjeto = VM_criarObjeto(pJVM, pClasse);
            if(pJVM->heap->objects == NULL){
                pJVM->heap->objects = pObjeto;
            }
            else{
                pObjeto->next = pJVM->heap->objects;
                pJVM->heap->objects = pObjeto;
            } */
            
            
            
            // LEMBRAR DE RESGARAR OS PARAMETROS DA MAIN
            ST_tpParameterStack *pPilhaDeParametrosMain = NULL;
            VM_executarMetodo(pJVM, pClasse, pPilhaDeParametrosMain, pMetodo);
        }
        
        
        
        /* Procura metodo <init> e o executa
        for(i = 0; i < pClasse->methods_count; i++){
            nameIndex = pClasse->method_info_table[i].name_index-1;
            descritorIndex = pClasse->method_info_table[i].descriptor_index-1;
            name = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
            descritor = (char *)  pClasse->constant_pool_table[descritorIndex].info.Utf8.bytes;
            // Duvida, o descritor deve ser ()V ou deve ser (I)V?
            //if(strcmp(name, "<init>") == 0 && strcmp(descritor, "(I)V") == 0 && pClasse->method_info_table[i].access_flags == ACC_PUBLIC){
            if(strcmp(name, "dividir") == 0 && strcmp(descritor, "(II)I") == 0 && pClasse->method_info_table[i].access_flags == ACC_PUBLIC_STATIC){
                printf("\n Executa metodo <init>\n");
                VM_executarMetodo(pJVM, pClasse, &pClasse->method_info_table[i]);
                flag1 = 1;
                break;
            }
        } */
        /* Procura metodo main e o executa */
        
        
        if(flag1 && flag2){
            break;
        }
    }
    
    return pJVM;
}
