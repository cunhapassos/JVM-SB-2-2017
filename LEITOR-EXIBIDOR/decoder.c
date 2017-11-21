//
//  decoder.c
//  JVM-SB-2-2017
//
//  Created by Daniel Matias on 21/11/17.
//  Copyright © 2017 Paulo Passos. All rights reserved.
//

#include "decoder.h"
#include <stdio.h>

int print_instructionName(DE_Instruction opcode){
    if (opcode==0){
        return 0;
    }
    else if (opcode){
        printf("OPCODE: 0x%x00 %s \n", opcode, DE_instruction_name[opcode]);
    }
    else{
        printf("instrução não reconhecida\n");
    }
    return 0;
}
