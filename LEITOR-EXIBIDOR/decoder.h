//
//  decoder.h
//  JVM-SB-2-2017
//
//  Created by Daniel Matias on 04/11/17.
//  Copyright © 2017 Paulo Passos. All rights reserved.
//

#ifndef decoder_h
#define decoder_h

enum DE_instructions_opcode {
    NOP, // 0X00
    ACONST_NULL,// 0X1
    ICONST_M1,// 0X2
    ICONST_0,// 0X3
    ICONST_1,// 0X4
    ICONST_2,// 0X5
    ICONST_3,// 0X6
    ICONST_4,// 0X7
    ICONST_5,// 0X8
    LCONST_0,// 0X9
    LCONST_1,// 0XA
    FCONST_0,// 0XB
    FCONST_1,// 0XC
    FCONST_2,// 0XD
    DCONST_0,// 0XE
    DCONST_1,// 0XF
    BIPUSH,// 0X10
    SIPUSH,// 0X11
    LDC,// 0X12
    LDC_W,// 0X13
    LDC2_W,// 0X14
    ILOAD,// 0X15
    LLOAD,// 0X16
    FLOAD,// 0X17
    DLOAD,// 0X18
    ALOAD,// 0X19
    ILOAD_0,// 0X1A
    ILOAD_1,// 0X1B
    ILOAD_2,// 0X1C
    ILOAD_3,// 0X1D
    LLOAD_0,// 0X1E
    LLOAD_1,// 0X1F
    LLOAD_2,// 0X20
    LLOAD_3,// 0X21
    FLOAD_0,// 0X22
    FLOAD_1,// 0X23
    FLOAD_2,// 0X24
    FLOAD_3,// 0X25
    DLOAD_0,// 0X26
    DLOAD_1,// 0X27
    DLOAD_2,// 0X28
    DLOAD_3,// 0X29
    ALOAD_0,// 0X2A
    ALOAD_1,// 0X2B
    ALOAD_2,// 0X2C
    ALOAD_3,// 0X2D
    IALOAD,// 0X2E
    LALOAD,// 0X2F
    FALOAD,// 0X30
    DALOAD,// 0X31
    AALOAD,// 0X32
    BALOAD,// 0X33
    CALOAD,// 0X34
    SALOAD,// 0X35
    ISTORE,// 0X36
    LSTORE,// 0X37
    FSTORE,// 0X38
    DSTORE,// 0X39
    ASTORE,// 0X3A
    ISTORE_0,// 0X3B
    ISTORE_1,// 0X3C
    ISTORE_2,// 0X3D
    ISTORE_3,// 0X3E
    LSTORE_0,// 0X3F
    LSTORE_1,// 0X40
    LSTORE_2,// 0X41
    LSTORE_3,// 0X42
    FSTORE_0,// 0X43
    FSTORE_1,// 0X44
    FSTORE_2,// 0X45
    FSTORE_3,// 0X46
    DSTORE_0,// 0X47
    DSTORE_1,// 0X48
    DSTORE_2,// 0X49
    DSTORE_3,// 0X4A
    ASTORE_0,// 0X4B
    ASTORE_1,// 0X4C
    ASTORE_2,// 0X4D
    ASTORE_3,// 0X4E
    IASTORE,// 0X4F
    LASTORE,// 0X50
    FASTORE,// 0X51
    DASTORE,// 0X52
    AASTORE,// 0X53
    BASTORE,// 0X54
    CASTORE,// 0X55
    SASTORE,// 0X56
    POP,// 0X57
    POP2,// 0X58
    DUP,//0X59
    DUP_X1,//0X5A
    DUP_X2,//0X5B
    DUP2,// 0X5C
    DUP2_X1,// 0X5D
    DUP2_X2,// 0X5E
    SWAP,// 0X5F
    IADD,// 0X60
    LADD,// 0X61
    FADD,// 0X62
    DADD,// 0X63
    ISUB,// 0X64
    LSUB,// 0X65
    FSUB,// 0X66
    DSUB,// 0X67
    IMUL,// 0X68
    LMUL,// 0X69
    FMUL,// 0X6A
    DMUL,// 0X6B
    IDIV,// 0X6C
    LDIV,// 0X6D
    FDIV,// 0X6E
    DDIV,// 0X6F
    IREM,// 0X70
    LREM,// 0X71
    FREM,// 0X72
    DREM,// 0X73
    INEG,// 0X74
    LNEG,// 0X75
    FNEG,// 0X76
    DNEG,// 0X77
    ISHL,// 0X78
    LSHL,// 0X79
    ISHR,// 0X7A
    LSHR,// 0X7B
    IUSHR,// 0X7C
    LUSHR,// 0X7D
    IAND,// 0X7E
    LAND,// 0X7F
    IOR,// 0X80
    LOR,// 0X81
    IXOR,// 0X82
    LXOR,// 0X83
    IINC,// 0X84
    I2L,// 0X85
    I2F,// 0X86
    I2D,// 0X87
    L2I,// 0X88
    L2F,// 0X89
    L2D,// 0X8A
    F2I,// 0X8B
    F2L,// 0X8C
    F2D,// 0X8D
    D2I,// 0X8E
    D2L,// 0X8F
    D2F,// 0X90
    I2B,// 0X91
    I2C,// 0X92
    I2S,// 0X93
    LCMP,// 0X94
    FCMPL,// 0X95
    FCMPG,// 0X96
    DCMPL,// 0X97
    DCMPG,// 0X98
    IFEQ,// 0X99
    IFNE,// 0X9A
    IFLT,// 0X9B
    IFGE,// 0X9C
    IFGT,// 0X9D
    IFLE,// 0X9E
    IF_ICMPEQ,// 0X9F
    IF_ICMPNE,// 0XA0
    IF_ICMPLT,// 0XA1
    IF_ICMPGE,// 0XA2
    IF_ICMPGT,// 0XA3
    IF_ICMPLE,// 0XA4
    IF_ACMPEQ,// 0XA5
    IF_ACMPNE,// 0XA6
    GOTO,// 0XA7
    JSR,// 0XA8
    RET,// 0XA9
    TABLESWITCH,// 0XAA
    LOOKUPSWITCH,// 0XAB
    IRETURN,// 0XAC
    LRETURN,// 0XAD
    FRETURN,// 0XAE
    DRETURN,// 0XAF
    ARETURN,// 0XB0
    RETURN,// 0XB1
    GETSTATIC,// 0XB2
    PUTSTATIC,// 0XB3
    GETFIELD,// 0XB4
    PUTFIELD,// 0XB5
    INVOKEVIRTUAL,// 0XB6
    INVOKESPECIAL,// 0XB7
    INVOKESTATIC,// 0XB8
    INVOKEINTERFACE,// 0XB9
    INVOKEDYNAMIC,// 0XBA
    NEW,// 0XBB
    NEWARRAY,// 0XBC
    ANEWARRAY,// 0XBD
    ARRAYLENGTH,// 0XBE
    ATHROW,// 0XBF
    CHECKCAST,// 0XC0
    INSTANCEOF,// 0XC1
    MONITORENTER,// 0XC2
    MONITOREXIT,// 0XC3
    WIDE,// 0XC4
    MULTIANEWARRAY,// 0XC5
    IFNULL,// 0XC6
    IFNONNULL,// 0XC7
    GOTO_W,// 0XC8
    JSR_W// 0XC9
};

typedef enum DE_instructions_opcode DE_Instruction;

extern char* DE_instruction_name[];

typedef enum DE_instructions_opcode DE_Instruction;

int print_instructionName(DE_Instruction opcode);

#endif /* decoder_h */
