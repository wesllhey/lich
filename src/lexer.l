%{
#include <string.h>

#include "ast.h"
#include "parser.tab.h"
#include "exception_handler.h"

void yyerror();

unsigned char_position = 1;

int yywrap(void)
{
    char_position = 1;
    return 1;
}

void next_token(void)
{
    exception_handler_token_position = char_position;
    char_position += yyleng;
}

%}

D			[0-9]
L			[a-zA-Z_]

%%

(" "|"\t"|"\r") { next_token(); } 
\n              { next_token(); exception_handler_new_line(); }

"{"             { next_token(); return L_BRACE; }
"}"             { next_token(); return R_BRACE; }
"("             { next_token(); return L_PAREN; }
")"             { next_token(); return R_PAREN; }

"+"             { next_token(); return PLUS; }
"-"             { next_token(); return MINUS; }
"*"             { next_token(); return TIMES; }
"/"             { next_token(); return DIVIDE; }

"=="            { next_token(); return EQ; }
">"             { next_token(); return GT; }
"<"             { next_token(); return LT; }
">="            { next_token(); return GE; }
"<="            { next_token(); return LE; }

":="            { next_token(); return ASSIGN; }
"->"            { next_token(); return ARROW; }

";"             { next_token(); return SEMICOLON; }
","             { next_token(); return COMMA; }

"if"            { next_token(); return IF; }
"while"         { next_token(); return WHILE; }
"return"        { next_token(); return RETURN; }
"for"           { next_token(); return FOR; }
"func"          { next_token(); return FUNC; }    

"int"           { next_token(); yylval.string_value = strdup(yytext); return INT; }

[0-9]+          { next_token(); yylval.int_value = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9_]* { next_token(); yylval.string_value = strdup(yytext); return IDENTIFIER; }

%%