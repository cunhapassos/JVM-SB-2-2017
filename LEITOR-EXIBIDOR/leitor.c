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

 #include <string.h>
 #include "leitor.h"

/**
 *  Descrição da função:
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
 *  Descrição da função:
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
 *  Descrição da função:
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
 *  Descrição da função:
 *       Le a Tabela de Constantes do bytecode .class
 *
 *  @param  pArq                - Ponteiro para o arquivo a ser lido
 *  @param  constant_pool_count - Numero de elementos da Tabela de Constantes a ser lida
 *
 *  @return constantPool        - Ponteiro para a Tabela de Constantes lida
 */
ST_tpCp_info *LE_lerConstant_pool(FILE *pArq, u2 constant_pool_count){
	
	ST_tpCp_info *pConstantPool = (ST_tpCp_info *) malloc((constant_pool_count-1) * sizeof(ST_tpCp_info));
	ST_tpCp_info *pI = NULL;
	
	for(pI = pConstantPool; pI <  (pConstantPool + constant_pool_count-1); pI++ ){
		pI->tag = LE_lerU1(pArq);
		switch(pI->tag) {
			case CONSTANT_Utf8:
				pI->info.Utf8.length = LE_lerU2(pArq);
				pI->info.Utf8.bytes = malloc(pI->info.Utf8.length * sizeof(u1));
//                for(u1 *j=i->info.Utf8.bytes;j<(i->info.Utf8.bytes+i->info.Utf8.length);j++)
//                    *j = LE_lerU1(pArq);
                fread(pI->info.Utf8.bytes, 1, pI->info.Utf8.length, pArq);
				break;
			case CONSTANT_Float:
				pI->info.Float.bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Integer:
				pI->info.Integer.bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Long:
				pI->info.Long.high_bytes = LE_lerU4(pArq);
				pI->info.Long.low_bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Double:
				pI->info.Double.high_bytes = LE_lerU4(pArq);
				pI->info.Double.low_bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Class:
				pI->info.Class.name_index = LE_lerU2(pArq);
				break;
			case CONSTANT_String:
				pI->info.String.string_index = LE_lerU2(pArq);
				break;
			case CONSTANT_Fieldref:
				pI->info.Fieldref.class_index = LE_lerU2(pArq);
				pI->info.Fieldref.name_and_type_index = LE_lerU2(pArq);
				break;
			case CONSTANT_Methodref:
				pI->info.Methodref.class_index = LE_lerU2(pArq);
				pI->info.Methodref.name_and_type_index = LE_lerU2(pArq);
				break;
			case CONSTANT_InterfaceMethodref:
				pI->info.InterfaceMethodref.class_index = LE_lerU2(pArq);
				pI->info.InterfaceMethodref.name_and_type_index = LE_lerU2(pArq);
				break;
			case CONSTANT_NameAndType:
				pI->info.NameAndType.name_index = LE_lerU2(pArq);
				pI->info.NameAndType.descriptor_index = LE_lerU2(pArq);
				break;
			default:
				break;
		}
	}
    return pConstantPool;
}

/**
 *  Descrição da função:
 *       Le Tabela de Interfaces do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *  @param interfaces_count - Numero de elementos da Tabela de Interfaces a ser lida
 *
 *  @return pinterfaces     - Ponteiro para a Tabela de Interfaces lida
 */
u2 *LE_lerInterfaces(FILE *pArq, u2 interfaces_count) {
    u2 *pInterfaces = (u2 *) malloc(interfaces_count * sizeof(u2));
    fread(pInterfaces, 1, interfaces_count * 2, pArq); //ainda não foi testado, pois o Classe de exemplo não possui nenhuma interface
    return pInterfaces;
}

/**
 *  Descrição da função:
 *       Le Tabela de Fields do bytecode .class
 *
 *  @param  pArq        - Ponteiro para o arquivo a ser lido
 *  @param fields_count - Numero de elementos da Tabela de Fields a ser lida
 *
 *  @return pfields     - Ponteiro para a Tabela de Fields lida
 */
ST_tpField_info *LE_lerFields(FILE *pArq, u2 fields_count) {
    ST_tpField_info *pfields = (ST_tpField_info *) malloc(fields_count * sizeof(ST_tpField_info));
    ST_tpField_info *pI = NULL;
    for(pI = pfields; pI <  (pfields + fields_count); pI++ ){
        pI->access_flags = LE_lerU2(pArq);
        pI->name_index = LE_lerU2(pArq);
        pI->descriptor_index = LE_lerU2(pArq);
        pI->attributes_count = LE_lerU2(pArq);
        pI->attributes = (ST_tpAttribute_info *) malloc(pI->attributes_count * sizeof(ST_tpAttribute_info));
        ST_tpAttribute_info *pJ;
        for(pJ = pI->attributes; pJ <  (pI->attributes + pI->attributes_count); pJ++ ){
            pJ->attribute_name_index = LE_lerU2(pArq);
            pJ->attribute_length = LE_lerU4(pArq);
            pJ->info = (u1 *) malloc(pJ->attribute_length * sizeof(u1));
            fread(pJ->info, 1, pJ->attribute_length, pArq);
        }
    }
    return pfields;
}

/**
 *  Descrição da função:
 *       Le Tabela de Metodos do bytecode .class
 *
 *  @param  pArq         - Ponteiro para o arquivo a ser lido
 *  @param methods_count - Numero de elementos da Tabela de Metodos a ser lida
 *
 *  @return pmethods     - Ponteiro para a Tabela de Metodos lida
 */
ST_tpMethod_info *LE_lerMethods(FILE *pArq, ST_tpCp_info *cp, u2 methods_count) {
    ST_tpMethod_info *pMethods = (ST_tpMethod_info *) malloc(methods_count * sizeof(ST_tpMethod_info));
    ST_tpMethod_info *pI;
    for(pI = pMethods; pI <  (pMethods+methods_count); pI++ ){
        pI->access_flags = LE_lerU2(pArq);
        pI->name_index = LE_lerU2(pArq);
        pI->descriptor_index = LE_lerU2(pArq);
        pI->attributes_count = LE_lerU2(pArq);
        pI->attributes = (ST_tpAttribute_info *) malloc(pI->attributes_count * sizeof(ST_tpAttribute_info));
        ST_tpAttribute_info *pJ;
        for(pJ = pI->attributes; pJ <  (pI->attributes + pI->attributes_count); pJ++ ){
            
            LE_lerAttributes(pArq, cp, pJ);
            
            /*pJ->attribute_name_index = LE_lerU2(pArq);
            pJ->attribute_length = LE_lerU4(pArq);
            pJ->info = (u1 *) malloc(pJ->attribute_length * sizeof(u1));
            fread(pJ->info, 1, pJ->attribute_length, pArq);*/
        }
    }
    return pMethods;
}

/**
 *  Descrição da função:
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
 *  Descrição da função:
 *       Le uma ExceptionTable
 *
 *  @param  pArq            - Ponteiro para o arquivo de onde sera lido a ExceptionTable
 *
 *  @return pExceptionTable   - Ponteiro para a ExceptionTable lida
 *
 */
ST_tpException_table * lerExceptionTable (FILE *pArq, u2 tam) {
    ST_tpException_table *pExceptionTable = (ST_tpException_table*)malloc(tam * sizeof(ST_tpException_table));
    for(ST_tpException_table *pAux = pExceptionTable; pAux < pExceptionTable + tam; pAux++){
        pAux->start_pc = LE_lerU2(pArq);
        pAux->end_pc = LE_lerU2(pArq);
        pAux->handler_pc = LE_lerU2(pArq);
        pAux->catch_type = LE_lerU2(pArq);
    }
    return pExceptionTable;
}

/**
*  Descrição da função:
*       Le um atributo CodeAttribute
*
*  @param  pArq            - Ponteiro para o arquivo de onde sera lido o CodeAttribute
*
*  @return pCode           - Ponteiro para o Code lido
*
*/
ST_tpCode_attribute *LE_lerCodeAttribute(FILE *pArq, ST_tpCp_info *cp, ST_tpAttribute_info *pAttributes){
    
    ST_tpCode_attribute *pCode = (ST_tpCode_attribute*) malloc(sizeof(ST_tpCode_attribute));
    // pq nao le attribute_name_index e attribute length
    pCode->max_stack = LE_lerU2(pArq);
    pCode->max_locals = LE_lerU2(pArq);
    pCode->code_length = LE_lerU4(pArq);
    
    if(pCode->code_length > 0 ){
        pCode->code = malloc(pCode->code_length * sizeof(u1));
        for(u1 *pAux = pCode->code; pAux < pCode->code + pCode->code_length; pAux++){
            *pAux = LE_lerU1(pArq);
        }
    }
    
    pCode->exception_table_length = LE_lerU2(pArq);
    
    if(pCode->exception_table_length >0 ){
        pCode->exception_table = malloc(pCode->exception_table_length * sizeof(ST_tpException_table));
        pCode->exception_table = lerExceptionTable(pArq, pCode->exception_table_length);
    }
    
    pCode->attributes_count = LE_lerU2(pArq);
    
    if(pCode->attributes_count > 0 ){
        pCode->attribute_info = (ST_tpAttribute_info*)malloc(pCode->attributes_count*sizeof(ST_tpAttribute_info*));
        for (ST_tpAttribute_info *pAux = pCode->attribute_info; pAux < pCode->attribute_info + pCode->attributes_count; pAux++) {
            pAux = LE_lerAttributes(pArq, cp, pAttributes);
        }
    }
    return pCode;
}

/**
 *  Descrição da função:
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
        for (u2 *pAux = pExceptions->exception_index_table; pAux < pExceptions->exception_index_table + pExceptions->number_of_exceptions; pAux++) {
            *pAux = LE_lerU2(pArq);
        }
    }
    return pExceptions;
}

ST_tpInnerClasses_table *LE_lerInnerClasses_table(FILE * pArq) {
    ST_tpInnerClasses_table *pClasse = (ST_tpInnerClasses_table*)malloc(sizeof(ST_tpInnerClasses_table));
    pClasse->inner_class_info_index = LE_lerU2(pArq);
    pClasse->outer_class_info_index = LE_lerU2(pArq);
    pClasse->inner_name_index = LE_lerU2(pArq);
    pClasse->inner_class_access_flags = LE_lerU2(pArq);
    
    return pClasse;
}

ST_tpInnerClasses_attribute *LE_lerInnerClassesAttribute(FILE *pArq){

    ST_tpInnerClasses_attribute *pInnerClasses = (ST_tpInnerClasses_attribute*)malloc(sizeof(ST_tpInnerClasses_attribute));
    pInnerClasses->number_of_classes = LE_lerU2(pArq);
    if (pInnerClasses->number_of_classes > 0) {
        pInnerClasses->classes = (ST_tpInnerClasses_table*)malloc(pInnerClasses->number_of_classes * sizeof(ST_tpInnerClasses_table));
        for (ST_tpInnerClasses_table *pAux = pInnerClasses->classes; pAux < pInnerClasses->classes + pInnerClasses->number_of_classes; pAux++) {
            pAux = LE_lerInnerClasses_table(pArq);
        }
    }
    return pInnerClasses;
}

/**
 *  Descrição da função:
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

ST_tpLineNumberTable_attribute *LE_lerLineNumberTable(FILE *pArq, ST_tpCp_info *cp) {
    ST_tpLineNumberTable_attribute *pLineNumberTable = (ST_tpLineNumberTable_attribute*)malloc(sizeof(ST_tpLineNumberTable_attribute));
    
    pLineNumberTable->line_number_table_length = LE_lerU2(pArq);
    
    if (pLineNumberTable->line_number_table_length > 0) {
        pLineNumberTable->info = (ST_tpLine_number_table*)malloc(pLineNumberTable->line_number_table_length*sizeof(ST_tpLine_number_table));
        
        for (ST_tpLine_number_table *pLinfo = pLineNumberTable->info; pLinfo < pLineNumberTable->info + pLineNumberTable->line_number_table_length; pLinfo++) {
            pLinfo->start_pc = LE_lerU2(pArq);
            pLinfo->line_number = LE_lerU2(pArq);
        }
    }
    return pLineNumberTable;
}
/**
 *  Descrição da função:
 *       Le Tabela de Atributos do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *  @param pAttributes      - Ponteiro para a Tabela de Atributos
 *
 */
ST_tpAttribute_info *LE_lerAttributes(FILE *pArq, ST_tpCp_info *cp, ST_tpAttribute_info *pAttributes) {
    char *pAttributeName;
    
    pAttributes->attribute_length = LE_lerU4(pArq);
    pAttributes->attribute_name_index = LE_lerU2(pArq);
    
    pAttributeName = malloc((cp[pAttributes->attribute_name_index].info.Utf8.length) * sizeof(char) + 1);
    
    strcpy((char*)pAttributeName, (const char*)(cp[pAttributes->attribute_name_index].info.Utf8.bytes));
    pAttributeName[cp[pAttributes->attribute_name_index].info.Utf8.length] = '\0'; // Toda string deve finalizar com \0
    
    if(strcmp(pAttributeName, "ConstantValue") == 0)
    {
        ST_tpConstantValue_attribute *pConstantValue = (ST_tpConstantValue_attribute*) malloc(sizeof(ST_tpConstantValue_attribute));
        pConstantValue = LE_lerConstantValueAttribute(pArq);
        pAttributes->info = (ST_tpConstantValue_attribute*) pConstantValue;
    }
    else if(strcmp(pAttributeName, "Code") == 0)
    {
        ST_tpCode_attribute *pCode = (ST_tpCode_attribute*) malloc(sizeof(ST_tpCode_attribute));
        pCode = LE_lerCodeAttribute(pArq, cp, pAttributes);
        pAttributes->info = (ST_tpCode_attribute*) pCode;
    }
    else if(strcmp(pAttributeName, "Exceptions") == 0)
    {
        ST_tpExceptions_attribute *pExceptions = (ST_tpExceptions_attribute*) malloc(sizeof(ST_tpExceptions_attribute));
        pExceptions = LE_lerExceptionsAttribute(pArq);
        pAttributes->info = (ST_tpExceptions_attribute*) pExceptions;
    }
    else if(strcmp(pAttributeName, "InnerClasses") == 0)
    {
        ST_tpInnerClasses_attribute *pInnerClasses =  (ST_tpInnerClasses_attribute*) malloc(sizeof(ST_tpInnerClasses_attribute));
        pInnerClasses = LE_lerInnerClassesAttribute(pArq);
        pAttributes->info = (ST_tpInnerClasses_attribute*) pInnerClasses;
    }
   else if(strcmp(pAttributeName, "SourceFile") == 0)
    {
        ST_tpSourceFile_attribute *pSourceFile = (ST_tpSourceFile_attribute*) malloc(sizeof(ST_tpSourceFile_attribute));
        pSourceFile = LE_lerSourceFileAttribute(pArq);
        pAttributes->info = (ST_tpSourceFile_attribute*) pSourceFile;
    }
     else if(strcmp(pAttributeName, "LineNumberTable") == 0)
    {
        ST_tpLineNumberTable_attribute *pLineNumberTable = (ST_tpLineNumberTable_attribute*) malloc(sizeof(ST_tpLineNumberTable_attribute));
        pLineNumberTable = LE_lerLineNumberTable(pArq, cp);
    }
    /*else
    {
        readUnknownAttribute(fp, pAttributes);
    }*/
    
    return pAttributes;
}

/*ST_tpAttribute_info *LE_lerAttributes(FILE *pArq, u2 attributes_count) {
    ST_tpAttribute_info *pattributes = (ST_tpAttribute_info *) malloc(attributes_count*sizeof(ST_tpAttribute_info));
    ST_tpAttribute_info *pI;
    for(pI = pattributes; pI <  (pattributes + attributes_count); pI++){
        pI->attribute_name_index = LE_lerU2(pArq);
        pI->attribute_length = LE_lerU4(pArq);
        pI->info = (u1 *) malloc(pI->attribute_length * sizeof(u1));
        fread(pI->info, 1, pI->attribute_length, pArq);
    }
    return pattributes;
} */

/**
 *  Descrição da função:
 *       Função que recebe o nome qualificado do arquivo .class e carrega o seu conteúdo,
 *       retornando o ponteiro para a estrutura classFile
 *
 *  @param  nomeArquivo     - Nome do arquivo a ser carregado
 *
 *  @return arqPontoClass   - Ponteiro para a a estrutura do .class carregada em memoria
 */
 ST_tpClassFile *LE_carregarClasse(char *nomeArquivo){
 	ST_tpClassFile *arqPontoClass = NULL; 				/* Cria ponteiro para estrutura classFile */
 	FILE * pArq = fopen(nomeArquivo,"rb");
 	
 	/* Verifica se foi possivel abrir o arquivo */
 	if(pArq == NULL){
 		printf("ERRO AO ABRIR O ARQUIVO .CLASS!\n");
 		return NULL;
	}
	
	arqPontoClass = (ST_tpClassFile*) malloc(sizeof(ST_tpClassFile));
	
	/* Verifica se o malloc n„o retornou NULL, estando a memoria cheia */
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
	if((arqPontoClass->major_version_number >= 0x35 || arqPontoClass->major_version_number <= 0x31)) {
		printf("Vers„o Java incompativel!\n");
		return NULL;
	}
	arqPontoClass->constant_pool_count = LE_lerU2(pArq);
	arqPontoClass->constant_pool_table = LE_lerConstant_pool(pArq, arqPontoClass->constant_pool_count);
	arqPontoClass->access_flags = LE_lerU2(pArq);
	arqPontoClass->this_class = LE_lerU2(pArq);
	arqPontoClass->super_class = LE_lerU2(pArq);
	arqPontoClass->interfaces_count = LE_lerU2(pArq);
	arqPontoClass->interfaces_table = LE_lerInterfaces(pArq, arqPontoClass->interfaces_count);
	arqPontoClass->fields_count = LE_lerU2(pArq);
	arqPontoClass->field_info_table = LE_lerFields(pArq, arqPontoClass->fields_count);
	arqPontoClass->methods_count = LE_lerU2(pArq);
	arqPontoClass->method_info_table = LE_lerMethods(pArq, arqPontoClass->constant_pool_table, arqPontoClass->methods_count);
	arqPontoClass->attributes_count = LE_lerU2(pArq);
	//arqPontoClass->attribute_info_table = LE_lerAttributes(pArq, arqPontoClass->constant_pool_table, arqPontoClass->attributes_count);
	// verificar qual ponteiro de contante pool passar
    return arqPontoClass;
 }

