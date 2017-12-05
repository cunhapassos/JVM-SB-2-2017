   /** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *  Software Basico - Turma A
 *
 *  @defgroup MODULO DECODER
 *  @{
 *  @ingroup MOD_DE
 *
 *  @file decoder.c
 *  @brief
 *            Relaciona o nome da instrução com seu hexadecimal
 *
 * @author ALON MOTA        - MAT. 13/0005002
 * @author DANIEL MATIAS    - MAT. 12/0139804
 * @author GABRIEL TOLLINI  - MAT. 14/0020454
 * @author PAULO PASSOS     - MAT. 10/0118577
 *
 * @version 1.0
 *
 @}********************************************************************************/
#include "decoder.h"
#include "structures.h"
#include <stdio.h>


char* DE_instruction_name[] = { //10 instrucoes por linha
    "nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", "iconst_3", "iconst_4", "iconst_5", "lconst_0", //0 ao 9
    "lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush", "ldc", "ldc_w",
    "ldc2_w", "iload", "lload", "fload","dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3",
    "lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", "dload_0", "dload_1",
    "dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload", "laload", "faload", "daload",
    "aaload", "baload", "caload", "saload", "istore", "lstore", "fstore", "dstore", "astore", "istore_0",
    "istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2",
    "fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore",
    "lastore", "fastore", "dastore", "aastore", "bastore", "castore", "sastore", "pop", "pop2", "dup",
    "dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd",
    "isub", "lsub", "fsub", "dsub", "imul", "lmul", "fmul", "dmul", "idiv", "ldiv", //100 ao 109
    "fdiv", "ddiv", "irem", "lrem", "frem", "drem", "ineg", "lneg", "fneg", "dneg",
    "ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land", "ior", "lor",
    "ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", "l2d", "f2i",
    "f2l", "f2d", "d2i", "d2l", "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl",
    "fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt", "ifge","ifgt", "ifle", "if_icmpeq", //150 ao 159
    "if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeq", "if_acmpne", "goto", "jsr", "ret",
    "tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", "dreturn", "areturn", "return", "getstatic", "putstatic",
    "getfield", "putfield", "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "invokedynamic", "new", "newarray", "anewarray",
    "arraylength", "athrow", "checkcast", "instanceof", "monitorenter", "monitorexit", "wide", "multianewarray", "ifnull", "ifnonnull",
    "goto_w", "jsr_w", "breakpoint"
};

int print_instructionName(int opcode){
    if (opcode==0){
        return 0;
    }
    else if (opcode<203){
        printf("%s", DE_instruction_name[opcode]);
    }
    else{
        printf("instrução não reconhecida\n");
    }
    return 0;
}

int printCode(ST_tpCode_attribute * pCodigo){
    
    for (int pc=0, linha = 1; pc < pCodigo->code_length; pc++, linha++) {
        int code = pCodigo->code[pc];
        if (((code>=0x00)&&(code<=0x0f))||((code>=0x1a)&&(code<=0x35))||((code>=0x3b)&&(code<=0x83))||((code>=0x85)&&(code<=0x98))||((code>=0xac)&&(code<=0xb1))||((code>=0xbe)&&(code<=0xbf))||((code>=0xc2)&&(code<=0xc3))) {
            printf("\t%d\t%d\t", linha, pc);
            print_instructionName(code);
        }
        else if((code==0x10)||(code==0x12)||(code==0xa9)||(code==0xbc)||((code>=0x15)&&(code<=0x19))||((code>=0x36)&&(code<=0x3a))){
            printf("\t%d\t%d\t", linha, pc);
            print_instructionName(code);
            pc++;
            printf(" %d ", pCodigo->code[pc]);
        }
        else {
            printf("\t%d\t%d\t", linha, pc);
            print_instructionName(code);
            pc++;
            printf(" %d ", pCodigo->code[pc]);
            pc++;
            printf(" %d ", pCodigo->code[pc]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
