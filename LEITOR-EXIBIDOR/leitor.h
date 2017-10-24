/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO LEITURA
 *  @{
 *  @ingroup MOD_LE
 *
 *  @file leitor.h
 *  @brief
 *            Modulo de definicao: Modulo LEITOR
 *            Define a assinatura de funcoes responsaveis ler a estrutura do
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
#ifndef leitor_h
#define leitor_h


#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

u1 LE_lerU1(FILE *pArq);

u2 LE_lerU2(FILE *pArq);

u4 LE_lerU4(FILE *pArq);

ST_tpCp_info *LE_lerConstant_pool(FILE *pArq, u2 constant_pool_count);

u2 *LE_lerInterfaces(FILE *pArq, u2 interfaces_count);

ST_tpField_info *LE_lerFields(FILE *pArq, ST_tpCp_info *cp, u2 fields_count);

ST_tpMethod_info *LE_lerMethods(FILE *pArq, ST_tpCp_info *cp, u2 methods_count);

ST_tpConstantValue_attribute *LE_lerConstantValueAttribute(FILE *pArq);

ST_tpCode_attribute * LE_lerCodeAttribute(FILE *pArq, ST_tpCp_info *cp, ST_tpAttribute_info *pAttributes);

ST_tpExceptions_attribute *LE_lerExceptionsAttribute(FILE *pArq);

ST_tpInnerClasses_attribute *LE_lerInnerClassesAttribute(FILE *pArq);

ST_tpSourceFile_attribute *LE_lerSourceFileAttribute(FILE * pArq);

ST_tpLineNumberTable_attribute *LE_lerLineNumberAttribute(FILE *pArq);

ST_tpAttribute_info *LE_lerAttribute(FILE *pArq, ST_tpCp_info *cp, ST_tpAttribute_info *pAttributes);

ST_tpClassFile *LE_carregarClasse(char *nomeArquivo);

#endif /* leitor_h */
