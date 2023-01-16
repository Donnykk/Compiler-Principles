#include "Ast.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include <string>
#include "Type.h"

extern FILE *yyout;
int Node::num = 0;
IRBuilder *Node::builder = nullptr;

Node::Node()
{
    seq = num++;
}

void Node::backPatchTrue(std::vector<Instruction *> &list, BasicBlock *bb)
{
    for (auto &inst : list)
    {
        if (inst->isCond())
        {
            bb->addPred(dynamic_cast<CondBrInstruction *>(inst)->getParent());
            dynamic_cast<CondBrInstruction *>(inst)->getParent()->addSucc(bb);
            dynamic_cast<CondBrInstruction *>(inst)->setTrueBranch(bb);
        }
        else if (inst->isUncond())
        {
            bb->addPred(dynamic_cast<CondBrInstruction *>(inst)->getParent());
            dynamic_cast<CondBrInstruction *>(inst)->getParent()->addSucc(bb);
            dynamic_cast<UncondBrInstruction *>(inst)->setBranch(bb);
        }
    }
}

void Node::backPatchFalse(std::vector<Instruction *> &list, BasicBlock *bb)
{
    for (auto &inst : list)
    {
        if (inst->isCond())
        {
            bb->addPred(dynamic_cast<CondBrInstruction *>(inst)->getParent());
            dynamic_cast<CondBrInstruction *>(inst)->getParent()->addSucc(bb);
            dynamic_cast<CondBrInstruction *>(inst)->setFalseBranch(bb);
        }
        else if (inst->isUncond())
        {
            bb->addPred(dynamic_cast<CondBrInstruction *>(inst)->getParent());
            dynamic_cast<CondBrInstruction *>(inst)->getParent()->addSucc(bb);
            dynamic_cast<UncondBrInstruction *>(inst)->setBranch(bb);
        }
    }
}

std::vector<Instruction *> Node::merge(std::vector<Instruction *> &list1, std::vector<Instruction *> &list2)
{
    std::vector<Instruction *> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    fprintf(yyout, "declare i32 @getint()\ndeclare void @putint(i32)\ndeclare i32 @getch()\ndeclare void @putch(i32)\n");
    root->genCode();
}

void BinaryExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();
    if (isCal())
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
        case MUL:
            opcode = BinaryInstruction::MUL;
            break;
        case DIV:
            opcode = BinaryInstruction::DIV;
            break;
        case MOD:
            opcode = BinaryInstruction::MOD;
            break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
    else if (isRel())
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        int opcode;
        switch (op)
        {
        case GREAT:
            opcode = CmpInstruction::G;
            break;
        case GREATEQ:
            opcode = CmpInstruction::GE;
            break;
        case LESS:
            opcode = CmpInstruction::L;
            break;
        case LESSEQ:
            opcode = CmpInstruction::LE;
            break;
        case EQ:
            opcode = CmpInstruction::E;
            break;
        case NEQ:
            opcode = CmpInstruction::NE;
            break;
        default:
            break;
        }
        new CmpInstruction(opcode, dst, src1, src2, bb);
        true_list = merge(expr1->trueList(), expr2->trueList());
        false_list = merge(expr1->falseList(), expr2->falseList());
        Instruction *temp = new CondBrInstruction(nullptr, nullptr, dst, bb);
        this->trueList().push_back(temp);
        this->falseList().push_back(temp);
    }
    else
    {
        if (op == AND)
        {
            BasicBlock *trueBB = new BasicBlock(func);
            expr1->genCode();
            backPatchTrue(expr1->trueList(), trueBB);
            builder->setInsertBB(trueBB);
            expr2->genCode();
            true_list = expr2->trueList();
            false_list = merge(expr1->falseList(), expr2->falseList());
        }
        else if (op == OR)
        {
            BasicBlock *falseBB = new BasicBlock(func);
            expr1->genCode();
            backPatchFalse(expr1->falseList(), falseBB);
            builder->setInsertBB(falseBB);
            expr2->genCode();
            false_list = expr2->falseList();
            true_list = merge(expr1->trueList(), expr2->trueList());
        }
    }
}

void Constant::genCode()
{
}

void Id::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry *>(symbolEntry)->getAddr();
    new LoadInstruction(dst, addr, bb);
}

void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    then_bb->addPred(builder->getInsertBB());
    builder->getInsertBB()->addSucc(then_bb);
    end_bb->addPred(then_bb);
    then_bb->addSucc(end_bb);
    end_bb->addPred(builder->getInsertBB());
    builder->getInsertBB()->addSucc(end_bb);

    cond->genCode();
    backPatchTrue(cond->trueList(), then_bb);
    backPatchFalse(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *else_bb, *end_bb;
    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);
    else_bb = new BasicBlock(func);

    then_bb->addPred(builder->getInsertBB());
    builder->getInsertBB()->addSucc(then_bb);
    else_bb->addPred(builder->getInsertBB());
    builder->getInsertBB()->addSucc(else_bb);
    end_bb->addPred(then_bb);
    then_bb->addSucc(end_bb);
    end_bb->addPred(else_bb);
    else_bb->addSucc(end_bb);

    cond->genCode();
    backPatchTrue(cond->trueList(), then_bb);
    backPatchFalse(cond->falseList(), else_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(else_bb);
    elseStmt->genCode();
    else_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, else_bb);

    builder->setInsertBB(end_bb);
}

void WhileStmt::genCode()
{
    Function *func;
    BasicBlock *loop_bb, *end_bb, *cond_bb;

    func = builder->getInsertBB()->getParent();
    loop_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);
    cond_bb = new BasicBlock(func);
    new UncondBrInstruction(cond_bb, builder->getInsertBB());

    cond_bb->addPred(builder->getInsertBB());
    builder->getInsertBB()->addSucc(cond_bb);
    loop_bb->addPred(cond_bb);
    cond_bb->addSucc(loop_bb);
    end_bb->addPred(loop_bb);
    loop_bb->addSucc(end_bb);
    end_bb->addPred(cond_bb);
    cond_bb->addSucc(end_bb);
    builder->setInsertBB(cond_bb);

    cond->genCode();
    backPatchTrue(cond->trueList(), loop_bb);
    backPatchFalse(cond->falseList(), end_bb);
    builder->setInsertBB(loop_bb);

    loop->genCode();
    loop_bb = builder->getInsertBB();
    new CondBrInstruction(cond_bb, end_bb, cond->getOperand(), loop_bb);

    builder->setInsertBB(end_bb);
}

void CompoundStmt::genCode()
{
    stmt->genCode();
}

void SeqNode::genCode()
{
    stmt1->genCode();
    stmt2->genCode();
}

void ReturnStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    retValue->genCode();
    Operand *src = retValue->getOperand();
    new RetInstruction(src, bb);
}

void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry *>(lval->getSymPtr())->getAddr();
    Operand *src = expr->getOperand();
    new StoreInstruction(addr, src, bb);
}

void OneStmt::genCode()
{
    expr->genCode();
}

void Empty::genCode()
{
}

void ConstIdList::genCode()
{
}

void IdList::genCode()
{
}

// 变量声明语句
void DeclStmt::genCode()
{
    for (auto iter = ids->ids.rbegin(); iter != ids->ids.rend(); iter++)
    {
        IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>((*iter)->getSymPtr());
        if (se->isGlobal())
        {
            // 全局变量声明
            SymbolEntry *addr_se = new IdentifierSymbolEntry(*se);
            Operand *addr = new Operand(addr_se);
            addr_se->setType(new PointerType(se->getType()));
            se->setAddr(addr);
            Operand *src;
            int i = 0;
            while (i < (int)ids->value.size() && ids->value[i]->lval->symbolEntry != se)
                i++;
            if (i < (int)ids->value.size())
            {
                // 翻译赋值语句
                ids->value[i]->genCode();
                src = ids->value[i]->expr->getOperand();
                Instruction *alloca = new AllocaInitInstruction(src, addr, se);
                alloca->output();
            }
            else
            {
                // 未赋值的全局变量初始化为0
                SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
                Constant *digit = new Constant(se);
                src = digit->getOperand();
                Instruction *alloca = new AllocaInitInstruction(src, addr, se);
                alloca->output();
            }
        }
        else if (se->isLocal())
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
            alloca = new AllocaInstruction(addr, se); // allocate space for local id in function stack.
            entry->insertFront(alloca);               // allocate instructions should be inserted into the begin of the entry block.
            se->setAddr(addr);                        // set the addr operand in symbol entry so that we can use it in subsequent code generation.
        }
    }
    for (int i = 0; i < (int)ids->value.size(); i++)
    {
        IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(ids->value[i]->lval->getSymPtr());
        if (se->isGlobal())
            continue;
        else if (se->isLocal())
        {
            Operand *addr = dynamic_cast<IdentifierSymbolEntry *>(ids->value[i]->lval->getSymPtr())->getAddr();
            se->setAddr(addr);
            ids->value[i]->genCode();
        }
    }
}

// 常量声明语句
void ConstDeclStmt::genCode()
{
    for (int i = 0; i < (int)const_ids->const_ids.size(); i++)
    {
        IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(const_ids->const_ids[i]->getSymPtr());
        if (se->isGlobal())
        {
            Operand *addr;
            SymbolEntry *addr_se;
            addr_se = new IdentifierSymbolEntry(*se);
            addr_se->setType(new PointerType(se->getType()));
            addr = new Operand(addr_se);
            se->setAddr(addr);
            const_ids->value[i]->genCode();
            Operand *src = const_ids->value[i]->expr->getOperand();
            Instruction *alloca = new AllocaInitInstruction(src, addr, se);
            alloca->output();
        }
        else if (se->isLocal())
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
            alloca = new AllocaInstruction(addr, se); // allocate space for local id in function stack.
            entry->insertFront(alloca);               // allocate instructions should be inserted into the begin of the entry block.
            se->setAddr(addr);

            const_ids->value[i]->expr->genCode();
            // 从符号表获取存储常量的地址
            Operand *const_addr = dynamic_cast<IdentifierSymbolEntry *>(const_ids->value[i]->lval->getSymPtr())->getAddr();
            se->setAddr(const_addr);
            // 赋值操作数
            Operand *src = const_ids->value[i]->expr->getOperand();
            BasicBlock *bb = builder->getInsertBB();
            new StoreInstruction(const_addr, src, bb); // set the addr operand in symbol entry so that we can use it in subsequent code generation.
        }
    }
}

void ContinueStmt::genCode()
{
}

void BreakStmt::genCode()
{
}

void ConstId::genCode()
{
}

void OneExpr::genCode()
{
    // TODO:实现 !
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *src = expr->getOperand();
    if (src->getType()->isBool())
    {
        Operand *t = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
        new ZextInstruction(t, expr->dst, bb);
        expr->dst = t;
        src = t;
    }
    int opcode;
    switch (op)
    {
    case ADD:
        opcode = BinaryInstruction::ADD;
        break;
    case SUB:
        opcode = BinaryInstruction::SUB;
        break;
    default:
        break;
    }
    SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
    Constant *digit = new Constant(se);
    new BinaryInstruction(opcode, dst, digit->getOperand(), src, bb);
    isCond = expr->isCond;
}

void Ast::typeCheck()
{
    if (root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
}

void BinaryExpr::typeCheck()
{
}

void Constant::typeCheck()
{
}

void Id::typeCheck()
{
}

void IfStmt::typeCheck()
{
}

void IfElseStmt::typeCheck()
{
}

void CompoundStmt::typeCheck()
{
}

void SeqNode::typeCheck()
{
}

void DeclStmt::typeCheck()
{
}

void ReturnStmt::typeCheck()
{
}

void AssignStmt::typeCheck()
{
}

void OneStmt::typeCheck()
{
}

void FuncRParams::typeCheck()
{
}

void Empty::typeCheck()
{
}

void FuncFParam::typeCheck()
{
}

void FuncFParams::typeCheck()
{
}

void ConstIdList::typeCheck()
{
}

void IdList::typeCheck()
{
}

void WhileStmt::typeCheck()
{
}

void FunctionCall::typeCheck()
{
}

void ConstDeclStmt::typeCheck()
{
}

void ContinueStmt::typeCheck()
{
}

void BreakStmt::typeCheck()
{
}

void ConstId::typeCheck()
{
}

void OneExpr::typeCheck()
{
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if (root != nullptr)
        root->output(4);
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch (op)
    {
    case ADD:
        op_str = "add";
        break;
    case SUB:
        op_str = "sub";
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
    case GREAT:
        op_str = "great";
        break;
    case LESSEQ:
        op_str = "lesseq";
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
    case DIV:
        op_str = "div";
        break;
    case MUL:
        op_str = "mul";
        break;
    case MOD:
        op_str = "mod";
        break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void OneExpr::output(int level)
{
    std::string op_str;
    switch (op)
    {
    case SUB:
        op_str = "negative";
        break;
    case ADD:
        op_str = "positive";
        break;
    case EXCLAMATION:
        op_str = "anti";
        break;
    }
    fprintf(yyout, "%*cOneExpr\top: %s\n", level, ' ', op_str.c_str());
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

void ConstId::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry *>(symbolEntry)->getScope();
    fprintf(yyout, "%*cConstId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry *>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
}

void FuncFParam::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry *>(symbolEntry)->getScope();
    fprintf(yyout, "%*cFuncFParam\tname:%s\tscope:%d\ttype:%s\n", level, ' ',
            name.c_str(), scope, type.c_str());
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    ids->output(level + 4);
}

void ConstDeclStmt::output(int level)
{
    fprintf(yyout, "%*cConstDeclStmt\n", level, ' ');
    const_ids->output(level + 4);
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

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ',
            name.c_str(), type.c_str());
    if (params != nullptr)
    {
        params->output(level + 4);
    }
    stmt->output(level + 4);
}

void FunctionCall::output(int level)
{
    std::string name, type;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    fprintf(yyout, "%*cFuncCall\tname: %s\ttype: %s\n", level, ' ',
            name.c_str(), type.c_str());
    if (params != nullptr)
    {
        params->output(level + 4);
    }
}

void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    loop->output(level + 4);
}

void IdList::output(int level)
{
    fprintf(yyout, "%*cIdList\n", level, ' ');
    for (int i = 0; i < (int)ids.size(); i++)
        ids[i]->output(level + 4);
    for (int i = 0; i < (int)value.size(); i++)
        value[i]->output(level + 4);
}
void ConstIdList::output(int level)
{
    fprintf(yyout, "%*cConstIdList\n", level, ' ');
    for (int i = 0; i < (int)const_ids.size(); i++)
    {
        const_ids[i]->output(level + 4);
        value[i]->output(level + 4);
    }
}

void FuncFParams::output(int level)
{
    fprintf(yyout, "%*cFuncFParams\n", level, ' ');
    for (int i = 0; i < (int)params.size(); i++)
    {
        params[i]->output(level + 4);
    }
    for (int i = 0; i < (int)value.size(); i++)
    {
        value[i]->output(level + 4);
    }
}

void FuncRParams::output(int level)
{
    fprintf(yyout, "%*cFuncRParams\n", level, ' ');
    for (int i = 0; i < (int)expr.size(); i++)
    {
        expr[i]->output(level + 4);
    }
}

void Empty::output(int level)
{
    fprintf(yyout, "%*cEmpty Statement\n", level, ' ');
}

void OneStmt::output(int level)
{
    fprintf(yyout, "%*cOne Statement\n", level, ' ');
    expr->output(level + 4);
}