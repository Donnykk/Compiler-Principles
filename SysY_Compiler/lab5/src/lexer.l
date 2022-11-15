%option noyywrap
%{
    /*
    * You will need to comment this line in lab5.
    */
    //#define ONLY_FOR_LEX
    
    #ifdef ONLY_FOR_LEX
    #else
    //#define YYSTYPE void *
    #endif

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include "parser.h"
    #include <string>
    #include <ostream>
    #include <fstream>
    #include <math.h>
    using namespace std;
    extern FILE *yyin; 
    extern FILE *yyout;
    extern bool dump_tokens;

    int wordnum=0;
    
    #ifdef ONLY_FOR_LEX
    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
    
    struct Symbol{
        string value;
        int scope;
    };

    Symbol sym_list[100]; //符号表
    int len = 0; //符号表长度
    int temp_scope = 0; //作用域编号
    int last_scope = 0;
    bool scope_used[100] = {false};
    bool inner = false;
    
    #endif
%}

DECIMIAL ([1-9][0-9]*|0)
OCT (0[1-7][0-7]*|00)
HEX (0[xX][1-9|A-F|a-f][0-9|A-f|a-f]*|0x0)
DECIMAL_FLOAT ((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fLlL]?)
HEXADECIMAL_FLOAT (0[xX](([0-9A-Fa-f]*[.][0-9A-Fa-f]*([pP][+-]?[0-9]+)?)|([0-9A-Fa-f]+[pP][+-]?[0-9]+))[fLlL]?)
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
        string temp = "INT\tint\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("int");
    #else
        return INT;
    #endif
}
"float" {
    #ifdef ONLY_FOR_LEX
        string temp = "FLOAT\tfloat\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("float");
    #else
        return FLOAT;
    #endif
}
"while" {
    #ifdef ONLY_FOR_LEX
        inner = true;
        string temp = "WHILE\twhile\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("while");
    #else
        return WHILE;
    #endif
}
"break" {
    #ifdef ONLY_FOR_LEX
        string temp = "BREAK\tbreak\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("break");
    #else
        return BREAK;
    #endif
}
"continue" {
    #ifdef ONLY_FOR_LEX
        string temp = "CONTINUE\tcontinue\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("continue");
    #else
        return CONTINUE;
    #endif
}
"const" {
    #ifdef ONLY_FOR_LEX
        string temp = "CONST\tconst\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("const");
    #else
        return CONST;
    #endif
}
"void" {
    #ifdef ONLY_FOR_LEX
        string temp = "VOID\tvoid\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("void");
    #else
        return VOID;
    #endif
}
"if" {
    #ifdef ONLY_FOR_LEX
        inner = true;
        string temp = "IF\tif\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("if");
    #else
        return IF;
    #endif
}
"else" {
    #ifdef ONLY_FOR_LEX
        string temp = "ELSE\telse\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("else");
    #else
        return ELSE;
    #endif
}
"return" {
    #ifdef ONLY_FOR_LEX
        string temp = "RETURN\treturn\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("return");
    #else
        return RETURN;
    #endif
}
"&&" {
    #ifdef ONLY_FOR_LEX
        string temp = "AND\t&&\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("&&");
    #else
        return AND;
    #endif
}
"||" {
    #ifdef ONLY_FOR_LEX
        string temp = "OR\t||\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("||");
    #else
        return OR;
    #endif
}
"==" {
    #ifdef ONLY_FOR_LEX
        string temp = "EQUAL\t==\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("==");
    #else
        return EQ;
    #endif
}
"=" {
    #ifdef ONLY_FOR_LEX
        string temp = "ASSIGN\t=\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("=");
    #else
        return ASSIGN;
    #endif
}
"!=" {
    #ifdef ONLY_FOR_LEX
        string temp = "UNEQUAL\t!=\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("!=");
    #else
        return NEQ;
    #endif
}
"!" {
    #ifdef ONLY_FOR_LEX
        string temp = "AGAINST\t!\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("!");
    #else
        return NOT;
    #endif
}
"*" {
    #ifdef ONLY_FOR_LEX
        string temp = "STAR\t*\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("*");
    #else
        return MUL;
    #endif
}
">=" {
    #ifdef ONLY_FOR_LEX
        string temp = "GTE\t>=\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(">=");
    #else
        return GREATEQ;
    #endif
}
"<=" {
    #ifdef ONLY_FOR_LEX
        string temp = "LTE\t<=\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("<=");
    #else
        return LESSEQ;
    #endif
}
"<" {
    #ifdef ONLY_FOR_LEX
        string temp = "LESS\t<\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("<");
    #else
        return LESS;
    #endif
}
">" {
    #ifdef ONLY_FOR_LEX
        string temp = "GREATER\t>\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(">");
    #else
        return GREAT;
    #endif
}
"+" {
    #ifdef ONLY_FOR_LEX
        string temp = "ADD\t+\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("+");
    #else
        return ADD;
    #endif
}
"-" {
    #ifdef ONLY_FOR_LEX
        string temp = "SUB\t-\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("-");
    #else
        return SUB;
    #endif
}
"/" {
    #ifdef ONLY_FOR_LEX
        string temp = "DIV\t/\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("/");
    #else
        return DIV;
    #endif
}
"%" {
    #ifdef ONLY_FOR_LEX
        string temp = "MOD\t%\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("%");
    #else
        return MOD;
    #endif
}
"," {
    #ifdef ONLY_FOR_LEX
        string temp = "COMMA\t,\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(",");
    #else
        return COMMA;
    #endif
}
";" {
    #ifdef ONLY_FOR_LEX
        string temp = "SEMICOLON\t;\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(";");
    #else
        return SEMICOLON;
    #endif
}
"(" {
    #ifdef ONLY_FOR_LEX
        string temp = "LPAREN\t(\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("(");
    #else 
        return LPAREN; 
    #endif
}
")" {
    #ifdef ONLY_FOR_LEX
        string temp = "RPAREN\t)\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(")");
    #else
        return RPAREN;
    #endif
}
"{" {
    #ifdef ONLY_FOR_LEX
    	if(!inner){
            last_scope = temp_scope;
            temp_scope++;
            while(scope_used[temp_scope]){
                temp_scope++;
            }
            scope_used[temp_scope] = true;
        }
        string temp = "LBRACE\t{\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("{");
    #else
        return LBRACE;
    #endif
}
"}" {
    #ifdef ONLY_FOR_LEX
    	if(inner){
            inner = false;
        } else{
            temp_scope = last_scope;
        }
        string temp = "RBRACE\t}\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("}");
    #else
        return RBRACE;
    #endif
}
"[" {
    #ifdef ONLY_FOR_LEX
        string temp = "LSQUARE\t[\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("[");
    #else
        return LBRACKET;
    #endif
}
"]" {
    #ifdef ONLY_FOR_LEX
        string temp = "RSQUARE\t]\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen("]");
    #else
        return RBRACKET;
    #endif
}

"getint" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::intType, {});
        SymbolTable* globalTable;  
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);   
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"getch" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::intType, {});
        SymbolTable* globalTable;  
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev());
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"getfloat" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::floatType, {});
        SymbolTable* globalTable;    
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"putint" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::intType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);//返回类型void，参数表[int]
        SymbolTable* globalTable;   
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"putch" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec;
        vec.push_back(TypeSystem::intType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);
        SymbolTable* globalTable; 
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"putfloat" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; 
        vec.push_back(TypeSystem::floatType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);
        SymbolTable* globalTable;    
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"starttime" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::voidType, {});//返回类型void，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
        globalTable->install(yytext, entry);
        return ID;
    #endif
}
"stoptime" {
    #ifdef ONLY_FOR_LEX
        
    #else
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::voidType, {});//返回类型void，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
        globalTable->install(yytext, entry);
        return ID;
    #endif
}

{DECIMIAL} {
    #ifdef ONLY_FOR_LEX
        string a=yytext;
        string temp="DECIMIAL\t"+a+"\tlinenum:"+to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(yytext);
    #else
        yylval.itype = atoi(yytext);
        return INTEGER;
    #endif
}
{OCT} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        int all=0;
        int len=a.length()-1;
        for(int i=0;i<len;i++)
        {
            int temp1=(pow(8,(len-i-1)));
            int temp2=(a[i+1]-'0');
            all=all+temp1*temp2;
        }
        string temp="OCT\t"+to_string(all)+"\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(yytext);
    #else
        char* stop;
        int dec = strtol(yytext, &stop, 8);
        yylval.itype = dec;
        return INTEGER;
    #endif
}
{HEX} {
    #ifdef ONLY_FOR_LEX
        string a  = yytext;
        int all = 0;
        int len=a.length() - 2;
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
        string temp = "HEX\t" + to_string(all) + "\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(yytext);
    #else 
        char* stop;
        int dec = strtol(yytext, &stop, 16);
        yylval.itype = dec;
        return INTEGER;
    #endif
}
{DECIMAL_FLOAT} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        string temp = "DECIMAL_FLOAT\t" + a + "\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(yytext);
    #else
        float temp;
        sscanf(yytext, "%f", &temp);
        yylval.ftype = double(temp);
        return FLOATING;
    #endif
}
{HEXADECIMAL_FLOAT} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        string temp = "HEXADECIMAL_FLOAT\t" + a + "\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum);
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(yytext);
    #else
        float temp;
        sscanf(yytext, "%f", &temp);
        yylval.ftype = double(temp);
        return FLOATING;
    #endif
}

{ID} {
    #ifdef ONLY_FOR_LEX
        string a = yytext;
        string temp;
        bool flag = false; //是否存在于符号表
        int i = 0;
        for(; i < len; i++){
            if(sym_list[i].value == a && sym_list[i].scope == temp_scope){
                flag = true;
                break;
            }
        }
        if(flag){
            temp = "ID\t" + a + "\tlinenum:" + to_string(yylineno) +"\toffset:"+to_string(wordnum)+ "\tSymbolTable_offset: " + to_string(i + 1);
        } else {
            len++;
            Symbol sym;
            sym.value = a;
            sym.scope = temp_scope;
            sym_list[len - 1] = sym;
            temp = "ID\t" + a + "\tlinenum:" + to_string(yylineno)+"\toffset:"+to_string(wordnum) + "\tSymbolTable_offset: " + to_string(len);
        }
        if(dump_tokens)
            DEBUG_FOR_LAB4(temp);
        wordnum+=strlen(yytext);
    #else
        char* lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        return ID;
    #endif
}


<*>{EOL} {
	wordnum+=strlen(yytext);
	yylineno++;
	wordnum=0;
}
{WHITE} {
    wordnum+=strlen(yytext);
}

{LINECOMMENT} {}
{BLOCKCOMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{BLOCKCOMMENTELEMENT} {}
<BLOCKCOMMENT>{BLOCKCOMMENTEND} {BEGIN INITIAL;}
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
