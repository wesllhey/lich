%{
#define YYSTYPE char*

#include <string.h>

#include "parser.tab.h"

void yyerror();
%}

D			[0-9]
L			[a-zA-Z_]

%%
[ \n\r\t]+        { /* Ignore whitespace */ }

[0-9]+          { yylval = strdup(yytext); return NUMBER; }

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

{L}({L}|{D})*   { yylval = strdup(yytext); return IDENTIFIER; }
