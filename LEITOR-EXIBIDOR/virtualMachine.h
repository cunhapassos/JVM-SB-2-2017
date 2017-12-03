/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *    Software Basico - Turma A
 *
 *  MODULO: VM_
 *  @file virtualMachine
 *  @brief
 *            Descricao: Definicao das estruturas de incicializacao da JVM.
 *
 * @author ALON MOTA     - MAT. 13/0005002
 * @author DANIEL MATIAS - MAT. 12/0139804
 * @author PAULO PASSOS  - MAT. 10/0118577
 *
 * @version 1.0
 * @since 31/10/17
 *
 @}********************************************************************************/

#ifndef virtualMachine_h
#define virtualMachine_h

#include <stdio.h>
#include "structures.h"
#include "funcoes.h"

ST_tpMethodArea *VM_criarAreaMetodo(void);

ST_tpHeap *VM_criarHeap(void);

ST_tpThread *VM_criarThread(void);

ST_tpJVM *VM_criarJVM(void);

void VM_inserirClasseCarregada(ST_tpJVM *pJvm, ST_tpClassFile *pClasse);

void VM_armazenarVariavel(ST_tpVariable *pVariaveisLocais, ST_tpVariable variavel, int posicao);

ST_tpVariable VM_recuperarVariavel(ST_tpVariable *pVariaveisLocais, int posicao);

ST_tpStackFrame *VM_criarFrame(ST_tpJVM *pJVM, ST_tpStackFrame **pJVMStack, ST_tpClassFile *pClasse, ST_tpParameterStack *pilhaParametros, int maxStackSize, u2 access_flag);

u1 *VM_retornaNomeSuperClasse(ST_tpClassFile *pClassFile);

u1 *VM_retornarNomeClasse(ST_tpClassFile *pClassFile);

ST_tpObjectHeap *VM_alocarMemoriaHeapObjeto(ST_tpJVM *pJVM, ST_tpClassFile *pClassFile);

ST_tpObjectHeap *VM_recuperarObjeto(ST_tpObjectHeap *pObejectHeap, char *nomeObjeto);

ST_tpArrayHeap *VM_criarArray(u1 tipo, char *nomeClasse, int tamanho);

void VM_armazenarValorArray(ST_tpArrayHeap *pArray, int posicao, ST_tpVariable variavel);

ST_tpVariable VM_recuperarValorArray(ST_tpArrayHeap *pArrayHeap, int posicao);

int retornarTipoString(char *string);

void *VM_armazenarValorField(ST_tpJVM *pJVM, char *nomeClasse, char *pFieldName, char *pFieldDescriptor, ST_tpVariable var, ST_tpVariable objRef);

ST_tpVariable *VM_recuperarValorField(ST_tpJVM *pJVM, char *nomeClasse, char *pFieldName, char *pFieldDescriptor, ST_tpVariable *objRef);

void *VM_alocarMemoriaHeapClasse(ST_tpJVM *pJVM, char *pClassName);

//void VM_armazenarVariavelNoFieldDaClasse(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, char *pClassName, char *pFieldName, char *pFieldDescritor,ST_tpVariable var);

void *VM_armazenarValorStaticField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescritor, ST_tpVariable var);

ST_tpVariable *VM_recuperarValorStaticField(ST_tpJVM *pJVM, char *pClassName, char *pFieldName, char *pFieldDescritor);

ST_tpClassFile *VM_carregarClasse(char *nomeClasses, ST_tpJVM *pJVM);

ST_tpJVM *VM_exucutarJVM(int numeroClasses, char *nomeClasses[]);

ST_tpVariable *VM_executarMetodo(ST_tpJVM *pJVM, ST_tpClassFile *pClasse, ST_tpParameterStack *pilhaParametros, ST_tpMethod_info *pMetodo);

ST_tpMethod_info *VM_procurarMetodo(ST_tpClassFile *pClassFile, char *descritorMetodo, char *nomeMetodo);

void VM_UTF8paraString(ST_tpCONSTANT_Utf8_info *pUTF8, char *string);

int VM_executarThrow(ST_tpException_table *pExceptionTable, ST_tpClassFile *pClassFile, ST_tpVariable refernciaObjeto,  u1 **pc, ST_tpOperandStack *pPilhaOperandos);

int retornarTipoRetorno(u1 *descritor);

#endif /* virtualMachine_h */

