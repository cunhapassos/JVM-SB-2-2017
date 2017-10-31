 /** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  MODULO: EX_
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

void EX_imprimirUtf8_ (u1 *s, int length)
{
    u1 *i;
    printf("<");
    for (i=s;i<s+length;i++)
        printf("%c", *i);
    printf(">\n");
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
    //ST_tpAttribute_info *pN = pAttributeInfoTable;
    
    //for(pN = pAttributeInfoTable; pN <  (pAttributeInfoTable + attributesCount); pN++) {
    for(i = 0; i < attributesCount; i++ ){
        //printf("___________________________________\n");
        
        printf("\n   -----------------");
        printf("\n      Attributes");
        printf("\n   -----------------\n\n");
        printf("\n[%02d] ",i);
        EX_imprimirUtf8(pClassFile->constant_pool_table[pAttributeInfoTable[i].attribute_name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pAttributeInfoTable[i].attribute_name_index-1].info.Utf8.length);
        
        printf("...................................\n\n");
        printf("\tGENERIC INFO:\n\n");
        printf("\tAttribute name index: 0x%04x\n", pAttributeInfoTable[i].attribute_name_index);
        printf("\tAttibute length: %d\n", pAttributeInfoTable[i].attribute_length);
        // Verificar impressão do campo Info da estrutura Atribute_info (nessa implementação a impressão é feita byte a byte)
        /*u1 *pQ;
        for(pQ = pN->info; pQ <  (pN->info + pN->attribute_length); pQ++){
            printf("\n\tSpecific info:\n");
            printf("\tSource file name index: 0x%02x\n", *pQ);
        }*/
    }
}

/**
 *  Descrição da função:
 *       Imprime todo o conteudo da Tabela de Constantes
 *
 *  @param  pClassFile - Ponteiro para a estrutura do ClassFile
 */
void EX_imprimirConstantPool(ST_tpClassFile *pClassFile) {
    
    int i;
    for(i = 0; i <  (pClassFile->constant_pool_count-1); i++ ){
        switch(pClassFile->constant_pool_table[i].tag) {
            case CONSTANT_Utf8:
                printf("\n-----[%d] CONSTANT_Utf8 INFO-----\n\n",i+1);
                printf("Length: %d\n",pClassFile->constant_pool_table[i].info.Utf8.length);
                printf("String: ");
                EX_imprimirUtf8(pClassFile->constant_pool_table[i].info.Utf8.bytes, pClassFile->constant_pool_table[i].info.Utf8.length);
                break;
            case CONSTANT_Float:
                printf("\n-----[%d] CONSTANT_Float INFO-----\n\n",i+1);
                printf("Float: 0x%08x\n",pClassFile->constant_pool_table[i].info.Float.bytes);
                break;
            case CONSTANT_Integer:
                printf("\n-----[%d] CONSTANT_Integer INFO-----\n\n",i+1);
                printf("Integer: 0x%08x\n",pClassFile->constant_pool_table[i].info.Integer.bytes);
                break;
            case CONSTANT_Long:
                printf("\n-----[%d] CONSTANT_Long INFO-----\n\n",i+1);
                printf("High Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Long.high_bytes);
                printf("Low Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Long.low_bytes);
                printf("\n-----[%d] (large numeric continued)-----\n\n",i+2);
                break;
            case CONSTANT_Double:
                printf("\n-----[%d] CONSTANT_Double INFO-----\n\n",i+1);
                printf("High Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Double.high_bytes);
                printf("Low Bytes: 0x%08x\n",pClassFile->constant_pool_table[i].info.Double.low_bytes);
                printf("\n-----[%d] (large numeric continued)-----\n\n",i+2);
                break;
            case CONSTANT_Class:
                printf("\n-----[%d] CONSTANT_Class INFO-----\n\n",i+1);
                printf("Name Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Class.name_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Class.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Class.name_index-1].info.Utf8.length);
                break;
            case CONSTANT_String:
                printf("\n-----[%d] CONSTANT_String INFO-----\n\n",i+1);
                printf("String Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.String.string_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.String.string_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.String.string_index-1].info.Utf8.length);
                break;
            case CONSTANT_Fieldref:
                printf("\n-----[%d] CONSTANT_Fieldref INFO-----\n\n",i+1);
                printf("Class Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Fieldref.class_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Fieldref.class_index-1].info.Class.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Fieldref.class_index-1].info.Class.name_index-1].info.Utf8.length);
                printf("Name and Type Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index-1].info.NameAndType.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index-1].info.NameAndType.name_index-1].info.Utf8.length);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index-1].info.NameAndType.descriptor_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Fieldref.name_and_type_index-1].info.NameAndType.descriptor_index-1].info.Utf8.length);
                break;
            case CONSTANT_Methodref:
                printf("\n-----[%d] CONSTANT_Methodref INFO-----\n\n",i+1);
                printf("Class Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Methodref.class_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Methodref.class_index-1].info.Class.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Methodref.class_index-1].info.Class.name_index-1].info.Utf8.length);
                printf("Name and Type Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index-1].info.NameAndType.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index-1].info.NameAndType.name_index-1].info.Utf8.length);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index-1].info.NameAndType.descriptor_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.Methodref.name_and_type_index-1].info.NameAndType.descriptor_index-1].info.Utf8.length);
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\n-----[%d] CONSTANT_InterfaceMethodref INFO-----\n\n",i+1);
                printf("Class Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.InterfaceMethodref.class_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.InterfaceMethodref.name_and_type_index-1].info.NameAndType.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.InterfaceMethodref.name_and_type_index-1].info.NameAndType.name_index-1].info.Utf8.length);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.InterfaceMethodref.name_and_type_index-1].info.NameAndType.descriptor_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.InterfaceMethodref.name_and_type_index-1].info.NameAndType.descriptor_index-1].info.Utf8.length);
                break;
            case CONSTANT_NameAndType:
                printf("\n-----[%d] CONSTANT_NameAndType INFO-----\n\n",i+1);
                printf("Name Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.NameAndType.name_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.NameAndType.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.NameAndType.name_index-1].info.Utf8.length);
                printf("Descriptor Index: cp_info #%d ",pClassFile->constant_pool_table[i].info.NameAndType.descriptor_index);
                EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.NameAndType.descriptor_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[i].info.NameAndType.descriptor_index-1].info.Utf8.length);
                break;
            default:
                break;
        }
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
        printf("\n[%02d] Method: ", pM->name_index);
        EX_imprimirUtf8(pClassFile->constant_pool_table[pM->name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pM->name_index-1].info.Utf8.length);
        printf("-----------------------------------\n");
        
        printf("\t Name: ");
        EX_imprimirUtf8(pClassFile->constant_pool_table[pM->name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pM->name_index-1].info.Utf8.length);
        
        printf("\t Descriptor: ");
        EX_imprimirUtf8(pClassFile->constant_pool_table[pM->descriptor_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pM->descriptor_index-1].info.Utf8.length);
        
        printf("\t Access flags: 0x%04x\n", pM->access_flags);
        EX_imprimirAtributos(pClassFile, pM->attributes, pM->attributes_count);
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
        printf("\tName: ");
        EX_imprimirUtf8(pClassFile->constant_pool_table[pL->name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pL->name_index-1].info.Utf8.length);
        
        printf("\tDescriptor: ");
        EX_imprimirUtf8(pClassFile->constant_pool_table[pL->descriptor_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pL->descriptor_index-1].info.Utf8.length);
        
        printf("\tAccess flags: 0x%04x\n", pL->access_flags);
        EX_imprimirAtributos(pClassFile, pL->attributes, pL->attributes_count);
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
    
    printf("\n-----GENERAL INFORMATION-----\n\n");
    printf("Magic: 0x%08x\n",pClassFile->magic);
    printf("Minor Version: 0x%04x\n",pClassFile->minor_version_number);
    printf("Major Version: 0x%04x\n",pClassFile->major_version_number);
    printf("Constant Pool Count: %d\n",pClassFile->constant_pool_count);
    printf("Access Flags: 0x%04x\n",pClassFile->access_flags);
    printf("This Class: cp_info #%d ",pClassFile->this_class);
    EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->this_class-1].info.Class.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->this_class-1].info.Class.name_index-1].info.Utf8.length);
    printf("Super Class: cp_info #%d ",pClassFile->super_class);
    EX_imprimirUtf8_(pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->super_class-1].info.Class.name_index-1].info.Utf8.bytes, pClassFile->constant_pool_table[pClassFile->constant_pool_table[pClassFile->super_class-1].info.Class.name_index-1].info.Utf8.length);
    printf("Interfaces Count: %d\n",pClassFile->interfaces_count);
    printf("Fields Count: %d\n",pClassFile->fields_count);
    printf("Methods Count: %d\n",pClassFile->methods_count);
    printf("Atributes Count: %d\n",pClassFile->attributes_count);    
    EX_imprimirConstantPool(pClassFile);
    EX_imprimirInterfaces(pClassFile);
    EX_imprimirFields(pClassFile);
    EX_imprimirMethods(pClassFile);
    EX_imprimirAtributos(pClassFile, pClassFile->attribute_info_table,pClassFile->attributes_count);
}

