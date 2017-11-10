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

ST_tpJVM *VM_exucutarJVM(int numeroClasses, char *nomeClasses[]);

void VM_executarMetodo(ST_tpThread *pThread, ST_tpClassFile *pClasse, ST_tpMethod_info *pMetodo);

#endif /* virtualMachine_h */

