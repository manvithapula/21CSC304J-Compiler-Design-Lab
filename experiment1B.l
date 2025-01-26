%{
#include <stdio.h>
%}

%%
[aeiouAEIOU]    printf("%s is a Vowel\n", yytext);
end             printf("%s is a Consonant\n", yytext);
.               { return 0; }
%%

int main() {
    yylex(); 
    return 0;
}
