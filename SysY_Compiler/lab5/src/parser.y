%code top {
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
    Type* currentType;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    double ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOATING
%token CONST
%token INT FLOAT VOID
%token IF ELSE WHILE BREAK CONTINUE RETURN 
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET SEMICOLON COMMA
%token ASSIGN ADD SUB MUL DIV MOD AND OR NOT LESS LESSEQ GREAT GREATEQ EQ NEQ 

%type <stmttype> Stmts Stmt AssignStmt ExpStmt BlockStmt IfStmt WhileStmt BreakStmt ContinueStmt ReturnStmt DeclStmt ConstDefList ConstDef VarDefList VarDef FuncDef FuncParams FuncParam FuncCallParams
%type <exprtype> Exp ConstExp AddExp MulExp NormalExp PrimaryExp LVal Cond LOrExp LAndExp EqExp RelExp
%type <type> Type 

%precedence THEN
%precedence ELSE
%%

Program
    :   Stmts {
            ast.setRoot($1);
        }
    ;
Stmts
    :   Stmts Stmt{
            SeqNode* node = (SeqNode*)$1;
            node->addNext((StmtNode*)$2);
            $$ = (StmtNode*) node;
        }
    |   Stmt{
            SeqNode* node = new SeqNode();
            node->addNext((StmtNode*)$1);
            $$ = (StmtNode*) node;
        }
    ;
Stmt
    :   AssignStmt {$$=$1;}
    |   BlockStmt {$$=$1;}
    |   ExpStmt SEMICOLON {$$=$1;}
    |   IfStmt {$$=$1;}
    |   WhileStmt {$$=$1;}
    |   BreakStmt {$$=$1;}
    |   ContinueStmt {$$=$1;}
    |   ReturnStmt {$$=$1;}
    |   DeclStmt {$$=$1;}
    |   FuncDef {$$=$1;}
    |   SEMICOLON {$$ = new EmptyStmt();}
    ;
LVal
    :   ID {
            SymbolEntry *se;
            se = identifiers->lookup($1);
            if(se == nullptr) {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
                delete [](char*)$1;
                assert(se != nullptr);
            }
            $$ = new Id(se);
            delete []$1;
        }
    ;
AssignStmt
    :   LVal ASSIGN Exp SEMICOLON {
            $$ = new AssignStmt($1, $3);
        }
    ;
ExpStmt
    :   ExpStmt COMMA Exp {
            ExprStmtNode* node = (ExprStmtNode*)$1;
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext($1);
            $$ = node;
        }
    ;
BlockStmt
    :   LBRACE {
            identifiers = new SymbolTable(identifiers);
        } 
        Stmts RBRACE {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
    |   LBRACE RBRACE {
            $$ = new CompoundStmt(nullptr);
        }
    ;
IfStmt
    :   IF LPAREN Cond RPAREN Stmt %prec THEN {
            $$ = new IfStmt($3, $5);
        }
    |   IF LPAREN Cond RPAREN Stmt ELSE Stmt {
            $$ = new IfElseStmt($3, $5, $7);
        }
    ;
WhileStmt
    :   WHILE LPAREN Cond RPAREN Stmt {
            $$ = new WhileStmt($3,$5);
        }
    ;
BreakStmt
    :   BREAK SEMICOLON {
            $$ = new BreakStmt();
        }
    ;
ContinueStmt
    :   CONTINUE SEMICOLON{
            $$ = new ContinueStmt();
        }
    ;
ReturnStmt
    :   RETURN Exp SEMICOLON{
            $$ = new ReturnStmt($2);
        }
    |   RETURN SEMICOLON {
            $$ = new ReturnStmt(nullptr);
        }
    ;
Exp
    :   AddExp {
            $$ = $1;
        }
    ;
ConstExp
    :   AddExp {
            $$ = $1;
        }
    ;
AddExp
    :   MulExp {
            $$ = $1;
        }
    |   AddExp ADD MulExp {
            SymbolEntry *se;
            if($1->getType()->isInt() && $3->getType()->isInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        }
    |   AddExp SUB MulExp {
            SymbolEntry *se;
            if($1->getType()->isInt() && $3->getType()->isInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        }
    ;
MulExp
    :   NormalExp {
            $$ = $1;
        }
    |   MulExp MUL NormalExp {
            SymbolEntry *se;
            if($1->getType()->isInt() && $3->getType()->isInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        }
    |   MulExp DIV NormalExp {
            SymbolEntry *se;
            if($1->getType()->isInt() && $3->getType()->isInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        }
    |   MulExp MOD NormalExp {
            SymbolEntry *se;
            if($1->getType()->isInt() && $3->getType()->isInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        }
    ;
NormalExp
    :   PrimaryExp {
            $$ = $1;
        }
    |   ID LPAREN FuncCallParams RPAREN {
            SymbolEntry *se;
            se = identifiers->lookup($1);
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
                delete [](char*)$1;
                assert(se != nullptr);
            }
            SymbolEntry *tmp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel());
            $$ = new FuncCallNode(tmp, new Id(se), (FuncCallParamsNode*)$3);
        }
    |   ADD NormalExp {
            $$ = $2;
        }
    |   SUB NormalExp {
            SymbolEntry *tmp = new TemporarySymbolEntry($2->getType(), SymbolTable::getLabel());
            $$ = new OneOpExpr(tmp, OneOpExpr::SUB, $2);
        }
    |   NOT NormalExp {
            SymbolEntry *tmp = new TemporarySymbolEntry($2->getType(), SymbolTable::getLabel());
            $$ = new OneOpExpr(tmp, OneOpExpr::NOT, $2);
        }
    ;
PrimaryExp
    :   LVal {
            $$ = $1;
        }
    |   LPAREN Exp RPAREN {
            $$ = $2;
        }
    |   INTEGER {
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
            $$ = new Constant(se);
        }
    |   FLOATING {
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, $1);
            $$ = new Constant(se);
        }
    ;
FuncCallParams
    :   FuncCallParams COMMA Exp {
            FuncCallParamsNode* node = (FuncCallParamsNode*) $1;
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            FuncCallParamsNode* node = new FuncCallParamsNode();
            node->addNext($1);
            $$ = node;
        }
    |   %empty {
            $$ = nullptr;
        }
    ;
Cond
    :   LOrExp {
            $$ = $1;
        }
    ;
LOrExp
    :   LAndExp {
            $$ = $1;
        }
    |   LOrExp OR LAndExp   {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
        }
    ;
LAndExp
    :   EqExp {
            $$ = $1;
        }
    |   LAndExp AND EqExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
        }
    ;
EqExp
    :   RelExp {
            $$ = $1;
        }
    |   EqExp EQ RelExp {
            SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
        }
    |   EqExp NEQ RelExp {
            SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::NEQ, $1, $3);
        }
    ;
RelExp
    :   AddExp {
            $$ = $1;
        }
    |   RelExp LESS AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
        }
    |   RelExp LESSEQ AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::LESSEQ, $1, $3);
        }
    |   RelExp GREAT AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::GREAT, $1, $3);
        }
    |   RelExp GREATEQ AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::GREATEQ, $1, $3);
        }
    ;
Type
    :   INT {
            $$ = TypeSystem::intType;
            currentType = TypeSystem::intType;
        }
    |   FLOAT {
            $$ = TypeSystem::floatType;
            currentType = TypeSystem::floatType;
        }    
    |   VOID {
            $$ = TypeSystem::voidType;
        }
    ;
DeclStmt
    :   CONST Type ConstDefList SEMICOLON {
            $$ = $3;
        }
    |   Type VarDefList SEMICOLON {
            $$ = $2;
        }
    ;
ConstDefList
    :   ConstDefList COMMA ConstDef {
            DeclStmt* node = (DeclStmt*) $1;
            node->addNext((DefNode*)$3);
            $$ = node;
        }
    |   ConstDef {
            DeclStmt* node = new DeclStmt(true);
            node->addNext((DefNode*)$1);
            $$ = node;
        }
    ;
ConstDef
    :   ID ASSIGN ConstExp {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::constIntType;
            }
            else{
                type = TypeSystem::constFloatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            $$ = new DefNode(new Id(se), true);
        }
    ;
VarDefList
    :   VarDefList COMMA VarDef {
            DeclStmt* node = (DeclStmt*) $1;
            node->addNext((DefNode*)$3);
            $$ = node;
        }
    |   VarDef {
            DeclStmt* node = new DeclStmt(true);
            node->addNext((DefNode*)$1);
            $$ = node;
        }
    ;
VarDef
    :   ID {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            $$ = new DefNode(new Id(se), false);
        }
    |   ID ASSIGN Exp {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            $$ = new DefNode(new Id(se), false);
        }
    ;
FuncDef
    :   Type ID {
            Type *funcType;
            funcType = new FunctionType($1,{});
            SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
            identifiers->install($2, se);
            identifiers = new SymbolTable(identifiers);
        }
        LPAREN FuncParams{
            SymbolEntry *se;
            se = identifiers->lookup($2);
            assert(se != nullptr);
            if($5!=nullptr){
                //将函数参数类型写入符号表
                ((FunctionType*)(se->getType()))->setparamsType(((FuncDefParamsNode*)$5)->getParamsType());
            }   
        } 
        RPAREN BlockStmt {
            SymbolEntry *se;
            se = identifiers->lookup($2);
            assert(se != nullptr);
            $$ = new FunctionDef(se, (FuncDefParamsNode*)$5, $8);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
            delete []$2;
        }
    ;
FuncParams
    :   FuncParams COMMA FuncParam {
            FuncDefParamsNode* node = (FuncDefParamsNode*)$1;
            node->addNext(((DefNode*)$3)->getId());
            $$ = node;
        }
    |   FuncParam {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext(((DefNode*)$1)->getId());
            $$ = node;
        }
    |   %empty {
            $$ = nullptr;
        }
    ;
FuncParam
    :   Type ID {
            SymbolEntry *se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
            identifiers->install($2, se);
            $$ = new DefNode(new Id(se), false);
        }
    ;
%%

int yyerror(char const* message) {
    std::cerr<<message<<std::endl;
    return -1;
}