/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO EXIBIDOR
 *  @{
 *  @ingroup MOD_EX
 *
 *  @file exibidor.c
 *  @brief
 *            Modulo de implementacao: Modulo Exibidor
 *            Implementa as funcoes que exibem o conteudo do arquivo .class.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @author DANIEL MATIAS
 * @author ALON MOTA
 * @author JURAMIR
 *
 * @version 1.0
 * @since 30/09/2017
 *
 @}********************************************************************************/

#include "exibidor.h"

/**
 *  Descrição da função:
 *       Imprime uma estrutura UTF8
 *
 *  @param  pS - Ponteiro que aponta para um byte
 *  @param  length - Numero de elementos UTF8
 */
void EX_imprimirUtf8 (u1 *pS, int length){
    u1 *pI;
    for (pI = pS; pI < pS+length; pI++)
        printf("%c", *pI);
    printf("\n");
}

/**
 *  Descrição da função:
 *       Imprime atributos contidos na Tabela de Atributos
 *
 *  @param  pAttributeInfoTable - Ponteiro para a Tabela de Atributos
 *  @param  attributesCount - quantidades de atributos da Tabela de Atributos
 */
void EX_imprimirAtributos(ST_tpAttribute_info *pAttributeInfoTable, u2 attributesCount){
    int j = 0;
    ST_tpAttribute_info *pN;
    
    for(pN = pAttributeInfoTable; pN <  (pAttributeInfoTable + attributesCount); pN++) {
        //printf("___________________________________\n");
        
        printf("\n   -----------------");
        printf("\n      Attributes");
        printf("\n   -----------------\n\n");
        printf("\n[%02d] 0x%04x\n",j, pN->attribute_name_index);
        printf("...................................\n\n");
        printf("\tGENERIC INFO:\n\n");
        printf("\tAttribute name index: 0x%04x\n", pN->attribute_name_index);
        printf("\tAttibute length: 0x%08x\n", pN->attribute_length);
        // Verificar impressão do campo Info da estrutura Atribute_info (nessa implementação a impressão é feita byte a byte)
        u1 *pQ;
        for(pQ = pN->info; pQ <  (pN->info + pN->attribute_length); pQ++){
            printf("\n\tSpecific info:\n");
            printf("\tSource file name index: 0x%02x\n", *pQ);
        }
        j++;
    }
}

/**
 *  Descrição da função:
 *       Imprime todo o conteudo da Tabela de Constantes
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirConstantPool(ST_tpClassFile *pClassFile) {
    
    int j=1;
    ST_tpCp_info *pI;
    printf("\n===================================\n           CONSTANT POOL\n===================================\n");

    for(pI = pClassFile->constant_pool_table; pI < (pClassFile->constant_pool_table + pClassFile->constant_pool_count-1); pI++ ){
        switch(pI->tag) {
            case CONSTANT_Utf8:
                printf("\n[%02d] CONSTANT_Utf8 INFO\n",j);
                printf("\t Length: 0x%04x\n",pI->info.Utf8.length);
                printf("\t String: ");
                EX_imprimirUtf8(pI->info.Utf8.bytes, pI->info.Utf8.length);
                break;
            case CONSTANT_Float:
                printf("\n[%02d] CONSTANT_Float INFO-----\n",j);
                printf("\t Float: 0x%08x\n", pI->info.Float.bytes);
                break;
            case CONSTANT_Integer:
                printf("\n[%02d] CONSTANT_Integer INFO\n",j);
                printf("\t Integer: 0x%08x\n", pI->info.Integer.bytes);
                break;
            case CONSTANT_Long:
                printf("\n[%02d] CONSTANT_Long INFO\n",j);
                printf("\t High Bytes: 0x%08x\n", pI->info.Long.high_bytes);
                printf("\t Low Bytes: 0x%08x\n", pI->info.Long.low_bytes);
                break;
            case CONSTANT_Double:
                printf("\n[%02d] CONSTANT_Double INFO\n",j);
                printf("\t High Bytes: 0x%08x\n", pI->info.Double.high_bytes);
                printf("\t Low Bytes: 0x%08x\n", pI->info.Double.high_bytes);
                break;
            case CONSTANT_Class:
                printf("\n[%02d] CONSTANT_Class INFO\n",j);
                printf("\t Name Index: 0x%04x\n", pI->info.Class.name_index);
                break;
            case CONSTANT_String:
                printf("\n[%02d] CONSTANT_String INFO\n",j);
                printf("\t String Index: 0x%04x\n", pI->info.String.string_index);
                break;
            case CONSTANT_Fieldref:
                printf("\n[%02d] CONSTANT_Fieldref INFO\n",j);
                printf("\t Class Index: 0x%04x\n", pI->info.Fieldref.class_index);
                printf("\t Name and Type Index: 0x%04x\n", pI->info.Fieldref.name_and_type_index);
                break;
            case CONSTANT_Methodref:
                printf("\n[%02d] CONSTANT_Methodref INFO\n", j);
                printf("\t Class Index: 0x%04x\n", pI->info.Methodref.class_index);
                printf("\t Name and Type Index: 0x%04x\n", pI->info.Methodref.name_and_type_index);
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\n[%02d] CONSTANT_InterfaceMethodref INFO\n", j);
                printf("\t Class Index: 0x%04x\n", pI->info.InterfaceMethodref.class_index);
                printf("\t Name and Type Index: 0x%04x\n", pI->info.InterfaceMethodref.name_and_type_index);
                break;
            case CONSTANT_NameAndType:
                printf("\n[%02d] CONSTANT_NameAndType INFO\n", j);
                printf("\t Name Index: 0x%04x\n", pI->info.NameAndType.name_index);
                printf("\t Descriptor Index: 0x%04x\n", pI->info.NameAndType.descriptor_index);
                break;
            default:
                break;
        }
        j++;
    }
}

/**
 *  Descrição da função:
 *       Imprime a Tabela de Metodos
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirMethods(ST_tpClassFile *pClassFile) {
    ST_tpMethod_info *pM;
    int j = 0;
    
    printf("\n===================================\n              METHODS\n===================================\n\n");
    for(pM = pClassFile->method_info_table; pM < (pClassFile->method_info_table + pClassFile->methods_count); pM++) {
        printf("\n[%02d] Method: 0x%04x\n", j, pM->name_index);
        printf("-----------------------------------\n");
        printf("\t Name: 0x%04x\n", pM->name_index);
        printf("\t Descriptor: 0x%04x\n", pM->descriptor_index);
        printf("\t Access flags: 0x%04x\n", pM->access_flags);
        EX_imprimirAtributos(pM->attributes, pM->attributes_count);
        j++;
    }
}

/**
 *  Descrição da função:
 *       Imprime a Tabela de Fields
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirFields(ST_tpClassFile *pClassFile) {
    ST_tpField_info *pL;
    for(pL = pClassFile->field_info_table; pL <  (pClassFile->field_info_table+pClassFile->fields_count); pL++) {
        printf("\n===================================\n              FIELDS\n===================================\n\n");
        printf("\tName: 0x%04x\n", pL->name_index);
        printf("\tDescriptor: 0x%04x\n", pL->descriptor_index);
        printf("\tAccess flags: 0x%04x\n", pL->access_flags);
        EX_imprimirAtributos(pL->attributes, pL->attributes_count);
    }
}

/**
 *  Descrição da função:
 *       Imprime a Tabela de Interfaces
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirInterfaces(ST_tpClassFile *pClassFile) {
    u2 *pK;
    for(pK = pClassFile->interfaces_table; pK <  (pClassFile->interfaces_table+pClassFile->interfaces_count); pK++)
        printf("Interfaces: %04x\n", *pK);
}

/**
 *  Descrição da função:
 *       Imprime todo o conteudo contido na ClassFile
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirClassFile(ST_tpClassFile *pClassFile){
    
    printf("\n===================================\n        GENERAL INFORMATION\n===================================\n\n");
    printf("Magic: 0x%08x\n", pClassFile->magic);
    printf("Minor Version: 0x%04x\n", pClassFile->minor_version_number);
    printf("Major Version: 0x%04x\n", pClassFile->major_version_number);
    printf("Constant Pool Count: 0x%04x\n", pClassFile->constant_pool_count);
    printf("Access Flags: 0x%04x\n", pClassFile->access_flags);
    printf("This Class: 0x%04x\n", pClassFile->this_class);
    printf("Super Class: 0x%04x\n", pClassFile->super_class);
    printf("Interfaces Count: 0x%04x\n", pClassFile->interfaces_count);
    printf("Fields Count: 0x%04x\n", pClassFile->fields_count);
    printf("Methods Count: 0x%04x\n", pClassFile->methods_count);
    printf("Atributes Count: 0x%02x\n", pClassFile->attributes_count);
    
    EX_imprimirConstantPool(pClassFile);
    EX_imprimirInterfaces(pClassFile);
    EX_imprimirFields(pClassFile);
    EX_imprimirMethods(pClassFile);
    EX_imprimirAtributos(pClassFile->attribute_info_table,pClassFile->attributes_count);
}

