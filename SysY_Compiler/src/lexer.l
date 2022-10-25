%option noyywrap
%{
    /*
    * You will need to comment this line in lab5.
    */
    #define ONLY_FOR_LEX
    
    #ifdef ONLY_FOR_LEX
    #else
    #define YYSTYPE void *
    #include "parser.h"
    #endif

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include <string>

    #ifdef ONLY_FOR_LEX
    #include <ostream>
    #include <fstream>
    #include <math.h>
    using namespace std;
    extern FILE *yyin; 
    extern FILE *yyout;

    struct Identifier{
        string name;
        int type;
        int value;
        bool access;
    };

    Identifier id_list[10];
    int len;

    void DEBUG_FOR_LAB4(std::string s, Identifier* ptr = NULL){
        if(ptr == NULL){
            std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
            fputs(DEBUG_INFO.c_str(), yyout);
        }
        else{
            
        }
        
    }
    #endif
%}

DECIMAL ([1-9][0-9]*|0)
OCT (0[1-7][0-7]*|00)
HEX (0[xX][1-9|A-F|a-f][0-9|A-f|a-f]*|0x0)
DECIMALS ((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fLlL]?)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]
LINECOMMENT \/\/[^\n]*
BLOCKCOMMENTBEGIN "/*"
BLOCKCOMMENTELEMENT .|\n
BLOCKCOMMENTEND "*/"
%x BLOCKCOMMENT

%%

"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    #ifdef ONLY_FOR_LEX
        string temp = "INT\tint\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return INT;
    #endif
}
"float" {
    #ifdef ONLY_FOR_LEX
        string temp = "FLOAT\tfloat\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return FLOAT;
    #endif
}
"char" {
    #ifdef ONLY_FOR_LEX
        string temp = "CHAR\tchar\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return CHAR;
    #endif
}
"while" {
    #ifdef ONLY_FOR_LEX
        string temp = "WHILE\twhile\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return WHILE;
    #endif
}
"break" {
    #ifdef ONLY_FOR_LEX
        string temp = "BREAK\tbreak\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return BREAK;
    #endif
}
"continue" {
    #ifdef ONLY_FOR_LEX
        string temp = "CONTINUE\tcontinue\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return CONTINUE;
    #endif
}
"const" {
    #ifdef ONLY_FOR_LEX
        string temp = "CONST\tconst\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return CONST;
    #endif
}
"new" {
    #ifdef ONLY_FOR_LEX
        string temp = "NEW\tcnew\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return NEW;
    #endif
}
"delete" {
    #ifdef ONLY_FOR_LEX
        string temp = "DELETE\tdelete\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return DELETE;
    #endif
}
"using" {
    #ifdef ONLY_FOR_LEX
        string temp = "USING\tusing\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return USING;
    #endif
}
"namespace" {
    #ifdef ONLY_FOR_LEX
        string temp = "NAMESPACE\tnamespace\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return namespace;
    #endif
}
"void" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("VOID\tvoid\tline:" + to_string(yylineno));
    #else
        return VOID;
    #endif 
}
"if" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("IF\tif\tline:" + to_string(yylineno));
    #else
        return IF;
    #endif
};
"else" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ELSE\telse\tline:" + to_string(yylineno));
    #else
        return ELSE;
    #endif
};
"return" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RETURN\treturn\tline:" + to_string(yylineno));
    #else
        return RETURN;
    #endif
}
"&&" {
    #ifdef ONLY_FOR_LEX
        string temp = "AND\t&&\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return AND;
    #endif
}
"||" {
    #ifdef ONLY_FOR_LEX
        string temp = "OR\t||\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return OR;
    #endif
}
"==" {
    #ifdef ONLY_FOR_LEX
        string temp = "EQUAL\t==\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return EQUAL;
    #endif
}
"=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGN\t=\tline:" + to_string(yylineno));
    #else
        return ASSIGN;
    #endif
}
"!=" {
    #ifdef ONLY_FOR_LEX
        string temp = "UNEQUAL\t!=\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return UNEQUAL;
    #endif
}
"!" {
    #ifdef ONLY_FOR_LEX
        string temp = "AGAINST\t!\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return AGAINST;
    #endif
}
"*" {
    #ifdef ONLY_FOR_LEX
        string temp = "STAR\t*\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return STAR;
    #endif
}
">=" {
    #ifdef ONLY_FOR_LEX
        string temp = "GTE\t>=\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return GTE;
    #endif
}
"<=" {
    #ifdef ONLY_FOR_LEX
        string temp = "LTE\t<=\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return LTE;
    #endif
}
"<" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LESS\t<\tline:" + to_string(yylineno));
    #else
        return LESS;
    #endif
}
">" {
    #ifdef ONLY_FOR_LEX
        string temp = "GREATER\t>\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return GREATER;
    #endif
}
"+" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ADD\t+\tline:" + to_string(yylineno));
    #else
        return ADD;
    #endif
}
"-" {
    #ifdef ONLY_FOR_LEX
        string temp = "SUB\t-\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return SUB;
    #endif
}
"/" {
    #ifdef ONLY_FOR_LEX
        string temp = "DIV\t/\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return DIV;
    #endif
}
"%" {
    #ifdef ONLY_FOR_LEX
        string temp = "MOD\t%\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return MOD;
    #endif
}
"," {
    #ifdef ONLY_FOR_LEX
        string temp = "COMMA\t,\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return COMMA;
    #endif
}
":" {
    #ifdef ONLY_FOR_LEX
        string temp = "COLON\t:\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return COLON;
    #endif
}
"'" {
    #ifdef ONLY_FOR_LEX
        string temp = "QUOTATION\t'\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return QUOTATION;
    #endif
}
";" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SEMICOLON\t;\tline:" + to_string(yylineno));
    #else
        return SEMICOLON;
    #endif
}
"(" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LPAREN\t(\tline:" + to_string(yylineno));
    #else
        return LPAREN;
    #endif
}
")" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RPAREN\t)\tline:" + to_string(yylineno));
    #else
        return RPAREN;
    #endif
}
"{" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LBRACE\t{\tline" + to_string(yylineno));
    #else
        return LBRACE;
    #endif
}
"}" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RBRACE\t}\tline:" + to_string(yylineno));
    #else
        return RBRACE;
    #endif
}
"[" {
    #ifdef ONLY_FOR_LEX
        string temp = "LSQUARE\t[\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return LSQUARE;
    #endif
}
"]" {
    #ifdef ONLY_FOR_LEX
        string temp = "RSQUARE\t]\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return RSQUARE;
    #endif
}
"#" {
    #ifdef ONLY_FOR_LEX
        string temp = "WELLNO\t#\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return WELLNO;
    #endif
}

{DECIMAL} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        string temp = "DECIMAL\t" + a + "\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return DECIMAL;
    #endif
}
{OCT} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        int all = 0;
        int len = a.length()-1;
        for(int i = 0; i < len; i++)
        {
            int temp1 = (pow(8, (len - i - 1)));
            int temp2 = (a[i+1] - '0');
            all = all + temp1 * temp2;
        }
        string temp = "OCT\t" + to_string(all) + "\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return  OCT;
    #endif
}
{HEX} {
    #ifdef ONLY_FOR_LEX
        string a  = yytext;
        int all = 0;
        int len = a.length() - 2;
        for(int i = 0; i < len; i++)
        {
            int temp1 = (pow(16, (len - i - 1)));
            int temp2;
            if(a[i + 2] >= '0' && a[i + 2] <= '9'){
                temp2 = (a[i + 2] - '0');
            }
            else if(a[i + 2] >= 'A' && a[i + 2] <= 'F'){
                temp2 = a[i + 2] - 'A' + 10;
            }
            else if(a[i + 2] >= 'a' && a[i + 2] <= 'f'){
                temp2 = a[i + 2] - 'a' + 10;
            }
            all = all + temp1 * temp2;         
        }
        string temp = "HEX\t" + to_string(all) + "\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else 
        return HEX;
    #endif
}
{DECIMALS} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        string temp = "DECIMALS\t" + a + "\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return DECIMALS;
    #endif
}
<*>{EOL} yylineno++;
{WHITE}

{LINECOMMENT} {}
{BLOCKCOMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{BLOCKCOMMENTELEMENT} {}
<BLOCKCOMMENT>{BLOCKCOMMENTEND} {BEGIN INITIAL;}

{ID} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        string temp = "ID\t" + a + "\tline:" + to_string(yylineno);
        DEBUG_FOR_LAB4(temp);
    #else
        return ID;
    #endif
}
%%

#ifdef ONLY_FOR_LEX
int main(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "Argument Not Enough");
        exit(EXIT_FAILURE);
    }

    if(!(yyin = fopen(argv[1], "r"))){
        fprintf(stderr, "No such file or directory: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(!(yyout = fopen(argv[3], "w"))){
        fprintf(stderr, "No such file or directory: %s", argv[3]);
        exit(EXIT_FAILURE);
    }

    yylex();
    return 0;
}
#endif