#include "print_ast.h"

static void print_ast_function(
    FILE *out,
    ast_function *function,
    int spaces);

static void print_ast_function_list(
    FILE *out,
    ast_function_list *function_list,
    int spaces);

static void print_ast_statement(
    FILE *out,
    ast_statement *statement,
    int spaces);

static void print_ast_statement_list(
    FILE *out,
    ast_statement_list *statement_list,
    int spaces);

static void print_ast_field(
    FILE *out,
    ast_field *field,
    int spaces);

static void print_ast_field_list(
    FILE *out,
    ast_field_list *field_list,
    int spaces);

static void print_ast_type(
    FILE *out,
    ast_type *type,
    int spaces);

static void indent(
    FILE *out,
    int spaces)
{
    for (int i = 0; i < spaces; i++)
        fprintf(out, " ");
}

static void print_new_line_indented(
    FILE *out,
    int spaces)
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

    switch (ast_root->kind) {
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

    if (function) {
        fprintf(out, "func %s (", function->name->name);
        print_ast_field_list(out, function->params, 0);
        fprintf(out, ") {\n");

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

    if (function_list) {
        fprintf(out, "function_list {\n");
        print_ast_function(out, function_list->head, spaces + PRINT_AST_INDENT_FACTOR);

        if (function_list->tail) {
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

    switch (statement->kind) {
        case AST_ASSIGN_STMT:
            fprintf(out, "assign_stm {\n");
            indent(out, spaces + 4);
            print_ast_type(out, statement->assign.type, spaces);
            fprintf(out, " name=%s := ", statement->assign.name);
            print_ast_statement(out, statement->assign.stmt, 0);
            print_new_line_indented(out, spaces);
            fprintf(out, "}");
            break;
        case AST_OP_STMT:
            fprintf(out, "op_stmt=");
            print_ast_statement(out, statement->operation.left, 0);

            switch (statement->operation.type) {
            case AST_PLUS_OP:
                fprintf(out, "+");
                break;
            case AST_MINUS_OP:
                fprintf(out, "-");
                break;
            case AST_TIMES_OP:
                fprintf(out, "*");
                break;
            case AST_DIVIDE_OP:
                fprintf(out, "/");
                break;
            default:
                break;
            }

            print_ast_statement(out, statement->operation.right, 0);
            break;
        case AST_INT_STMT:
            fprintf(out, "int_stmt=%d", statement->int_stmt);
            break;

        case AST_VAR_STMT:
            fprintf(out, "%s", statement->var->simple->name);
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

    if (statement_list) {
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

static void print_ast_field(
    FILE *out,
    ast_field *field,
    int spaces)
{
    print_ast_type(out, field->type, spaces);
    fprintf(out, " name=%s", field->name->name);
}

static void print_ast_field_list(
    FILE *out,
    ast_field_list *field_list,
    int spaces)
{
    if (field_list) {
        print_ast_field(out, field_list->head, spaces);

        if (field_list->tail) {
            fprintf(out, ", ");
            print_ast_field_list(out, field_list->tail, spaces);
        }
    }
}

static void print_ast_type(
    FILE *out,
    ast_type *type,
    int spaces)
{
    switch (type->kind) {
        case AST_INT_TYPE:
            fprintf(out, "type=%s", "int");
            break;
        case AST_IDENTIFIER_TYPE:
            fprintf(out, "type=%s", "int");
            break;
        default:
            break;
    }
}
