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


#ifndef instrucoes_h
#define instrucoes_h

#include <stdio.h>
#include "structures.h"
#include "virtualMachine.h"

void FU_invokevirtual(ST_tpCp_info *pConstantPool, ST_tpThread *thread, u1 *pc);

#endif /* instrucoes_h */
