/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *	Software Basico - Turma A
 *
 *	@addgroup MODULO LEITOR_EXIBIDOR
 *  @{
 *  @ingroup MOD_LE
 *
 *  @file leitor.c
 *  @brief 
 *			Modulo de implementaco: Modulo Leitor-Exibidor:
 *         	Implementa as funcoes de leitura do bytecode.
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


/** ******************************************************************************
 *                             Inclusao do compilador 
 ** *******************************************************************************/

 #include <stdio.h>
 #include <string.h>
 #include "leitor.h"
 #include "configuracao.h"
 

/**
 *  Descri��o da fun��o:
 *       Le um byte de um arquivo apontado por pArq
 *
 *  @param  pArq - Ponteiro para o arquivo a ser lido
 *
 *  @return retorno     - Quatro bytes lidos do bytecode
 */
 u1 LE_lerU1(FILE *pArq){
 	u1 retorno;
	fread(&retorno, sizeof(u1), 1, pArq);
	
	return retorno;
}

/**
 *  Descri��o da fun��o:
 *       Le dois bytes de um arquivo apontado por pArq
 *
 *  @param  pArq - Ponteiro para o arquivo a ser lido
 *
 *  @return retorno     - Dois bytes lidos do bytecode
 */
u2 LE_lerU2(FILE *pArq){
 	u2 retorno;
    u1 segu = LE_lerU1(pArq);
    u1 prim = LE_lerU1(pArq);
	
    retorno = ( segu << 8 | prim);
	return retorno;
}

/**
 *  Descri��o da fun��o:
 *       Le quatro bytes de um arquivo apontado por pArq
 *
 *  @param  pArq        - Ponteiro para o arquivo a ser lido
 *
 *  @return retorno     - Quatro bytes lidos do bytecode
 */
u4 LE_lerU4(FILE *pArq){
     u4 retorno;
     u1 quar = LE_lerU1(pArq);
     u1 terc = LE_lerU1(pArq);
     u1 segu = LE_lerU1(pArq);
     u1 prim = LE_lerU1(pArq);
     
     retorno = (quar << 24 | terc << 16 | segu << 8 | prim);
     return retorno;
}

/**
 *  Descri��o da fun��o:
 *       Le a Tabela de Constantes do bytecode .class
 *
 *  @param  pArq                - Ponteiro para o arquivo a ser lido
 *  @param  constant_pool_count - Numero de elementos da Tabela de Constantes a ser lida
 *
 *  @return constantPool        - Ponteiro para a Tabela de Constantes lida
 */
ST_tpCp_info *LE_lerConstant_pool(FILE *pArq, u2 constant_pool_count){
    
    ST_tpCp_info *constantPool = (ST_tpCp_info *) malloc((constant_pool_count-1)*sizeof(ST_tpCp_info));
    int i;
    
    for(i = 0; i <  (constant_pool_count-1); i++ ){
        constantPool[i].tag = LE_lerU1(pArq);
        switch(constantPool[i].tag) {
            case CONSTANT_Utf8:
                constantPool[i].info.Utf8.tag = CONSTANT_Utf8;
                constantPool[i].info.Utf8.length = LE_lerU2(pArq);
                constantPool[i].info.Utf8.bytes = malloc(sizeof(u1) * (constantPool[i].info.Utf8.length+1));
                fread(constantPool[i].info.Utf8.bytes, 1, constantPool[i].info.Utf8.length, pArq);
                constantPool[i].info.Utf8.bytes[constantPool[i].info.Utf8.length] = '\0';
                break;
            case CONSTANT_Float:
                constantPool[i].info.Float.tag = CONSTANT_Float;
                constantPool[i].info.Float.bytes = LE_lerU4(pArq);
                break;
            case CONSTANT_Integer:
                constantPool[i].info.Integer.tag = CONSTANT_Integer;
                constantPool[i].info.Integer.bytes = LE_lerU4(pArq);
                break;
            case CONSTANT_Long:
                constantPool[i].info.Long.tag = CONSTANT_Long;
                constantPool[i].info.Long.high_bytes = LE_lerU4(pArq);
                constantPool[i].info.Long.low_bytes = LE_lerU4(pArq);
                i++;
                break;
            case CONSTANT_Double:
                constantPool[i].info.Double.tag = CONSTANT_Double;
                constantPool[i].info.Double.high_bytes = LE_lerU4(pArq);
                constantPool[i].info.Double.low_bytes = LE_lerU4(pArq);
                i++;
                break;
            case CONSTANT_Class:
                constantPool[i].info.Class.tag = CONSTANT_Class;
                constantPool[i].info.Class.name_index = LE_lerU2(pArq);
                break;
            case CONSTANT_String:
                constantPool[i].info.String.tag = CONSTANT_String;
                constantPool[i].info.String.string_index = LE_lerU2(pArq);
                constantPool[i].info.String.StringObject = NULL;
                break;
            case CONSTANT_Fieldref:
                constantPool[i].info.Fieldref.tag = CONSTANT_Fieldref;
                constantPool[i].info.Fieldref.class_index = LE_lerU2(pArq);
                constantPool[i].info.Fieldref.name_and_type_index = LE_lerU2(pArq);
                break;
            case CONSTANT_Methodref:
                constantPool[i].info.Methodref.tag = CONSTANT_Methodref;
                constantPool[i].info.Methodref.class_index = LE_lerU2(pArq);
                constantPool[i].info.Methodref.name_and_type_index = LE_lerU2(pArq);
                break;
            case CONSTANT_InterfaceMethodref:
                constantPool[i].info.InterfaceMethodref.tag = CONSTANT_InterfaceMethodref;
                constantPool[i].info.InterfaceMethodref.class_index = LE_lerU2(pArq);
                constantPool[i].info.InterfaceMethodref.name_and_type_index = LE_lerU2(pArq);
                break;
            case CONSTANT_NameAndType:
                constantPool[i].info.NameAndType.tag = CONSTANT_NameAndType;
                constantPool[i].info.NameAndType.name_index = LE_lerU2(pArq);
                constantPool[i].info.NameAndType.descriptor_index = LE_lerU2(pArq);
                break;
            default:
                break;
        }
    }
    return constantPool;
}

/**
 *  Descri��o da fun��o:
 *       Le Tabela de Interfaces do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *  @param interfaces_count - Numero de elementos da Tabela de Interfaces a ser lida
 *
 *  @return pinterfaces     - Ponteiro para a Tabela de Interfaces lida
 */
u2 *LE_lerInterfaces(FILE *pArq, ST_tpCp_info *cp, u2 interfaces_count) {
    
    ST_tpInterface_list *pInterfaces = (ST_tpInterface_list*) malloc(interfaces_count * sizeof(ST_tpInterface_list));
    for(int i = 0; i < interfaces_count; i++){
        pInterfaces[i].constant_pool_index = LE_lerU2(pArq);
    }

    return (u2*) pInterfaces;
}

/**
 *  Descri��o da fun��o:
 *       Le Tabela de Fields do bytecode .class
 *
 *  @param  pArq        - Ponteiro para o arquivo a ser lido
 *  @param fields_count - Numero de elementos da Tabela de Fields a ser lida
 *
 *  @return pfields     - Ponteiro para a Tabela de Fields lida
 */
ST_tpField_info *LE_lerFields(FILE *pArq, ST_tpCp_info *cp, u2 fields_count) {
    int i, j;
    ST_tpField_info *pFields;
    if (fields_count > 0) {
        pFields = (ST_tpField_info *) malloc(fields_count * sizeof(ST_tpField_info));
    }
    else{
        pFields = NULL;
    }
    

    for(i = 0; i < fields_count; i++){
        pFields[i].access_flags     = LE_lerU2(pArq);
        pFields[i].name_index       = LE_lerU2(pArq);
        pFields[i].descriptor_index = LE_lerU2(pArq);
        pFields[i].attributes_count = LE_lerU2(pArq);
        for (j = 0 ; j < (pFields[i].attributes_count); j++) {
            pFields[i].attributes = (ST_tpAttribute_info *)malloc((pFields[i].attributes_count) * sizeof(ST_tpAttribute_info));
             LE_lerAttribute(pArq, cp, &(pFields[i].attributes[j]));
            if((j+1) < pFields[i].attributes_count){
                (pFields[i].attributes[j]).next = &(pFields[i].attributes[j+1]);
            }
            else{
                (pFields[i].attributes[j]).next = NULL;
            }
        }
        if((i + 1) < fields_count){
            pFields[i].next = &pFields[i+1];
        }
        else{
            pFields[i].next = NULL;
        }
    }
    return pFields;
}

/**
 *  Descri��o da fun��o:
 *       Le Tabela de Metodos do bytecode .class
 *
 *  @param  pArq         - Ponteiro para o arquivo a ser lido
 *  @param methods_count - Numero de elementos da Tabela de Metodos a ser lida
 *
 *  @return pmethods     - Ponteiro para a Tabela de Metodos lida
 */
ST_tpMethod_info *LE_lerMethods(FILE *pArq, ST_tpCp_info *cp, u2 methods_count) {
    int i, j;
    
    ST_tpMethod_info *pMethods = (ST_tpMethod_info *) malloc(methods_count * sizeof(ST_tpMethod_info));
    /*
     ST_tpMethod_info *pI;
    for(pI = pMethods; pI <  (pMethods+methods_count); pI++ ){
        pI->access_flags = LE_lerU2(pArq);
        pI->name_index = LE_lerU2(pArq);
        pI->descriptor_index = LE_lerU2(pArq);
        pI->attributes_count = LE_lerU2(pArq);
        pI->attributes = (ST_tpAttribute_info *) malloc(pI->attributes_count * sizeof(ST_tpAttribute_info));
        ST_tpAttribute_info *pJ; */
    
     for(i = 0; i < methods_count; i++){
         pMethods[i].access_flags = LE_lerU2(pArq);
         pMethods[i].name_index = LE_lerU2(pArq);
         pMethods[i].descriptor_index = LE_lerU2(pArq);
         pMethods[i].attributes_count = LE_lerU2(pArq);
         pMethods[i].attributes = malloc((pMethods[i].attributes_count) * sizeof(ST_tpAttribute_info));
         
         for(j = 0; j < pMethods[i].attributes_count; j++){
             LE_lerAttribute(pArq, cp, &(pMethods[i].attributes[j]));
             if((j+1) < pMethods[i].attributes_count){
                 (pMethods[i].attributes[j]).next = &(pMethods[i].attributes[j+1]);
             }
             else{
                 (pMethods[i].attributes[j]).next = NULL;
             }
         }
         if((i+1) < methods_count){
             pMethods[i].next = &pMethods[i+1];
         }
         else{
             pMethods[i].next = NULL;
         }
             
        //printf("%02d\n", pI->attributes_count);
        
        /*for(pJ = pI->attributes; pJ <  (pI->attributes + pI->attributes_count); pJ++ ){
            pJ->info = LE_lerAttributes(pArq, cp, pJ);
            
            pJ->attribute_name_index = LE_lerU2(pArq);
            pJ->attribute_length = LE_lerU4(pArq);
            pJ->info = (u1 *) malloc(pJ->attribute_length * sizeof(u1));
            fread(pJ->info, 1, pJ->attribute_length, pArq);
        }*/
    }
    return pMethods;
}

/**
 *  Descri��o da fun��o:
 *       Le um atributo ConstantValue
 *
 *  @param  pArq            - Ponteiro para o arquivo de onde sera lido o ConstantValue
 *
 *  @return constantValue   - Ponteiro para o atributo ConstantValue lido
 *
 */
ST_tpConstantValue_attribute *LE_lerConstantValueAttribute(FILE *pArq){
    ST_tpConstantValue_attribute *constantValue = (ST_tpConstantValue_attribute*) malloc(sizeof(ST_tpConstantValue_attribute));
    constantValue->constantvalue_index = LE_lerU2(pArq);
    
    return constantValue;
}

/**
 *  Descri��o da fun��o:
 *       Le uma ExceptionTable
 *
 *  @param  pArq            - Ponteiro para o arquivo de onde sera lido a ExceptionTable
 *
 *  @return pExceptionTable   - Ponteiro para a ExceptionTable lida
 *
 */
/* RETIRAR ESSE TECHO DE CODIGO COAMENTADO
 ST_tpException_table * LE_lerExceptionTable (FILE *pArq, ST_tpException_table *pExceptionTable) {
    pExceptionTable->start_pc = LE_lerU2(pArq);
    pExceptionTable->end_pc = LE_lerU2(pArq);
    pExceptionTable->handler_pc = LE_lerU2(pArq);
    pExceptionTable->catch_type = LE_lerU2(pArq);
    
    return pExceptionTable;
}
*/
/**
*  Descri��o da fun��o:
*       Le um atributo CodeAttribute
*
*  @param  pArq            - Ponteiro para o arquivo de onde sera lido o CodeAttribute
*
*  @return pCode           - Ponteiro para o Code lido
*
*/
ST_tpCode_attribute *LE_lerCodeAttribute(FILE *pArq, ST_tpCp_info *cp, ST_tpAttribute_info *pAttributes){
    int i;
    ST_tpCode_attribute *pCode = (ST_tpCode_attribute*) malloc(sizeof(ST_tpCode_attribute));
    // pq nao le attribute_name_index e attribute length
    pCode->max_stack = LE_lerU2(pArq);
    pCode->max_locals = LE_lerU2(pArq);
    pCode->code_length = LE_lerU4(pArq);
    
    if(pCode->code_length > 0 ){
        pCode->code = malloc(pCode->code_length * sizeof(u1));
        for(i = 0; i < pCode->code_length; i++){
            pCode->code[i] = LE_lerU1(pArq);
        }
    }
    
    pCode->exception_table_length = LE_lerU2(pArq);
    
    if(pCode->exception_table_length > 0 ){
        pCode->exception_table = malloc((pCode->exception_table_length) * sizeof(ST_tpException_table));
        for(i = 0; i < pCode->exception_table_length ; i++){
            //LE_lerExceptionTable(pArq, &(pCode->exception_table[i]));
            pCode->exception_table[i].start_pc = LE_lerU2(pArq);
            pCode->exception_table[i].end_pc = LE_lerU2(pArq);
            pCode->exception_table[i].handler_pc = LE_lerU2(pArq);
            pCode->exception_table[i].catch_type = LE_lerU2(pArq);
        }
    }
    
    pCode->attributes_count = LE_lerU2(pArq);
    
    if(pCode->attributes_count > 0 ){
        //pCode->attribute_info = (ST_tpAttribute_info*)malloc(pCode->attributes_count*sizeof(ST_tpAttribute_info*));
        pCode->attribute_info = (ST_tpAttribute_info*)malloc(pCode->attributes_count*sizeof(ST_tpAttribute_info));
        for (i = 0; i < pCode->attributes_count; i++) {
            LE_lerAttribute(pArq, cp, &(pCode->attribute_info[i]));
            if((i+1) < pCode->attributes_count){
                (pCode->attribute_info[i]).next = &(pCode->attribute_info[i+1]);
            }
            else{
                (pCode->attribute_info[i]).next = NULL;
            }
        }
    }
    return pCode;
}

/**
 *  Descri��o da fun��o:
 *       Le os atributos de excecao do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *
 *  @return pExceptions;    - Ponteiro para a ExceptionsAttribute lida
 *
 */
ST_tpExceptions_attribute *LE_lerExceptionsAttribute(FILE *pArq){
    
    ST_tpExceptions_attribute *pExceptions = (ST_tpExceptions_attribute*)malloc(sizeof(ST_tpExceptions_attribute));
    pExceptions->number_of_exceptions = LE_lerU2(pArq);
    pExceptions->exception_index_table = NULL;
    
    if (pExceptions->number_of_exceptions > 0) {
        pExceptions->exception_index_table = (u2*)malloc(pExceptions->number_of_exceptions * sizeof(u2));
        /*for (u2 *pAux = pExceptions->exception_index_table; pAux < pExceptions->exception_index_table + pExceptions->number_of_exceptions; pAux++) {
            *pAux = LE_lerU2(pArq);
        }*/
        for(int i = 0; i < pExceptions->number_of_exceptions; i++){
            pExceptions->exception_index_table[i] = LE_lerU2(pArq);
        }
     
    }
    return pExceptions;
}
/*      RETIRAR ESSE TRECHO DE CODIGO COMENTADO
ST_tpInnerClasses_table *LE_lerInnerClasses_table(FILE * pArq, ST_tpInnerClasses_table *pClasse) {
    //ST_tpInnerClasses_table *pClasse = (ST_tpInnerClasses_table*)malloc(sizeof(ST_tpInnerClasses_table));
    pClasse->inner_class_info_index = LE_lerU2(pArq);
    pClasse->outer_class_info_index = LE_lerU2(pArq);
    pClasse->inner_name_index = LE_lerU2(pArq);
    pClasse->inner_class_access_flags = LE_lerU2(pArq);
    
    return pClasse;
}
*/
ST_tpInnerClasses_attribute *LE_lerInnerClassesAttribute(FILE *pArq){

    ST_tpInnerClasses_attribute *pInnerClasses = (ST_tpInnerClasses_attribute*)malloc(sizeof(ST_tpInnerClasses_attribute));
    pInnerClasses->number_of_classes = LE_lerU2(pArq);
    
    if (pInnerClasses->number_of_classes > 0) {
        pInnerClasses->classes = (ST_tpInnerClasses_table*)malloc(pInnerClasses->number_of_classes * sizeof(ST_tpInnerClasses_table));
        /*for (ST_tpInnerClasses_table *pAux = pInnerClasses->classes; pAux < pInnerClasses->classes + pInnerClasses->number_of_classes; pAux++) {
            pAux = LE_lerInnerClasses_table(pArq);
        } */
        for(int i = 0; i < pInnerClasses->number_of_classes; i++){
             //LE_lerInnerClasses_table(pArq, &(pInnerClasses->classes[i]));
            pInnerClasses->classes[i].inner_class_info_index   = LE_lerU2(pArq);
            pInnerClasses->classes[i].outer_class_info_index   = LE_lerU2(pArq);
            pInnerClasses->classes[i].inner_name_index         = LE_lerU2(pArq);
            pInnerClasses->classes[i].inner_class_access_flags = LE_lerU2(pArq);
        }
    }
    return pInnerClasses;
}

/**
 *  Descri��o da fun��o:
 *       Le Tabela de Atributo  SourceFile do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *  @return pSourceFile    - Ponteiro para o SourceFile lido
 *
 */
ST_tpSourceFile_attribute *LE_lerSourceFileAttribute(FILE * pArq) {
    ST_tpSourceFile_attribute *pSourceFile = NULL;
    pSourceFile = (ST_tpSourceFile_attribute*)malloc(sizeof(ST_tpSourceFile_attribute));
    pSourceFile->source_file_index = LE_lerU2(pArq);
    
    return pSourceFile;
}

ST_tpLineNumberTable_attribute *LE_lerLineNumberAttribute(FILE *pArq) {
    ST_tpLineNumberTable_attribute *pLineNumberTable = (ST_tpLineNumberTable_attribute*)malloc(sizeof(ST_tpLineNumberTable_attribute));
    
    pLineNumberTable->line_number_table_length = LE_lerU2(pArq);
    
    if (pLineNumberTable->line_number_table_length > 0) {
        pLineNumberTable->info = (ST_tpLine_number_table*)malloc(pLineNumberTable->line_number_table_length*sizeof(ST_tpLine_number_table));
        
        for (int i = 0; i < pLineNumberTable->line_number_table_length; i++) {
            pLineNumberTable->info[i].start_pc = LE_lerU2(pArq);
            pLineNumberTable->info[i].line_number = LE_lerU2(pArq);
        }
    }
    return pLineNumberTable;
}


ST_tpLocalVariableTable_attribute *LE_lerLocalVariableAttribute(FILE *pArq){
    ST_tpLocalVariableTable_attribute *pLocalVariableTable = (ST_tpLocalVariableTable_attribute*) malloc(sizeof(ST_tpLocalVariableTable_attribute));
    
    pLocalVariableTable->local_variable_table_length = LE_lerU2(pArq);
    
    if(pLocalVariableTable->local_variable_table_length > 0){
        pLocalVariableTable->Local_variable_table = (ST_tpLocal_variable_table*) malloc(sizeof(ST_tpLocal_variable_table));
        
        for(int i = 0; i < pLocalVariableTable->local_variable_table_length; i++){
            pLocalVariableTable->Local_variable_table[i].start_pc = LE_lerU2(pArq);
            pLocalVariableTable->Local_variable_table[i].length = LE_lerU2(pArq);
            pLocalVariableTable->Local_variable_table[i].name_index = LE_lerU2(pArq);
            pLocalVariableTable->Local_variable_table[i].descriptor_index = LE_lerU2(pArq);
            pLocalVariableTable->Local_variable_table[i].index = LE_lerU2(pArq);
        }
    }
    return pLocalVariableTable;
}
/**
 *  Descri��o da fun��o:
 *       Le Tabela de Atributos do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *  @param pAttributes      - Ponteiro para a Tabela de Atributos
 *
 */
ST_tpAttribute_info *LE_lerAttribute(FILE *pArq, ST_tpCp_info *cp, ST_tpAttribute_info *pAttributes) {
   
    pAttributes->attribute_name_index = LE_lerU2(pArq);
    
    pAttributes->attribute_length = LE_lerU4(pArq);
    
    if(strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "ConstantValue") == 0)
    {
        ST_tpConstantValue_attribute *pConstantValue = (ST_tpConstantValue_attribute*) malloc(sizeof(ST_tpConstantValue_attribute));
        pConstantValue = LE_lerConstantValueAttribute(pArq);
        pAttributes->info = (ST_tpConstantValue_attribute*) pConstantValue;
        pConstantValue = NULL;
    }
    else if(strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "Code") == 0)
    {
        ST_tpCode_attribute *pCode = (ST_tpCode_attribute*) malloc(sizeof(ST_tpCode_attribute));
        pCode = LE_lerCodeAttribute(pArq, cp, pAttributes);
        pAttributes->info = (ST_tpCode_attribute*) pCode;
        pCode = NULL;
    }
    else if(strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "Exceptions") == 0)
    {
        ST_tpExceptions_attribute *pExceptions = (ST_tpExceptions_attribute*) malloc(sizeof(ST_tpExceptions_attribute));
        pExceptions = LE_lerExceptionsAttribute(pArq);
        pAttributes->info = (ST_tpExceptions_attribute*) pExceptions;
        pExceptions = NULL;
    }
    else if(strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "InnerClasses") == 0)
    {
        ST_tpInnerClasses_attribute *pInnerClasses =  (ST_tpInnerClasses_attribute*) malloc(sizeof(ST_tpInnerClasses_attribute));
        pInnerClasses = LE_lerInnerClassesAttribute(pArq);
        pAttributes->info = (ST_tpInnerClasses_attribute*) pInnerClasses;
        pInnerClasses = NULL;
    }
   else if(strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "SourceFile") == 0)
    {
        ST_tpSourceFile_attribute *pSourceFile = (ST_tpSourceFile_attribute*) malloc(sizeof(ST_tpSourceFile_attribute));
        pSourceFile = LE_lerSourceFileAttribute(pArq);
        pAttributes->info = (ST_tpSourceFile_attribute*) pSourceFile;
        pSourceFile = NULL;
    }
     else if(strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "LineNumberTable") == 0)
    {
        ST_tpLineNumberTable_attribute *pLineNumberTable = (ST_tpLineNumberTable_attribute*) malloc(sizeof(ST_tpLineNumberTable_attribute));
        pLineNumberTable = LE_lerLineNumberAttribute(pArq);
        pAttributes->info = (ST_tpLineNumberTable_attribute*) pLineNumberTable;
        pLineNumberTable = NULL;
    }
     else if (strcmp((char *) cp[(pAttributes->attribute_name_index)-1].info.Utf8.bytes, "LocalVariableTable") == 0){
         ST_tpLocalVariableTable_attribute *pLocalVariableAttribute = (ST_tpLocalVariableTable_attribute*) malloc(sizeof(ST_tpLocalVariableTable_attribute));
         pLocalVariableAttribute = LE_lerLocalVariableAttribute(pArq);
         pAttributes->info = (ST_tpLocalVariableTable_attribute*) pLocalVariableAttribute;
         pLocalVariableAttribute = NULL;
     }
    //faz a leitura dos atributos desconhecidos
     else
    {
        pAttributes->info = (u1 *) malloc(pAttributes->attribute_length * sizeof(u1));
        fread(pAttributes->info, 1, pAttributes->attribute_length, pArq);
    }
    
    return pAttributes;
}

/**
 *  Descri��o da fun��o:
 *       Fun��o que recebe o nome qualificado do arquivo .class e carrega o seu conte�do,
 *       retornando o ponteiro para a estrutura classFile
 *
 *  @param  nomeArquivo     - Nome do arquivo a ser carregado
 *
 *  @return arqPontoClass   - Ponteiro para a a estrutura do .class carregada em memoria
 */
 ST_tpClassFile *LE_lerClasse(char *nomeArquivo){
    
    char *arq;
    long aux;
    u4 index;
    u2 tamanho;
    ST_tpClassFile *arqPontoClass = NULL;


    aux = strlen(PATH) + strlen(nomeArquivo) + strlen(".class") + 1;

    arq = (char *)malloc(sizeof(char)* aux);
    strcpy(arq, PATH);
    strcat(arq, nomeArquivo);
    strcat(arq, ".class");

    //printf("%s\n", arq);

    /* Cria ponteiro para estrutura classFile */
    FILE * pArq = fopen(arq,"rb");
    /* Verifica se foi possivel abrir o arquivo */
    if(pArq == NULL){
        printf("ERRO AO ABRIR O ARQUIVO .CLASS!\n");
        return NULL;
    }
	
	arqPontoClass = (ST_tpClassFile*) malloc(sizeof(ST_tpClassFile));
	
	/* Verifica se o malloc n�o retornou NULL, estando a memoria cheia */
	if(arqPontoClass == NULL){							
		printf("A memoria esta cheia e nao foi possivel carregar o arquivo .class!\n");
		return NULL;
	}
	
	arqPontoClass->magic = LE_lerU4(pArq);
	if((arqPontoClass->magic != 0xcafebabe)) {
		printf("Arquivo corrompido ou nao referente a um .class!\n");
		return NULL;
	}
	arqPontoClass->minor_version_number = LE_lerU2(pArq);
	arqPontoClass->major_version_number = LE_lerU2(pArq);
	/*if((arqPontoClass->major_version_number >= 0x35 || arqPontoClass->minor_version_number <= 0x31)) {
		printf("Versao Java incompativel!\n");
		return NULL;
	}*/
	arqPontoClass->constant_pool_count = LE_lerU2(pArq);
	arqPontoClass->constant_pool_table = LE_lerConstant_pool(pArq, arqPontoClass->constant_pool_count);
	arqPontoClass->access_flags = LE_lerU2(pArq);
	arqPontoClass->this_class = LE_lerU2(pArq);
	arqPontoClass->super_class = LE_lerU2(pArq);
	arqPontoClass->interfaces_count = LE_lerU2(pArq);
	arqPontoClass->interfaces_table = LE_lerInterfaces(pArq, arqPontoClass->constant_pool_table, arqPontoClass->interfaces_count);
	arqPontoClass->fields_count = LE_lerU2(pArq);
	arqPontoClass->field_info_table = LE_lerFields(pArq, arqPontoClass->constant_pool_table, arqPontoClass->fields_count);
	arqPontoClass->methods_count = LE_lerU2(pArq);
	arqPontoClass->method_info_table = LE_lerMethods(pArq, arqPontoClass->constant_pool_table, arqPontoClass->methods_count);
	arqPontoClass->attributes_count = LE_lerU2(pArq);
     
    arqPontoClass->attribute_info_table = malloc((arqPontoClass->attributes_count) * sizeof(ST_tpAttribute_info));
     for(int j = 0; j < arqPontoClass->attributes_count; j++){
         LE_lerAttribute(pArq, arqPontoClass->constant_pool_table, &(arqPontoClass->attribute_info_table[j]));
         if((j+1) < arqPontoClass->attributes_count){
             (arqPontoClass->attribute_info_table[j]).next = &arqPontoClass->attribute_info_table[j+1];
         }
         else{
             (arqPontoClass->attribute_info_table[j]).next = NULL;
         }
     }
     
     index   = arqPontoClass->constant_pool_table[arqPontoClass->this_class - 1].info.Class.name_index;
     tamanho = arqPontoClass->constant_pool_table[index - 1].info.Utf8.length;
     memcpy(&arqPontoClass->nomeClasse, &(arqPontoClass->constant_pool_table[index - 1].info.Utf8.bytes), tamanho + 1);
     
     
     //wprintf(L"%s", arqPontoClass->nomeClasse);
     
     
     if(arqPontoClass->super_class > 0){
         index   = arqPontoClass->constant_pool_table[arqPontoClass->super_class - 1].info.Class.name_index;
         tamanho = arqPontoClass->constant_pool_table[index - 1].info.Utf8.length;
         
         memcpy(&arqPontoClass->nomeSuperClasse, &(arqPontoClass->constant_pool_table[index - 1].info.Utf8.bytes), tamanho + 1);
     }
     
     //wprintf(L"%s", arqPontoClass->nomeSuperClasse);
     
     // FALTA ACRESCENTAR NOME COMPLETO DA CLASSE
     
     
    return arqPontoClass;
 }

