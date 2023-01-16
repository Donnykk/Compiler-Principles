#include "Instruction.h"
#include <iostream>
#include <sstream>
#include "BasicBlock.h"
#include "Function.h"
#include "Type.h"
extern FILE *yyout;

Instruction::Instruction(unsigned instType, BasicBlock *insert_bb)
{
    prev = next = this;
    opcode = -1;
    this->instType = instType;
    if (insert_bb != nullptr)
    {
        insert_bb->insertBack(this);
        parent = insert_bb;
    }
}

Instruction::~Instruction()
{
    parent->remove(this);
}

BasicBlock *Instruction::getParent()
{
    return parent;
}

void Instruction::setParent(BasicBlock *bb)
{
    parent = bb;
}

void Instruction::setNext(Instruction *inst)
{
    next = inst;
}

void Instruction::setPrev(Instruction *inst)
{
    prev = inst;
}

Instruction *Instruction::getNext()
{
    return next;
}

Instruction *Instruction::getPrev()
{
    return prev;
}

BinaryInstruction::BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb) : Instruction(BINARY, insert_bb)
{
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

BinaryInstruction::~BinaryInstruction() {}

void BinaryInstruction::output() const {}

CmpInstruction::CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb) : Instruction(CMP, insert_bb)
{
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

CmpInstruction::~CmpInstruction() {}

void CmpInstruction::output() const {}

UncondBrInstruction::UncondBrInstruction(BasicBlock *to, BasicBlock *insert_bb) : Instruction(UNCOND, insert_bb)
{
    branch = to;
}

void UncondBrInstruction::output() const {}

void UncondBrInstruction::setBranch(BasicBlock *bb)
{
    branch = bb;
}

BasicBlock *UncondBrInstruction::getBranch()
{
    return branch;
}

CondBrInstruction::CondBrInstruction(BasicBlock *true_branch, BasicBlock *false_branch, Operand *cond, BasicBlock *insert_bb) : Instruction(COND, insert_bb)
{
    this->true_branch = true_branch;
    this->false_branch = false_branch;
    cond->addUse(this);
    operands.push_back(cond);
}

CondBrInstruction::~CondBrInstruction() {}

void CondBrInstruction::output() const {}

void CondBrInstruction::setFalseBranch(BasicBlock *bb)
{
    false_branch = bb;
}

BasicBlock *CondBrInstruction::getFalseBranch()
{
    return false_branch;
}

void CondBrInstruction::setTrueBranch(BasicBlock *bb)
{
    true_branch = bb;
}

BasicBlock *CondBrInstruction::getTrueBranch()
{
    return true_branch;
}

RetInstruction::RetInstruction(Operand *src, BasicBlock *insert_bb) : Instruction(RET, insert_bb)
{
    if (src != nullptr)
    {
        operands.push_back(src);
        src->addUse(this);
    }
}

RetInstruction::~RetInstruction() {}

void RetInstruction::output() const {}

AllocaInstruction::AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb) : Instruction(ALLOCA, insert_bb)
{
    operands.push_back(dst);
    dst->setDef(this);
    this->se = se;
}

AllocaInstruction::~AllocaInstruction() {}

void AllocaInstruction::output() const {}

LoadInstruction::LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb) : Instruction(LOAD, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src_addr);
    dst->setDef(this);
    src_addr->addUse(this);
}

LoadInstruction::~LoadInstruction() {}

void LoadInstruction::output() const {}

StoreInstruction::StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb) : Instruction(STORE, insert_bb)
{
    operands.push_back(dst_addr);
    operands.push_back(src);
    dst_addr->addUse(this);
    src->addUse(this);
}

StoreInstruction::~StoreInstruction() {}

void StoreInstruction::output() const {}

MachineOperand *Instruction::genMachineReg(int reg)
{
    return new MachineOperand(MachineOperand::REG, reg);
}

MachineOperand *Instruction::genMachineVReg()
{
    return new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel());
}

MachineOperand *Instruction::genMachineImm(int val)
{
    return new MachineOperand(MachineOperand::IMM, val);
}

MachineOperand *Instruction::genMachineLabel(int block_no)
{
    std::ostringstream buf;
    buf << ".L" << block_no;
    std::string label = buf.str();
    return new MachineOperand(label);
}

void AllocaInstruction::genMachineCode(AsmBuilder *builder)
{
    /* HINT:
     * Allocate stack space for local variabel
     * Store frame offset in symbol entry */
    auto cur_func = builder->getFunction();
    int size = se->getType()->getSize() / 8;
    if (size < 0)
    {
        size = 4;
    }
    int offset = cur_func->AllocSpace(size);
    dynamic_cast<TemporarySymbolEntry *>(operands[0]->getEntry())->setOffset(-offset);
}

void StoreInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    MachineInstruction *current_inst = nullptr;
    MachineOperand *dst = genMachineOperand(operands[0]);
    MachineOperand *src = genMachineOperand(operands[1]);
    auto t = dynamic_cast<IdentifierSymbolEntry *>(operands[0]->getEntry());
    if (operands[1]->getEntry()->isConstant())
    {
        MachineOperand *temp = genMachineVReg();
        current_inst = new LoadMInstruction(current_block, temp, src);
        current_block->InsertInst(current_inst);
        src = new MachineOperand(*temp);
    }
    if (operands[0]->getEntry()->isTemporary() && operands[0]->getDef() && operands[0]->getDef()->isAlloc())
    {
        MachineOperand *temp = genMachineReg(11);
        current_inst = new StoreMInstruction(current_block, src, temp, genMachineImm(dynamic_cast<TemporarySymbolEntry *>(operands[0]->getEntry())->getOffset()));
        current_block->InsertInst(current_inst);
    }
    else if (operands[0]->getEntry()->isVariable() && t->isGlobal())
    {
        MachineOperand *temp = genMachineVReg();
        current_block->InsertInst(new LoadMInstruction(current_block, temp, dst));
        current_block->InsertInst(new StoreMInstruction(current_block, src, temp));
    }
    else if (operands[0]->getType()->isPtr())
    {
        current_inst = new StoreMInstruction(current_block, src, dst);
        current_block->InsertInst(current_inst);
    }
}

void CmpInstruction::genMachineCode(AsmBuilder *builder)
{
    MachineBlock *current_block = builder->getBlock();
    MachineOperand *src1 = genMachineOperand(operands[1]);
    MachineOperand *src2 = genMachineOperand(operands[2]);
    MachineInstruction *current_inst = nullptr;
    if (src1->isImm())
    {
        MachineOperand *temp_reg = genMachineVReg();
        current_inst = new LoadMInstruction(current_block, temp_reg, src1);
        current_block->InsertInst(current_inst);
        src1 = new MachineOperand(*temp_reg);
    }
    if (src2->isImm())
    {
        MachineOperand *temp_reg = genMachineVReg();
        current_inst = new LoadMInstruction(current_block, temp_reg, src2);
        current_block->InsertInst(current_inst);
        src2 = new MachineOperand(*temp_reg);
    }
    current_block->InsertInst(new CmpMInstruction(current_block, src1, src2, opcode));
    if (opcode >= 2 && opcode <= 5)
    {
        current_block->InsertInst(new MovMInstruction(current_block, MovMInstruction::MOV, genMachineOperand(operands[0]), genMachineImm(1), opcode));
        current_block->InsertInst(new MovMInstruction(current_block, MovMInstruction::MOV, genMachineOperand(operands[0]), genMachineImm(0), 7 - opcode));
    }
}

void LoadInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    MachineInstruction *current_inst = nullptr;
    // 加载一个全局变量或者常量
    if (operands[1]->getEntry()->isVariable() && dynamic_cast<IdentifierSymbolEntry *>(operands[1]->getEntry())->isGlobal())
    {
        // 生成两条加载指令
        // 全局的地址标签中将其地址加载到寄存器中
        // 之后再从该地址中加载出其实际的值
        auto dst = genMachineOperand(operands[0]);
        auto internal_reg1 = genMachineVReg();
        auto internal_reg2 = new MachineOperand(*internal_reg1);
        auto src = genMachineOperand(operands[1]);
        current_inst = new LoadMInstruction(current_block, internal_reg1, src);
        current_block->InsertInst(current_inst);
        current_inst = new LoadMInstruction(current_block, dst, internal_reg2);
        current_block->InsertInst(current_inst);
    }
    // 加载一个栈中的临时变量
    else if (operands[1]->getEntry()->isTemporary() && operands[1]->getDef() && operands[1]->getDef()->isAlloc())
    {
        auto dst = genMachineOperand(operands[0]);
        auto src1 = genMachineReg(11);
        auto src2 = genMachineImm(dynamic_cast<TemporarySymbolEntry *>(operands[1]->getEntry())->getOffset());
        current_inst = new LoadMInstruction(current_block, dst, src1, src2);
        current_block->InsertInst(current_inst);
    }
    // 加载一个数组元素
    else
    {
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        current_inst = new LoadMInstruction(current_block, dst, src);
        current_block->InsertInst(current_inst);
    }
}

void UncondBrInstruction::genMachineCode(AsmBuilder *builder)
{
    // 生成一条无条件跳转指令即可
    MachineBlock *current_block = builder->getBlock();
    std::string temp = ".L" + std::to_string(branch->getNo());
    current_block->InsertInst(new BranchMInstruction(current_block, BranchMInstruction::B, new MachineOperand(temp)));
}

void CondBrInstruction::genMachineCode(AsmBuilder *builder)
{
    // 指令位于 CmpInstruction 之后
    // 首先需要在 AsmBuilder 中添加成员以记录前一条 CmpInstruction 的条件码
    MachineBlock *current_block = builder->getBlock();
    std::string temp = ".L" + std::to_string(true_branch->getNo());
    BranchMInstruction *current_inst = new BranchMInstruction(current_block, BranchMInstruction::B, new MachineOperand(temp), current_block->getCmpNo());
    current_block->InsertInst(current_inst);
    // 之后生成一条无条件跳转指令
    temp = ".L" + std::to_string(false_branch->getNo());
    current_inst = new BranchMInstruction(current_block, BranchMInstruction::B, new MachineOperand(temp));
    current_block->InsertInst(current_inst);
}

void RetInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    if (!operands.empty())
    {
        // 当函数有返回值时，我们需要生成 MOV 指令，将返回值保存在 R0 寄存器中
        auto *temp = new MovMInstruction(current_block, MovMInstruction::MOV, new MachineOperand(MachineOperand::REG, 0), genMachineOperand(operands[0]));
        current_block->InsertInst(temp);
    }
    // 释放栈空间，恢复保存的寄存器
    MachineOperand *sp = new MachineOperand(MachineOperand::REG, 13);
    MachineOperand *size = new MachineOperand(MachineOperand::IMM, builder->getFunction()->AllocSpace(0));
    // 生成 ADD 指令来恢复栈帧
    current_block->InsertInst(new BinaryMInstruction(current_block, BinaryMInstruction::ADD, sp, sp, size));
    MachineOperand *lr = new MachineOperand(MachineOperand::REG, 14);
    // 最后再生成跳转指令来返回到 Caller
    current_block->InsertInst(new BranchMInstruction(current_block, BranchMInstruction::BX, lr));
}

FuncCallInstruction::FuncCallInstruction(Operand *dst, SymbolEntry *func, std::vector<Operand *> params, BasicBlock *insert_bb) : Instruction(CALL, insert_bb), func(func), dst(dst)
{
    operands.push_back(dst);
    if (dst)
        dst->setDef(this);
    for (long unsigned int i = 0; i < params.size(); i++)
    {
        operands.push_back(params[i]);
        params[i]->addUse(this);
    }
}

void FuncCallInstruction::output() const {}

FuncCallInstruction::~FuncCallInstruction() {}

ZextInstruction::ZextInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb) : Instruction(ZEXT, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}

void ZextInstruction::output() const {}

ZextInstruction::~ZextInstruction() {}

XorInstruction::XorInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb) : Instruction(XOR, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}

void XorInstruction::output() const {}

XorInstruction::~XorInstruction() {}

GepInstruction::GepInstruction(Operand *dst, Operand *arr, Operand *index, BasicBlock *insert_bb, bool paramFirst) : Instruction(GEP, insert_bb), paramFirst(paramFirst)
{
    operands.push_back(dst);
    operands.push_back(arr);
    operands.push_back(index);
    dst->setDef(this);
    arr->addUse(this);
    index->addUse(this);
    first = false;
    init = nullptr;
    last = false;
}

void GepInstruction::output() const {}

GepInstruction::~GepInstruction() {}

void FuncCallInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    MachineOperand *operand;
    MachineInstruction *current_inst;
    int index = 0;
    long unsigned int i = 1;
    // 对于含参函数，需要使用 R0-R3 寄存器传递参数
    while (i != operands.size())
    {
        if (index == 4)
            break;
        if (genMachineOperand(operands[index + 1])->isImm())
            current_block->InsertInst(new LoadMInstruction(current_block, genMachineReg(index), genMachineOperand(operands[index + 1])));
        else
            current_block->InsertInst(new MovMInstruction(current_block, MovMInstruction::MOV, genMachineReg(index), genMachineOperand(operands[index + 1])));
        index++;
        i++;
    }
    // 如果参数个数大于四个还需要生成 PUSH 指令来传递参数
    for (int i = operands.size() - 1; i > 4; i--)
    {
        operand = genMachineOperand(operands[i]);
        if (operand->isImm())
        {
            current_inst = new LoadMInstruction(current_block, genMachineVReg(), operand);
            current_block->InsertInst(current_inst);
            operand = genMachineVReg();
        }
        std::vector<MachineOperand *> temp;
        current_block->InsertInst(new StackMInstrcuton(current_block, StackMInstrcuton::PUSH, temp, operand));
    }
    // 之后生成跳转指令来进入 Callee 函数
    current_inst = new BranchMInstruction(current_block, BranchMInstruction::BL, new MachineOperand(func->toStr().c_str()));
    current_block->InsertInst(current_inst);
    // 在此之后，需要进行现场恢复的工作，如果之前通过压栈的方式传递了参数，需要恢复 SP 寄存器；最后，如果函数执行结果被用到，还需要保存 R0 寄存器中的返回值。
    if (operands.size() > 5)
    {
        MachineOperand *sp = new MachineOperand(MachineOperand::REG, 13);
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::ADD, sp, sp, genMachineImm((operands.size() - 5) * 4));
        current_block->InsertInst(current_inst);
    }
    if (dst)
    {
        // 有返回值
        current_inst = new MovMInstruction(current_block, MovMInstruction::MOV, genMachineOperand(dst), new MachineOperand(MachineOperand::REG, 0));
        current_block->InsertInst(current_inst);
    }
}

void BinaryInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    MachineInstruction *current_inst = nullptr;
    // 参数类型转换
    if (src1->isImm())
    {
        // 如果存在立即数需要将立即数载入寄存器中才能合理运行代码
        auto temp_reg = genMachineVReg();
        current_inst = new LoadMInstruction(current_block, temp_reg, src1);
        current_block->InsertInst(current_inst);
        // 重新将 src1 进行赋值
        src1 = new MachineOperand(*temp_reg);
    }
    if (src2->isImm())
    {
        auto temp_reg = genMachineVReg();
        current_inst = new LoadMInstruction(current_block, temp_reg, src2);
        current_block->InsertInst(current_inst);
        src2 = new MachineOperand(*temp_reg);
    }
    switch (opcode)
    {
    case ADD:
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::ADD, dst, src1, src2);
        break;
    case SUB:
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::SUB, dst, src1, src2);
        break;
    case AND:
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::AND, dst, src1, src2);
        break;
    case OR:
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::OR, dst, src1, src2);
        break;
    case MUL:
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::MUL, dst, src1, src2);
        break;
    case DIV:
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::DIV, dst, src1, src2);
        break;
    case MOD:
    {
        // 正在翻译的机器代码块，指令类型，dst 值，两个源操作数
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::DIV, dst, src1, src2);
        MachineOperand *temp = new MachineOperand(*dst);
        current_block->InsertInst(current_inst);
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::MUL, temp, dst, new MachineOperand(*src2));
        current_block->InsertInst(current_inst);
        dst = new MachineOperand(*temp);
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::SUB, dst, new MachineOperand(*src1), temp);
        break;
    }
    default:
        break;
    }
    current_block->InsertInst(current_inst);
}

MachineOperand *Instruction::genMachineOperand(Operand *ope)
{
    auto se = ope->getEntry();
    MachineOperand *mope = nullptr;
    if (se->isConstant())
        mope = new MachineOperand(MachineOperand::IMM, dynamic_cast<ConstantSymbolEntry *>(se)->getValue());
    else if (se->isTemporary())
        mope = new MachineOperand(MachineOperand::VREG, dynamic_cast<TemporarySymbolEntry *>(se)->getLabel());
    else if (se->isVariable())
    {
        auto id_se = dynamic_cast<IdentifierSymbolEntry *>(se);
        if (id_se->isGlobal())
            mope = new MachineOperand(id_se->toStr().c_str());
        else if (id_se->isParam())
        {
            if (id_se->getParamNo() < 4)
            {
                int temp = id_se->getParamNo();
                mope = new MachineOperand(MachineOperand::REG, temp);
            }
            else
                mope = new MachineOperand(MachineOperand::REG, 3);
        }
    }
    return mope;
}

void ZextInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src = genMachineOperand(operands[1]);
    auto current_inst = new MovMInstruction(current_block, MovMInstruction::MOV, dst, src);
    current_block->InsertInst(current_inst);
}

void XorInstruction::genMachineCode(AsmBuilder *builder)
{
    MachineBlock *current_block = builder->getBlock();
    MovMInstruction *current_inst = new MovMInstruction(current_block, MovMInstruction::MOV, genMachineOperand(operands[0]), genMachineImm(1), MachineInstruction::EQ);
    current_block->InsertInst(current_inst);
    current_inst = new MovMInstruction(current_block, MovMInstruction::MOV, genMachineOperand(operands[0]), genMachineImm(0), MachineInstruction::NE);
    current_block->InsertInst(current_inst);
}

void GepInstruction::genMachineCode(AsmBuilder *builder)
{
    auto current_block = builder->getBlock();
    MachineInstruction *current_inst;
    // 分别获取目的操作数和数组下标操作数
    auto dst = genMachineOperand(operands[0]);
    auto index = genMachineOperand(operands[2]);
    MachineOperand *base = nullptr;
    int size;
    auto idx1 = genMachineVReg();
    if (index->isImm())
    {
        // 下标为立即数则load到虚拟寄存器内
        current_inst = new LoadMInstruction(current_block, idx1, index);
        index = new MachineOperand(*idx1);
        current_block->InsertInst(current_inst);
    }
    if (!paramFirst)
    {
        // Load基地址
        if (first)
        {
            base = genMachineVReg();
            if (operands[1]->getEntry()->isVariable() && ((IdentifierSymbolEntry *)(operands[1]->getEntry()))->isGlobal())
            {
                auto src = genMachineOperand(operands[1]);
                current_inst = new LoadMInstruction(current_block, base, src);
            }
            else
            {
                int offset = ((TemporarySymbolEntry *)(operands[1]->getEntry()))->getOffset();
                current_inst = new LoadMInstruction(current_block, base, genMachineImm(offset));
            }
            current_block->InsertInst(current_inst);
        }
        ArrayType *type = (ArrayType *)(((PointerType *)(operands[1]->getType()))->getType());
        size = type->getElementType()->getSize() / 8;
    }
    else
        size = ((PointerType *)(operands[1]->getType()))->getType()->getSize() / 8;
    // load 大小至寄存器
    auto size1 = genMachineVReg();
    current_inst = new LoadMInstruction(current_block, size1, genMachineImm(size));
    current_block->InsertInst(current_inst);
    // load 偏移量至寄存器
    auto off = genMachineVReg();
    current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::MUL, off, index, size1);
    off = new MachineOperand(*off);
    current_block->InsertInst(current_inst);
    if (paramFirst || !first)
    {
        auto arr = genMachineOperand(operands[1]);
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::ADD, dst, arr, off);
        current_block->InsertInst(current_inst);
    }
    else
    {
        auto addr = genMachineVReg();
        auto base1 = new MachineOperand(*base);
        current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::ADD, addr, base1, off);
        current_block->InsertInst(current_inst);
        addr = new MachineOperand(*addr);
        if (operands[1]->getEntry()->isVariable() && ((IdentifierSymbolEntry *)(operands[1]->getEntry()))->isGlobal())
            current_inst = new MovMInstruction(current_block, MovMInstruction::MOV, dst, addr);
        else
        {
            auto fp = genMachineReg(11);
            current_inst = new BinaryMInstruction(current_block, BinaryMInstruction::ADD, dst, fp, addr);
        }
        current_block->InsertInst(current_inst);
    }
}
