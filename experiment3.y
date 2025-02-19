%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    int yylex();
    void yyerror(const char *s);
%}

%union {
    int num;
}

/* Declare token types */
%token <num> NUMBER
%token POW EXP

/* Declare non-terminals with the appropriate type */
%type <num> expression

%left '+' '-'
%left '*' '/'
%right POW EXP
%left '(' ')'

%%
calculation:
    calculation expression '\n' { printf("Result: %d\n", $2); }
    | /* empty */
    ;

expression:
    NUMBER { $$ = $1; }
    | expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { 
        if ($3 == 0) {
            printf("Error: Division by zero!\n");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | expression POW expression { $$ = pow($1, $3); }
    | EXP '(' expression ')' { $$ = exp($3); }
    | '(' expression ')' { $$ = $2; }
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expressions (e.g., 2+3, pow 2 3, exp(1), etc.):\n");
    yyparse();
    return 0;
}
