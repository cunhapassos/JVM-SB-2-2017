   /** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO VIRTUAL_MACHINE
 *  @{
 *  @ingroup MOD_VM
 *
 *  @file virtualMachine.c
 *  @brief
 *            Implementacao das estruturas de incicialização da JVM
 *
 * @author ALON MOTA        - MAT. 13/0005002
 * @author DANIEL MATIAS    - MAT. 12/0139804
 * @author GABRIEL TOLLINI  - MAT. 14/0020454
 * @author PAULO PASSOS     - MAT. 10/0118577
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

/**
 *  Descricao da funcao:
 *       Aloca memória para um método
 *
 *  @return pAreaMetodo - Endereço da área alocada para o método
 */
ST_tpMethodArea *VM_criarAreaMetodo(){
    ST_tpMethodArea *pAreaMetodo;
    
    pAreaMetodo = malloc(sizeof(ST_tpMethodArea));
    pAreaMetodo->classFile = NULL;
    
    return pAreaMetodo;
}

/**
 *  Descricao da funcao:
 *       Aloca memória para um Heap
 *
 *  @return pHeap - Endereço da área alocada para o Heap
 */
ST_tpHeap *VM_criarHeap(){
    ST_tpHeap *pHeap;
    
    pHeap = malloc(sizeof(ST_tpHeap));
    pHeap->array = NULL;
    pHeap->classes = NULL;
    pHeap->objects = NULL;
    
    return pHeap;
}
/**
 *  Descricao da funcao:
 *       Aloca memória para uma Thread
 *
 *  @return pThread - Endereço da área alocada para a Thread
 */
ST_tpThread *VM_criarThread(){
    ST_tpThread *pThread;
    
    pThread = malloc(sizeof(ST_tpThread));
    pThread->pJVMStack = NULL;
    pThread->PC = 0;
    
    return pThread;
}
/**
 *  Descricao da funcao:
 *       Aloca memória para a JVM, e a inicializa
 *
 *  @return pHeap - Endereço da área alocada para a JVM
 */
ST_tpJVM *VM_criarJVM(){
    ST_tpJVM *pJvm;
    
    pJvm = malloc(sizeof(ST_tpJVM));
    pJvm->heap = VM_criarHeap();
    pJvm->methodArea = VM_criarAreaMetodo();
    pJvm->thread = VM_criarThread();
    
    return pJvm;
}
/**
 *  Descricao da funcao:
 *       Armazena uma variável na lista de variáveis locais
 *
 *  @param  pVariaveisLocais - Endereço base da lista de variáveis locais
 *  @param  variavel - variável a ser adicionada na lista
 *  @param  posicao - deslocamento a partir do endereço base onde será salva a variável
 *
 */
void VM_armazenarVariavel(ST_tpVariable *pVariaveisLocais, ST_tpVariable variavel, int posicao){
    memcpy((void *)(pVariaveisLocais + posicao), (void *) &variavel, sizeof(variavel));
}
/**
 *  Descricao da funcao:
 *       Lê a variável em uma certa posição na lista de variáveis locais
 *
 *  @param  pVariaveisLocais - Endereço base da lista de variáveis locais
 *  @param  posicao - deslocamento a partir do endereço base de onde será lida a variável 
 *
 *  @return varTemporaria - variável lida
 */

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
ST_tpStackFrame *VM_criarFrame(ST_tpJVM *pJVM, ST_tpStackFrame **pJVMStack, ST_tpClassFile *pClasse, ST_tpParameterStack *pilhaParametros, int maxStackSize, u2 access_flag){
    int i = 0;
    ST_tpVariable varTemporaria;
    ST_tpStackFrame *pFrame;
    
    pFrame = (ST_tpStackFrame *) malloc(sizeof(ST_tpStackFrame));
    pFrame->cp              = pClasse;
    pFrame->next            = NULL;
    pFrame->operandStack    = NULL;
    pFrame->parameterStack  = NULL;
    pFrame->localVariables  = (ST_tpVariable *) malloc(sizeof(ST_tpVariable) * (maxStackSize + 1));
    
    /****************************************************
     *   Verifica se eh um metodo de instancia          *
     *   Se for coloca o objeto this referente a        *
     *   classe que contem o metodo corrente na         *
     *   posicao 0 do vetor de variaveis locais         *
     ****************************************************/
    /*if ((access_flag & ACC_STATIC) != ACC_STATIC) {
        varTemporaria.tipo          = JREF;
        varTemporaria.valor.obj_ref = 0;
        VM_armazenarVariavel(pFrame->localVariables, varTemporaria, 0);
        i = 1;
    }*/
    
    /****************************************************
     *  Caso seja um metodo de instancia o this ocupa   *
     *  a posicao 0 do vetor de variaveis locais e o    *
     *  primeiro parametro a posicao 1, caso contratio  *
     *  o primeiro paramentro ocupa a posicao 0         *
     ****************************************************/
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
/**
* Descrição da função:
*       Executa um método
*
* @param pJVM            - Ponteiro para a JVM
* @param pClasse         - Classe de onde são lidos os dados para a execução
* @param pilhaParametros - Pilha de parametros que é passada para o metodo que sera executado
* @param pMetodo         - Método a ser executado
*
* @return                - Retorna o resultado, caso a instrução seja return
**/
ST_tpVariable *VM_executarMetodo(ST_tpJVM *pJVM, ST_tpClassFile *pClasse, ST_tpParameterStack *pilhaParametros, ST_tpMethod_info *pMetodo){
    int i, flag, numeroVariaveis, tipoRetorno;
    u1 *end, *PC;
    char *name;
    u1 *descritorMetodo;
    u2 nameIndex, access_flag;
    ST_tpStackFrame *pFrame;
    ST_tpVariable *pRetorno;
    ST_tpCode_attribute *pCode;
    
    pRetorno = (ST_tpVariable*)malloc(sizeof(ST_tpVariable));
    pRetorno->tipo = JVOID;
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
        
        access_flag = pMetodo->access_flags;
        nameIndex   = pMetodo->attributes[i].attribute_name_index-1;
        name        = (char *) pClasse->constant_pool_table[nameIndex].info.Utf8.bytes;
       descritorMetodo = (pClasse->constant_pool_table[pMetodo->descriptor_index-1].info.Utf8.bytes);
        tipoRetorno = retornarTipoRetorno(descritorMetodo);
        pRetorno->tipo = tipoRetorno;
        
        if(strcmp(name, "Code") == 0){
            numeroVariaveis = ((ST_tpCode_attribute*)pMetodo->attributes[i].info)->max_locals;
            /* Cria uma Stack Frame */
            pFrame = VM_criarFrame(pJVM, &(pJVM->thread->pJVMStack), pClasse, pilhaParametros,  numeroVariaveis, access_flag);
            
            
            // EXECUTAR CODIGO //
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
            
            PC = (u1 *)pCode->code;
            end = PC + (pCode->code_length - 1);
            
            

            while(PC <= end){
                flag = IT_executaInstrucao(pJVM, &pFrame, &pRetorno, pCode->exception_table, &PC);
                if (flag == 1){
                    PC = end;
                    break; // Testa se está vindo de um return
                }
                PC++;
            }

          /*SaidaDoMetodo:
            while (pFrame->operandStack != NULL) {
                pRetorno = PL_popOperando(&pFrame->operandStack);
            }*/

        }
    }
    return pRetorno;
}

/**
* Descrição da função:
*       Busca um método pelo seu nome e descritor
*
* @param pClasseFile     - ClassFile onde se procurará o método
* @param descritorMetodo - Descritor do método a ser procurado
* @param nomeMetodo      - Nome do método a ser procurado
*
* @return NULL                              - Se o método não foi encontrado
*         pClassFile->method_info_table[i]  - Tabela contendo as informações do método procurado
**/

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

/**
* Descrição da função:
*       Dado um ClassFile, retorna o nome de sua Super Classe
*
* @param pClasseFile        - ClassFile de onde se lerá o nome da Super Classe
*
* @return superClasseString - O nome da Super Classe
*         
**/

u1 *VM_retornaNomeSuperClasse(ST_tpClassFile *pClassFile){
    u1 *superClasseString;
    u2 classNameIndex;
    u2 superClassIndex;
    
    superClassIndex     = pClassFile->super_class;
    classNameIndex      = pClassFile->constant_pool_table[superClassIndex -1].info.Class.name_index;
    superClasseString   = (u1 *)pClassFile->constant_pool_table[classNameIndex - 1].info.Utf8.bytes;
    
    return superClasseString;
}
/**
* Descrição da função:
*       Dado um ClassFile, retorna o nome de sua Classe
*
* @param pClasseFile        - ClassFile de onde se lerá o nome da Classe
*
* @return superClasseString - O nome da Classe
*         
**/
u1 *VM_retornarNomeClasse(ST_tpClassFile *pClassFile){
    u1 *classeString;
    u2 classNameIndex;
    u2 classIndex;
    
    classIndex      = pClassFile->this_class;
    classNameIndex  = pClassFile->constant_pool_table[classIndex -1].info.Class.name_index;
    classeString    = (u1 *)pClassFile->constant_pool_table[classNameIndex - 1].info.Utf8.bytes;
    
    return classeString;
}
/**
* Descrição da função:
*       Aloca a memória de um Heap para objeto, e o inicializa
*
* @param  pJVM          - Ponteiro para a JVM
* @param  pClasseFile   - ClassFile de onde se lerá o alguns dos dados do objeto
*
* @return NULL          - Caso haja erro ao carregar a classe
*         pObjeto       - Endereço do Heap para objeto alocado
*         
**/
ST_tpObjectHeap *VM_alocarMemoriaHeapObjeto(ST_tpJVM *pJVM, ST_tpClassFile *pClassFile){
    u1 *nome;
    int maxVariaveis;
    ST_tpObjectHeap *pObjeto;
    ST_tpClassFile *pAuxClassFile1, *pAuxClassFile2;
    
    /*
    pObjeto = PL_buscaObjetoHeap(pJVM->heap->objects, pClassFile->nomeClasse);
    if(pObjeto != NULL){
        return pObjeto;
    }*/
    
    pObjeto = (ST_tpObjectHeap *)malloc(sizeof(ST_tpObjectHeap));
    
    pAuxClassFile1 = pClassFile;
    maxVariaveis = pClassFile->fields_count;
    
    while(pAuxClassFile1->super_class != 0 ){
        nome = VM_retornaNomeSuperClasse(pAuxClassFile1);
        /* Verifica se a SuperClasse esta carregada */
        pAuxClassFile2 = PL_buscarClasse(pJVM, (char *) nome);
        
        /* Se nao estiver carragada, carrega */
        if(pAuxClassFile2 == NULL){
            
            pAuxClassFile2 = LE_lerClasse((char *)nome);
            if(pAuxClassFile2 != NULL){
                pAuxClassFile2 = VM_carregarClasse((char *)nome, pJVM);
            }
            else{
                printf("ERRO AO CARREGAR CLASSE");
                return NULL;
            }
            maxVariaveis += pAuxClassFile2->fields_count;
        }
        pAuxClassFile1 = pAuxClassFile2;
    }
    pObjeto->field_area = (ST_tpVariable *)malloc(sizeof(ST_tpVariable ) * (maxVariaveis + 1));

    pObjeto->className = malloc(sizeof(char) * strlen(pClassFile->nomeClasse) + 1);
    strcpy(pObjeto->className, pClassFile->nomeClasse);
    //printf("\n %s \n", pObjeto->className);
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

/**
* Descrição da função:
*       Busca um objeto, pelo seu nome, na pilha de Objetos
*
* @param  pObejectHeap  - Pilha de Objetos
* @param  nomeObjeto    - Nome do objeto a ser buscado
*
* @return pObejec       - Endereço do objeto buscado
*         
*         
**/

ST_tpObjectHeap *VM_recuperarObjeto(ST_tpObjectHeap *pObejectHeap, char *nomeObjeto){
    ST_tpObjectHeap *pObejec;
    
    pObejec = pObejectHeap;
    while (pObejec != NULL) {
        if(strcmp(pObejec->className, nomeObjeto) == 0) break;
        pObejec = pObejec->next;
    }
    return pObejec;
}

/**
* Descrição da função:
*       Aloca memória para um Array e o inicializa
*
* @param  tipo          - Tipo do Array a ser inicializado
* @param  nomeClasse    - Valor que será colocado no atributo className
* @param  tamanho       - Tamanho do Array a ser alocado
*
* @return pArray        - Endereço do Array alocado e inicializado
*         
*         
**/

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
    pArray->className = (char *)malloc(sizeof(char) * strlen(nomeClasse) + 1);
    strcpy(pArray->className, nomeClasse);
    pArray->length = tamanho;
    pArray->type = tipo;
    pArray->ref_count = 0;
    
    return pArray;
    
}

/**
* Descrição da função:
*       Adiciona um novo termo a um array
*
* @param  pArray        - Arrays aonde será adicionado o novo termo 
* @param  posicao       - Posição do Array aonde será adicionado o novo termo
* @param  variavel      - Termo que será adicionado
*
*         
*         
**/

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
            if (variavel.valor.obj_ref == NULL) {
                pObjRef = NULL;
            }
            else{
                memcpy((void *)pObjRef, (void *)variavel.valor.obj_ref, sizeof(ST_tpObjectHeap));
                
            }
            break;
        case T_AREF:
            pArrayRef  = (ST_tpArrayHeap *)pArray->area;
            pArrayRef += posicao;
            memcpy((void *)pArrayRef, (void *)variavel.valor.array_ref, sizeof(ST_tpArrayHeap));
            break;
    }
}
/**
* Descrição da função: 
*       Aloca memória para um Array multiplo e o inicializa 
*
* @param  nomeClasse        - Nome da classe lida
* @param  pPilhaOperandos   - Pilha de operandos
* @param  dimensao          - Tamanho do Array a ser alocado
*
* @return pArray            - Endereço do Array alocado e inicializado
*         
*         
**/

ST_tpArrayHeap *alocarMemoriaArrayMulti(char *nomeClasse, ST_tpOperandStack *pPilhaOperandos, int dimensao){
    int tipo, i;
    char *aux, *nome = NULL;
    ST_tpArrayHeap *pArray, *pArray1;
    ST_tpVariable *var, varAux;
    
    
    aux = strchr(nomeClasse, '[');

    if (aux == 0) {
        tipo = retornarTipoString(nomeClasse);
//        if (tipo == T_REF) {
//            aux = nomeClasse;
//            aux++;
//            memset(nome, 0, strlen(aux));
//            memcpy((void *) nome, (void *) nomeClasse, strlen(aux)-1);
//        }
        pArray = VM_criarArray(tipo, nomeClasse, dimensao);
        
        return pArray;
    }
    else{
        aux++;
        var = PL_popOperando(&pPilhaOperandos);
        varAux.tipo = T_AREF;
        
        pArray1 = VM_criarArray(T_AREF, nomeClasse, dimensao);
        for (i = 0; i < dimensao; i++) {
            pArray = alocarMemoriaArrayMulti(aux, pPilhaOperandos, var->valor.Int);
            varAux.valor.array_ref = pArray; // Testar se está correto
            VM_armazenarValorArray(pArray1, i, varAux);
        }
        var->tipo = JINT;
        PL_pushOperando(&pPilhaOperandos, varAux);
        
        return pArray1;
    }
}

/**
* Descrição da função:
*       Dada uma string, retorna o seu tipo
*
* @param  string        - String a ser analizada
*
* @return               - Tipo da String
*         
**/
int retornarTipoString(char *string){
    char aux;
    int tam;
    
    tam = (int) strlen(string);
    
    for (int i = 0; i < tam; i++) {
        aux = string[i];
        switch (aux) {
            case 'B':
                return 8;
            case 'C':
                return 5;
            case 'D':
                return 7;
            case 'F':
                return 6;
            case 'I':
                return 10;
            case 'J':
                return 11;
            case 'L':
                return 12;
            case 'S':
                return 9;
            case 'Z':
                return 4;
        }
    }
    return 0;
}

int retornarTipoRetorno(u1 *descritor){
    char aux;
    int i = 0;
    do {
        aux = descritor[i];
        i++;
    } while (aux != ')');
    
    aux = descritor[i];
    switch (aux) {
        case 'B':
            return 8;
        case 'C':
            return 5;
        case 'D':
            return 7;
        case 'F':
            return 6;
        case 'I':
            return 10;
        case 'J':
            return 11;
        case 'L':
            return 12;
        case 'S':
            return 9;
        case 'Z':
            return 4;
        case 'V':
            return 5;
    }
    return 5;
}
/**
* Descrição da função:
*       Retorna o valor em uma dada posição de um Array
*
* @param  pArrayHeap    - Array a ser lido
* @param  posicao       - Posição do valor a ser lido
*
* @return var           - Valor lido
*         
**/
ST_tpVariable VM_recuperarValorArray(ST_tpArrayHeap *pArrayHeap, int posicao){
    
    u2 *pChar;
    int *pInt;
    float *pFloat;
    double *pDouble;
    int64_t *pLong;
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
            memcpy((void *)&(var.valor.Byte), (void *)pByte, sizeof(var.valor.Byte));
            break;
        case T_LONG:
            pLong  = (__int64_t *)pArrayHeap->area;
            pLong += posicao;
            var.tipo = JLONG;
            memcpy((void *)&(var.valor.Long), (void *)pLong, sizeof(var.valor.Long));
            break;
        case T_BOOLEAN:
            pBoolean  = (char*) pArrayHeap->area;
            pBoolean += posicao;
            var.tipo = JBOOL;
            memcpy((void *)&(var.valor.Boolean), (void *)pBoolean, sizeof(var.valor.Boolean));
            break;
        case T_CHAR:
            pChar  = (u2*)pArrayHeap->area;
            pChar += posicao;
            var.tipo = JCHAR;
            memcpy((void *)&(var.valor.Char), (void *)pChar, sizeof(var.valor.Char));
            break;
        case T_SHORT:
            pShort  = (short int  *)pArrayHeap->area;
            pShort += posicao;
            var.tipo = JSHORT;
            memcpy((void *)&(var.valor.Short), (void *)pShort, sizeof(var.valor.Short));
            break;
        case T_FLOAT:
            pFloat  = (float *)pArrayHeap->area;
            pFloat += posicao;
            var.tipo = JFLOAT;
            memcpy((void *)&(var.valor.Float), (void *)pFloat, sizeof(var.valor.Float));
            break;
        case T_INT:
            pInt  = (int *)pArrayHeap->area;
            pInt += posicao;
            memcpy((void *)&(var.valor.Int), (void *)pInt, sizeof(var.valor.Int));
            var.tipo = JINT;
            break;
        case T_DOUBLE:
            pDouble  = (double *)pArrayHeap->area;
            pDouble += posicao;
            var.tipo = JDOUBLE;
            memcpy((void *)&(var.valor.Double), (void *)pDouble, sizeof(var.valor.Double));
            break;
        case T_REF:
            
            pObjRef  = (ST_tpObjectHeap *)pArrayHeap->area + posicao;
            //pObjRef += posicao;
            var.tipo = JREF;
            var.valor.obj_ref = (ST_tpObjectHeap *) malloc(sizeof(ST_tpObjectHeap));
            memcpy((void*)var.valor.obj_ref, (void*)pObjRef, sizeof(ST_tpObjectHeap));
            break;
        case T_AREF:
            pArrayRef  = (ST_tpArrayHeap *)pArrayHeap->area;
            pArrayRef += posicao;
            var.tipo = JAREF;
            var.valor.array_ref = (ST_tpArrayHeap*) malloc(sizeof(ST_tpArrayHeap));
            memcpy((void*)var.valor.array_ref, (void*)pArrayRef, sizeof(ST_tpArrayHeap));
            break;
    }
    return var;
}
/**
* Descrição da função: 
*       Armazena o valor de um Field
*
* @param  pJVM              - Ponteiro para a JVM
* @param  pClassName        - Nome da classe lida 
* @param  pFieldName        - Nome do Field a ser salvo 
* @param  pFieldDescriptor  - Descritor do Field a ser salvo
* @param  var               - Área do Field
* @param  objRef            - Referencia para o objeto lido
*
* @return NULL             - Em caso de erro
*         pHeap            - Ponteiro para o Heap de objeto ?
*         
**/
void *VM_armazenarValorField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescriptor, ST_tpVariable var, ST_tpVariable objRef){
    int i = 0;
    ST_tpObjectHeap *pHeap;
    ST_tpField_info *pFieldTable;
    ST_tpClassFile *pClassFile;
    char *pNomeClasse = NULL, *pNameField, *pDescriptorField;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);
    
    strcpy(pNomeClasse, pClassName);
    
    if(objRef.valor.obj_ref == 0){
        return NULL; // Lancar um erro
    }
    
    while (TRUE) {
        pClassFile = PL_buscarClasse(pJVM, pNomeClasse);
        if(pClassFile == NULL){
            pClassFile = VM_carregarClasse((char*)pNomeClasse, pJVM);
        }
        pFieldTable = pClassFile->field_info_table;
        while (pFieldTable != NULL) {
            pNameField = (char *)(pClassFile->constant_pool_table[pFieldTable->name_index - 1].info.Utf8.bytes);
            pDescriptorField = (char *)pClassFile->constant_pool_table[pFieldTable->descriptor_index-1].info.Utf8.bytes;
            
             if (strcmp(pNameField, pFieldName) == 0 && strcmp(pDescriptorField, pFieldDescriptor) == 0 && ((pFieldTable->access_flags & ACC_STATIC) != ACC_STATIC)){
                 break;
            }
            
            if ((pFieldTable->access_flags & ACC_STATIC) != ACC_STATIC) {
                i++;
                pFieldTable = pFieldTable->next;
                continue;
            }
            
            if((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC){
                pFieldTable = pFieldTable->next;
                continue;
            }
            break;
        }
        if (pFieldTable != NULL) {
            break;
        }
        if (pClassFile->super_class == 0) {
            break;
        }
        else{
            strcpy(pNomeClasse, pClassFile->nomeSuperClasse);
        }
    }

    pHeap = (ST_tpObjectHeap *)objRef.valor.obj_ref;
    memcpy((pHeap->field_area + i), &var, sizeof(var));
    
    return pHeap;
}
/**
* Descrição da função: ?????
*       Retorna o valor em uma dada posição de um Array
*
* @param pJVM           - Ponteiro para a JVM
* @param  pArrayHeap    - Array a ser lido
* @param  posicao       - Posição do valor a ser lido
*
* @return NULL          - Em caso de erro 
*         var           - Valor lido
*         
**/
ST_tpVariable *VM_recuperarValorField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescriptor, ST_tpVariable *objRef){

    int i = 0;
    ST_tpVariable *var = NULL;
    ST_tpObjectHeap *pHeap;
    ST_tpField_info *pFieldTable;
    ST_tpClassFile *pClassFile;
    //ST_tpVariable objRef;
    char *pNomeClasse = NULL, *pNameField, *pDescriptorField;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);

    //objRef.tipo = JREF;
    //objRef.valor.obj_ref = PL_buscaObjetoHeap(pJVM->heap->objects, pClassName);

    strcpy(pNomeClasse, pClassName);
    
    if(objRef->valor.obj_ref == 0){
        return NULL; // Lancar um erro
    }

    while (TRUE) {
        pClassFile = PL_buscarClasse(pJVM, pNomeClasse);
        if(pClassFile == NULL){
            pClassFile = VM_carregarClasse((char*)pNomeClasse, pJVM);
        }
        pFieldTable = pClassFile->field_info_table;
        while (pFieldTable != NULL) {
            pNameField = (char *)(pClassFile->constant_pool_table[pFieldTable->name_index - 1].info.Utf8.bytes);
            pDescriptorField = (char *)pClassFile->constant_pool_table[pFieldTable->descriptor_index-1].info.Utf8.bytes;
            
            if (strcmp(pNameField, pFieldName) == 0 && strcmp(pDescriptorField, pFieldDescriptor) == 0 && ((pFieldTable->access_flags & ACC_STATIC) != ACC_STATIC)){
                break;
            }
            
            if ((pFieldTable->access_flags & ACC_STATIC) != ACC_STATIC) {
                i++;
                pFieldTable = pFieldTable->next;
                continue;
            }
            
            if((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC){
                pFieldTable = pFieldTable->next;
                continue;
            }
            break;
        }
        if (pFieldTable != NULL) {
            break;
        }
        if (pClassFile->super_class == 0) {
            printf("ERRO! FIELD NAO ENCONTRADO!");
            return NULL;
        }
        else{
            strcpy(pNomeClasse, pClassFile->nomeSuperClasse);
        }
    }
    
    pHeap = (ST_tpObjectHeap *)objRef->valor.obj_ref;
    var = (ST_tpVariable*)malloc(sizeof(ST_tpVariable));
    memcpy(var, (pHeap->field_area + i), sizeof(ST_tpVariable));
    
    return var;
}
/**
* Descrição da função: 
*       Aloca memória e inicializa um Heap de Classes
*
* @param  pJVM          - Ponteiro para a JVM
* @param  pClassName    - Nome da Classe com a qual se inicializará os valores da memória alocada
*
* @return pClassHeap    - Endereço aonde se alocou a memória
*         
**/
void *VM_alocarMemoriaHeapClasse(ST_tpJVM *pJVM, char *pClassName){
    
    int maxStaticVar = 0;
    char *pNomeClasse;
    ST_tpClassHeap *pClassHeap;
    ST_tpField_info *pFieldTable;
    ST_tpClassFile *pClassFile1, *pClassFile2;
    
    pClassFile1 = PL_buscarClasse(pJVM, pClassName);
    pClassHeap = PL_buscaClassHeap(pJVM->heap->classes, pClassName);


    if (pClassHeap != NULL) {
        return pClassHeap;
    }
    
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
        
        pClassFile2 = PL_buscarClasse(pJVM, pNomeClasse);
    
        if (pClassFile2 == NULL) {
            pClassFile2 = VM_carregarClasse((char*)pNomeClasse, pJVM);
        }
        pClassFile1 = pClassFile2;
    }
    pClassHeap = (ST_tpClassHeap *)malloc(sizeof(ST_tpClassHeap));
    pClassHeap->pClassName = (char *)malloc(strlen(pClassName)+2);
    strcpy(pClassHeap->pClassName, pClassName);
    
    //ATENCAO NA ESTA COMPLETO: Acrescenntar os outros valores de ST_tpFieldHeap
    pClassHeap->field_area = (ST_tpVariable  *)malloc(sizeof(ST_tpVariable ) * (maxStaticVar + 1));
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
}
*/
/**
* Descrição da função: 
*       Armazena valor em campo de Statics ?????
*
* @param  pJVM              - Ponteiro para a JVM
* @param  pClassName        - Nome da Classe que ?
* @param  pFieldName        - Nome do campo que será lido?
* @param  pFieldDescritor   - Descritor do campo que será lido?
* @param  var               - Valor a ser armazenado
*
* @return NULL              - Em caso de erro 
* pJVM->heap->classes       - ?
*         
**/
void *VM_armazenarValorStaticField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescritor, ST_tpVariable var){
    int i = 0;
    ST_tpClassFile *pClassFile1;
    ST_tpClassHeap *pClassHeap = NULL;
    ST_tpField_info *pFieldTable = NULL;
    char *pNomeClasse, *pNameField, *pDescriptorField;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);
    
    strcpy(pNomeClasse, pClassName);
    
    while (TRUE) {
        pClassFile1 = PL_buscarClasse(pJVM, pNomeClasse);
        if (pClassFile1 == NULL) {
            pClassFile1 = VM_carregarClasse((char*)pNomeClasse, pJVM);
        }
        pFieldTable = pClassFile1->field_info_table;
        
        while (pFieldTable != NULL) {
            pNameField = (char *) pClassFile1->constant_pool_table[pFieldTable->name_index-1].info.Utf8.bytes;
            pDescriptorField = (char *) pClassFile1->constant_pool_table[pFieldTable->descriptor_index-1].info.Utf8.bytes;
            
            if (strcmp(pNameField, pFieldName) == 0 && strcmp(pDescriptorField, pFieldDescritor) == 0 && ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC)) {
                break;
            }

            if ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC) {
                i++;
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
            printf("ERRO! FIELD NAO ENCONTRADO!");
            return NULL;
        }
        else{
            strcpy(pNomeClasse, pClassFile1->nomeSuperClasse);
        }
    }
    // Verificar se é mais conveniete fazer essa parte igual ao
    // VM_armazenarValorField
    /*pClassHeap = pJVM->heap->classes;
    while (pClassHeap != NULL) {
        if (!(strcmp(pClassHeap->pClassName, pClassName))) break;
        pClassHeap = pClassHeap->next;
    }*/
    pClassHeap = PL_buscaClassHeap(pJVM->heap->classes, pClassName);
    memcpy(pClassHeap->field_area + i, &var, sizeof(var));
    
    return pJVM->heap->classes;
    
}
/**
* Descrição da função: 
*       Ler valor em campo de Statics ?????
*
* @param  pJVM              - Ponteiro para a JVM
* @param  pClassName        - Nome da Classe que ?
* @param  pFieldName        - Nome do campo que será lido?
* @param  pFieldDescritor   - Descritor do campo que será lido?
*
* @return NULL              - Em caso de erro 
*         var               - Valor lido?
*         
**/
ST_tpVariable  *VM_recuperarValorStaticField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescritor){
    
    int i = 0;
    char *pNomeClasse;
    ST_tpVariable *var;
    ST_tpClassFile *pClassFile1;
    ST_tpClassHeap *pClassHeap;
    ST_tpField_info *pFieldTable = NULL;
    
    char *pNameField, *pDescriptorField;
    
    pNomeClasse = (char *)malloc(strlen(pClassName)+2);
    
    strcpy(pNomeClasse, pClassName);
    
    while (TRUE) {
        pClassFile1 = PL_buscarClasse(pJVM, pNomeClasse);
        if (pClassFile1 == NULL) {
            pClassFile1 = VM_carregarClasse((char*)pNomeClasse, pJVM);
        }
        pFieldTable = pClassFile1->field_info_table;
        
        while (pFieldTable != NULL) {
            pNameField = (char *) pClassFile1->constant_pool_table[pFieldTable->name_index-1].info.Utf8.bytes;
            pDescriptorField = (char *) pClassFile1->constant_pool_table[pFieldTable->descriptor_index-1].info.Utf8.bytes;
            
            if (strcmp(pNameField, pFieldName) == 0 && strcmp(pDescriptorField, pFieldDescritor) == 0 && ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC)) {
                break;
            }
            
            if ((pFieldTable->access_flags & ACC_STATIC) == ACC_STATIC) {
                i++;
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
            printf("ERRO! FIELD NAO ENCONTRADO!");
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
    var = malloc(sizeof(ST_tpVariable));
    memcpy(var, pClassHeap->field_area + i, sizeof(ST_tpVariable));
    
    return var;
}

/**
* Descrição da função: 
*       Carrega uma classe
*
* @param  nomeClasses       - Nome da Classe que será carregada
* @param  pJVM              - Ponteiro para a JVM
*
* @return pClasse           - Endereço aonde for carregada a classe em questão
*         
*         
**/
ST_tpClassFile *VM_carregarClasse(char *nomeClasses, ST_tpJVM *pJVM) {
    ST_tpClassFile *pClasse;
    ST_tpMethod_info *pMetodo;

    pClasse = LE_lerClasse(nomeClasses);
    if(pClasse != NULL){
        /* Insere classe carregada na lista de classes carregadas da JVM */
        PL_inserirClasseTopo(pJVM, pClasse);
        VM_alocarMemoriaHeapClasse(pJVM, (pClasse)->nomeClasse);
        VM_alocarMemoriaHeapObjeto(pJVM, pClasse);

        /*
        pMetodo = VM_procurarMetodo( pClasse, "()V", "<init>");
        if (pMetodo != NULL){
            ST_tpParameterStack *pPilhaDeParametros = NULL;
            VM_executarMetodo(pJVM, pClasse, pPilhaDeParametros, pMetodo);
        }*/

        pMetodo = VM_procurarMetodo( pClasse, "()V", "<clinit>");
        if (pMetodo != NULL){
            ST_tpParameterStack *pPilhaDeParametros = NULL;
            VM_executarMetodo(pJVM, pClasse, pPilhaDeParametros, pMetodo);
        }
    }
    else{
        printf("ERRO AO CARREGAR CLASSE!");
    }
    return pClasse;
}
/**
* Descrição da função: 
*       Executa a JVM
*
* @param  numeroClasses     - Número de Classes que serão carregadas e lidas
* @param  nomeClasses       - Nome das Classes que serão carregadas e lidas
*
* @return pJVM              - Ponteiro para a JVM
*         
*         
**/
ST_tpJVM *VM_exucutarJVM(int numeroClasses, char *nomeClasses[]){
    int i;

    ST_tpJVM *pJVM;
    ST_tpClassFile *pClasse; //*pSystemCLass;
    ST_tpMethod_info *pMetodo; //*pInicializeMethod;
    //ST_tpParameterStack *pSystemStack = NULL;
    
    /* Cria a maquina virtual, a area de metodos, o heap e uma thread*/
    pJVM = VM_criarJVM();
    /*
    pSystemCLass = VM_carregarClasse("java/lang/System", pJVM);
    pInicializeMethod = VM_procurarMetodo( pSystemCLass, "()V", "initializeSystemClass");
    VM_executarMetodo(pJVM, pSystemCLass, pSystemStack, pInicializeMethod);
    */
    /* Carregando classes na JVM */
    /*for(i = 0; i < numeroClasses; i++){
        pClasse = VM_carregarClasse(nomeClasses[i], pJVM);
    }*/

    /* Procurando a primeira classe que tem o main */
    for(i = 0 ; i < numeroClasses; i++){
        //pClasse = LE_lerClasse(nomeClasses[i]);
        //pMetodo = VM_procurarMetodo( pClasse, "()V", "<init>");
        pClasse = VM_carregarClasse(nomeClasses[i], pJVM);
        PL_esvaziarPilhaParametros(&pJVM->thread->pJVMStack->parameterStack);
        
        pMetodo = VM_procurarMetodo( pClasse, "([Ljava/lang/String;)V", "main");
        if (pMetodo != NULL){
            
            // OBS: VERIFICAR A PASSAGEM DE PARAMETROS PARA A MAIN 
            VM_executarMetodo(pJVM, pClasse, pJVM->thread->pJVMStack->parameterStack, pMetodo);
        }
    }
    
    return pJVM;
}

/**
* Descrição da função:      ?????
*       Executa um Throw
*
* @param  pExceptionTable   - Tabela de excessões que ?
* @param  pClassFile        - ClassFile de onde se lêem o indice e o nome da classe usados para ?
* @param  refernciaObjeto   - ?
* @param  pc                - Contador de Programa
* @param  pPilhaOperandos   - Pilha de Operandos, onde ?
*
* @return 0 ou 1            - ?
*         
*         
**/
int VM_executarThrow(ST_tpException_table *pExceptionTable, ST_tpClassFile *pClassFile, ST_tpVariable refernciaObjeto,  u1 **pc, ST_tpOperandStack *pPilhaOperandos){
    ST_tpVariable catch;
    ST_tpException_table *pException;
    u2 index;
    int aux = 0;
    char *nomeClasse;
    
    catch.valor.Int = -1;
    
    pException = pExceptionTable;
    
    while (pException != NULL) {
        if ((*(*pc) >= pException->start_pc) && ( (*(*pc)) < pExceptionTable->end_pc)) {
            
            if (pException->catch_type == 0) {
                catch.valor.Int = pException->handler_pc;
                break;
            }
            else{
                // Verificar se essa parte da implementação está correta
                index = pClassFile->constant_pool_table[pException->catch_type - 1].info.Class.name_index;
                nomeClasse = (char *)pClassFile->constant_pool_table[index - 1].info.Utf8.bytes;
                
                // verificar se refernciaObjeto é da classe nomeClasse ou se é sub classe de nomeClasse
                
                if (aux == 1) {
                    catch.valor.Int = pException->handler_pc;
                    break;
                }
            }
        }
        pException++;
    }
    if (catch.valor.Int != -1) {
        *(*pc) = catch.valor.Int;
        while (pPilhaOperandos != NULL) {
            PL_popOperando(&pPilhaOperandos);
        }
        refernciaObjeto.tipo = JREF;
        PL_pushOperando(&pPilhaOperandos, refernciaObjeto);
    }
    else{
        while (pPilhaOperandos != NULL) {
            PL_popOperando(&pPilhaOperandos);
        }
        refernciaObjeto.tipo = JREF;
        PL_pushOperando(&pPilhaOperandos, refernciaObjeto);
        return 1;
    }
    return 0;
}

















