/** ********************************************************************************
 *  Universidade de Brasilia - 02/2017
 *	Software Basico - Turma A
 *
 *	@addgroup MODULO LEITOR_EXIBIDOR
 *  @{
 *  @ingroup MOD_LE
 *
 *  @file leitor.c
 *  @brief 
 *			Modulo de implementação: Modulo Leitor-Exibidor:
 *         	Implementa o leitor de bytecode.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @version 1.0
 * @since 07/09/2017
 *
 @}********************************************************************************/


 #include "leitor.h"
 
 u1 LE_lerU1(FILE *pArq){
 	u1 retorno;
	fread(&retorno, sizeof(u1), 1, pArq);
	
	return retorno;
}

u2 LE_lerU2(FILE *pArq){
 	u2 retorno;
    u1 segu = LE_lerU1(pArq);
    u1 prim = LE_lerU1(pArq);
	
    retorno = ( segu << 8 | prim);
	return retorno;
}

 u4 LE_lerU4(FILE *pArq){
     u4 retorno;
     u1 quar = LE_lerU1(pArq);
     u1 terc = LE_lerU1(pArq);
     u1 segu = LE_lerU1(pArq);
     u1 prim = LE_lerU1(pArq);
     
     retorno = (quar << 24 | terc << 16 | segu << 8 | prim);
     return retorno;
}

ST_tpCp_info *LE_lerConstant_pool(FILE *pArq, u2 constant_pool_count){
	
	ST_tpCp_info *constantPool = (ST_tpCp_info *) malloc((constant_pool_count-1)*sizeof(ST_tpCp_info));
	ST_tpCp_info *i = NULL;
	
	for(i = constantPool; i <  (constantPool+constant_pool_count-1); i++ ){
		i->tag = LE_lerU1(pArq);
		switch(i->tag) {
			case CONSTANT_Utf8:
				i->info.Utf8.length = LE_lerU2(pArq);
				i->info.Utf8.bytes = malloc(i->info.Utf8.length*sizeof(u1));
//                for(u1 *j=i->info.Utf8.bytes;j<(i->info.Utf8.bytes+i->info.Utf8.length);j++)
//                    *j = LE_lerU1(pArq);
                fread(i->info.Utf8.bytes, 1, i->info.Utf8.length, pArq);
				break;
			case CONSTANT_Float:
				i->info.Float.bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Integer:
				i->info.Integer.bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Long:
				i->info.Long.high_bytes = LE_lerU4(pArq);
				i->info.Long.low_bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Double:
				i->info.Double.high_bytes = LE_lerU4(pArq);
				i->info.Double.low_bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Class:
				i->info.Class.name_index = LE_lerU2(pArq);
				break;
			case CONSTANT_String:
				i->info.String.string_index = LE_lerU2(pArq);
				break;
			case CONSTANT_Fieldref:
				i->info.Fieldref.class_index = LE_lerU2(pArq);
				i->info.Fieldref.name_and_type_index = LE_lerU2(pArq);
				break;
			case CONSTANT_Methodref:
				i->info.Methodref.class_index = LE_lerU2(pArq);
				i->info.Methodref.name_and_type_index = LE_lerU2(pArq);
				break;
			case CONSTANT_InterfaceMethodref:
				i->info.InterfaceMethodref.class_index = LE_lerU2(pArq);
				i->info.InterfaceMethodref.name_and_type_index = LE_lerU2(pArq);
				break;
			case CONSTANT_NameAndType:
				i->info.NameAndType.name_index = LE_lerU2(pArq);
				i->info.NameAndType.descriptor_index = LE_lerU2(pArq);
				break;
			default:
				break;
		}
	}
    return constantPool;
}

u2 *LE_lerInterfaces(FILE *pArq, u2 interfaces_count) {
    u2 *pinterfaces = (u2 *) malloc(interfaces_count*sizeof(u2));
    fread(pinterfaces, 1, interfaces_count*2, pArq); //ainda n‹o foi testado, pois o Classe de exemplo n‹o possui nenhuma interface
    return pinterfaces;
}

ST_tpField_info *LE_lerFields(FILE *pArq, u2 fields_count) {
    ST_tpField_info *pfields = (ST_tpField_info *) malloc(fields_count*sizeof(ST_tpField_info));
    ST_tpField_info *i = NULL;
    for(i = pfields; i <  (pfields+fields_count); i++ ){
        i->access_flags = LE_lerU2(pArq);
        i->name_index = LE_lerU2(pArq);
        i->descriptor_index = LE_lerU2(pArq);
        i->attributes_count = LE_lerU2(pArq);
        i->attributes = (ST_tpAttribute_info *) malloc(i->attributes_count*sizeof(ST_tpAttribute_info));
        ST_tpAttribute_info *j;
        for(j = i->attributes; j <  (i->attributes+i->attributes_count); j++ ){
            j->attribute_name_index = LE_lerU2(pArq);
            j->attribute_length = LE_lerU4(pArq);
            j->info = (u1 *) malloc(j->attribute_length*sizeof(u1));
            fread(j->info, 1, j->attribute_length, pArq);
        }
    }
    return pfields;
}

ST_tpMethod_info *LE_lerMethods(FILE *pArq, u2 methods_count) {
    ST_tpMethod_info *pmethods = (ST_tpMethod_info *) malloc(methods_count*sizeof(ST_tpMethod_info));
    ST_tpMethod_info *i;
    for(i = pmethods; i <  (pmethods+methods_count); i++ ){
        i->access_flags = LE_lerU2(pArq);
        i->name_index = LE_lerU2(pArq);
        i->descriptor_index = LE_lerU2(pArq);
        i->attributes_count = LE_lerU2(pArq);
        i->attributes = (ST_tpAttribute_info *) malloc(i->attributes_count*sizeof(ST_tpAttribute_info));
        ST_tpAttribute_info *j;
        for(j = i->attributes; j <  (i->attributes+i->attributes_count); j++ ){
            j->attribute_name_index = LE_lerU2(pArq);
            j->attribute_length = LE_lerU4(pArq);
            j->info = (u1 *) malloc(j->attribute_length*sizeof(u1));
            fread(j->info, 1, j->attribute_length, pArq);
        }
    }
    return pmethods;
}

ST_tpAttribute_info *LE_lerAttributes(FILE *pArq, u2 attributes_count) {
    ST_tpAttribute_info *pattributes = (ST_tpAttribute_info *) malloc(attributes_count*sizeof(ST_tpAttribute_info));
    ST_tpAttribute_info *i;
    for(i = pattributes; i <  (pattributes+attributes_count); i++){
        i->attribute_name_index = LE_lerU2(pArq);
        i->attribute_length = LE_lerU4(pArq);
        i->info = (u1 *) malloc(i->attribute_length*sizeof(u1));
        fread(i->info, 1, i->attribute_length, pArq);
    }
    return pattributes;
}

// Fun‹o que recebe o nome qualificado do arquivo .class e carrega o seu conteœdo, retornando o ponteiro para a estrutura classFile
 ST_tpClassFile *LE_lerArquivo(char *nomeArquivo){
 	ST_tpClassFile *arqPontoClass = NULL; 				/* Cria ponteiro para estrutura classFile */
 	FILE * pArq = fopen(nomeArquivo,"rb");
 	
 	/* Verifica se foi possivel abrir o arquivo */
 	if(pArq == NULL){
 		printf("ERRO AO ABRIR O ARQUIVO .CLASS!\n");
 		return NULL;
	}
	
	arqPontoClass = (ST_tpClassFile*) malloc(sizeof(ST_tpClassFile));
	
	/* Verifica se o malloc não retornou NULL, estando a memória cheia */
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

