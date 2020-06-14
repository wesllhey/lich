#include "print_ast.h"

static void print_ast_function(FILE *out, ast_function *function, int spaces);
static void print_ast_function_list(FILE *out, ast_function_list *function_list, int spaces);

static void print_ast_statement(FILE *out, ast_statement *statement, int spaces);
static void print_ast_statement_list(FILE *out, ast_statement_list *statement_list, int spaces);

static void print_ast_var(FILE *out, ast_var *var, int spaces);

static void indent(FILE *out, int d)
{
    for (int i = 0; i <= d; i++) {
        fprintf(out, " ");
    }
        
}

static void print_new_line_indented(FILE *out, int spaces)
{
    fprintf(out, "\n");
    indent(out, spaces);
}

void print_ast_dec(
    FILE *out,
    ast_dec *ast_root,
    int spaces)
{
    indent(out, spaces);

    switch (ast_root->kind)
    {
    case AST_FUNCTION_DEC:
        fprintf(out, "functions_dec {\n");
        print_ast_function_list(out, ast_root->function_list, spaces + PRINT_AST_INDENT_FACTOR);
        print_new_line_indented(out, spaces);
        fprintf(out, "}");
    default:
        break;
    }
}

static void print_ast_function(
    FILE *out,
    ast_function *function,
    int spaces)
{
    indent(out, spaces);

    if (function)
    {
        fprintf(out, "fun %s {", function->name->name);
        fprintf(out, "\n");

        print_ast_statement_list(out, function->body, spaces + PRINT_AST_INDENT_FACTOR);
        print_new_line_indented(out, spaces);
        fprintf(out, "}");
    }
}

static void print_ast_function_list(
    FILE *out,
    ast_function_list *function_list,
    int spaces)
{
    indent(out, spaces);

    if (function_list)
    {
        fprintf(out, "function_list {\n");
        print_ast_function(out, function_list->head, spaces + PRINT_AST_INDENT_FACTOR);

        if (function_list->tail)
        {
            fprintf(out, ",\n");
            print_ast_function_list(out, function_list->tail, spaces + PRINT_AST_INDENT_FACTOR);
        }
        print_new_line_indented(out, spaces);
        fprintf(out, "}");
    }
}

static void print_ast_statement(
    FILE *out,
    ast_statement *statement,
    int spaces)
{
    indent(out, spaces);

    switch (statement->kind)
    {
    case AST_ASSIGN_STMT:
        fprintf(out, "assign_stm {\n");
        indent(out, spaces + 4);
        print_ast_var(out, statement->assign.var, spaces);
        fprintf(out, ", name=%s :=", statement->assign.name);
        print_ast_statement(out, statement->assign.stmt, 0);
        print_new_line_indented(out, spaces);
        fprintf(out, "}");
        break;
    case AST_OP_STMT:
        fprintf(out, "op_stmt=");
        print_ast_statement(out, statement->operation.left, 0);

        switch (statement->operation.type) {
            case AST_PLUS_OP:
                fprintf(out, " +");
                break;
            case AST_MINUS_OP:
                fprintf(out, " -");
                break;
            case AST_TIMES_OP:
                fprintf(out, " *");
                break;
            case AST_DIVIDE_OP:
                fprintf(out, " /");
                break;
            default:
                break;
        }

        print_ast_statement(out, statement->operation.right, 0);
        break;
    case AST_INT_STMT:
        fprintf(out, "int_stmt=%d", statement->int_stmt);
        break;
        
    default:
        break;
    }
}

static void print_ast_statement_list(
    FILE *out,
    ast_statement_list *statement_list,
    int spaces)
{
    indent(out, spaces);

    if (statement_list)
    {
        fprintf(out, "statement_list {\n");
        print_ast_statement(out, statement_list->head, spaces + PRINT_AST_INDENT_FACTOR);

        if (statement_list->tail) {
            fprintf(out, ",\n");
            print_ast_statement_list(out, statement_list->tail, spaces + PRINT_AST_INDENT_FACTOR);
        }
        print_new_line_indented(out, spaces);
        fprintf(out, "}");
    }
}

static void print_ast_var(
    FILE *out, 
    ast_var *var, 
    int spaces)
{
    switch (var->kind) {
        case AST_SIMPLE_VAR:
            fprintf(out, "type=%s", var->simple->name);
            break;
        default:
            break;
    }
}