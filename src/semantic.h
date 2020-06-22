#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include "types.h"
#include "ast.h"

typedef struct semantic_type {
    struct ast_statement *stmt;
    struct types *type;
} statement_type;

void semantic_translate(
    ast_statement *stmt);

#endif