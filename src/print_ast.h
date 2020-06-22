#ifndef __PRINT_AST_H__
#define __PRINT_AST_H__

#define PRINT_AST_INDENT_FACTOR 2

#include <stdio.h>

#include "ast.h"

void pint_ast_stmt_root(
    FILE *out,
    ast_statement *ast_root,
    int spaces);

#endif