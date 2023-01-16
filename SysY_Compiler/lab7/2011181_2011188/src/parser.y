%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    #include <cstring>
    #include <stack>
    extern Ast ast;

    int yylex();
    int yyerror(char const*);
    ArrayType* arrayType;
    std::stack<InitExpr*> init_list;
    std::stack<StmtNode*> while_stack;
    InitExpr* top;
    int iter;
    int count = 0;
    int param_num = 0;
    int* value_arr;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
    SymbolEntry* se;
}

%start Program
%token <strtype> ID STRING
%token <itype> INTEGER
%token IF ELSE WHILE
%token INT VOID
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LBRACKET RBRACKET COMMA  
%token ADD SUB MUL DIV MOD OR AND LESS LESSEQ GREAT GREATEQ ASSIGN EQ NEQ NOT
%token CONST
%token RETURN CONTINUE BREAK

%type<stmttype> Stmts Stmt AssignStmt ExprStmt BlockStmt IfStmt WhileStmt BreakStmt ContinueStmt ReturnStmt DeclStmt VarDecl ConstDecl VarList ConstList VarDef ConstDef FuncDef FuncFParam FuncFParams EmptyStmt
%type<exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp MulExp ConstExp EqExp UnaryExp InitVal ConstInitVal FuncRParams Array Param_Arr
%type<type> Type

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {
        $$=$1;
    }
    | ExprStmt {$$ = $1;}
    | BlockStmt {$$=$1;}
    | EmptyStmt {$$ = $1;}
    | IfStmt {$$ = $1;}
    | WhileStmt {$$ = $1;}
    | BreakStmt {
        $$=$1;
    }
    | ContinueStmt {
        $$=$1;
    }
    | ReturnStmt {$$ = $1;}
    | DeclStmt {$$ = $1;}
    | FuncDef {$$ = $1;}
    ;
LVal
    : ID {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        $$ = new Id(se);
        delete []$1;
    }
    |
    ID Array 
    {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        $$ = new Id(se, $2);
        delete []$1;
    }    
    ; 
AssignStmt
    : LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
ExprStmt
    : Exp SEMICOLON {
        $$ = new ExprStmt($1);
    }
    ;
EmptyStmt
    : SEMICOLON {
        $$ = new EmptyStmt();
    }
    ;
BlockStmt
    : LBRACE {
        identifiers = new SymbolTable(identifiers);
    } 
      Stmts RBRACE {
        $$ = new CompoundStmt($3);

        SymbolTable* top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
    }
    | LBRACE RBRACE {
        $$ = new CompoundStmt();
    }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
WhileStmt
    : WHILE LPAREN Cond RPAREN {
        WhileStmt *whileNode = new WhileStmt($3);
        $<stmttype>$ = whileNode;
        while_stack.push(whileNode);
    }
    Stmt {
        StmtNode *whileNode = $<stmttype>5; 
        ((WhileStmt*)whileNode)->setStmt($6);
        $$=whileNode;
        while_stack.pop();
    }
    ;
BreakStmt
    : BREAK SEMICOLON {
        $$ = new BreakStmt(while_stack.top());
    }
    ;
ContinueStmt
    : CONTINUE SEMICOLON {
        $$ = new ContinueStmt(while_stack.top());
    }
    ;
ReturnStmt
    : RETURN SEMICOLON {
        $$ = new ReturnStmt();
    }
    | RETURN Exp SEMICOLON {
        $$ = new ReturnStmt($2);
    }
    ;
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    LOrExp {$$ = $1;}
    ;
PrimaryExp
    : LPAREN Exp RPAREN {
        $$ = $2;
    }
    | LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry* se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    ;
UnaryExp 
    : PrimaryExp {$$ = $1;}
    | ID LPAREN FuncRParams RPAREN {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        if(se == nullptr)
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)$1);
        $$ = new FunctionCall(se, $3);
    }
    | ID LPAREN RPAREN {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        if(se == nullptr)
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)$1);
        $$ = new FunctionCall(se);
    }
    | ADD UnaryExp {$$ = $2;}
    | SUB UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::SUB, $2);
    }
    | NOT UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::NOT, $2);
    }
    ;
MulExp
    : UnaryExp {$$ = $1;}
    | MulExp MUL UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    | MulExp DIV UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    | MulExp MOD UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
    }
    ;
AddExp
    : MulExp {$$ = $1;}
    | AddExp ADD MulExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    | AddExp SUB MulExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;
RelExp
    : AddExp {
        $$ = $1;
    }
    | RelExp LESS AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    | RelExp LESSEQ AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSEQ, $1, $3);
    }
    | RelExp GREAT AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREAT, $1, $3);
    }
    | RelExp GREATEQ AddExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATEQ, $1, $3);
    }
    ;
EqExp
    : RelExp {$$ = $1;}
    | EqExp EQ RelExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
    }
    | EqExp NEQ RelExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NEQ, $1, $3);
    }
    ;
LAndExp
    : EqExp {$$ = $1;}
    | LAndExp AND EqExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
LOrExp
    : LAndExp {$$ = $1;}
    | LOrExp OR LAndExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
ConstExp
    : AddExp {$$ = $1;}
    ;
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    ;
DeclStmt
    : VarDecl {$$ = $1;}
    | ConstDecl {$$ = $1;}
    ;
VarDecl
    : Type VarList SEMICOLON {$$ = $2;}
    ;
ConstDecl
    : CONST Type ConstList SEMICOLON {
        $$ = $3;
    }
    ;
VarList
    : VarList COMMA VarDef {
        $$ = $1;
        $1->setNext($3);
    } 
    | VarDef {$$ = $1;}
    ;
ConstList
    : ConstList COMMA ConstDef {
        $$ = $1;
        $1->setNext($3);
    }
    | ConstDef {$$ = $1;}
    ;
VarDef
    : ID {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        if(!identifiers->install($1, se))
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    | ID Array {
        SymbolEntry* se;
        std::vector<int> vec;
        ExprNode* temp = $2;
        while(temp){
            vec.push_back(temp->getValue());
            temp = (ExprNode*)(temp->getNext());
        }
        Type *type = TypeSystem::intType;
        Type* temp1;
        while(!vec.empty()){
            temp1 = new ArrayType(type, vec.back());
            if(type->isArray())
                ((ArrayType*)type)->setArrayType(temp1);
            type = temp1;
            vec.pop_back();
        }
        arrayType = (ArrayType*)type;
        se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setInitZero();
        int *p = new int[type->getSize()];
        ((IdentifierSymbolEntry*)se)->setArrayValue(p);
        if(!identifiers->install($1, se))
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    | ID ASSIGN InitVal {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        ((IdentifierSymbolEntry*)se)->setValue($3->getValue());
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    ;
ConstDef
    : ID ASSIGN ConstInitVal {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry(TypeSystem::constIntType, $1, identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setConst();
        identifiers->install($1, se);
        ((IdentifierSymbolEntry*)se)->setValue($3->getValue());
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    ;
Array
    : LBRACKET ConstExp RBRACKET 
    {
        $$ = $2;
    }
    | Array LBRACKET ConstExp RBRACKET 
    {
        $$ = $1;
        $1->setNext($3);
    }
    ;
InitVal 
    : Exp 
    {
        $$ = $1;
        if(!init_list.empty())
        {
            value_arr[iter++] = $1->getValue();
            Type* arrTy = init_list.top()->getSymbolEntry()->getType();
            if(arrTy == TypeSystem::intType)
                init_list.top()->addExpr($1);
            else
                while(arrTy)
                {
                    if(((ArrayType*)arrTy)->getElementType() != TypeSystem::intType)
                    {
                        arrTy = ((ArrayType*)arrTy)->getElementType();
                        SymbolEntry* se = new ConstantSymbolEntry(arrTy);
                        InitExpr* list = new InitExpr(se);
                        init_list.top()->addExpr(list);
                        init_list.push(list);
                    }
                    else
                    {
                        init_list.top()->addExpr($1);
                        while(init_list.top()->isFull() && init_list.size() != (long unsigned int)count)
                        {
                            arrTy = ((ArrayType*)arrTy)->getArrayType();
                            init_list.pop();
                        }
                        break;
                    }
                }
        }         
    }
    ;
ConstInitVal
    : ConstExp 
    {
        $$ = $1;
    }
    ;
FuncRParams 
    : Exp {$$ = $1;}
    | FuncRParams COMMA Exp {
        $$ = $1;
        $$->setNext($3);
    }
FuncDef
    :
    Type ID {
        identifiers = new SymbolTable(identifiers);
        param_num = 0;
    }
    LPAREN FuncFParams RPAREN 
    {
        Type* funcType;
        std::vector<Type*> vec;
        std::vector<SymbolEntry*> vec1;
        DeclStmt* temp = (DeclStmt*)$5;
        while(temp)
        {
            vec.push_back(temp->getId()->getSymbolEntry()->getType());
            vec1.push_back(temp->getId()->getSymbolEntry());
            temp = (DeclStmt*)(temp->getNext());
        }
        funcType = new FunctionType($1, vec, vec1);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, $2, identifiers->getPrev()->getLevel());
        if(!identifiers->getPrev()->install($2, se)){}
        $<se>$ = se; 
    } 
    BlockStmt {
        $$ = new FunctionDef($<se>7, (DeclStmt*)$5, $8);
        SymbolTable* top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
FuncFParams
    : FuncFParams COMMA FuncFParam {
        $$ = $1;
        $$->setNext($3);
    }
    | FuncFParam {
        $$ = $1;
    }
    | %empty {$$ = nullptr;}
    ;
FuncFParam
    : Type ID {
        SymbolEntry* se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel(), param_num++);
        identifiers->install($2, se);
        ((IdentifierSymbolEntry*)se)->setLabel();
        ((IdentifierSymbolEntry*)se)->setAddr(new Operand(se));
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    | Type ID Param_Arr 
    {
        SymbolEntry* se;
        ExprNode* temp = $3;
        Type* arr = TypeSystem::intType;
        Type* arr1;
        std::stack<ExprNode*> init_list;
        while(temp)
        {
            init_list.push(temp);
            temp = (ExprNode*)(temp->getNext());
        }
        while(!init_list.empty())
        {
            arr1 = new ArrayType(arr, init_list.top()->getValue());
            if(arr->isArray())
                ((ArrayType*)arr)->setArrayType(arr1);
            arr = arr1;
            init_list.pop();
        }
        se = new IdentifierSymbolEntry(arr, $2, identifiers->getLevel(), param_num++);
        identifiers->install($2, se);
        ((IdentifierSymbolEntry*)se)->setLabel();
        ((IdentifierSymbolEntry*)se)->setAddr(new Operand(se));
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    ;
Param_Arr 
    : LBRACKET RBRACKET 
    {
        $$ = new ExprNode(nullptr);
    }
    | Param_Arr LBRACKET Exp RBRACKET 
    {
        $$ = $1;
        $$->setNext($3);
    }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
