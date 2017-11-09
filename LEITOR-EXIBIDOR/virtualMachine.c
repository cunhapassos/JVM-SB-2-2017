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
    pThread->pFrameStack = NULL;
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

ST_tpFrame *VM_criarFrame(ST_tpClassFile *pClasse){

    ST_tpFrame *pFrame = (ST_tpFrame *) malloc(sizeof(ST_tpFrame));
    
    pFrame->operandStack = PL_criarPilhaOperandos();
    pFrame->localVariablesStack = PL_criarPilhaVariaveisLocais();
    pFrame->cp = pClasse;
    
    return pFrame;
}

void VM_executarMetodo(ST_tpJVM *pJVM, ST_tpClassFile *pClasse, ST_tpMethod_info *pMetodo){
    int i, j;
    u1* opcode;
    u2 nameIndex;
    char *name;
    ST_tpCode_attribute *pCode;
    ST_tpFrame *pFrame;
    
    for(i = 0; i < pMetodo->attributes_count; i++){
        nameIndex = pMetodo->attributes[i].attribute_name_index-1;
        name = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
        
        if(strcmp(name, "Code") == 0){
            
            /* Cria uma Frame para ser inserido na lista de Frames da thread */
            pFrame = VM_criarFrame(pClasse);
            
            /* Se a pilha de Frames da Thread ainda estiver vazia */
            if(pJVM->thread->pFrameStack == NULL){
                pJVM->thread->pFrameStack = (ST_tpPilha *) malloc(sizeof(ST_tpPilha));
                pJVM->thread->pFrameStack->dado = pFrame;
                pJVM->thread->pFrameStack->prox = NULL;
            }
            else{ /* Caso a pilha de Frames da Thread ainda nao estijavazia */
                PL_push(&pJVM->thread->pFrameStack, pFrame); /* Insere Frame na lista de Frames da Thread */
            }
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
            for(j = 0; j < pCode->code_length; j++ ){
                memcpy(&opcode, pJVM->thread->PC, 1);
                //IT_executaInstrucao(pJVM->thread); // VERIFICAR ONDE EXECUTA AS EXCESSOES
                pJVM->thread->PC++;
            }
        }
    }
}

ST_tpJVM *VM_exucutarJVM(int numeroClasses, char *nomeClasses[]){
    int i, flag1, flag2;
    char *name, *descritor;
    u2 nameIndex, descritorIndex;
    ST_tpJVM *pJVM;
    ST_tpClassFile *pClasse;
    
    /* Cria a maquina virtual, a area de metodos, o heap e uma thread*/
    pJVM = VM_criarJVM();
    
    /* Carregando classes na JVM */
    for(i = 0; i < numeroClasses; i++){
        ST_tpClassFile *pClasse= LE_carregarClasse(nomeClasses[i]);
        /* Insere classe carregada na lista de classes carregadas da JVM */
        PL_inserirClasseTopo(pJVM, pClasse);
    }
    flag1 = 0;
    flag2 = 0;
    /* Procurando a primeira classe que tem o main */
    for(pClasse = pJVM->methodArea->classFile; pClasse != NULL; pClasse = pClasse->next){
        
        /* Procura metodo <init> e o executa */
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
        }
        /* Procura metodo main e o executa */
        for(i = 0; i < pClasse->methods_count; i++){
            nameIndex = pClasse->method_info_table[i].name_index-1;
            descritorIndex = pClasse->method_info_table[i].descriptor_index-1;
            name = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
            descritor = (char *)  pClasse->constant_pool_table[descritorIndex].info.Utf8.bytes;
            
            if(strcmp(name, "main") == 0 && strcmp(descritor, "([Ljava/lang/String;)V") == 0 && pClasse->method_info_table[i].access_flags == ACC_PUBLIC_STATIC){
                printf("\n Executa metodo main\n");
                VM_executarMetodo(pJVM, pClasse, &pClasse->method_info_table[i]);
                flag1 = 1;
                break;
            }
        }
        
        if(flag1 && flag2){
            break;
        }
    }
    
    return pJVM;
}
