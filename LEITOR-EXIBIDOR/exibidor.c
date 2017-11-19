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
 *
 * @version 1.0
 * @since 30/09/2017
 *
 @}********************************************************************************/

#include "exibidor.h"
#include "string.h"
#include <stdlib.h>

/**
 *  Descrição da função:
 *       Imprime todo o conteudo contido na ClassFile
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirClassFile(ST_tpClassFile *pClassFile){
    EX_imprimirGeneralInformation(pClassFile);
    EX_imprimirConstantPool(pClassFile);
    EX_imprimirInterfaces(pClassFile);
    EX_imprimirFields(pClassFile);
    EX_imprimirMethods(pClassFile);
    EX_imprimirAtributosClasse(pClassFile, pClassFile->attribute_info_table,pClassFile->attributes_count);
}

/**
 *  Descrição da função:
 *       Imprime as Informacoes Gerais da Classe
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirGeneralInformation(ST_tpClassFile *pClassFile) {
    printf("\n===================================\n        GENERAL INFORMATION\n===================================\n\n");
    printf("Magic: 0x%08x\n",pClassFile->magic);
    printf("Minor Version: 0x%04x\n",pClassFile->minor_version_number);
    printf("Major Version: 0x%04x\n",pClassFile->major_version_number);
    printf("Constant Pool Count: %d\n",pClassFile->constant_pool_count);
    printf("Access Flags: 0x%04x ",pClassFile->access_flags);
    EX_imprimirAccessFlags(pClassFile->access_flags);
    printf("This Class: cp_info #%d ",pClassFile->this_class);
    EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->this_class);
    printf("\nSuper Class: cp_info #%d ",pClassFile->super_class);
    EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->super_class);
    printf("\nInterfaces Count: %d\n",pClassFile->interfaces_count);
    printf("Fields Count: %d\n",pClassFile->fields_count);
    printf("Methods Count: %d\n",pClassFile->methods_count);
    printf("Atributes Count: %d\n",pClassFile->attributes_count);
}

/**
 *  Descrição da função:
 *       Imprime todo o conteudo da Tabela de Constantes
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirConstantPool(ST_tpClassFile *pClassFile) {
    
    int i;
    printf("\n===================================\n           CONSTANT POOL\n===================================\n\n");
    for(i = 0; i <  (pClassFile->constant_pool_count-1); i++ ){
        switch(pClassFile->constant_pool_table[i].tag) {
            case CONSTANT_Utf8:
                printf("\n-----[%d] CONSTANT_Utf8 INFO-----\n\n", i+1);
                printf("Length: %d\n",pClassFile->constant_pool_table[i].info.Utf8.length);
                printf("String: ");
                EX_imprimirStringPool(pClassFile->constant_pool_table, i+1);
                printf("\n");
                break;
            case CONSTANT_Float:
                printf("\n-----[%d] CONSTANT_Float INFO-----\n\n", i+1);
                printf("Float: 0x%08x\n",pClassFile->constant_pool_table[i].info.Float.bytes);
                break;
            case CONSTANT_Integer:
                printf("\n-----[%d] CONSTANT_Integer INFO-----\n\n", i+1);
                printf("Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Integer.bytes);
                printf("Integer: %d\n",(int) pClassFile->constant_pool_table[i].info.Integer.bytes);
                break;
            case CONSTANT_Long:
                printf("\n-----[%d] CONSTANT_Long INFO-----\n\n", i+1);
                printf("High Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Long.high_bytes);
                printf("Low Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Long.low_bytes);
                uint64_t const_64 = (uint64_t) pClassFile->constant_pool_table[i].info.Long.high_bytes;
                const_64 <<= 32;
                const_64 |= pClassFile->constant_pool_table[i].info.Long.low_bytes;
                long const_long;
                memcpy(&const_long, &const_64, sizeof(int64_t));
                printf("Long: %ld\n", const_long);
                printf("\n-----[%d] (large numeric continued)-----\n\n", i+2);
                break;
            case CONSTANT_Double:
                printf("\n-----[%d] CONSTANT_Double INFO-----\n\n", i+1);
                printf("High Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Double.high_bytes);
                printf("Low Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Double.low_bytes);
                const_64 = (uint64_t) pClassFile->constant_pool_table[i].info.Double.high_bytes;
                const_64 <<= 32;
                const_64 |= pClassFile->constant_pool_table[i].info.Double.low_bytes;
                double const_double;
                memcpy(&const_double, &const_64, sizeof(int64_t));
                printf("Double: %lf\n", const_double);
                printf("\n-----[%d] (large numeric continued)-----\n\n", i+2);
                break;
            case CONSTANT_Class:
                printf("\n-----[%d] CONSTANT_Class INFO-----\n\n", i+1);
                printf("Name Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Class.name_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, i+1);
                printf("\n");
                break;
            case CONSTANT_String:
                printf("\n-----[%d] CONSTANT_String INFO-----\n\n", i+1);
                printf("String Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.String.string_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, i+1);
                printf("\n");
                break;
            case CONSTANT_Fieldref:
                printf("\n-----[%d] CONSTANT_Fieldref INFO-----\n\n", i+1);
                printf("Class Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Fieldref.class_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.Fieldref.class_index);
                printf("\n");
                printf("Name and Type Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index);
                printf("\n");
                break;
            case CONSTANT_Methodref:
                printf("\n-----[%d] CONSTANT_Methodref INFO-----\n\n", i+1);
                printf("Class Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Methodref.class_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.Methodref.class_index);
                printf("\n");
                printf("Name and Type Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index);
                printf("\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\n-----[%d] CONSTANT_InterfaceMethodref INFO-----\n\n",i+1);
                printf("Class Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.InterfaceMethodref.class_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.InterfaceMethodref.class_index);
                printf("\n");
                break;
            case CONSTANT_NameAndType:
                printf("\n-----[%d] CONSTANT_NameAndType INFO-----\n\n",i+1);
                printf("Name Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.NameAndType.name_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.NameAndType.name_index);
                printf("\n");
                printf("Descriptor Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.NameAndType.descriptor_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->constant_pool_table[i].info.NameAndType.descriptor_index);
                printf("\n");
                break;
            default:
                break;
        }
    }
}

/**
 *  Descrição da função:
 *       Imprime a Tabela de Interfaces
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirInterfaces(ST_tpClassFile *pClassFile) {
    printf("\n\n===================================\n              INTERFACES\n===================================");
    for(int i = 0; i < pClassFile->interfaces_count; i++) {
        printf("\n\nInterface %d\n", i);
        printf("\n\tInterface: cp_info #%d ", pClassFile->interfaces_table[i]);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->interfaces_table[i]);
    }
}

/**
 *  Descrição da função:
 *       Imprime a Tabela de Fields
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirFields(ST_tpClassFile *pClassFile) {
    printf("\n\n===================================\n              FIELDS\n===================================\n\n");
    for(int i = 0; i <  pClassFile->fields_count; i++) {
        printf("\n[%02d] Field: ", i);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->field_info_table[i].name_index);
        printf("\n\tName: cp_info #%d ", pClassFile->field_info_table[i].name_index);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->field_info_table[i].name_index);
        
        printf("\n\tDescriptor: cp_info #%d ", pClassFile->field_info_table[i].descriptor_index);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->field_info_table[i].descriptor_index);
        
        printf("\n\tAccess flags: 0x%04x\n", pClassFile->field_info_table[i].access_flags);
        EX_imprimirAccessFlags(pClassFile->field_info_table[i].access_flags);
        EX_imprimirAtributos(pClassFile, pClassFile->field_info_table[i].attributes, pClassFile->field_info_table[i].attributes_count);
    }
}

/**
 *  Descrição da função:
 *       Imprime a Tabela de Metodos
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirMethods(ST_tpClassFile *pClassFile) {
    printf("\n===================================\n              METHODS\n===================================\n\n");
    for(int i = 0; i < pClassFile->methods_count; i++) {
        printf("\n[%02d] Method: ", i);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->method_info_table[i].name_index);
        printf("\n...................................\n\n");
        printf("\t Name: cp_info #%d ", pClassFile->method_info_table[i].name_index);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->method_info_table[i].name_index);
        printf("\n");
        printf("\t Descriptor: cp_info #%d ", pClassFile->method_info_table[i].descriptor_index);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pClassFile->method_info_table[i].descriptor_index);
        printf("\n");
        printf("\t Access flags: 0x%04x ", pClassFile->method_info_table[i].access_flags);
        EX_imprimirAccessFlags(pClassFile->method_info_table[i].access_flags);
        EX_imprimirAtributos(pClassFile, pClassFile->method_info_table[i].attributes, pClassFile->method_info_table[i].attributes_count);
    }
}

/**
 *  Descrição da função:
 *       Imprime atributos contidos na Tabela de Atributos
 *
 *  @param  pAttributeInfoTable - Ponteiro para a Tabela de Atributos
 *  @param  attributesCount - quantidades de atributos da Tabela de Atributos
 */
void EX_imprimirAtributos(ST_tpClassFile *pClassFile, ST_tpAttribute_info *pAttributeInfoTable, u2 attributesCount){
    int i;
    for(i = 0; i < attributesCount; i++ ){
        printf("\n[%02d] ",i);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pAttributeInfoTable[i].attribute_name_index);
        
        printf("\n...................................\n\n");
        printf("\tGENERIC INFO:\n\n");
        printf("\tAttribute name index: cp_info #%d ", pAttributeInfoTable[i].attribute_name_index);
        EX_imprimirStringPool(pClassFile->constant_pool_table, pAttributeInfoTable[i].attribute_name_index);
        printf("\n");
        printf("\tAttibute length: %d\n", pAttributeInfoTable[i].attribute_length);
        printf("...................................\n\n");
        printf("\tSPECIFC INFO:\n\n");
        if(strcmp((char *) pClassFile->constant_pool_table[(pAttributeInfoTable->attribute_name_index)-1].info.Utf8.bytes, "SourceFile") == 0) {
                printf("\tSource file name index: cp_info #%d ", ((ST_tpSourceFile_attribute *) pAttributeInfoTable[i].info)->source_file_index);
                EX_imprimirStringPool(pClassFile->constant_pool_table, ((ST_tpSourceFile_attribute *) pAttributeInfoTable[i].info)->source_file_index);
                printf("\n");
        }
        else if (strcmp((char *) pClassFile->constant_pool_table[(pAttributeInfoTable->attribute_name_index)-1].info.Utf8.bytes, "ConstantValue") == 0) {
            printf("Constant value index: cp_info #%d ",( (ST_tpConstantValue_attribute *) pAttributeInfoTable[i].info)->constantvalue_index);
            EX_imprimirStringPool(pClassFile->constant_pool_table, ((ST_tpConstantValue_attribute *) pAttributeInfoTable[i].info)->constantvalue_index);
        }
        else if (strcmp((char *) pClassFile->constant_pool_table[(pAttributeInfoTable->attribute_name_index)-1].info.Utf8.bytes, "Code") == 0) {
                printf("\tmax_stack: %d\n",((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->max_stack);
                printf("\tmax_locals: %d\n",((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->max_locals);
                printf("\tcode_length: %d\n",((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->code_length);
                printf("\n\tBytecode:\n");
               for (int j=0; j < ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->code_length; j++)
                   printf("\t%d -> x%0x \n", j , ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->code[j]);
               printf("\n\texception_table_length: %d\n",((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->exception_table_length);
                for (int j=0; j < ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->exception_table_length; j++) {
                    printf("\t%d -> x%0x \n", j , ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->exception_table[j].start_pc);
                    printf("\t%d -> x%0x \n", j , ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->exception_table[j].end_pc);
                    printf("\t%d -> x%0x \n", j , ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->exception_table[j].handler_pc);
                    printf("\t%d -> x%0x \n", j , ((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->exception_table[j].catch_type);
                }
                printf("\n\tattributes_count: %d\n",((ST_tpCode_attribute *) pAttributeInfoTable[i].info)->attributes_count);
        }
    }
}
void EX_imprimirAtributosClasse(ST_tpClassFile *pClassFile, ST_tpAttribute_info *pAttributeInfoTable, u2 attributesCount){
    printf("\n===================================\n              ATRIBUTOS\n===================================\n\n");
    EX_imprimirAtributos(pClassFile, pAttributeInfoTable, attributesCount);

}

void EX_imprimirStringPool(ST_tpCp_info* cp, int index)
{
    if (cp[index-1].tag == CONSTANT_Utf8)
    {
        printf("%s", cp[index-1].info.Utf8.bytes);
        return;
    }
    switch(cp[index-1].tag)
    {
        case CONSTANT_Class:
            printf("<");
            EX_imprimirStringPool(cp, cp[index-1].info.Class.name_index);
            printf(">");
            break;
            
        /*case CONSTANT_Fieldref:
            printf("<");
            EX_imprimirStringPool(cp, cp[index-1].info.Fieldref.class_index);
            EX_imprimirStringPool(cp, cp[index-1].info.Fieldref.name_and_type_index);
            printf(">");
            break;*/
            
        case CONSTANT_NameAndType:
            printf("<");
            EX_imprimirStringPool(cp, cp[index-1].info.NameAndType.name_index);
            printf(":");
            EX_imprimirStringPool(cp, cp[index-1].info.NameAndType.descriptor_index);
            printf(">");
            break;
            
        /*case CONSTANT_Methodref:
            printf("<");
            EX_imprimirStringPool(cp, cp[index-1].info.Methodref.class_index);
            EX_imprimirStringPool(cp, cp[index-1].info.Methodref.name_and_type_index);
            printf(">");
            break;
            
        case CONSTANT_InterfaceMethodref:
            EX_imprimirStringPool(cp, cp[index-1].info.InterfaceMethodref.class_index);
            EX_imprimirStringPool(cp, cp[index-1].info.InterfaceMethodref.name_and_type_index);
            break;*/
        case CONSTANT_String:
            printf("<");
            EX_imprimirStringPool(cp, cp[index-1].info.String.string_index);
            printf(">");
            break;
        case CONSTANT_Long:
    //Todo
            break;
        default:
            break;
    }
}

void EX_imprimirAccessFlags(u2 access_flags) {
    printf("[");
    if (access_flags & ACC_PUBLIC) printf("public");
    else if (access_flags & ACC_PRIVATE) printf("private");
    else if (access_flags & ACC_PROTECTED) printf("protected");
    else if (access_flags & ACC_INTERFACE) printf("interface");
    if (access_flags & ACC_STATIC) printf(" static");
    if (access_flags & ACC_ABSTRACT) printf(" abstract");
    if (access_flags & ACC_FINAL) printf(" final");
    printf("]\n");
}


