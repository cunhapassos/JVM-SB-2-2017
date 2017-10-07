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
				pI->info.Utf8.bytes = malloc(pI->info.Utf8.length*sizeof(u1));
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
ST_tpMethod_info *LE_lerMethods(FILE *pArq, u2 methods_count) {
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
            pJ->attribute_name_index = LE_lerU2(pArq);
            pJ->attribute_length = LE_lerU4(pArq);
            pJ->info = (u1 *) malloc(pJ->attribute_length * sizeof(u1));
            fread(pJ->info, 1, pJ->attribute_length, pArq);
        }
    }
    return pMethods;
}

/**
 *  Descrição da função:
 *       Le Tabela de Atributos do bytecode .class
 *
 *  @param  pArq            - Ponteiro para o arquivo a ser lido
 *  @param attributes_count - Numero de elementos da Tabela de Atributos a ser lida
 *
 *  @return pattributes     - Ponteiro para a Tabela de Atributos lida
 */
ST_tpAttribute_info *LE_lerAttributes(FILE *pArq, u2 attributes_count) {
    ST_tpAttribute_info *pattributes = (ST_tpAttribute_info *) malloc(attributes_count*sizeof(ST_tpAttribute_info));
    ST_tpAttribute_info *pI;
    for(pI = pattributes; pI <  (pattributes+attributes_count); pI++){
        pI->attribute_name_index = LE_lerU2(pArq);
        pI->attribute_length = LE_lerU4(pArq);
        pI->info = (u1 *) malloc(pI->attribute_length * sizeof(u1));
        fread(pI->info, 1, pI->attribute_length, pArq);
    }
    return pattributes;
}

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
	arqPontoClass->minor_version_number = LE_lerU2(pArq);
	arqPontoClass->major_version_number = LE_lerU2(pArq);
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
	arqPontoClass->method_info_table = LE_lerMethods(pArq, arqPontoClass->methods_count);
	arqPontoClass->attributes_count = LE_lerU2(pArq);
	arqPontoClass->attribute_info_table = LE_lerAttributes(pArq, arqPontoClass->attributes_count);
	
    return arqPontoClass;
 }

