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
struct id
{
    char idStr[50];
    double value;
} id_;
%}

%token ID
%token NUMBER
%token ADD SUB
%token MUL DIV
%token LEFT RIGHT
%token EQUAL
%token ADD_ SUB_

%right EQUAL
%left ADD SUB
%left MUL DIV
%right ADD_ SUB_
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
        |   ID              {$$ = id_.value;}
        |   ID EQUAL expr   {id_.value = $3;
                                $$ = $3;}
        |   ID ADD_         {$$ = id_.value; 
                                id_.value += 1;}
		|   ID SUB_         {$$ = id_.value;
                                id_.value -= 1;}
		|   ADD_ ID         {id_.value += 1; 
                                $$ = id_.value;}
		|   SUB_ ID         {id_.value -= 1;
                                $$ = id_.value;}
        |   SUB expr %prec UMINUS {$$ = -$2;}
        |   NUMBER          {$$ = $1;}
        ;

%%

//programs section
int yylex()
{
    char t;
    while(1) {
        t = getchar();
        if(t == ' ' || t == '\t' || t == '\n') {
            //do nothing
        } else if (( t >= 'a' && t <= 'z') || ( t >= 'A' && t <= 'Z') || ( t == '_')) {
            int ti = 0;
            while (( t >= 'a' && t <= 'z') || ( t >= 'A' && t <= 'Z') || ( t == '_') || (t >= '0' && t <='9')) {
                id_.idStr[ti] = t;
                ti++;
                t = getchar();
            }
            id_.idStr[ti] = '\0';
            ungetc(t, stdin);
            return ID;
        } else if(isdigit(t)) {
            yylval = 0;
            while(isdigit(t)) {
                yylval = yylval * 10 + t - '0';
                t = getchar();
            }
            ungetc(t, stdin);
            return NUMBER;
        } else if(t == '+') {
            t = getchar();
			if(t == '+')
			    return ADD_;
			else {
				ungetc(t, stdin);
				return ADD;
            }
        } else if(t == '-') {
            t = getchar();
			if(t == '-')
				return SUB_;
			else {
				ungetc(t, stdin);
				return SUB;
            }
        } else if(t == '*') {
            return MUL;
        } else if(t == '/') {
            return DIV;
        } else if(t == '(') {
            return LEFT;
        } else if(t == ')') {
            return RIGHT;
        } else if(t == '=') {
            return EQUAL;
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