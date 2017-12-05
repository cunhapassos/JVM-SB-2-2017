//
//  main.c
//  JVM-SB-2-2017
//
//  Created by Paulo Passos on 17/09/17.
//  Copyright © 2017 Paulo Passos. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include "structures.h"
#include "leitor.h"
#include "exibidor.h"
#include "virtualMachine.h"
#include "pilhas_listas.h"
#include "configuracao.h"

int main(int argc, char * argv[]) {

	if (argc == 1 ) {
		printf("Especifique o arquivo .class a ser executado\n");
		return 1;
	} else {
		int exib = 0;
		char *aux;
		aux = argv[1];
		if (argc > 2)  {
			if (strcmp("+e", argv[2]) == 0) {
				exib = 1;
			}
		}

	    if(exib) {
	        EX_imprimirClassFile(LE_lerClasse(aux));
	        return 0;
	    }
	    else {
	       VM_exucutarJVM(1, aux);
	    }

	}
    //char *aux[] = {"ARQUIVOS PARA TESTES/Belote"};
    //if(VIEWER) {
     //   EX_imprimirClassFile(LE_lerClasse(aux[0]));
      //  return 0;
    //}
    //else {
    //   VM_exucutarJVM(1, aux);
    //}
    

    //char *pNomeArquivo = malloc(200*sizeof(char));
    
    //printf("Insira o nome do  arquivo .class: \n");
    //scanf("%s", pNomeArquivo);
    //getchar();
    
    
    //EX_imprimirClassFile(LE_lerArquivo(pNomeArquivo));
    
    //ST_tpClassFile *p;
    //p = LE_carregarClasse("/Users/danielmatias/Desktop/JVM-SB-2-2017/double_aritmetica.class");
/*    p = LE_carregarClasse("/Users/paulopassos/Documents/JVM-SB-2-2017/ARQUIVOS PARA TESTES/TesteExcecao.class");
    EX_imprimirClassFile(p);
    free(p);
    p = NULL;*/

    //const char* s = getenv("ROOT");
    //printf("PATH :%s\n",(s!=NULL)? s : "getenv returned NULL");


    
    
    
    
    
    /** ******************************************************************************
     *                            PARA CARREGAR MAIS DE UMA CLASSE
     ** ******************************************************************************/
    //char *aux[] = {"/Users/paulopassos/Documents/JVM-SB-2-2017/File.class", "/Users/paulopassos/Documents/JVM-SB-2-2017/double_aritmetica.class"};
    //char *aux[] = {"/Users/paulopassos/Documents/JVM-SB-2-2017/ARQUIVOS PARA TESTES/TesteExcecao.class"};
    // LEMBRAR DE INSERIR O NUMERO DE CLASSES A SEREM LIDA CONFORME O NUMERO DE STRINGS PASSADAS PARA aux[]
    //ST_tpJVM *pJVM = VM_exucutarJVM(1, aux);
     
     // TESTE DE BUSCA DE CLASSE NA JVM
     /*if (PL_buscarClasse(pJVM, "File") != NULL){
     printf("yes\n");
     }
     else{
     printf("Naaaaaaao\n");
     }*/
     
    // /Users/paulopassos/OneDrive/Documentos/13º SEMESTRE/SOFTWARE BÁSICO/TRABALHOS/JVM-SB-2-2017/File.class
    // /Users/danielmatias/Desktop/JVM-SB-2-2018/double_aritmetica.class
    return 0;
}
