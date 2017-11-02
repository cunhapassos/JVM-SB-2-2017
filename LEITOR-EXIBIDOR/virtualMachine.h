/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *    Software Basico - Turma A
 *
 *  MODULO: VM_
 *  @file virtualMachine
 *  @brief
 *            Descricao: Definicao das estruturas de incicializacao da JVM.
 *
 * @author ALON MOTA     - MAT. 13/0005002
 * @author DANIEL MATIAS - MAT. 12/0139804
 * @author PAULO PASSOS  - MAT. 10/0118577
 *
 * @version 1.0
 * @since 31/10/17
 *
 @}********************************************************************************/

#ifndef virtualMachine_h
#define virtualMachine_h

#include <stdio.h>
#include "structures.h"

union variable{
    char Byte;
    u2 Char;
    short int Short;
    int Int;
    __int64_t Long;
    float Float;
    double Double;
    char Boolean;
    // GLOBAL_HEAP obj_ref;
    // ARRAY_HEAP array_ref;
    // RETADDRESS retAddres;
};

typedef struct {
    ST_tpClassFile *classFile; /* lista de classe carregadas */
}VM_tpMethodArea;

/** ******************************************************************************
 *                         ESTRUTURAS DE PILHA JVM E FRAMES
 ** *******************************************************************************/

typedef struct {
    u1 type;
    union variable variable;
    struct VM_tpLocalVariables *next;
}VM_tpLocalVariables;

typedef struct {
    u1 type;
    union variable variable;
    struct VM_tpOperandStack *next;
}VM_tpOperandStack;

typedef struct {
    VM_tpLocalVariables *localVariables;
    VM_tpOperandStack   *operandes;
    /* ReferenceConstantPoll */
}VM_tpFrameStack;

typedef struct {
    u1 PC;
    VM_tpFrameStack *JVMStack; /* Ponteiro para lista de frames da Pilha */
    //VM_tpNativeMethodStack NativeStack;
}VM_tpThread;


/** ******************************************************************************
 *                                ESTRUTURAS DO HEAP
 ** *******************************************************************************/

typedef struct {
    wchar_t *pClasseName;
    union variable *field_area;
    struct VM_tpClassHeap *next;
}VM_tpClassHeap;

typedef struct {
    wchar_t *pClasseName;
    union variable *field_area;
    VM_tpThread thread;
    u4 ref_count;
    u2 max_var;
    struct VM_tpObjectHeap *next;
}VM_tpObjectHeap;

typedef struct {
    u1 type;
    wchar_t *pClasseName;
    int length;
    void *area;
    u4 ref_count;
    struct VM_tpArrayHeap *next;
}VM_tpArrayHeap;

typedef struct {
    VM_tpClassHeap *classes;
    VM_tpObjectHeap *objects;
    VM_tpArrayHeap   *array;
}VM_tpHeap;


typedef struct {
    VM_tpMethodArea *methodArea;
    VM_tpHeap *heap;
    VM_tpThread *thread;
}VM_tpJVM;



#endif /* virtualMachine_h */

