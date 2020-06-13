#ifndef __AST_H__
#define __AST_H__

#include "symbol_table.h"

typedef struct ast_var ast_var;
typedef struct ast_statement ast_statement;
typedef struct ast_statement_list ast_statement_list;
typedef struct ast_dec ast_dec;

typedef struct ast_field ast_field;
typedef struct ast_field_list ast_field_list;

typedef struct ast_function_list ast_function_list;
typedef struct ast_function ast_function;

typedef enum {
    AST_PLUS_OP,
    AST_MINUS_OP,
    AST_TIMES_OP,
    AST_DIVIDE_OP,
    AST_EQ_OP,
    AST_NEQ_OP,
    AST_LT_OP,
    AST_LE_OP,
    AST_GT_OP,
    AST_GE_OP
} ast_operator_type;

struct ast_var {
    unsigned position;

    enum {
        AST_SIMPLE_VAR,
        AST_FIELD_VAR
    } kind;

    union {
        struct symbol_table_entry *simple;

        struct {
            ast_var *var;
            symbol_table_entry *symbol;
        } field;
    };

};

struct ast_statement {
    unsigned position;

    enum {
        AST_VAR_STMT,
        AST_NIL_STMT,
        AST_INT_STMT,
        AST_STRING_STMT,
        AST_CALL_STMT,
        AST_OP_STMT,
        AST_INPUT_STMT,
        AST_PRINT_STMT,
        AST_ASSIGN_STMT,
        AST_IF_STMT,
        AST_WHILE_STMT,
        AST_FOR_STMT,
        AST_BREAK_STMT,
        AST_ARRAY_STMT,
        AST_RETURN_STMT
    } kind;

    union {
        int int_stmt;      // TODO: create types
        char *string_stmt; // TODO: create types

        ast_var *var;

        struct {
            ast_var *var;
            char *name;
            ast_statement *stmt;
        } assign;

        struct {
            ast_operator_type type;
            ast_statement *left;
            ast_statement *right;
        } operation;
    };

};

struct ast_statement_list {
    ast_statement *head;
    ast_statement_list *tail;
};

struct ast_dec {
    unsigned position;

    enum {
        AST_FUNCTION_DEC,
        AST_VAR_DEC
    } kind;

    union {
        ast_function_list *function;

        struct {
            symbol_table_entry *symbol;
            symbol_table_entry *type;
            ast_statement *stmt;
        } var;
    };

};

struct ast_field {
    unsigned position;
    symbol_table_entry *name, *type;
};

struct ast_field_list {
    unsigned position;

    ast_field *head;
    ast_field_list *tail;
};

struct ast_function {
    unsigned position;
    symbol_table_entry *name, *result;
    ast_field_list *params;
    ast_statement_list *body;
};

struct ast_function_list {
    ast_function *head;
    ast_function_list *tail;
};

/* var prototypes */
ast_var *ast_simple_var(
    unsigned position,
    symbol_table_entry *symbol);

ast_var *ast_field_var(
    unsigned position,
    ast_var *var,
    symbol_table_entry *symbol);

/* statement prototypes */
ast_statement *ast_var_stmt(
    unsigned position,
    ast_var *var);

ast_statement *ast_int_stmt(
    unsigned position,
    int value);

ast_statement *ast_op_stmt(
    unsigned position,
    ast_operator_type type,
    ast_statement *left,
    ast_statement *right);

ast_statement *ast_assign_stmt(
    unsigned position,
    ast_var *var,
    char *name,
    ast_statement *stmt);

/* dec prototypes */
ast_dec *ast_function_dec_new(
    unsigned position,
    ast_function_list *function_list);

ast_dec *ast_var_dec(
    unsigned position,
    symbol_table_entry *symbol,
    symbol_table_entry *type,
    ast_statement *stmt);

/* raw prototypes */
ast_field *ast_field_new(
    unsigned position,
    symbol_table_entry *name,
    symbol_table_entry *type);

ast_field_list *ast_field_list_new(
    ast_field *head,
    ast_field_list *tail);

ast_function *ast_function_new(
    unsigned position,
    symbol_table_entry *name,
    ast_field_list *params,
    ast_statement_list *body,
    symbol_table_entry *result);

ast_function_list *ast_function_list_new(
    ast_function *head,
    ast_function_list *tail);

ast_statement_list *ast_statement_list_new(
    ast_statement *head,
    ast_statement_list *tail);

#endif