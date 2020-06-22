#include <stdio.h>

#include "ast.h"
#include "parser.tab.h"
#include "print_ast.h"
#include  "exception_handler.h"

extern ast_statement *ast_root;

extern int yyparse(void);

int main(
    int argc,
    char *argv[])
{
    extern FILE *yyin;
    ++argv;
    --argc;

    char *file_name = argv[0];

    yyin = fopen(file_name, "r");

    exception_handler_init(file_name, yyin);

    if (yyparse() == 0) {
        printf("Parse Completed\n");

        pint_ast_stmt_root(stdout, ast_root, 0);
        fprintf(stdout, "\n");
        
        exception_handler_free();
    }
}
