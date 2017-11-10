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
}


ST_tpVariable VM_recuperarVariavel(ST_tpVariable *pVariaveisLocais, int posicao){
    ST_tpVariable varTemporaria;
    
    memcpy((void *)&varTemporaria, (void*)(pVariaveisLocais + posicao), sizeof(varTemporaria));
    
    return varTemporaria;
}


ST_tpStackFrame *VM_criarStackFrame(ST_tpStackFrame *pJVMStack, long maxStackSize){
    int i;
    ST_tpVariable varTemporaria;
    
    pJVMStack = (ST_tpStackFrame *) malloc(sizeof(ST_tpStackFrame));
    pJVMStack->operandStack     = PL_criarPilhaOperandos();
    pJVMStack->parameterStack   = PL_criarPilhaParametros(); // AINDA NAO ESTA RECEBENDO OS PARAMETROS PASSADOS PELO METODO
    pJVMStack->localVariables   = (ST_tpVariable *) malloc(sizeof(ST_tpVariable)*(maxStackSize));
    
    varTemporaria.tipo          = JREF;
    varTemporaria.valor.obj_ref = NULL;
    VM_armazenarVariavel(pJVMStack->localVariables, varTemporaria, 0);
    
    i = 0;
    while(pJVMStack->parameterStack != NULL){
        
        varTemporaria = PL_popParametro(pJVMStack->parameterStack);
        VM_armazenarVariavel(pJVMStack->localVariables, varTemporaria, i);
        i++;
        if(varTemporaria.tipo == JLONG || varTemporaria.tipo == JDOUBLE) i++;
    }
    
    return pJVMStack;
}

void VM_executarMetodo(ST_tpThread *pThread, ST_tpClassFile *pClasse, ST_tpMethod_info *pMetodo){
    int i;
    u1* end;
    u2 nameIndex;
    char *name;
    ST_tpCode_attribute *pCode;
    ST_tpStackFrame *pFrame;
    
    for(i = 0; i < pMetodo->attributes_count; i++){
        nameIndex = pMetodo->attributes[i].attribute_name_index-1;
        name = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
        
        if(strcmp(name, "Code") == 0){
            
            /* Cria uma Stack Frame */
            pFrame = VM_criarStackFrame(pThread->pJVMStack, ((ST_tpCode_attribute*)pMetodo->attributes[i].info)->max_locals);
            
            /* Se a pilha de Frames da Thread ainda estiver vazia
            if(pJVM->thread->pFrameStack == NULL){
                pJVM->thread->pFrameStack = (ST_tpPilha *) malloc(sizeof(ST_tpPilha));
                pJVM->thread->pFrameStack->dado = pFrame;
                pJVM->thread->pFrameStack->prox = NULL;
            }
            else{  Caso a pilha de Frames da Thread ainda nao estijavazia
                PL_push(&pJVM->thread->pFrameStack, pFrame);  Insere Frame na lista de Frames da Thread
            } */
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
            
            pThread->PC = (u1 *)pCode->code;
            end = pThread->PC + pCode->code_length;
            while(pThread->PC < end){
                IT_executaInstrucao(pThread); // VERIFICAR ONDE EXECUTA AS EXCESSOES
                pThread->PC++;
            }
            
            // VERIFICAR COMO FAZER O RETORNO DA FUNCAO
        }
    }
}

ST_tpMethod_info *VM_procurarMetodo(ST_tpClassFile *pClassFile, char *descritorMetodo, char *nomeMetodo) {
    char *name, *descritor;
    u2 nameIndex, descritorIndex;
    
    for(int i = 0; i < pClassFile->methods_count; i++){
        nameIndex = pClassFile->method_info_table[i].name_index-1;
        descritorIndex = pClassFile->method_info_table[i].descriptor_index-1;
        name = (char *) pClassFile->constant_pool_table[nameIndex].info.Utf8.bytes;
        descritor = (char *)  pClassFile->constant_pool_table[descritorIndex].info.Utf8.bytes;
        
        if(strcmp(name, nomeMetodo) == 0 && strcmp(descritor, descritorMetodo) == 0 && pClassFile->method_info_table[i].access_flags == ACC_PUBLIC_STATIC){ // VERIFICAR SOBRE A FLAG DE ACESSO
            return &pClassFile->method_info_table[i];    
        }
    }
    return NULL;
}
ST_tpObjectHeap *VM_criarObjeto(ST_tpJVM *pJVM, ST_tpClassFile *pClassFile){
    int maxVariaveis;
    char *nome;
    ST_tpClassFile *pClasseAux;
    ST_tpObjectHeap *pObjeto = (ST_tpObjectHeap *)malloc(sizeof(ST_tpObjectHeap));
    
    maxVariaveis = pClassFile->fields_count;
    
    while(pClassFile->super_class != 0 ){
        nome = (char*) pClassFile->constant_pool_table[pClassFile->super_class].info.Utf8.bytes;
        pClasseAux = PL_buscarClasse(pJVM, nome);
        
        /* Carregar Super Classe */
        if(pClasseAux == NULL){
            pClasseAux = LE_carregarClasse(nome);
            /* Insere classe carregada na lista de classes carregadas da JVM */
            PL_inserirClasseTopo(pJVM, pClasseAux);
        }
        maxVariaveis += pClasseAux->fields_count;
    }
    wcscpy(pObjeto->pClasseName, (wchar_t *)pClassFile->constant_pool_table[pClassFile->this_class].info.Utf8.bytes);
    pObjeto->field_area = (ST_tpVariable *)malloc(sizeof(ST_tpVariable) * (maxVariaveis + 1));
    pObjeto->thread = pJVM->thread;
    pObjeto->max_var = maxVariaveis;
    pObjeto->ref_count = 0;
    pObjeto->next = NULL;
    
    return pObjeto;
}

ST_tpJVM *VM_exucutarJVM(int numeroClasses, char *nomeClasses[]){
    int i, flag1, flag2;

    ST_tpJVM *pJVM;
    ST_tpClassFile *pClasse;
    ST_tpObjectHeap *pObjeto;
    ST_tpMethod_info *pMetodo;
    
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
        
        pMetodo = VM_procurarMetodo( pClasse, "(I)V", "<init>");
        if (pMetodo != NULL){
            pObjeto = VM_criarObjeto(pJVM, pClasse);
            
            // FALTA INSERIR OBJETO NA PILHA DE HEAP
            
            VM_executarMetodo(pJVM->thread, pClasse, pMetodo);
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
