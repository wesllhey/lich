%{
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>


ast_statement *ast_root;

int yylex(void);

void yyerror(
    const char *str)
{
	fprintf(stderr, "error: %s\n", str);
}

%}


%union {
    unsigned position;
    int int_value;
    char *string_value;

    ast_statement *stmt;
    ast_statement_list *stmt_list;
    ast_dec *dec;
    ast_var *var;

    ast_field *field;
    ast_field_list *field_list;
    ast_function_dec *function_dec;
    ast_function_dec_list *function_dec_list;
}

%token <string_value> IDENTIFIER INT
%token <int_value> NUMBER

%token RETURN FUNC

%token L_BRACE R_BRACE L_PAREN R_PAREN 

%token IF WHILE FOR

%token EQ GT LT GE LE 
%token ASSIGN ARROW  

%token COMMA SEMICOLON


%nonassoc EQ NEQ LE GE LT GT

%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS
    
%type <stmt> statement statement_assign statement_operator statement_value statement_const 
%type <stmt_list> statement_list
%type <var> types

%start program

%%

program:
    program function_dec
    |
    ;

function_dec:
    FUNC IDENTIFIER L_PAREN parameter_list R_PAREN L_BRACE statement_list R_BRACE
    |
    FUNC IDENTIFIER L_PAREN parameter_list R_PAREN ARROW types L_BRACE statement_list R_BRACE
    ;

parameter_list:
    |
    parameter
    |
    parameter COMMA parameter_list
    ;

parameter: 
    types IDENTIFIER
    ; 

types:
    INT { $$ = ast_simple_var(0, symbol_table_entry_new($1)); }
    |
    IDENTIFIER { $$ = ast_simple_var(0, symbol_table_entry_new($1)); }
    ;

separator:
    SEMICOLON
    ;

statement_list:
    statement separator { $$ =  ast_statement_list_new($1, NULL); }
    |
    statement separator statement_list { $$ =  ast_statement_list_new($1, $3); }
    | { $$ = NULL; }
    ;

statement:
    statement_assign { $$ = $1; }
    |
    statement_operator { $$ = $1; }
    |
    statement_call
    |
    statement_return
    ;

statement_assign:
    types IDENTIFIER ASSIGN statement { $$ = ast_assign_stmt(0, $1, $2, $4); }
    ;

statement_operator:
    statement_value PLUS statement_value { $$ = ast_op_stmt(0, AST_PLUS_OP, $1, $3); }
    |
    statement_value { $$ = $1; }
    ;

statement_value:
    statement_const { $$ = $1; }
    ;

statement_const:
    NUMBER { $$ = ast_int_stmt(0, $1); }
    ;

statement_call:
    IDENTIFIER L_PAREN args R_PAREN {}
    ;

args: 
    arg
    |
    arg COMMA args
    |
    ;

arg:
    types
    ;

statement_return:
    RETURN statement_operator {}
    |
    RETURN statement_call {}
    |
    ;

%%

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
