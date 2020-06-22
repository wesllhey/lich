%{
#include <stdlib.h>
#include <stdio.h>

#include "ast.h"
#include "exception_handler.h"

ast_statement *ast_root;

int yylex(void);

void yyerror(
    const char *message)
{
    exception_handler_error(exception_handler_token_position, "%s", message);
	exit(1);
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
    ast_function *function;
    ast_function_list *function_list;

    ast_type *type;
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
%type <function> function
%type <function_list> function_list
%type <stmt_list> statement_list
%type <type> type
%type <field> parameter
%type <field_list> parameter_list

%start program
%%

program:
    program function_list { 
        ast_root = ast_dec_stmt(ast_function_dec_new(exception_handler_token_position, $2)); }
    |
    ;

function_list:
    function { $$ = ast_function_list_new($1, NULL); }
    |
    function function_list { $$ = ast_function_list_new($1, $2); }
    ;

function:
    FUNC IDENTIFIER L_PAREN parameter_list R_PAREN L_BRACE statement_list R_BRACE 
        { $$ = ast_function_new(exception_handler_token_position, symbol_table_entry_new($2), $4, $7, NULL); }
    |
    FUNC IDENTIFIER L_PAREN parameter_list R_PAREN ARROW type L_BRACE statement_list R_BRACE { $$ = NULL; }
    ;

parameter_list:
    parameter { $$ = ast_field_list_new($1, NULL); }
    |
    parameter COMMA parameter_list { $$ = ast_field_list_new($1, $3); }
    |
    { $$ = NULL; }
    ;

parameter: 
    type IDENTIFIER { $$ = ast_field_new(exception_handler_token_position, $1, symbol_table_entry_new($2)); }
    ; 

type:
    INT { $$ = ast_type_new(exception_handler_token_position, AST_INT_TYPE); }
    |
    IDENTIFIER { $$ = ast_type_new(exception_handler_token_position, AST_IDENTIFIER_TYPE); }
    ;

separator:
    SEMICOLON
    ;

statement_list:
    statement separator { $$ = ast_statement_list_new($1, NULL); }
    |
    statement separator statement_list { $$ = ast_statement_list_new($1, $3); }
    | 
    { $$ = NULL; }
    ;

statement:
    statement_assign { $$ = $1; }
    |
    statement_value { $$ = $1; }
    |
    statement_call
    |
    statement_return
    ;

statement_assign:
    type IDENTIFIER ASSIGN statement { $$ = ast_assign_stmt(exception_handler_token_position, $1, $2, $4); }
    ;

statement_operator:
    statement_value PLUS statement_value %prec PLUS { $$ = ast_op_stmt(exception_handler_token_position, AST_PLUS_OP, $1, $3); }
    |
    statement_value MINUS statement_value %prec MINUS { $$ = ast_op_stmt(exception_handler_token_position, AST_MINUS_OP, $1, $3); }
    |
    statement_value TIMES statement_value %prec TIMES { $$ = ast_op_stmt(exception_handler_token_position, AST_TIMES_OP, $1, $3); }
    |
    statement_value DIVIDE statement_value %prec DIVIDE { $$ = ast_op_stmt(exception_handler_token_position, AST_DIVIDE_OP, $1, $3); }
    |
    MINUS statement_value %prec UMINUS 
        { $$ = ast_op_stmt(exception_handler_token_position, AST_MINUS_OP, ast_int_stmt(exception_handler_token_position, 0) , $2); }
    ;

statement_value:
    statement_const { $$ = $1; }
    |
    statement_operator { $$ = $1; }
    |
    IDENTIFIER 
        { $$ = ast_var_stmt(exception_handler_token_position, ast_simple_var(exception_handler_token_position, symbol_table_entry_new($1))); }
    ;

statement_const:
    NUMBER { $$ = ast_int_stmt(exception_handler_token_position, $1); }
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
    type
    ;

statement_return:
    RETURN statement_operator {}
    |
    RETURN statement_call {}
    |
    ;

%%
