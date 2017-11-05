/** ********************************************************************************
 *
 *  Universidade de Brasilia - 02/2017
 *    Software Basico - Turma A
 *
 *  MODULO: ST_
 *  @file structures.h
 *  @brief 
 *            Modulo de definicao: Modulo Estruturas:
 *             Define as estruturas do bytecode.
 *
 * @author PAULO DA CUNHA PASSOS - MAT. 10/0118577
 * @author DANIEL MATIAS
 * @author ALON MOTA
 * @author JURAMIR
 *
 * @version 1.0
 * @since 07/09/2017
 *
 @}********************************************************************************/

/* Controle de escopo do arquivo de definicao */
#ifndef    STRUCTURES_H
#define STRUCTURES_H

/** ******************************************************************************
*                             Inclusao do compilador 
** *******************************************************************************/

/* Inclusao de biblioteca para tratamento de tipo inteiro com representatividade
alternada de acordo com a quantidade de bits*/
#include <stdint.h>
#include <wchar.h>

/* Defini��es de tipos de dados*/
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

/** ******************************************************************************
 *                                FLAGS DE ACESSO
 ** *******************************************************************************/

/**                             DEFINICOES DE TAGS                               **/
#define ACC_PUBLIC          0X0001
#define ACC_PRIVATE         0X0002
#define ACC_SUPER           0X0003
#define ACC_PROTECTED       0X0004
#define ACC_STATIC          0X0008
#define ACC_PUBLIC_STATIC   0x0009
#define ACC_FINAL           0X0010
#define ACC_INTERFACE       0X0200
#define ACC_ABSTRACT        0X0400
#define ACC_SYNTHETIC       0x1000
#define ACC_ANNOTATION      0x2000
#define ACC_ENUM            0x4000

/** ******************************************************************************
*                            TEBELA POOL DE CONSTANTES
** *******************************************************************************/

/**                             DEFINICOES DE TAGS                                    **/
#define CONSTANT_Utf8       1
#define CONSTANT_Float      4
#define CONSTANT_Integer    3
#define CONSTANT_Long       5
#define CONSTANT_Double     6
#define CONSTANT_Class      7
#define CONSTANT_String     8
#define CONSTANT_Fieldref   9
#define CONSTANT_Methodref  10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_NameAndType 12

/**                             DEFINICOES DE TAGS PARA ATRIBUTOS                                    **/
#define CONSTANTVALUE       1
#define CODE       2
#define EXCEPTIONS       3
#define INNERCLASSES       4
#define SOURCEFILE       5
#define LINENUMBERTABLE       6
#define LOCALVARIABLETABLE       7

/**                             ESTRUTURAS                                         **/

/* Representa valores strings constantes, inclusive Unicode */
typedef struct{
    u2 length;
    u1 *bytes;
}ST_tpCONSTANT_Utf8_info;

/* Representa uma constante de ponto flutuante de 4 bytes */
typedef struct{
    u4 bytes;
}ST_tpCONSTANT_Float_info;

/* Representa uma constante inteira de 4 bytes */
typedef struct{
    u4 bytes;
}ST_tpCONSTANT_Integer_info;

/* Representa uma constante inteira de 8 bytes */
typedef struct{
    u4 high_bytes;
    u4 low_bytes;
}ST_tpCONSTANT_Long_info;

/* Representa constante de ponto flutuante de 8 bytes */
typedef struct{
    u4 high_bytes;
    u4 low_bytes;
}ST_tpCONSTANT_Double_info;

/* Representa uma Classe ou Interface */
typedef struct{
    u4 name_index;
}ST_tpCONSTANT_Class_info;

/* Representa objetos constantes do tipo String */
typedef struct{
    u2 string_index;
    //GLOBAL_HEAP StringObject;
}ST_tpCONSTANT_String_info;

/* Representa um field */
typedef struct{
    u2 class_index;
    u2 name_and_type_index;
}ST_tpCONSTANT_Fieldref_info;

/* Representa um m�todo */
typedef struct{
    u2 class_index;
    u2 name_and_type_index;
}ST_tpCONSTANT_Methodref_info;

/* Representa uma interface */
typedef struct{
    u2 class_index;
    u2 name_and_type_index;
}ST_tpCONSTANT_InterfaceMethodref_info;

/* Representa um field ou m�todo sem indicar classe ou interface a que pertence */
typedef struct{
    u2 name_index;
    u2 descriptor_index;
}ST_tpCONSTANT_NameAndType_info;

typedef union {
    ST_tpCONSTANT_Utf8_info Utf8;
    ST_tpCONSTANT_Float_info Float;
    ST_tpCONSTANT_Integer_info Integer;
    ST_tpCONSTANT_Long_info Long;
    ST_tpCONSTANT_Double_info Double;
    ST_tpCONSTANT_Class_info Class;
    ST_tpCONSTANT_String_info String;
    ST_tpCONSTANT_Fieldref_info Fieldref;
    ST_tpCONSTANT_Methodref_info Methodref;
    ST_tpCONSTANT_InterfaceMethodref_info InterfaceMethodref;
    ST_tpCONSTANT_NameAndType_info NameAndType;
}ST_tpConstantPool;

typedef struct{
    u1 tag; 
    ST_tpConstantPool info;// Verificar se aqui convem ser um ponteiro
}ST_tpCp_info;

/** ******************************************************************************
*                                TABELA DE INTERFACE
** *******************************************************************************/
typedef struct{
    u2 constant_pool_index;
}ST_tpInterface_list;

/** ******************************************************************************
*                                TABELA DE ATRIBUTOS
** *******************************************************************************/
typedef struct{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 tag;
    void *info;
}ST_tpAttribute_info;

/** ******************************************************************************
 *                               ATRIBUTO CONSTANTVALUE
 ** ******************************************************************************/
typedef struct{
    u2 constantvalue_index;
}ST_tpConstantValue_attribute;

/** ******************************************************************************
 *                                TABELA DE EXCESSAO
 ** ******************************************************************************/
typedef struct{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
}ST_tpException_table;

/** ******************************************************************************
 *                                ATRIBUTO CODE
 ** ******************************************************************************/
typedef struct{
    //u2 attribute_name_index;
    //u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    ST_tpException_table *exception_table;
    u2 attributes_count;
    ST_tpAttribute_info *attribute_info;
}ST_tpCode_attribute;

/** ******************************************************************************
 *                                ATRIBUTO DEPRECATED
 ** ******************************************************************************/
typedef struct{
//    u2 attribute_name_index;
//    u4 attribute_length;
}ST_tpDeprecated_attribute;

/** ******************************************************************************
 *                                ATRIBUTO EXCEPTIONS
 ** ******************************************************************************/
typedef struct {
    u2 number_of_exceptions;
    u2 *exception_index_table;
}ST_tpExceptions_attribute;

/** ******************************************************************************
 *                                TABELA INNERCLASSES
 ** ******************************************************************************/
typedef struct {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
}ST_tpInnerClasses_table;

/** ******************************************************************************
 *                                ATRIBUTO INNERCLASSES
 ** ******************************************************************************/
typedef struct {
    u2 number_of_classes;
    ST_tpInnerClasses_table *classes;
}ST_tpInnerClasses_attribute;

/** ******************************************************************************
 *                                TABELA LINERNUMBER
 ** ******************************************************************************/
typedef struct {
    u2 start_pc;
    u2 line_number;
}ST_tpLine_number_table;

/** ******************************************************************************
 *                                ATRIBUTO LINERNUMBERTABLE
 ** ******************************************************************************/
typedef struct {
    u2 line_number_table_length;
    ST_tpLine_number_table *info;
}ST_tpLineNumberTable_attribute;

/** ******************************************************************************
 *                                TABELA LOCALVARIABLETABLE
 ** ******************************************************************************/
typedef struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
}ST_tpLocal_variable_table;

/** ******************************************************************************
 *                                ATRIBUTO LOCALVARIABLETABLE
 ** ******************************************************************************/
typedef struct {
    u2 local_variable_table_length;
    ST_tpLocal_variable_table *Local_variable_table;
}ST_tpLocalVariableTable_attribute;

/** ******************************************************************************
 *                                ATRIBUTO SOURCEFILE
 ** ******************************************************************************/
typedef struct {
    u2 source_file_index;
}ST_tpSourceFile_attribute;

/** ******************************************************************************
*                                TABELA DE CAMPOS (FIELD)
** *******************************************************************************/
typedef struct{ 
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    ST_tpAttribute_info *attributes;
    //struct field_info *next; Paulo, n�o entendi o motivo de ter o ponteiro para o pr�ximo Field j� que eles est�o em sequ�ncia na mem�ria.
}ST_tpField_info; 

/** ******************************************************************************
*                                TABELA DE METODOS
** *******************************************************************************/
typedef struct{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    ST_tpAttribute_info *attributes;
}ST_tpMethod_info;

/** ******************************************************************************
*                                ESTRUTURA CLASSFILE
** *******************************************************************************/
typedef struct ClassFile{
    wchar_t *fully_qualified_name;    
    u4    magic;                        // Assinatura de um arquivo .class
    u2    minor_version_number;         // Versao minima do arquivo - Relacao com a versao do Java
    u2    major_version_number;         // Versao manima do arquivo - Relacao com a versao do Java
    u2    constant_pool_count;          // Numero de entradas na estrutura Constant Pool
    ST_tpCp_info    *constant_pool_table;// Tabela Constant Pool
    u2     access_flags;                 // Mascara de bits que especifica permissao de acesso da classe
    u2    this_class;                    // Representa a classe definida
    u2    super_class;                   // Representa a super classe direta da classe definida
    u2    interfaces_count;              // Numero de entradas na estrutura Interfaces
    u2    *interfaces_table;             // Tabela Interfaces que sao superinterfaces diretas da classe
    u2    fields_count;                  // Numero de variaveis de classe ou de instacias declaradas na classe presentes na estrutura Field
    ST_tpField_info     *field_info_table;// Tabela de Field
    u2    methods_count;                 // Numero de estruturas method_info na tabela de Methods
    ST_tpMethod_info *method_info_table; // Tabela de Metodos
    u2    attributes_count;              // Numero de estruturas attributes_info na tabela Atributos
    ST_tpAttribute_info *attribute_info_table; // Tabela de Attributos
    //u2 code_index;
    //u2 main_name_index;
    //u2 start_method_index;
    //CACHE_FIELD_LOCATION cache_field_loc;
    //CACHE_FIELD_LOCATION cache_curr_loc;
    //METHOD_HASH_TABLE method_hash_table;
    struct ClassFile *prev;
    struct ClassFile *next;
}ST_tpClassFile;


/** ******************************************************************************
 *                                ESTRUTURAS DO HEAP
 ** ******************************************************************************/
typedef struct thread ST_tpThread;

/**  Estrutura que representa o Heap de classes */
typedef struct {
    wchar_t *pClasseName;
    union variable *field_area;
    struct VM_tpClassHeap *next;
}ST_tpClassHeap;

/**  Estrutura que representa o Heap para objetos */
typedef struct{
    wchar_t *pClasseName;
    union variable *field_area;
    ST_tpThread *thread;
    u4 ref_count;
    u2 max_var;
    struct VM_tpObjectHeap *next;
}ST_tpObjectHeap;

/**  Estrutura que representa o Heap para array */
typedef struct{
    u1 type;
    wchar_t *pClasseName;
    int length;
    void *area;
    u4 ref_count;
    struct VM_tpArrayHeap *next;
}ST_tpArrayHeap;

/**  Estrutura que representa o Heap Geral */
typedef struct {
    ST_tpClassHeap *classes;
    ST_tpObjectHeap *objects;
    ST_tpArrayHeap   *array;
}ST_tpHeap;

/** ******************************************************************************
 *                                  TIPOS DE DADOS
 ** ******************************************************************************/

union variable{
    char Byte;
    u2 Char;
    short int Short;
    int Int;
    __int64_t Long;
    float Float;
    double Double;
    char Boolean;
    ST_tpObjectHeap obj_ref;
    ST_tpArrayHeap array_ref;
    // RETADDRESS retAddres;
};

typedef struct {
    u1 tipo;                /* Tipo da variavel */
    union variable valor;   /* Valor da variavel */
}ST_tpVariable;

/** ******************************************************************************
 *                         ESTRUTURAS DA AREA DE METODOS
 ** ******************************************************************************/

typedef struct {
    ST_tpClassFile *classFile; /* lista de classe carregadas */
}ST_tpMethodArea;

/** ******************************************************************************
 *                         ESTRUTURAS DE PILHA JVM E FRAMES
 ** ******************************************************************************/

typedef struct tpPilha{
    void *dado;
    struct tpPilha *prox;
}ST_tpPilha;

/**  Estrutura que representa a pilha de variaveis locais */
typedef struct {
    u1 type;
    union variable variable;
    struct VM_tpLocalVariables *next;
}ST_tpLocalVariables;

/**  Estrutura que representa a pilha de Operandos */
typedef struct {
    u1 type;
    union variable variable;
    struct VM_tpOperandStack *next;
}ST_tpOperandStack;

/**  Estrutura que representa um Frame */
typedef struct {
    ST_tpLocalVariables *localVariablesStack;
    ST_tpOperandStack   *operandStack;
    ST_tpClassFile *cp;
    /* ReferenceConstantPoll */
}ST_tpFrame;

/**  Estrutura que representa uma thread */
typedef struct thread{
    u1 *PC;
    ST_tpPilha *pFrameStack; /* Ponteiro para lista de frames da Thread */
    //VM_tpNativeMethodStack NativeStack;
}ST_tpThread;

/** ******************************************************************************
 *                                ESTRUTURAS Da JVM
 ** ******************************************************************************/

/**  Estrutura que representa a Java Virtual MAchine */
typedef struct {
    ST_tpMethodArea *methodArea;
    ST_tpHeap *heap;
    ST_tpThread *thread;
}ST_tpJVM;


#endif /* structures_h */
