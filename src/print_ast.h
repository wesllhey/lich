#ifndef __PRINT_AST_H__
#define __PRINT_AST_H__

#define PRINT_AST_INDENT_FACTOR 2

#include <stdio.h>

#include "ast.h"

void print_ast_dec(
    FILE *out,
    ast_dec *ast_root,
    int spaces);

#endif