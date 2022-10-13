%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef YYSTYPE
#define YYSTYPE double
#endif
int yylex ();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);
%}

%token NUMBER
%token ADD
%token SUB
%token MUL
%token DIV
%token LEFT
%token RIGHT
%token OPOS

%left ADD SUB
%left MUL DIV
%right UMINUS

%%

lines   :   lines expr ';' {printf("%f\n", $2);}
        |   lines ';'
        |
        ;
    
expr    :   expr ADD expr   {$$ = $1 + $3;} 
        |   expr SUB expr   {$$ = $1 - $3;} 
        |   expr MUL expr   {$$ = $1 * $3;} 
        |   expr DIV expr   {$$ = $1 / $3;} 
        |   LEFT expr RIGHT {$$ = $2;}
        |   OPOS expr %prec UMINUS {$$ = -$2;}
        |   NUMBER          {$$ = $1;}
        ;

%%

//programs section
int yylex()
{
    int t;
    while(1) {
        t = getchar();
        if(t == ' ' || t == '\t' || t == '\n'){
            //do nothing
        } else if(isdigit(t)) {
            yylval = 0;
            while(isdigit(t)) {
                yylval = yylval * 10 + t - '0';
                t = getchar();
            }
            ungetc(t, stdin);
            return NUMBER;
        } else if(t == '+') {
            return ADD;
        } else if(t == '-') {
            return SUB;
        } else if(t == '*') {
            return MUL;
        } else if(t == '/') {
            return DIV;
        } else if(t == '(') {
            return LEFT;
        } else if(t == ')') {
            return RIGHT;
        } else {
            return t;
        }
    }
}

int main(void)
{
    yyin = stdin;
    do {
        yyparse();
    } while(!feof(yyin));
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error : %s\n", s);
    exit(1);
}