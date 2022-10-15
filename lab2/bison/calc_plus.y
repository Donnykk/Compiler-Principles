%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
int yylex ();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);
struct id
{
    char *name;
    double value;
} id_list[50];
struct id* find_id(char* s);
char idStr[50];
%}

%union {
    double dval;
    struct id *identifier;
}

%token <identifier> ID
%token <dval> NUMBER
%token <dval> ADD
%token <dval> SUB
%token <dval> MUL
%token <dval> DIV
%token <dval> LEFT
%token <dval> RIGHT
%token <dval> EQUAL
%token <dval> ADD_
%token <dval> SUB_

%right EQUAL
%left ADD SUB
%left MUL DIV
%right ADD_ SUB_
%right UMINUS

%type <dval> expr

%%
lines   :   lines stmt ';' 
        |   stmt ';'
        |
        ;

stmt    :   ID EQUAL expr   {$1->value = $3;}
        |   expr            {printf("%f\n", $1);}
        ;

expr    :   expr ADD expr   {$$ = $1 + $3;} 
        |   expr SUB expr   {$$ = $1 - $3;} 
        |   expr MUL expr   {$$ = $1 * $3;} 
        |   expr DIV expr   {$$ = $1 / $3;} 
        |   LEFT expr RIGHT {$$ = $2;}
        |   ID              {$$ = $1->value;}
        |   ID ADD_         {$$ = $1->value; 
                                $1->value += 1;}
		|   ID SUB_         {$$ = $1->value;
                                $1->value -= 1;}
		|   ADD_ ID         {$2->value += 1; 
                                $$ = $2->value;}
		|   SUB_ ID         {$2->value -= 1;
                                $$ = $2->value;}
        |   SUB expr %prec UMINUS {$$ = -$2;}
        |   NUMBER          {$$ = $1;}
        ;
%%

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
                idStr[ti] = t;
                ti++;
                t = getchar();
            }
            idStr[ti] = '\0';
            yylval.identifier = find_id(idStr);
            ungetc(t, stdin);
            return ID;
        } else if(isdigit(t)) {
            yylval.dval = 0;
            while(isdigit(t)) {
                yylval.dval = yylval.dval * 10 + t - '0';
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

struct id* find_id(char* s){
    struct id *sp;
    for(sp = id_list; sp < &id_list[50]; sp++){
        //符号表中存在目标符号
        if(sp->name && !strcmp(sp->name, s))
            return sp;
        //符号表查找完
        if(!sp->name){
            sp->name = strdup(s);
            return sp;
        }
    }
    yyerror("id_list FULL");
    exit(1);
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