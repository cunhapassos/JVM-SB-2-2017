//
//  main.c
//  JVM-SB-2-2017
//
//  Created by Paulo Passos on 17/09/17.
//  Copyright © 2017 Paulo Passos. All rights reserved.
//

#include <stdio.h>
#include "LEITOR-EXIBIDOR/structures.h"
#include "LEITOR-EXIBIDOR/leitor.h"
#include "LEITOR-EXIBIDOR/exibidor.h"
#include "LEITOR-EXIBIDOR/virtualMachine.h"
#include "LEITOR-EXIBIDOR/pilhas_listas.h"


int main(int argc, const char * argv[]) {
	
	//char *pNomeArquivo = malloc(200*sizeof(char));
	
	//printf("Insira o nome do  arquivo .class: \n");
	//scanf("%s", pNomeArquivo);
	//getchar();
	
	
	//EX_imprimirClassFile(LE_lerArquivo(pNomeArquivo));
	
	// ST_tpClassFile *p;
	// p = LE_carregarClasse("/Users/danielmatias/Desktop/JVM-SB-2-2017/ArquivosTestesLadeira/arrays/multi.class");
	// EX_imprimirClassFile(p);
	// free(p);
	// p = NULL;

	char *aux[] = {"File.class"};
    ST_tpJVM *pJVM = VM_exucutarJVM(1, aux);

    if(PL_buscarClasse(pJVM, "File") != NULL) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

	// /Users/paulopassos/OneDrive/Documentos/13º SEMESTRE/SOFTWARE BÁSICO/TRABALHOS/JVM-SB-2-2017/File.class
	// /Users/danielmatias/Desktop/JVM-SB-2-2018/double_aritmetica.class
	return 0;
}
