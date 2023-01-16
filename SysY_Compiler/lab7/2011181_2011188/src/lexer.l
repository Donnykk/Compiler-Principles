%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include "parser.h"
    #include <ostream>
    #include <fstream>
    #include <iostream>
    using namespace std;
    extern FILE *yyin; 
    extern FILE *yyout;
    int len = 0;
%}
DEC ([1-9][0-9]*|0)
OCT (0[0-7]+)
HEX (0[xX][0-9A-Fa-f]+)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]
BLOCKCOMMENTBEGIN \/\*
BLOCKCOMMENTELEMENT .
BLOCKCOMMENTEND \*\/
%x BLOCKCOMMENT
LINECOMMENT \/\/[^\n]*
%%
"int" {
    return INT;
}
"void" {
    return VOID;
}
"const" {
    return CONST;
}
"if" {
    return IF;
};
"else" {
    return ELSE;
};
"return" {
    return RETURN;
}
"while" {
    return WHILE;
}
"break" {
    return BREAK;
}
"continue" {
    return CONTINUE;
}
"==" {
    return EQ;
}
"!=" {
    return NEQ;
}
"=" {
    return ASSIGN;
}
"<" {
    return LESS;
}
"<=" {
    return LESSEQ;
}
">" {
    return GREAT;
}
">=" {
    return GREATEQ;
}
"+" {
    return ADD;
}
"-" {
    return SUB;
}
"*" {
    return MUL;
}
"/" {
    return DIV;
}
"%" {
    return MOD;
}
"&&" {
    return AND;
}
"||" {
    return OR;
}
"!" {
    return NOT;
}
";" {
    return SEMICOLON;
}
"(" {
    return LPAREN;
}
")" {
    return RPAREN;
}
"{" {
    return LBRACE;
}
"}" {
    return RBRACE;
}
"[" {
    return LBRACKET;
}
"]" {
    return RBRACKET;
}
"," {
    return COMMA;
}
{DEC} {
    len += strlen(yytext);
    yylval.itype = atoi(yytext);
    return INTEGER;
}
{OCT} {
    int temp;
    sscanf(yytext, "%o", &temp);
    yylval.itype = temp;
    return INTEGER;
}
{HEX} {
    int temp;
    sscanf(yytext, "%x", &temp);
    yylval.itype = temp;
    return INTEGER;
}

"putint" {
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    if(identifiers->lookup(yytext)==nullptr){
        std::vector<Type*> type_list; 
        std::vector<SymbolEntry*> se_list;
        type_list.push_back(TypeSystem::intType);
        Type* funcType = new FunctionType(TypeSystem::voidType, type_list, se_list);
        SymbolTable* globalTable;    
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}

"putch" {
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    if(identifiers->lookup(yytext)==nullptr){
        std::vector<Type*> type_list; 
        std::vector<SymbolEntry*> se_list;
        type_list.push_back(TypeSystem::intType);
        Type* funcType = new FunctionType(TypeSystem::voidType, type_list, se_list);
        SymbolTable* globalTable;   
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}

"getint" {
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    if(identifiers->lookup(yytext)==nullptr){
        Type* funcType = new FunctionType(TypeSystem::intType, {}, {});
        SymbolTable* globalTable;    
        for(globalTable = identifiers; globalTable->getPrev(); globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}

"getch" {
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    if(identifiers->lookup(yytext)==nullptr){
        Type* funcType = new FunctionType(TypeSystem::intType, {}, {});
        SymbolTable* globalTable;    
        for(globalTable = identifiers; globalTable->getPrev(); globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
    }
    return ID;
}

{ID} {
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}  

<*>{EOL} {
    len += strlen(yytext);
    yylineno++;
    len = 0;
}
{WHITE}
{LINECOMMENT} {}
{BLOCKCOMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{BLOCKCOMMENTELEMENT} {}
<BLOCKCOMMENT>{BLOCKCOMMENTEND} {BEGIN INITIAL;}


%%
