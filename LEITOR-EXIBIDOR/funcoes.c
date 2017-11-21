/**
* UnB - 2/2017 - Software Basico
* Funcoes a serem utilizadas pela jvm
* Autor: Alon Mota
*
*/

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include "virtualMachine.h"
#include "pilhas_listas.h"
#include "instrucoes.h"
/*
*    Para ler algum argumento do code incremente o PC usando 
    thread->PC ++;
*/
void IT_executaInstrucao(ST_tpJVM *pJVM, ST_tpStackFrame *pFrame, ST_tpVariable **Retorno) {
    u1 opcode = *(pJVM->thread->PC);
    printf("%d = x%0x\t", opcode, opcode);

    switch(opcode) {


        /********************************************************************************************
        
            nop : Do nothing
            page : 547
            
            @inputs: 
            @pop: .. >
            @push: .. 

            throws :

        *******************************************************************************************/
        case 0x00:
            break;

        
        /********************************************************************************************
        
            aconst_null : Push null
            page : 372
            
            @inputs: 
            @pop: .. >
            @push: .. null

            throws :

        *******************************************************************************************/
        case 0x01:
            FU_pushNull(pFrame);
            break;



        /********************************************************************************************
        
            iconst_m1: Push int constant -1 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. -1

            throws:

        *******************************************************************************************/
        case 0x02:
            FU_pushConstInt(pFrame, -1);
            break;



        /********************************************************************************************
        
            iconst_0: Push int constant 0 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. 0

            throws::

        *******************************************************************************************/
        case 0x03:
            FU_pushConstInt(pFrame, 0);
            break;



        /********************************************************************************************
        
            iconst_1: Push int constant 1 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. 1

            throws:

        *******************************************************************************************/
        case 0x04:
            FU_pushConstInt(pFrame, 1);
            break;



        /********************************************************************************************
        
            iconst_2: Push int constant 2 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. 2

            throws:

        *******************************************************************************************/
        case 0x05:
            FU_pushConstInt(pFrame, 2);
            break;



        /********************************************************************************************
        
            iconst_3: Push int constant 3 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. 3

            throws:

        *******************************************************************************************/
        case 0x06:
            FU_pushConstInt(pFrame, 3);
            break;



        /********************************************************************************************
        
            iconst_4: Push int constant 4 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. 4

            throws:

        *******************************************************************************************/
        case 0x07:
            FU_pushConstInt(pFrame, 4);
            break;



        /********************************************************************************************
        
            iconst_5: Push int constant 5 on stack
            page: 458
            
            @inputs:
            @pop: .. >
            @push: .. 5

            throws:

        *******************************************************************************************/
        case 0x08:
            FU_pushConstInt(pFrame, 5);
            break;



        /********************************************************************************************
        
            lconst_0: Push long const 0 on stack
            page: 514
            
            @inputs:
            @pop: .. >
            @push: .. 0

            throws:

        *******************************************************************************************/
        case 0x09:
            FU_pushConstLong(pFrame, 0);
            break;



        /********************************************************************************************
        
            lconst_1: Push long const 1 on stack
            page: 514
            
            @inputs:
            @pop: .. >
            @push: .. 1

            throws:
            
        *******************************************************************************************/
        case 0x0a:
            FU_pushConstLong(pFrame, 1);
            break;



        /********************************************************************************************
        
            fconst_0: Push float
            page: 428
            
            @inputs: 
            @pop: .. >
            @push: .. 0

            throws:
            
        *******************************************************************************************/
        case 0x0b:
            FU_pushConstFloat(pFrame, 0);
            break;



        /********************************************************************************************
        
            fconst_1: Push float
            page: 428
            
            @inputs: 
            @pop: .. >
            @push: .. 1

            throws:

        *******************************************************************************************/
        case 0x0c:
            FU_pushConstFloat(pFrame, 1);
            break;



        /********************************************************************************************
        
            fconst_2: Push float
            page: 428
            
            @inputs: 
            @pop: .. >
            @push: .. 2

            throws:

        *******************************************************************************************/
        case 0x0d:
            FU_pushConstFloat(pFrame, 2);
            break;



        /********************************************************************************************
        
            dconst_0: Push double
            page: 398
            
            @inputs: 
            @pop: .. >
            @push: .. 0

            throws:

        *******************************************************************************************/
        case 0x0e:
            FU_pushConstDouble(pFrame, 0);
            break;



        /********************************************************************************************
        
            dconst_1: Push double
            page: 398
            
            @inputs: 
            @pop: .. >
            @push: .. 1

            throws:

        *******************************************************************************************/
        case 0x0f:
            FU_pushConstDouble(pFrame, 1);
            break;



        /********************************************************************************************
        
            bipush: Push byte
            page: 384
            
            @inputs: byte
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x10:
            FU_bipush(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            sipush: Push short
            page: 558
            
            @inputs: byte1, byte2
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x11:
            FU_sipush(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            ldc: Push item from run-time constant pool
            page: 514
            
            @inputs: index
            @pop: ..  >
            @push: .. value

            throws:
                -> Linking exceptions
                -> Method exceptions
            
        *******************************************************************************************/
        case 0x12:
            FU_ldc(pJVM, pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            ldc_w: Push item from run-time constant pool (wide index)
            page: 517
            
            @inputs: indexbyte1, indexbyte2
            @pop: ..  >
            @push: .. value

            throws:
                -> Linking exceptions
                -> Method exceptions
            
        *******************************************************************************************/
        case 0x13:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;



        /********************************************************************************************
        
            ldc2_w: Push long or double from run-time constant pool (wide index)
            page: 517
            
            @inputs: indexbyte1, indexbyte2
            @pop: ..  >
            @push: .. value

            throws:
            
        *******************************************************************************************/
        case 0x14:
            FU_ldc2_w(pJVM, pFrame, &pJVM->thread->PC);
            
            //FU_ldc2_w(pJVM, pFrame, &opcode);
            break;



        /********************************************************************************************
        
            iload: Load int from local variable
            page: 468
            
            @inputs: index
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x15:
            FU_iload(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            lload: Load long from local variable
            page: 521
            
            @inputs: index
            @pop: .. >
            @push: ..value

            throws:

        *******************************************************************************************/
        case 0x16:
            FU_lload(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            fload: Load float from local variable
            page: 431
            
            @inputs: index
            @pop: .. >
            @push: ..value

            throws:

        *******************************************************************************************/
        case 0x17:
            FU_fload(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            dload: Load double from local variable
            page: 401
            
            @inputs: index
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x18:
            FU_dload(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            aload: Load reference from local variable
            page: 373
            
            @inputs: index
            @pop: .. >
            @push: .. objectref

            throws :

        *******************************************************************************************/
        case 0x19:
            FU_aload(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            iload_0: Load int from local variable 0
            page: 469
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x1a:
            FU_iload_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            iload_1: Load int from local variable 1
            page: 469
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x1b:
            FU_iload_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            iload_2: Load int from local variable 2
            page: 469
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x1c:
            FU_iload_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            iload_3: Load int from local variable 3
            page: 469
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x1d:
            FU_iload_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            lload_0: Load long from local variable 0
            page: 522
            
            @inputs: 
            @pop: .. >
            @push: ..value

            throws:

        *******************************************************************************************/
        case 0x1e:
            FU_lload_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            lload_1: Load long from local variable 1
            page: 522
            
            @inputs: 
            @pop: .. >
            @push: ..value

            throws:

        *******************************************************************************************/
        case 0x1f:
            FU_lload_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            lload_2: Load long from local variable 2
            page: 522
            
            @inputs: 
            @pop: .. >
            @push: ..value

            throws:

        *******************************************************************************************/
        case 0x20:
            FU_lload_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            lload_3: Load long from local variable 3
            page: 522
            
            @inputs: 
            @pop: .. >
            @push: ..value

            throws:

        *******************************************************************************************/
        case 0x21:
            FU_lload_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            fload_0: Load float from local variable 0
            page: 432
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x22:
            FU_fload_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            fload_1: Load float from local variable 1
            page: 432
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x23:
            FU_fload_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            fload_2: Load float from local variable 2
            page: 432
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x24:
            FU_fload_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            fload_3: Load float from local variable 3
            page: 432
            
            @inputs:
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x25:
            FU_fload_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            dload_0: Load double from local variable from local variable 0
            page: 402
            
            @inputs:    
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x26:
            FU_dload_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            dload_1: Load double from local variable from local variable 1
            page: 402
            
            @inputs:    
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x27:
            FU_dload_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            dload_2: Load double from local variable from local variable 2
            page: 402
            
            @inputs:    
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x28:
            FU_dload_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            dload_3: Load double from local variable from local variable 3
            page: 402
            
            @inputs:    
            @pop: .. >
            @push: .. value

            throws:

        *******************************************************************************************/
        case 0x29:
            FU_dload_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            aload_0: Load the 0 index from reference from local variable
            page: 374
            
            @inputs: 
            @pop: .. >
            @push: .. objectref

            throws :

        *******************************************************************************************/
        case 0x2a:
            FU_aload_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            aload_1: Load the 1 index from reference from local variable
            page: 374

            @inputs: 
            @pop: .. >
            @push: .. objectref

            throws :

        *******************************************************************************************/
        case 0x2b:
            FU_aload_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            aload_2: Load the 2 index from reference from local variable
            page: 374

            @inputs: 
            @pop: .. >
            @push: .. objectref

            throws :

        *******************************************************************************************/
        case 0x2c:
            FU_aload_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            aload_3: Load the 3 index from reference from local variable
            page: 374

            @inputs: 
            @pop: .. >
            @push: .. objectref

            throws :

        *******************************************************************************************/
        case 0x2d:
            FU_aload_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            iaload: Load int from array
            page: 455
            
            @inputs:
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x2e:
            FU_iaload(pFrame);
            break;

        /********************************************************************************************
        
            laload: Load long from array
            page: 510
            
            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x2f:
            FU_laload(pFrame);
            break;



        /********************************************************************************************
        
            faload: Load float from array
            page: 424
            
            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x30:
            FU_faload(pFrame);
            break;



        /********************************************************************************************
        
            daload: Load double from array
            page: 394
            
            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x31:
            FU_daload(pFrame);
            break;



        /********************************************************************************************
        
            aaload: Load reference from array
            page: 369
            
            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x32:
            FU_aaload(pFrame);
            break;



        /********************************************************************************************
        
            baload: Load bytr or boolean from array
            page: 382

            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws :
                -> NullPointerException ~ Case arrayref is null
                -> ArrayIndexOutOfBoundsException ~ Case index is not inside arrayref limits


        *******************************************************************************************/
        case 0x33:
            FU_baload(pFrame);
            break;



        /********************************************************************************************
        
            caload: Load char from array
            page: 385
            
            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ Case arrayref is null
                -> ArrayIndexOutOfBoundsException ~ Case index is not inside arrayref limits

        *******************************************************************************************/
        case 0x34:
            FU_caload(pFrame);
            break;



        /********************************************************************************************
        
            saload: Load short from array
            page: 385
            
            @inputs: 
            @pop: .. arrayref, index >
            @push: .. value

            throws:
                -> NullPointerException ~ Case arrayref is null
                -> ArrayIndexOutOfBoundsException ~ Case index is not inside arrayref limits

        *******************************************************************************************/
        case 0x35:
            FU_saload(pFrame);
            break;



        /********************************************************************************************
        
            istore: Store int into local variable
            page: 499
            
            @inputs: index
            @pop: .. value >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x36:
            FU_istore(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            lstore: Store long into local variable
            page: 439
            
            @inputs: index
            @pop: .. value >
            @push: ..

            throws:

        *******************************************************************************************/
        case 0x37:
            FU_lstore(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            fstore: Store float into local variable
            page: 439
            
            @inputs: index
            @pop: .. value >
            @push: ..

            throws:

        *******************************************************************************************/
        case 0x38:
            FU_fstore(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            dstore: Store double into local variable
            page: 409
            
            @inputs: index
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x39:
            FU_dstore(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            astore: Store reference in local variable
            page: 378

            @inputs: index
            @pop: .. objectref >
            @push: ..

            throws :


        *******************************************************************************************/
        case 0x3a:
            FU_astore(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            istore_0: Store int into local variable 0
            page: 500
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x3b:
            FU_istore_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            istore_1: Store int into local variable 1
            page: 500
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x3c:
            FU_istore_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            istore_2: Store int into local variable 2
            page: 500
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x3d:
            FU_istore_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            istore_3: Store int into local variable 3
            page: 500
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x3e:
            FU_istore_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            lstore_0: Store long into local variable 0
            page: 533
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x3f:
            FU_lstore_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            lstore_1: Store long into local variable 1
            page: 533
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x40:
            FU_lstore_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            lstore_2: Store long into local variable 2
            page: 533
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x41:
            FU_lstore_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            lstore_3: Store long into local variable 3
            page: 533
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x42:
            FU_lstore_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            fstore_0: Store float into local variable 0
            page: 440
            
            @inputs:
            @pop: .. value >
            @push: ..

            throws:

        *******************************************************************************************/
        case 0x43:
            FU_fstore_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            fstore_1: Store float into local variable 1
            page: 440
            
            @inputs:
            @pop: .. value >
            @push: ..

            throws:

        *******************************************************************************************/
        case 0x44:
            FU_fstore_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            fstore_2: Store float into local variable 2
            page: 440
            
            @inputs:
            @pop: .. value >
            @push: ..

            throws:

        *******************************************************************************************/
        case 0x45:
            FU_fstore_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            fstore_3: Store float into local variable 3
            page: 440
            
            @inputs:
            @pop: .. value >
            @push: ..

            throws:

        *******************************************************************************************/
        case 0x46:
            FU_fstore_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            dstore_0: Store double into local variable 0
            page: 410
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x47:
            FU_dstore_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            dstore_1: Store double into local variable 1
            page: 410
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x48:
            FU_dstore_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            dstore_2: Store double into local variable 2
            page: 410
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x49:
            FU_dstore_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            dstore_3: Store double into local variable 3
            page: 410
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x4a:
            FU_dstore_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            astore_0: Store reference into local variable 0
            page: 379

            @inputs: 
            @pop: .. objectref >
            @push: ..

            throws :

        *******************************************************************************************/
        case 0x4b:
            FU_astore_n(pFrame, 0);
            break;



        /********************************************************************************************
        
            astore_1: Store reference into local variable 1
            page: 379

            @inputs: 
            @pop: .. objectref >
            @push: ..

            throws :

        *******************************************************************************************/
        case 0x4c:
            FU_astore_n(pFrame, 1);
            break;



        /********************************************************************************************
        
            astore_2: Store reference into local variable 2
            page: 379

            @inputs: 
            @pop: .. objectref >
            @push: ..

            throws :

        *******************************************************************************************/
        case 0x4d:
            FU_astore_n(pFrame, 2);
            break;



        /********************************************************************************************
        
            astore_3: Store reference into local variable 3
            page: 379

            @inputs: 
            @pop: .. objectref >
            @push: ..

            throws :

        *******************************************************************************************/
        case 0x4e:
            FU_astore_n(pFrame, 3);
            break;



        /********************************************************************************************
        
            iastore: Store into int array
            page: 457
            
            @inputs:
            @pop: .. arrayref, index, value >
            @push: .. 

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref
            
        *******************************************************************************************/
        case 0x4f:
            FU_iastore(pFrame);
            break;



        /********************************************************************************************
        
            lastore: Store into long array
            page: 512
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: .. 

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x50:
            FU_lastore(pFrame);
            break;



        /********************************************************************************************
        
            fastore: Load float from array
            page: 425
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: .. 

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref

        *******************************************************************************************/
        case 0x51:
            FU_fastore(pFrame);
            break;



        /********************************************************************************************
        
            dastore: Store into double array
            page: 395
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: .. 

            throws:
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref


        *******************************************************************************************/
        case 0x52:
            FU_dastore(pFrame);
            break;



        /********************************************************************************************
        
            aastore : Store into reference array
            page : 370
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: 

            throws :
                -> NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref
                -> ArrayStoreException ~ If type of value is diferent from arrayref type


        *******************************************************************************************/
        case 0x53:
            FU_aastore(pFrame);
            break;



        /********************************************************************************************
        
            bastore : Store into byte or boolean array
            page : 383
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: ..

            throws :
                ->  NullPointerException ~ If arrayRef is null
                -> ArrayIndexOutOfBoundsException ~ If index is not within the bounds of arrayref


        *******************************************************************************************/
        case 0x54:
            FU_bastore(pFrame);
            break;



        /********************************************************************************************
        
            castore: Store into char array
            page: 386
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: .. 

            throws:
                -> NullPointerException ~ Case arrayref is null
                -> ArrayIndexOutOfBoundsException ~ Case index is not inside arrayref limits

        *******************************************************************************************/
        case 0x55:
            FU_castore(pFrame);
            break;



        /********************************************************************************************
        
            sastore: Store into short array
            page: 556
            
            @inputs: 
            @pop: .. arrayref, index, value >
            @push: .. 

            throws:
                -> NullPointerException ~ Case arrayref is null
                -> ArrayIndexOutOfBoundsException ~ Case index is not inside arrayref limits

        *******************************************************************************************/
        case 0x56:
            FU_sastore(pFrame);
            break;



        /********************************************************************************************
        
            pop: Pop the top operand stack value
            page: 548
            
            @inputs: 
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x57:
            FU_pop(pFrame);
            break;



        /********************************************************************************************
        
            pop2: Pop the two top operand stack value
            page: 548
            
            @inputs: 
            @pop: .. value2, value1 >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0x58:
            FU_pop2(pFrame);
            break;



        /********************************************************************************************
        
            dup: Duplicate the top operand stack value 
            page: 412
            
            @inputs: 
            @pop: .. value >
            @push: .. value, value

            throws:

        *******************************************************************************************/
        case 0x59:
            FU_dup(pFrame);
            break;



        /********************************************************************************************
        
            dup_x1: Duplicate the top operand stack value and insert two values down
            page: 413
            
            @inputs: 
            @pop: .. value2, value1 >
            @push: .. value1, value2, value1

            throws:

        *******************************************************************************************/
        case 0x5a:
            FU_dup_x1(pFrame);
            break;



        /********************************************************************************************
        
            dup_x2: Duplicate the top operand stack value and insert two or three values down
            page: 414
            
            @inputs: 
            @pop: .. value3, value2, value1 >
            @push: .. value1, value3, value2, value1

            throws:

        *******************************************************************************************/
        case 0x5b:
            FU_dup_x2(pFrame);
            break;



        /********************************************************************************************
        
            dup2: Duplicate the two top operand stack values
            page: 415
            
            @inputs: 
            @pop: .. value2, value1 >
            @push: .. value2, value1, value2, value1

            throws:

        *******************************************************************************************/
        case 0x5c:
            FU_dup2(pFrame);
            break;



        /********************************************************************************************
        
            dup2_x1: Duplicate the two top operand stack values and insert one value down
            page: 416
            
            @inputs: 
            @pop: .. value3, value2, value1 >
            @push: .. value2, value1, value3, value2, value1

            throws:

        *******************************************************************************************/
        case 0x5d:
            FU_dup2_x1(pFrame);
            break;



        /********************************************************************************************
        
            dup2_x2: Duplicate the two top operand stack values and insert two values down
            page: 416
            
            @inputs: 
            @pop: .. value4, value3, value2, value1 >
            @push: .. value2, value1, value4, value3, value2, value1

            throws:

        *******************************************************************************************/
        case 0x5e:
            FU_dup2_x2(pFrame);
            break;



        /********************************************************************************************
        
            swap: Swap the two operand stack values
            page: 454
            
            @inputs:
            @pop: .. value2, value1 >
            @push: .. value1, value2

            throws:

        *******************************************************************************************/
        case 0x5f:
            FU_swap(pFrame);
            break;



        /********************************************************************************************
        
            iadd: Add int
            page: 454
            
            @inputs:
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x60:
            FU_iadd(pFrame);
            break;



        /********************************************************************************************
        
            ladd: Add long
            page: 509
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x61:
            FU_ladd(pFrame);
            break;



        /********************************************************************************************
        
            fadd: Add float
            page: 422
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x62:
            FU_fadd(pFrame);
            break;



        /********************************************************************************************
        
            dadd: Add double
            page: 391
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x63:
            FU_dadd(pFrame);
            break;



        /********************************************************************************************
        
            isub: Subtract int
            page: 501
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x64:
            FU_isub(pFrame);
            break;



        /********************************************************************************************
        
            lsub: Substract long
            page: 534
            
            @inputs:
            @pop: .. value1, value 2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x65:
            FU_lsub(pFrame);
            break;



        /********************************************************************************************
        
            fsub: Substract float
            page: 441
            
            @inputs:
            @pop: .. value1, value 2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x66:
            FU_fsub(pFrame);
            break;



        /********************************************************************************************
        
            dsub: Subtract double
            page: 411
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x67:
            FU_dsub(pFrame);
            break;



        /********************************************************************************************
        
            imul: Multipli int
            page: 470
            
            @inputs:
            @pop: .. value1, value2>
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x68:
            FU_imul(pFrame);
            break;



        /********************************************************************************************
        
            lmul: Multipli long
            page: 523
            
            @inputs:
            @pop: ..value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x69:
            FU_lmul(pFrame);
            break;



        /********************************************************************************************
        
            fmul: Multipli float
            page: 433
            
            @inputs:
            @pop: ..value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x6a:
            FU_fmul(pFrame);
            break;



        /********************************************************************************************
        
            dmul: Multipli double
            page: 403
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x6b:
            FU_dmul(pFrame);
            break;



        /********************************************************************************************
        
            idiv: Divide int
            page: 459
            
            @inputs:
            @pop: .. value1, value2 >
            @push: .. result

            throws:
                -> ArithmeticException ~ If divisor is 0

        *******************************************************************************************/
        case 0x6c:
            FU_idiv(pFrame);
            break;



        /********************************************************************************************
        
            ldiv: Divide long
            page: 520
            
            @inputs:
            @pop: .. value1, value2 >
            @push: .. result

            throws:
                -> ArithmeticException ~ If divisor is 0

            
        *******************************************************************************************/
        case 0x6d:
            FU_ldiv(pFrame);
            break;



        /********************************************************************************************
        
            fdiv: Divide float
            page: 429
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x6e:
            FU_fdiv(pFrame);
            break;



        /********************************************************************************************
        
            ddiv: Divide double
            page: 399
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x6f:
            FU_ddiv(pFrame);
            break;



        /********************************************************************************************
        
            irem: Reminder int
            page: 495
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:
                -> ArithmeticException ~ If divider = 0

        *******************************************************************************************/
        case 0x70:
            FU_irem(pFrame);
            break;



        /********************************************************************************************
        
            lrem: Reminder long
            page: 528
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:
                -> ArithmeticException ~ If divider = 0

        *******************************************************************************************/
        case 0x71:
            FU_lrem(pFrame);
            break;



        /********************************************************************************************
        
            frem: Remainder float
            page: 43437
            
            @inputs:
            @pop: ..value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x72:
            FU_frem(pFrame);
            break;



        /********************************************************************************************
        
            drem: Remainder double
            page: 406
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x73:
            FU_drem(pFrame);
            break;



        /********************************************************************************************
        
            ineg: Negate int
            page: 471
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x74:
            FU_ineg(pFrame);
            break;



        /********************************************************************************************
        
            lneg: Negate long
            page: 524
            
            @inputs:
            @pop: ..value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x75:
            FU_lneg(pFrame);
            break;



        /********************************************************************************************
        
            fneg: Negate float
            page: 435
            
            @inputs:
            @pop: ..value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x76:
            FU_fneg(pFrame);
            break;



        /********************************************************************************************
        
            dneg: Negate double
            page: 405
            
            @inputs: 
            @pop: .. value1 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x77:
            FU_dneg(pFrame);
            break;



        /********************************************************************************************
        
            ishl: Shift left int
            page: 497
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:
            
        *******************************************************************************************/
        case 0x78:
            FU_ishl(pFrame);
            break;



        /********************************************************************************************
        
            lshl: Shift left long
            page: 530
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:
            
        *******************************************************************************************/
        case 0x79:
            FU_lshl(pFrame);
            break;



        /********************************************************************************************
        
            ishr: Shift right int
            page: 498
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:
            
        *******************************************************************************************/
        case 0x7a:
            FU_ishr(pFrame);
            break;



        /********************************************************************************************
        
            lshr: Shift right long
            page: 532
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:
            
        *******************************************************************************************/
        case 0x7b:
            FU_lshr(pFrame);
            break;



        /********************************************************************************************
        
            iushr: Logical shift right int
            page: 502
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x7c:
            FU_iushr(pFrame);
            break;



        /********************************************************************************************
        
            lushr: Logical shift right long
            page: 535
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x7d:
            FU_lushr(pFrame);
            break;



        /********************************************************************************************
        
            iand: Boolean AND int
            page: 455
            
            @inputs:
            @pop: .. value1, value2 >
            @push: .. result

            throws:
            
        *******************************************************************************************/
        case 0x7e:
            FU_iand(pFrame);
            break;



        /********************************************************************************************
        
            land: Boolean AND long
            page: 511
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x7f:
            FU_land(pFrame);
            break;



        /********************************************************************************************
        
            ior: Boolean Or int
            page: 493
            
            @inputs:
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x80:
            FU_ior(pFrame);
            break;



        /********************************************************************************************
        
            lor: Boolean Or long
            page: 527
            
            @inputs:
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x81:
            FU_lor(pFrame);
            break;



        /********************************************************************************************
        
            ixor: Boolean XOR int
            page: 503
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x82:
            FU_ixor(pFrame);
            break;



        /********************************************************************************************
        
            lxor: Boolean XOR long
            page: 536
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x83:
            FU_lxor(pFrame);
            break;



        /********************************************************************************************
        
            iinc: Increment local variable by constant
            page: 467
            
            @inputs: index, const
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x84:
            FU_iinc(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************
        
            i2l: Convert int to long
            page: 452
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x85:
            FU_i2l(pFrame);
            break;



        /********************************************************************************************
        
            i2f: Convert int to float
            page: 451
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x86:
            FU_i2f(pFrame);
            break;



        /********************************************************************************************
        
            i2d: Convert int to double
            page: 450
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x87:
            FU_i2d(pFrame);
            break;



        /********************************************************************************************
        
            l2i: Convert long to int
            page: 508
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x88:
            FU_l2i(pFrame);
            break;



        /********************************************************************************************
        
            l2f: Convert long to float
            page: 507
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x89:
            FU_l2f(pFrame);
            break;



        /********************************************************************************************
        
            l2d: Convert long to double
            page: 506
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x8a:
            FU_l2d(pFrame);
            break;



        /********************************************************************************************
        
            f2i: Convert float to int
            page: 420
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x8b:
            FU_f2i(pFrame);
            break;



        /********************************************************************************************
        
            f2l: Convert float to long
            page: 421
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x8c:
            FU_f2l(pFrame);
            break;




        /********************************************************************************************
        
            f2d: Convert float to double
            page: 419
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x8d:
            FU_f2d(pFrame);
            break;



        /********************************************************************************************
        
            d2i: Convert double to integer
            page: 390
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x8e:
            FU_d2i(pFrame);
            break;



        /********************************************************************************************
        
            d2l: Convert double to long
            page: 391
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x8f:
            FU_d2l(pFrame);
            break;



        /********************************************************************************************
        
            d2f: Convert double to float
            page: 389
            
            @inputs: 
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x90:
            FU_d2f(pFrame);
            break;



        /********************************************************************************************
        
            i2b: Convert int to bayte
            page: 448
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x91:
            FU_i2b(pFrame);
            break;



        /********************************************************************************************
        
            i2c: Convert int to char
            page: 449
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x92:
            FU_i2c(pFrame);
            break;



        /********************************************************************************************
        
            i2s: Convert int to short
            page: 453
            
            @inputs:
            @pop: .. value >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x93:
            FU_i2s(pFrame);
            break;



        /********************************************************************************************
        
            lcmp: Compare long
            page: 513
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x94:
            FU_lcmp(pFrame);
            break;

        /********************************************************************************************
        
            fcmpl: Compare float
            page: 426
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

         *******************************************************************************************/
        case 0x95:
            FU_fcmpl(pFrame);
            break;
        
        /********************************************************************************************
        
            fcmpg: Compare float
            page: 426
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x96:
            FU_fcmpg(pFrame);
            break;



        /********************************************************************************************
        
            dcmpl: Compare double
            page: 396
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x97:
            FU_dcmpl(pFrame);
            break;



        /********************************************************************************************
        
            dcmpg: Compare double
            page: 396
            
            @inputs: 
            @pop: .. value1, value2 >
            @push: .. result

            throws:

        *******************************************************************************************/
        case 0x98:
            FU_dcmpg(pFrame);
            break;



        /********************************************************************************************
        
            ifeq: Branch if  value = 0
            page: 463
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x99:
            FU_ifeq(pFrame, &pJVM->thread->PC);
            break;



        /********************************************************************************************

            ifne: Branch if  value ≠ 0
            page: 463
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x9a:
            FU_ifne(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            iflt: Branch if  value < 0
            page: 463
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x9b:
            FU_iflt(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            ifge: Branch if  value >= 0
            page: 463
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x9c:
            FU_ifge(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            ifgt: Branch if  value > 0
            page: 463
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x9d:
            FU_ifgt(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            ifle: Branch if  value <= 0
            page: 463
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x9e:
            FU_ifle(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_cmpeq: Branch if value1 = value2
            page: 461
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0x9f:
            FU_if_icmpeq(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_cmpne: Branch if value1 ≠ value2
            page: 461
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xa0:
            FU_if_icmpne(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_cmplt: Branch if  value1 < value2
            page: 461
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0xa1:
            FU_if_icmplt(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_cmple: Branch if  value1 =< value2
            page: 461
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0xa2:
            FU_if_icmpge(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_cmpgt: Branch if  value1 g value2
            page: 461
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0xa3:
            FU_if_icmpgt(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_cmpge: Branch if  value1 >= value2
            page: 461
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:
            
        *******************************************************************************************/
        case 0xa4:
            FU_if_icmple(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_acmpeq: Branch if reference comparizon suceeds
            page: 460
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xa5:
            FU_if_acmpeq(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            if_acmpne: Branch if reference comparizon suceeds
            page: 460
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value1, value2 >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xa6:
            FU_if_acmpne(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            goto: Branch always
            page: 446
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xa7:
            FU_goto(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            jsr: Jump subroutine
            page: 504
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. >
            @push: .. address    

            throws:

        *******************************************************************************************/
        case 0xa8:
            FU_jsr(pFrame, &pJVM->thread->PC);
            break;

        /********************************************************************************************
        
            ret: Return from subroutine
            page: 554
            
            @inputs: index
            @pop: .. >
            @push: ..     

            throws:

        *******************************************************************************************/
        case 0xa9:
            FU_ret(pFrame, &pJVM->thread->PC);
            break;

        /********************************************************************************************
        
            
            tableswitch: Access jump table by index and jump
            page: 496
            
            @inputs: 0-3 byte pad, defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, 
                        lowbyte1, lowbyte2, lowbyte3, lowbyte4, highbyte1, highbyte2, highbyte3,
                        highbyte4, jump of sets...
            @pop: .. index >
            @push: .. 

            throws:
        *******************************************************************************************/
        case 0xaa:
            FU_tableswitch(pFrame, &pJVM->thread->PC);
            break;

        /********************************************************************************************
        
            lookupswitch: Access jump table by key match and jump
            page: 496
            
            @inputs: 0-3 byte pad, defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, 
                        npairs1, npairs2, npairs3, npairs4, match-offset pairs ..
            @pop: .. key >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xab:
            FU_lookupswitch(pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            ireturn: Return int from method
            page: 496
            
            @inputs: 
            @pop: .. value >
            @push: .. empty

            throws:
                -> IllegalMonitorStateException ~ If violates structure locking rules

        *******************************************************************************************/
        case 0xac:
            FU_ireturn(pFrame, Retorno);
            break;
        /********************************************************************************************
        
            lreturn: Return long from method
            page: 529
            
            @inputs: 
            @pop: .. value >
            @push: .. empty

            throws:
                -> IllegalMonitorStateException ~ If violates structure locking rules

        *******************************************************************************************/
        case 0xad:
            FU_lreturn(pFrame, Retorno);
            break;
        /********************************************************************************************
        
            freturn: Return float from method
            page: 438
            
            @inputs:
            @pop: ..value >
            @push: .. empty

            throws:
                -> IllegalMonitorStateException ~ If violates structure locking rules

        *******************************************************************************************/
        case 0xae:
            FU_freturn(pFrame, Retorno);
            break;

        /********************************************************************************************
        
            dretunr: Rethurn double from method
            page: 408
            
            @inputs: 
            @pop: .. value >
            @push: .. [empty]

            throws:
                -> IllegalMonitorStateException ~ If violates structure locking rules

        *******************************************************************************************/
        case 0xaf:
            FU_dreturn(pFrame, Retorno);
            break;

        /********************************************************************************************
        
            areturn: Return reference from method
            page: 376

            @inputs: 
            @pop: .. objectref >
            @push: [empty]

            throws :
                -> IllegalMonitorStateException ~ If violates structure locking rules

        *******************************************************************************************/
        case 0xb0:
            FU_areturn(pFrame, Retorno);
            break;
        /********************************************************************************************
        
            return: Return void from method
            page: 555

            @inputs: 
            @pop: .. >
            @push: [empty]

            throws :
                -> IllegalMonitorStateException ~ If violates structure locking rules

        *******************************************************************************************/
        case 0xb1:
            FU_return(pFrame);
            break;
        /********************************************************************************************
        
            getstatic: Get static field from class
            page: 444
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. >
            @push: .. value

            throws:
                -> field resolution errors
                -> IncompatibleClassChangeError ~ If the resolved field is not a static field
                -> Error ~ If this execution couses an inicialization of the class

        *******************************************************************************************/
        case 0xb2:
            FU_getstatic(pJVM, pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            putstatic: Set static field in class
            page: 550
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. value >
            @push: .. 

            throws:
                -> field resolution errors
                -> IncompatibleClassChangeError ~ If the resolved field is a static field
                -> IllegalAccessError ~ If fiel is final

        *******************************************************************************************/
        case 0xb3:
            FU_putstatic(pJVM, pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            getfield: Fetch field from object
            page: 442
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. objectref >
            @push: .. value

            throws:
                -> field resolution errors
                -> IncompatibleClassChangeError ~ If the resolved field is a static field
                -> NullPointerException ~ If objectref is null

        *******************************************************************************************/
        case 0xb4:
            FU_getfield(pJVM, pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            putfield: Set fiel in object
            page: 550
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. objectref, value >
            @push: .. 

            throws:
                -> field resolution errors
                -> IncompatibleClassChangeError ~ If the resolved field is a static field
                -> NullPointerException ~ If objectref is null
                -> IllegalAccessError ~ If fiel is final

        *******************************************************************************************/
        case 0xb5:
            FU_putfield(pJVM, pFrame, &pJVM->thread->PC);
            break;
        /********************************************************************************************
        
            invokevirtual: Invoke instance method; dispatch based on class
            page: 489
            
            ## TODO nao entendi essa funcao

            @inputs: indexbyte1, indexbyte2
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xb6:
            FU_invokevirtual(pJVM, pFrame, &(pJVM->thread->PC), Retorno);
            break;
        /********************************************************************************************
        
            invokespecial: Invoke instance method; special handling for superclass, private,
                            and instance initialization method invocations
            page: 482
            
            ## TODO nao entendi essa funcao

            @inputs: indexbyte1, indexbyte2
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xb7:
            FU_invokespecial(pJVM, pFrame, &(pJVM->thread->PC), Retorno);
            break;
        /********************************************************************************************
        
            invokestatic: Invoke a class static method
            page: 486
            
            ## TODO nao entendi essa funcao

            @inputs: indexbyte1, indexbyte2
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xb8:
            FU_invokestatic(pJVM, pFrame, &(pJVM->thread->PC), Retorno);
            break;
        /********************************************************************************************
        
            invokeinterface: Invoke interface method
            page: 479
            
            ## TODO nao entendi essa funcao

            @inputs: indexbyte1, indexbyte2, count, 0
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xb9:
            FU_invokeinterface(pJVM, pFrame, &(pJVM->thread->PC), Retorno);
            break;
        /********************************************************************************************
        
            invokedynamic: Invoke dynamyc method
            page: 474
            
            ## TODO nao entendi essa funcao

            @inputs: indexbyte1, indexbyte2, 0, 0
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xba:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            new: Create new object
            page: 543
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. >
            @push: .. objectref

            throws:
                -> Any linking exceptions
                -> InstantiationError ~ If class is abstract or an interface

        *******************************************************************************************/
        case 0xbb:
            FU_new(pJVM, pFrame, &(pJVM->thread->PC));
            break;
        /********************************************************************************************
        
            newarray: Create new array
            page: 545
            
            @inputs: atype
            @pop: .. count >
            @push: .. arrayref

            throws:
                -> NegativeArraySizeException ~ If count < 0

        *******************************************************************************************/
        case 0xbc:
            FU_newarray(pFrame, &(pJVM->thread->PC));
            break;
        /********************************************************************************************
        
            anewarray: Create a new array reference
            page: 375

            @inputs: indexbyte1, 
            @pop: .. count >
            @push: .. arrayfer

            throws :
                -> Any documented exception
                -> NegativeArraySizeException ~ If count < 0

        *******************************************************************************************/
        case 0xbd:
            FU_anewarray(pFrame, &(pJVM->thread->PC));
            break;
        /********************************************************************************************
        
            arraylength: Get lenth of an array
            page: 377

            @inputs:
            @pop: .. arrayref >
            @push: .. length

            throws :
                -> NullPointerException. ~ If arrayref is null

        *******************************************************************************************/
        case 0xbe:
            FU_arraylenght(pFrame);
            break;
        /********************************************************************************************
        
            athrow: Throw exception or erro
            page: 380

            @inputs: 
            @pop: .. objectref >
            @push: .. objectref

            throws :
                -> objectref
                -> NullPointerException ~ Case objectref is null
                -> IllegalMonitorStateException ~ ??? TODO

        *******************************************************************************************/
        case 0xbf:
            FU_athrow(pFrame);
            break;
        /********************************************************************************************
        
            checkcast: check if object is of given type
            page: 387
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. objectref >
            @push: .. objectref

            throws:
                -> LinkingExeptions ~ On erro of resolving dependencies
                -> ClassCastException ~ If object can't be cast properly

        *******************************************************************************************/
        case 0xc0:
            FU_checkcast(pJVM, pFrame, &(pJVM->thread->PC));
            break;
        /********************************************************************************************
        
            instanceof: Determine if object is of given type
            page: 472
            
            @inputs: indexbyte1, indexbyte2
            @pop: .. objectref >
            @push: .. result

            throws:
                -> LinkingExeptions ~ On erro of resolving dependencies

        *******************************************************************************************/
        case 0xc1:
            FU_instanceof(pJVM, pFrame,  &(pJVM->thread->PC));
            break;


        /********************************************************************************************
        
            monitorenter: Enter monitor for object
            page: 537
            
            @inputs: 
            @pop: .. objectref >
            @push: .. 

            throws:
                -> NullPointerException ~ If objectref is null

        *******************************************************************************************/
        case 0xc2:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            monitorexit: Exit monitor for object
            page: 539
            
            @inputs: 
            @pop: .. objectref >
            @push: .. 

            throws:
                -> NullPointerException ~ If objectref is null
                -> IllegalMonitorStateException ~ If method owner is the one assiciated with the call
                -> IllegalMonitorStateException ~ If structure locking rules are broken

        *******************************************************************************************/
        case 0xc3:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            wide: Extend local variable index by aditional bytes
            page: 562
            

            Format 1
                @inputs: 0x84, indexbyte1, indexbyte2, constbyte1, constbyte2
                @pop: .. same of instrunction from 0x84>
                @push: .. 

            Format 1
                @inputs: other_codes, indexbyte1, indexbyte2, constbyte1, constbyte2
                @pop: .. same of instrunction from other_codes >
                @push: .. 

            throws:
                
        *******************************************************************************************/
        case 0xc4:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            multianewarray: Creates a new multidimentional array
            page: 541
            
            @inputs: indexbyte1, indexbyte2, dimentions
            @pop: .. count1, [count2, ...]  >
            @push: .. arrayref

            throws:
                -> Any resolution linking exception
                -> IllegalAccessError ~ If it's not authorized to use the the requested class
                -> NegativeArraySizeException. ~ If dimentions <= 0

        *******************************************************************************************/
        case 0xc5:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            ifnull: Branch if reference is null
            page: 465
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xc6:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            ifnonnull: Branch if reference not null
            page: 465
            
            @inputs: branchbyte1, branchbyte2
            @pop: .. value >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xc7:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            goto_w: Branch always (wide index)
            page: 447
            
            @inputs: branchbyte1, branchbyte2, branchbyte3, branchbyte4
            @pop: .. >
            @push: .. 

            throws:

        *******************************************************************************************/
        case 0xc8:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            jsr_w: Jump subroutine wide index
            page: 505
            
            @inputs: branchbyte1, branchbyte2, branchbyte3, branchbyte4
            @pop: .. >
            @push: .. address 

            throws:

        *******************************************************************************************/
        case 0xc9:
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            Opcode ainda nao registrado!

        *******************************************************************************************/
        case 0xfe:
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            Opcode ainda nao registrado!

        *******************************************************************************************/
        case 0xff:
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
            break;


        /********************************************************************************************
        
            nenhuma funcao encontrada

        *******************************************************************************************/
        default:
            printf("Opcode não encontrado");
    
    }
}
