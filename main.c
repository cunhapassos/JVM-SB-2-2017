//
//  main.c
//  JVM-SB-2-2017
//
//  Created by Paulo Passos on 17/09/17.
//  Copyright © 2017 Paulo Passos. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "LEITOR-EXIBIDOR/structures.h"
#include "LEITOR-EXIBIDOR/leitor.h"
#include "LEITOR-EXIBIDOR/exibidor.h"
#include "virtualMachine.h"
#include "pilhas_listas.h"


int main(int argc, const char * argv[]) {
    
    //char *pNomeArquivo = malloc(200*sizeof(char));
    
    //printf("Insira o nome do  arquivo .class: \n");
    //scanf("%s", pNomeArquivo);
    //getchar();
    
    
    //EX_imprimirClassFile(LE_lerArquivo(pNomeArquivo));
    
    /*
    ST_tpClassFile *p;
    p = LE_carregarClasse("/Users/paulopassos/Documents/JVM-SB-2-2017/LEITOR-EXIBIDOR/File.class");
    EX_imprimirClassFile(p);
    free(p);
    p = NULL; */
    
    
/** ******************************************************************************
 *                            PARA CARREGAR MAIS DE UMA CLASSE
 ** ******************************************************************************/
    char *aux[] = {"/Users/paulopassos/Documents/JVM-SB-2-2017/LEITOR-EXIBIDOR/File.class", "/Users/paulopassos/Documents/JVM-SB-2-2017/LEITOR-EXIBIDOR/double_aritmetica.class"};
    
    // LEMBRAR DE INSERIR O NUMERO DE CLASSES A SEREM LIDA CONFORME O NUMERO DE STRINGS PASSADAS PARA aux[]
    ST_tpJVM *pJVM = VM_exucutarJVM(2, aux);
    
    // TESTE DE BUSCA DE CLASSE NA JVM
    if (PL_buscarClasse(pJVM, "File") != NULL){
        printf("yes\n");
    }
    else{
        printf("Naaaaaaao\n");
    }
    
    // /Users/paulopassos/OneDrive/Documentos/13º SEMESTRE/SOFTWARE BÁSICO/TRABALHOS/JVM-SB-2-2017/File.class
    // /Users/danielmatias/Desktop/JVM-SB-2-2018/LEITOR-EXIBIDOR/double_aritmetica.class
    return 0;
}
