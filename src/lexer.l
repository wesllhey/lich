%{
#include <string.h>

#include "ast.h"
#include "parser.tab.h"

void yyerror();

int charPos=1;

int yywrap(void)
{
    return 1;
}

%}

D			[0-9]
L			[a-zA-Z_]

%%
[ \n\r\t]+        { /* Ignore whitespace */ }

"{"             { return L_BRACE; }
"}"             { return R_BRACE; }
"("             { return L_PAREN; }
")"             { return R_PAREN; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }

"=="            { return EQ; }
">"             { return GT; }
"<"             { return LT; }
">="            { return GE; }
"<="            { return LE; }

":="            { return ASSIGN; }
"->"            { return ARROW; }

";"             { return SEMICOLON; }
","             { return COMMA; }

"if"            { return IF; }
"while"         { return WHILE; }
"return"        { return RETURN; }
"for"           { return FOR; }
"func"          { return FUNC; }    

"int"           { yylval.string_value = strdup(yytext); return INT; }

[0-9]+	 { yylval.int_value = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9_]* { yylval.string_value = strdup(yytext); return IDENTIFIER; }

%%