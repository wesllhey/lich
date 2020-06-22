#include "environment.h"
#include "alloc.h"

environment *environment_var_new(
    type *type)
{
    environment *env = (environment *)alloc_and_check(sizeof(environment));
    env->kind = ENVIRONMENT_VAR_ENTRY;
    env->var = type;

    return env;
}

environment *environment_function_new(
    type *result_type,
    type_list *args_type)
{
    environment *env = (environment *)alloc_and_check(sizeof(environment));
    env->kind = ENVIRONMENT_FUNC_ENTRY;
    env->function.result_type = result_type;
    env->function.args_type = args_type;

    return env;
}

symbol_table *environment_built_in_types(void)
{
    symbol_table *built_int_types_table = symbol_table_new();
    symbol_table_put(built_int_types_table, symbol_table_entry_new(TYPE_NIL_LITERAL), type_nil());
    symbol_table_put(built_int_types_table, symbol_table_entry_new(TYPE_INT_LITERAL), type_int());

    return built_int_types_table;
}
