%{
#include <stdlib.h>
#include <stdio.h>

#define YYSTYPE char*

int yylex();

void yyerror(
    const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
	return 1;
}

%}

%token IDENTIFIER RETURN NUMBER FUNC

%token L_BRACE R_BRACE L_PAREN R_PAREN 

%token IF WHILE FOR

%token EQ GT LT GE LE 
%token ASSIGN ARROW  

%token COMMA SEMICOLON

%token INT

%nonassoc EQ NEQ LE GE LT GT

%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS

%%

program:
    program function_dec
    |
    ;

function_dec:
    FUNC IDENTIFIER L_PAREN parameter_list R_PAREN L_BRACE statement_list R_BRACE
    |
    FUNC IDENTIFIER L_PAREN parameter_list R_PAREN ARROW type L_BRACE statement_list R_BRACE
    ;

parameter_list:
    |
    parameter
    |
    parameter COMMA parameter_list
    ;

parameter: 
    type IDENTIFIER
    ; 

type:
    NUMBER
    |
    IDENTIFIER
    ;

separator:
    SEMICOLON
    ;

statement_list:
    statement separator
    |
    statement separator statement_list
    |
    ;

statement:
    statement_assign 
    |
    statement_operator
    |
    statement_call
    |
    statement_return
    ;

statement_assign:
    type IDENTIFIER ASSIGN statement
    ;

statement_operator:
    statement_value PLUS statement_value
    |
    statement_value
    ;

statement_call:
    IDENTIFIER L_PAREN args R_PAREN
    ;

args: 
    arg
    |
    arg COMMA args
    |
    ;

arg:
    type
    ;

statement_value:
    type
    ;

statement_return:
    RETURN statement_operator
    |
    RETURN statement_call
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
