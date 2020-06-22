#ifndef __TYPES_H__
#define __TYPES_H__

#define TYPE_INT_LITERAL "int"
#define TYPE_NIL_LITERAL "nil"

#include "symbol_table.h"

typedef struct type type;

typedef struct type_list type_list;


struct type {
    enum {
        TYPE_NIL,
        TYPE_INT,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_NAME,
        TYPE_VOID
    } kind;

    symbol_table_entry *name;
};

struct type_list {
    type *head;
    type_list *tail;
};

type *type_nil();

type *type_int();

type *type_void();

#endif