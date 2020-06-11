#include "alloc.h"
#include "ast.h"

/* var prototypes */
ast_var *ast_simple_var(
    unsigned position,
    ast_var *var,
    symbol_table_entry *symbol)
{
    ast_var *p = (ast_var *)alloc_and_check(sizeof(ast_var));
    p->kind = AST_SIMPLE_VAR;
    p->position = position;
    p->simple = symbol;

    return p;
}

ast_var *ast_field_var(
    unsigned position,
    ast_var *var,
    symbol_table_entry *symbol)
{
    ast_var *p = (ast_var *)alloc_and_check(sizeof(ast_var));
    p->kind = AST_FIELD_VAR;
    p->position = position;
    p->field.var = var;
    p->field.symbol = symbol;

    return p;
}

/* statement prototypes */
ast_statement *ast_var_stmt(
    unsigned position,
    ast_var *var)
{
    ast_statement *p = (ast_statement *)alloc_and_check(sizeof(ast_statement));
    p->kind = AST_VAR_STMT;
    p->position = position;
    p->var = var;

    return p;
}

ast_statement *ast_int_stmt(
    unsigned position,
    int value)
{
    ast_statement *p = (ast_statement *)alloc_and_check(sizeof(ast_statement));
    p->kind = AST_INT_STMT;
    p->position = position;
    p->int_stmt = value;

    return p;
}

ast_statement *ast_op_stmt(
    unsigned position,
    ast_operator_type type,
    ast_statement *left,
    ast_statement *right)
{
    ast_statement *p = (ast_statement *)alloc_and_check(sizeof(ast_statement));
    p->kind = AST_OP_STMT;
    p->position = position;

    p->operation.right = right;
    p->operation.type = type;
    p->operation.left = left;

    return p;
}

ast_statement *ast_assign_stmt(
    unsigned position,
    ast_var *var,
    ast_statement *stmt)
{
    ast_statement *p = (ast_statement *)alloc_and_check(sizeof(ast_statement));
    p->kind = AST_ASSIGN_STMT;
    p->position = position;
    p->assign.stmt = stmt;
    p->assign.var = var;

    return p;
}

/* dec prototypes */
ast_dec *ast_function_dec_stmt(
    unsigned position,
    ast_function_dec_list *function)
{
    ast_dec *p = (ast_dec *)alloc_and_check(sizeof(ast_dec));
    p->kind = AST_FUNCTION_DEC;
    p->position = position;
    p->function = function;

    return p;
}

ast_dec *ast_var_dec(
    unsigned position,
    symbol_table_entry *symbol,
    symbol_table_entry *type,
    ast_statement *stmt)
{
    ast_dec *p = (ast_dec *)alloc_and_check(sizeof(ast_dec));
    p->kind = AST_VAR_DEC;
    p->position = position;

    p->var.symbol = symbol;
    p->var.type = type;
    p->var.stmt = stmt;

    return p;
}

/* raw prototypes */
ast_field *ast_field_new(
    unsigned position,
    symbol_table_entry *name,
    symbol_table_entry *type)
{
    ast_field *p = (ast_field *)alloc_and_check(sizeof(ast_field));
    p->position = position;
    p->name = name;
    p->type = type;

    return p;
}

ast_field_list *ast_field_list_new(
    ast_field *head,
    ast_field_list *tail)
{
    ast_field_list *p = (ast_field_list *)alloc_and_check(sizeof(ast_field_list));
    p->head = head;
    p->tail = tail;

    return p;
}

ast_function_dec *ast_function_dec_new(
    unsigned position,
    symbol_table_entry *name,
    ast_field_list *params,
    symbol_table_entry *result,
    ast_statement *body)
{
    ast_function_dec *p = (ast_function_dec *)alloc_and_check(sizeof(ast_function_dec));
    p->position = position;
    p->params = params;
    p->result = result;
    p->name = name;
    p->body = body;

    return p;
}

ast_function_dec_list *ast_function_dec_list_new(
    ast_function_dec *head,
    ast_function_dec_list *tail)
{
    ast_function_dec_list *p = (ast_function_dec_list *)alloc_and_check(sizeof(ast_function_dec_list));
    p->head = head;
    p->tail = tail;

    return p;
}
