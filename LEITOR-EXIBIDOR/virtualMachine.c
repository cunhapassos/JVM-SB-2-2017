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
    pThread->JVMStack = NULL;
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
            
            if(strcmp(name, "<init>") == 0 && strcmp(descritor, "()V") == 0 && pClasse->method_info_table[i].access_flags == ACC_PUBLIC){
                printf("\n Executa metodo <init>\n");
                // chamar funcao que executa metodo aqui
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
                // chamar funcao que executa metodo aqui
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
