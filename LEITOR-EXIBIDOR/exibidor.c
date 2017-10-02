//
//  exibidor.c
//  JVM-SB-2-2017
//
//  Created by Paulo Passos on 17/09/17.
//  Copyright © 2017 Paulo Passos. All rights reserved.
//

#include "exibidor.h"

void imprimeUtf8 (u1 *s, int length)
{
    u1 *i;
    for (i=s;i<s+length;i++)
        printf("%c", *i);
    printf("\n");
}

void imprime_atributos(ST_tpAttribute_info *attribute_info_table,u2 attributes_count){
    ST_tpAttribute_info *n;
    for(n = attribute_info_table; n <  (attribute_info_table+attributes_count); n++) {
        printf("\n-----Attributes-----\n\n");
        printf("\n-----Generic info-----\n\n");
        printf("Attribute name index: 0x%04x\n",n->attribute_name_index);
        printf("Attibute length: 0x%08x\n",n->attribute_length);
        // Verificar impressão do campo Info da estrutura Atribute_info (nessa implementação a impressão é feita byte a byte)
        u1 *q;
        for(q = n->info; q <  (n->info+n->attribute_length); q++){
            printf("\n-----Specific info-----\n\n");
            printf("Source file name index: 0x%02x\n", *q);
        }
    }
}

void EX_imprimirClassFile(ST_tpClassFile *classFile){
    
    
    printf("\n-----GENERAL INFORMATION-----\n\n");
    printf("Magic: 0x%08x\n",classFile->magic);
    printf("Minor Version: 0x%04x\n",classFile->minor_version_number);
    printf("Major Version: 0x%04x\n",classFile->major_version_number);
    printf("Constant Pool Count: 0x%04x\n",classFile->constant_pool_count);
    printf("Access Flags: 0x%04x\n",classFile->access_flags);
    printf("This Class: 0x%04x\n",classFile->this_class);
    printf("Super Class: 0x%04x\n",classFile->super_class);
    printf("Interfaces Count: 0x%04x\n",classFile->interfaces_count);
    printf("Fields Count: 0x%04x\n",classFile->fields_count);
    printf("Methods Count: 0x%04x\n",classFile->methods_count);
    printf("Atributes Count: 0x%02x\n",classFile->attributes_count);
    printf("\n-----CONSTANT POOL-----\n\n");
    ST_tpCp_info *i;
    int j=1;
    for(i = classFile->constant_pool_table; i <  (classFile->constant_pool_table+classFile->constant_pool_count-1); i++ ){
        switch(i->tag) {
            case CONSTANT_Utf8:
                printf("\n-----[%d] CONSTANT_Utf8 INFO-----\n\n",j);
                printf("Length: 0x%04x\n",i->info.Utf8.length);
                printf("String: ");
                imprimeUtf8(i->info.Utf8.bytes, i->info.Utf8.length);
                break;
            case CONSTANT_Float:
                printf("\n-----[%d] CONSTANT_Float INFO-----\n\n",j);
                printf("Float: 0x%08x\n",i->info.Float.bytes);
                break;
            case CONSTANT_Integer:
                printf("\n-----[%d] CONSTANT_Integer INFO-----\n\n",j);
                printf("Integer: 0x%08x\n",i->info.Integer.bytes);
                break;
            case CONSTANT_Long:
                printf("\n-----[%d] CONSTANT_Long INFO-----\n\n",j);
                printf("High Bytes: 0x%08x\n",i->info.Long.high_bytes);
                printf("Low Bytes: 0x%08x\n",i->info.Long.low_bytes);
                break;
            case CONSTANT_Double:
                printf("\n-----[%d] CONSTANT_Double INFO-----\n\n",j);
                printf("High Bytes: 0x%08x\n",i->info.Double.high_bytes);
                printf("Low Bytes: 0x%08x\n",i->info.Double.high_bytes);
                break;
            case CONSTANT_Class:
                printf("\n-----[%d] CONSTANT_Class INFO-----\n\n",j);
                printf("Name Index: 0x%04x\n",i->info.Class.name_index);
                break;
            case CONSTANT_String:
                printf("\n-----[%d] CONSTANT_String INFO-----\n\n",j);
                printf("String Index: 0x%04x\n",i->info.String.string_index);
                break;
            case CONSTANT_Fieldref:
                printf("\n-----[%d] CONSTANT_Fieldref INFO-----\n\n",j);
                printf("Class Index: 0x%04x\n",i->info.Fieldref.class_index);
                printf("Name and Type Index: 0x%04x\n",i->info.Fieldref.name_and_type_index);
                break;
            case CONSTANT_Methodref:
                printf("\n-----[%d] CONSTANT_Methodref INFO-----\n\n",j);
                printf("Class Index: 0x%04x\n",i->info.Methodref.class_index);
                printf("Name and Type Index: 0x%04x\n",i->info.Methodref.name_and_type_index);
                break;
            case CONSTANT_InterfaceMethodref:
                printf("\n-----[%d] CONSTANT_InterfaceMethodref INFO-----\n\n",j);
                printf("Class Index: 0x%04x\n",i->info.InterfaceMethodref.class_index);
                printf("Name and Type Index: 0x%04x\n",i->info.InterfaceMethodref.name_and_type_index);
                break;
            case CONSTANT_NameAndType:
                printf("\n-----[%d] CONSTANT_NameAndType INFO-----\n\n",j);
                printf("Name Index: 0x%04x\n",i->info.NameAndType.name_index);
                printf("Descriptor Index: 0x%04x\n",i->info.NameAndType.descriptor_index);
                break;
            default:
                break;
        }
        j++;
    }
    u2 *k;
    for(k = classFile->interfaces_table; k <  (classFile->interfaces_table+classFile->interfaces_count); k++)
        printf("Interfaces: %04x\n",*k);
    ST_tpField_info *l;
    for(l = classFile->field_info_table; l <  (classFile->field_info_table+classFile->fields_count); l++) {
        printf("\n-----Fields-----\n\n");
        printf("Name: 0x%04x\n",l->name_index);
        printf("Descriptor: 0x%04x\n",l->descriptor_index);
        printf("Access flags: 0x%04x\n",l->access_flags);
        imprime_atributos(l->attributes,l->attributes_count);
    }
    ST_tpMethod_info *m;
    for(m = classFile->method_info_table; m <  (classFile->method_info_table+classFile->methods_count); m++) {
        printf("\n-----Methods-----\n\n");
        printf("Name: 0x%04x\n",m->name_index);
        printf("Descriptor: 0x%04x\n",m->descriptor_index);
        printf("Access flags: 0x%04x\n",m->access_flags);
        imprime_atributos(m->attributes,m->attributes_count);
    }
    imprime_atributos(classFile->attribute_info_table,classFile->attributes_count);
}

