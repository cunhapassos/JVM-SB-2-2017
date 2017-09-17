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
 *			Modulo de implementa��o: Modulo Leitor-Exibidor:
 *         	Implementa o leitor de bytecode.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @version 1.0
 * @since 07/09/2017
 *
 @}********************************************************************************/
 
 #include "structures.h"
 #include <stdio.h>
 #include <stdlib.h>
 
 u1 LE_lerU1(FILE *pArq){
 	u1 retorno;
	fread(&retorno, sizeof(u1), 1, pArq);
	
	return retorno;
}

u2 LE_lerU2(FILE *pArq){
 	u2 retorno;
	fread(&retorno, sizeof(u2), 1, pArq);
	
	return retorno;
}

 u4 LE_lerU4(FILE *pArq){
 	u4 retorno;
	fread(&retorno, sizeof(u4), 1, pArq);
	
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
				i->	info.Utf8.bytes = malloc(i->info.Utf8.length*sizeof(u1));
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
				i->info.Double.high_bytes = LE_lerU4(pArq);
				break;
			case CONSTANT_Class:
				i->info.Class.name_index = LE_lerU4(pArq);
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
}

 ST_tpClassFile *LE_lerArquivo(char *nomeArquivo){
 	ST_tpClassFile *arqPontoClass = NULL; 				/* Cria ponterio para estrutura classFile */
 	FILE * pArq = fopen(nomeArquivo,"rb");
 	
 	/* Verifica se foi possivel abrir o arquivo */
 	if(pArq == NULL){
 		printf("ERRO AO ABRIR O ARQUIVO .CLASS!\n");
 		return NULL;
	}
	
	arqPontoClass = (ST_tpClassFile*) malloc(sizeof(ST_tpClassFile));
	
	/* Verifica se o malloc n�o retornou NULL, estando a mem�ria cheia */
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
	//arqPontoClass->attribute_info_table = ;
	
	
	printf("0x%x", arqPontoClass->magic); // imprime o U4
     
 }
 
 int main(int argc, char const *argv[]){
 	printf("Ola mundo\n");
 	//char nome[50];
 	
	//scanf("%s", nome);
 	LE_lerArquivo("File.class");
 }
