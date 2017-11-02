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

#include "virtualMachine.h"
#include "leitor.h"
#include <stdlib.h>

VM_tpMethodArea *VM_criarAreaMetodo(){
    VM_tpMethodArea *pAreaMetodo;
    
    pAreaMetodo = malloc(sizeof(VM_tpMethodArea));
    pAreaMetodo->classFile = NULL;
    
    return pAreaMetodo;
}

VM_tpHeap *VM_criarHeap(){
    VM_tpHeap *pHeap;
    
    pHeap = malloc(sizeof(VM_tpHeap));
    pHeap->array = NULL;
    pHeap->classes = NULL;
    pHeap->objects = NULL;
    
    return pHeap;
}

VM_tpThread *VM_criarThread(){
    VM_tpThread *pThread;
    
    pThread = malloc(sizeof(VM_tpThread));
    pThread->JVMStack = NULL;
    pThread->PC = 0;
    
    return pThread;
}

VM_tpJVM *VM_criarJVM(){
    VM_tpJVM *pJvm;
    
    pJvm = malloc(sizeof(VM_tpJVM));
    pJvm->heap = VM_criarHeap();
    pJvm->methodArea = VM_criarAreaMetodo();
    pJvm->thread = VM_criarThread();
    
    return pJvm;
}

void VM_inserirClasseCarregada(VM_tpJVM *pJvm, ST_tpClassFile *pClasse){
    
    if(pJvm->methodArea->classFile == NULL){
         pJvm->methodArea->classFile = pClasse;
    }
    else{
        pJvm->methodArea->classFile->right = pClasse->left;
        pJvm->methodArea->classFile = pClasse;
    }
}

void VM_exucutarJVM(VM_tpJVM *pJvm, void *listaDeNomesdeArquivosComClasses){ // verificar se precisar carregar mais de um .class
    
    for(int i = 0;...;...){ // fazer for com a quantidade de .class a serem lidos
        ST_tpClassFile *pClasse= LE_carregarClasse(listaDeNomesdeArquivosComClasses[i]);
        VM_inserirClasseCarregada(pJvm, pClasse);
    }
}
