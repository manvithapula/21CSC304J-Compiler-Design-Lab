%{
    #include "calc.tab.h"
    #include <stdlib.h>
%}

%option noyywrap

NUMBER  [0-9]+
%%
"pow"   { return POW; }
"exp"   { return EXP; }
{NUMBER} { yylval.num = atoi(yytext); return NUMBER; }
[-+*/()] { return yytext[0]; }
[\t ]+  { /* Ignore whitespace */ }
\n      { return '\n'; }
.       { printf("Unexpected character: %s\n", yytext); }

%%
