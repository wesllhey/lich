#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "symbol_table.h"
#include "types.h"

typedef struct environment {
    enum {
        ENVIRONMENT_VAR_ENTRY,
        ENVIRONMENT_FUNC_ENTRY,
        ENVIRONMENT_CLASS_ENTRY
    } kind;

    union {
        type *var;
        struct {
            type *result_type;
            type_list *args_type;
        } function;

        type *object; // TODO
    };

} environment;

environment *environment_var_new(
    type *type);

environment *environment_function_new(
    type *result_type,
    type_list *args_type);

symbol_table *environment_built_in_types(void);

symbol_table *environment_built_in_functions(void); // TODO

#endif
