#include <stdio.h>
#include "ast.h"

#include "parser.tab.h"

extern ast_dec *ast_root;
extern int yyparse(void);

int main(
    int argc, 
    char *argv[])
{ 
    extern FILE *yyin;
    ++argv; --argc;

    char *file_name = argv[0];

    yyin = fopen(file_name, "r");
    
    if (yyparse() == 0) {
        printf("Parse Completed\n");
    }
}
