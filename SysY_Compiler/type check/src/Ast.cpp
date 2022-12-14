#include <iostream>
#include <string>
#include "Ast.h"
#include "SymbolTable.h"
#include "Type.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"

extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;
Type* returnType = nullptr;
bool funcReturned = false;
bool inIteration = false;//在迭代中

Node::Node()
{
    seq = counter++;
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

//lab6 added
void Node::backPatch(std::vector<Instruction*> &list, BasicBlock*bb)
{
    for(auto &inst:list)
    {
        if(inst->isCond())
            dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
        else if(inst->isUncond())
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2)
{
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::genCode()
{
    Unit *unit = builder->getUnit();
    Function *func = new Function(unit, se);
    BasicBlock *entry = func->getEntry();
    // set the insert point to the entry basicblock of this function.
    builder->setInsertBB(entry);

    stmt->genCode();

    /**
     * Construct control flow graph. You need do set successors and predecessors for each basic block.
     * Todo
    */
   
}

void BinaryExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();
    if (op == AND)
    {
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());
    }
    else if(op == OR)
    {
        // Todo
    }
    else if(op >= LESS && op <= GREAT)
    {
        // Todo
    }
    else if(op >= ADD && op <= SUB)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        int opcode;
        switch (op)
        {
        case ADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SUB:
            opcode = BinaryInstruction::SUB;
            break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    new LoadInstruction(dst, addr, bb);
}

void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode()
{
    // Todo
}

void CompoundStmt::genCode()
{
    // Todo
}

void SeqNode::genCode()
{
    // Todo
}

void DeclStmt::genCode()
{
    IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(id->getSymPtr());
    if(se->isGlobal())
    {
        Operand *addr;
        SymbolEntry *addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
    }
    else if(se->isLocal())
    {
        Function *func = builder->getInsertBB()->getParent();
        BasicBlock *entry = func->getEntry();
        Instruction *alloca;
        Operand *addr;
        SymbolEntry *addr_se;
        Type *type;
        type = new PointerType(se->getType());
        addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        addr = new Operand(addr_se);
        alloca = new AllocaInstruction(addr, se);                   // allocate space for local id in function stack.
        entry->insertFront(alloca);                                 // allocate instructions should be inserted into the begin of the entry block.
        se->setAddr(addr);                                          // set the addr operand in symbol entry so that we can use it in subsequent code generation.
    }
}

void ReturnStmt::genCode()
{
    // Todo
}

void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
    Operand *src = expr->getOperand();
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    new StoreInstruction(addr, src, bb);
}

void WhileStmt::genCode()
{
    // Todo
}

void FuncDefParamsNode::genCode()
{
    // Todo
}

void ContinueStmt::genCode()
{
    // Todo
}

void BreakStmt::genCode()
{
    // Todo
}

void InitValNode::genCode()
{
    // Todo
}

void DefNode::genCode()
{
    // Todo
}

void FuncCallParamsNode::genCode()
{
    // Todo
}

void FuncCallNode::genCode()
{
    // Todo
}

void ExprStmtNode::genCode()
{
    // Todo
}

void EmptyStmt::genCode()
{
    // Todo
}

void OneOpExpr::genCode()
{
    // Todo
}

void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
    //获取函数的返回值类型
    returnType = ((FunctionType*)se->getType())->getRetType();
    //判断函数是否返回
    funcReturned = false;
    stmt->typeCheck();
    if(!funcReturned && !returnType->isVoid())
    {
        fprintf(stderr, "expected a type to return, but no returned value found\n");
        exit(EXIT_FAILURE);
    }
    returnType = nullptr;
}

void BinaryExpr::typeCheck()
{
    expr1->typeCheck();
    expr2->typeCheck();
    //检查是否void函数返回值参与运算
    Type* realTypeLeft = expr1->getType()->isFunc() ? 
        ((FunctionType*)expr1->getType())->getRetType() : 
        expr1->getType();
    if(!realTypeLeft->calculatable()){
        fprintf(stderr, "type is not calculatable!\n");
        exit(EXIT_FAILURE);
    }
    Type* realTypeRight = expr2->getType()->isFunc() ? 
        ((FunctionType*)expr2->getType())->getRetType() : 
        expr2->getType();
    if(!realTypeRight->calculatable()){
        fprintf(stderr, "type is not calculatable!\n");
        exit(EXIT_FAILURE);
    }
    if(realTypeLeft != realTypeRight){
        fprintf(stderr, "type is not calculatable!\n");
        exit(EXIT_FAILURE);
    }
    symbolEntry -> setType(realTypeLeft);
}

void Constant::typeCheck()
{

}

void Id::typeCheck()
{
}

void IfStmt::typeCheck()
{
    cond->typeCheck();
    if(!cond->getSymPtr()->getType()->isBool())
    {
        fprintf(stderr, "Implicit conversion\n");
        exit(EXIT_FAILURE);
    }
    if(thenStmt!=nullptr)
    {
        thenStmt->typeCheck();

    }
    else
    {
        thenStmt=new EmptyStmt();
    }
}

void IfElseStmt::typeCheck()
{
    cond->typeCheck();    
    if(!cond->getSymPtr()->getType()->isBool())
    {
        fprintf(stderr, "Implicit conversion\n");
        exit(EXIT_FAILURE);
    }
    if(thenStmt!=nullptr)
    {
        thenStmt->typeCheck();

    }
    else
    {
        thenStmt=new EmptyStmt();
    }
    if(elseStmt!=nullptr)
    {
        elseStmt->typeCheck();

    }
    else
    {
        elseStmt=new EmptyStmt();
    }
}

void CompoundStmt::typeCheck()
{
    if(stmt!=nullptr){
        stmt->typeCheck();
    }
    else {
        stmt = new EmptyStmt();
    }
}

void SeqNode::typeCheck()
{
    for(int i = 0;i<(int)stmtList.size();++i){
        stmtList[i]->typeCheck();
    }
}

void DeclStmt::typeCheck()
{
    for(int i = 0;i<(int)defList.size();++i){
        defList[i]->typeCheck();
    }
}

void ReturnStmt::typeCheck()
{
    if(returnType == nullptr)
    {
        fprintf(stderr, "return statement outside functions\n");
        exit(EXIT_FAILURE);
    }
    else if(returnType->isVoid() && retValue!=nullptr)
    {
        fprintf(stderr, "value returned in a void() function\n");
        exit(EXIT_FAILURE);
    }
    else if(!returnType->isVoid() && retValue==nullptr)
    {
        fprintf(stderr, "expected a %s type to return, but returned nothing\n", returnType->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    if(!returnType->isVoid())
    {
        retValue->typeCheck();
    }
    
    funcReturned = true;
}

void AssignStmt::typeCheck()
{
    lval->typeCheck();
    expr->typeCheck();
    if(lval->getType()->isConst()) 
    {
        fprintf(stderr, "Unable to assign value to const variable %s\n", lval->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    if(expr->getType()->isFunc() && ((FunctionType*)(expr->getType()))->getRetType()->isVoid())
    {//返回值为void的函数做运算数
        fprintf(stderr, "expected a return value, but functionType %s returns nothing\n", expr->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
}

void FuncDefParamsNode::typeCheck(){}

void ContinueStmt::typeCheck()
{
    if(!inIteration){
        fprintf(stderr, "continue statement outside iterations\n");
        exit(EXIT_FAILURE);
    }
}

void BreakStmt::typeCheck()
{
    if(!inIteration){
        fprintf(stderr, "break statement outside iterations\n");
        exit(EXIT_FAILURE);
    }
}

void WhileStmt::typeCheck()
{
    cond->typeCheck();
    if(!cond->getSymPtr()->getType()->isBool())
    {
        fprintf(stderr, "Implicit conversion\n");
        exit(EXIT_FAILURE);
    }
    if(bodyStmt!=nullptr)
    {
        inIteration = true;
        bodyStmt->typeCheck();
        inIteration = false;
    }
    else
    {
        bodyStmt=new EmptyStmt();
    }
}

void InitValNode::typeCheck()
{
}

void DefNode::typeCheck()
{
    
}

void FuncCallParamsNode::typeCheck()
{
    // 对每一个孩子节点进行常量计算
    for(ExprNode* param : paramsList) {
        param->typeCheck();
    }
}

void FuncCallNode::typeCheck()
{
    // 先对FuncCallParamsNode进行类型检查，主要是完成常量计算
    this->params->typeCheck();
    // 然后进行类型匹配
    std::vector<Type*> funcParamsType = (dynamic_cast<FunctionType*>(this->funcId->getSymPtr()->getType()))->getParamsType();
    std::vector<ExprNode*> funcCallParams = this->params->getParamsList();
    // 如果数量不一致直接报错
    if(funcCallParams.size() != funcParamsType.size()) {
        fprintf(stderr, "function %s call params number is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    // 依次匹配类型
    for(int i = 0; i < funcParamsType.size(); i++){
        Type* needType = funcParamsType[i];
        Type* giveType = funcCallParams[i]->getSymPtr()->getType();
        if(!needType->calculatable() && giveType->calculatable()||needType->calculatable() && !giveType->calculatable()){
            fprintf(stderr, "function %s call params type is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
            exit(EXIT_FAILURE);
        }
    }
}

void ExprStmtNode::typeCheck()
{
    for(int i = 0;i<(int)exprList.size();++i){
        exprList[i]->typeCheck();
    }
}

void EmptyStmt::typeCheck(){}

void OneOpExpr::typeCheck()
{
    expr->typeCheck();
    //检查是否void函数返回值参与运算
    Type* realType = expr->getType()->isFunc() ? 
        ((FunctionType*)expr->getType())->getRetType() : 
        expr->getType();
    if(!realType->calculatable()){
        fprintf(stderr, "type %s is not calculatable!\n", expr->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
}

Type* ExprNode::getType()
{
    return symbolEntry->getType();
}

void ExprNode::setType(Type* type)
{
    symbolEntry->setType(type);
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case LESSEQ:
            op_str = "lesseq";
            break;
        case GREAT:
            op_str = "great";
            break;
        case GREATEQ:
            op_str = "greateq";
            break;
        case EQ:
            op_str = "eq";
            break;
        case NEQ:
            op_str = "neq";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\ttype: %s\n", level, ' ', op_str.c_str(), symbolEntry->getType()->toStr().c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void OneOpExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case NOT:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
    }
    fprintf(yyout, "%*cOneOpExpr\top: %s\ttype: %s\n", level, ' ', op_str.c_str(), symbolEntry->getType()->toStr().c_str());
    expr->output(level + 4);
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

bool Id::isArray()
{
    return getType()->isArray();
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    if(isArray() && indices!=nullptr){
        fprintf(yyout, "%*cArrayIndices\n", level+4, ' ');
        indices->output(level+8);
    }
}

void EmptyStmt::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
}

void ExprStmtNode::addNext(ExprNode* next)
{
    exprList.push_back(next);
}

void ExprStmtNode::output(int level)
{
    fprintf(yyout, "%*cExprStmtNode\n", level, ' ');
    for(auto expr : exprList)
    {
        expr->output(level+4);
    }
}

void ExprStmtNode::initDimInSymTable(IdentifierSymbolEntry* se)
{
    for(auto expr :exprList){
        // 既不是字面值常量，也不是常量表达式
        if(!(expr->getSymPtr()->isConstant() || expr->getType()->isConst())){
            fprintf(stderr, "array dimensions must be constant! %d %d\n", expr->getSymPtr()->isConstant(), expr->getType()->isConst());
            fprintf(stderr, "%d %d\n", (int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue(), (int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
            exit(EXIT_FAILURE);
        }
        // 字面值常量，值存在ConstantSymbolEntry中
        if(expr->getSymPtr()->isConstant()){
            se->arrayDimension.push_back((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
        }
        // 常量表达式，值存在IdentifierSymbolEntry中
        else if(expr->getType()->isConst()){
            se->arrayDimension.push_back((int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
        }
    }
}

void FuncCallNode::output(int level)
{
    std::string name, type;
    int scope;
    SymbolEntry* funcEntry = funcId->getSymbolEntry();
    name = funcEntry->toStr();
    type = funcEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(funcEntry)->getScope();
    fprintf(yyout, "%*cFuncCallNode\tfuncName: %s\t funcType: %s\tscope: %d\n", 
            level, ' ', name.c_str(), type.c_str(), scope);
    if(params!=nullptr){
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncCallParamsNode NULL\n", level+4, ' ');
    }
}

void FuncCallParamsNode::addNext(ExprNode* next)
{
    paramsList.push_back(next);
}

void FuncCallParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncCallParamsNode\n", level, ' ');
    for(auto param : paramsList){
        param->output(level+4);
    }
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if(stmt == nullptr){
        fprintf(yyout, "%*cNull Stmt\n", level+4, ' ');
    }
    else{
        stmt->output(level + 4);
    }
}

void SeqNode::addNext(StmtNode* next)
{
    stmtList.push_back(next);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    for(auto stmt : stmtList)
    {
        stmt->output(level + 4);
    }
}

void DeclStmt::addNext(DefNode* next)
{
    defList.push_back(next);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    for(auto def : defList){
        def->output(level+4);
    }
}

void DefNode::output(int level)
{
    std::string constStr = isConst ? "true" : "false";
    std::string arrayStr = isArray ? "true" : "false";
    fprintf(yyout, "%*cDefNode\tisConst:%s\tisArray:%s\n", level, ' ', constStr.c_str(), arrayStr.c_str());
    id->output(level+4);
    if(initVal == nullptr){
        fprintf(yyout, "%*cnull\n", level+4, ' ');
    }
    else{
        initVal->output(level+4);
    }
}

void InitValNode::addNext(InitValNode* next)
{
    innerList.push_back(next);
}

void InitValNode::output(int level)
{
    std::string constStr = isConst ? "true" : "false";
    fprintf(yyout, "%*cInitValNode\tisConst:%s\n", level, ' ', constStr.c_str());
    for(auto child : innerList)
    {
        child->output(level+4);
    }
    if(leafNode!=nullptr){
        leafNode->output(level+4);
    }
}

void InitValNode::setLeafNode(ExprNode* leaf)
{
    leafNode = leaf;
}

bool InitValNode::isLeaf()
{
    return innerList.empty();
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level+4);
    bodyStmt->output(level+4);
}

void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    if(retValue!=nullptr) retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FuncDefParamsNode::addNext(Id* next)
{
    paramsList.push_back(next);
}

std::vector<Type*> FuncDefParamsNode::getParamsType()
{
    std::vector<Type*> typeArray;
    for(auto param : paramsList){
        typeArray.push_back(param->getType());
    }
    return typeArray;
}

void FuncDefParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncDefParamsNode\n", level, ' ');
    for(auto param : paramsList){
        param->output(level+4);
    }
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(params!=nullptr){
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncDefParamsNode NULL\n", level+4, ' ');
    }
    stmt->output(level + 4);
}
