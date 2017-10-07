/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO EXIBIDOR
 *  @{
 *  @ingroup MOD_ES
 *
 *  @file exibidor.h
 *  @brief
 *            Modulo de definicao: Modulo EXIBIDOR
 *            Define a assinatura de funcoes responsaveis por imprimir a estrutura do
 * arquivo .class.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @author DANIEL MATIAS
 * @author ALON MOTA
 * @author JURAMIR
 *
 * @version 1.0
 * @since 07/09/2017
 *
 @}********************************************************************************/

#ifndef exibidor_h
#define exibidor_h

#include <stdio.h>
#include "structures.h"

void EX_imprimirUtf8 (u1 *pS, int length);

void EX_imprimirAtributos(ST_tpAttribute_info *attribute_info_table,u2 attributes_count);

void EX_imprimirConstantPool(ST_tpClassFile *pClassFile);

void EX_imprimirMethods(ST_tpClassFile *pClassFile);

void EX_imprimirFields(ST_tpClassFile *pClassFile);

void EX_imprimirInterfaces(ST_tpClassFile *pClassFile);

void EX_imprimirClassFile(ST_tpClassFile *classFile);

#endif /* exibidor_h */
