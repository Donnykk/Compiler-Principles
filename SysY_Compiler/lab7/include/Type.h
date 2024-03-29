#ifndef __TYPE_H__
#define __TYPE_H__
#include <string>
#include <vector>
#include "SymbolTable.h"

class Type
{
private:
    int kind;

protected:
    enum
    {
        INT,
        VOID,
        FUNC,
        PTR,
        ARRAY
    };
    int size;

public:
    Type(int kind, int size = 0) : kind(kind), size(size){};
    virtual ~Type(){};
    virtual std::string toStr() = 0;
    bool isInt() const { return kind == INT; };
    bool isVoid() const { return kind == VOID; };
    bool isFunc() const { return kind == FUNC; };
    bool isPtr() const { return kind == PTR; };
    bool isArray() const { return kind == ARRAY; };
    int getKind() const { return kind; };
    int getSize() const { return size; };
};

class IntType : public Type
{
private:
    bool constant;

public:
    IntType(int size, bool constant = false)
        : Type(Type::INT, size), constant(constant){};
    std::string toStr();
    bool isConst() const { return constant; };
};

class VoidType : public Type
{
public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

class FunctionType : public Type
{
private:
    Type *type_return;
    std::vector<Type *> type_param;
    std::vector<SymbolEntry *> params;

public:
    FunctionType(Type *type_return,
                 std::vector<Type *> type_param,
                 std::vector<SymbolEntry *> params)
        : Type(Type::FUNC),
          type_return(type_return),
          type_param(type_param),
          params(params){};
    void setParamsType(std::vector<Type *> type_param)
    {
        this->type_param = type_param;
    };
    std::vector<Type *> getParamsType() { return type_param; };
    std::vector<SymbolEntry *> getParamsSe() { return params; };
    Type *getRetType() { return type_return; };
    std::string toStr();
};

class ArrayType : public Type
{
private:
    Type *elementType;
    Type *arrayType = nullptr;
    int length;
    bool constant;

public:
    ArrayType(Type *elementType, int length, bool constant = false)
        : Type(Type::ARRAY),
          elementType(elementType),
          length(length),
          constant(constant)
    {
        size = elementType->getSize() * length;
    };
    std::string toStr();
    int getLength() const { return length; };
    Type *getElementType() const { return elementType; };
    void setArrayType(Type *arrayType) { this->arrayType = arrayType; };
    bool isConst() const { return constant; };
    Type *getArrayType() const { return arrayType; };
};

class PointerType : public Type
{
private:
    Type *valueType;

public:
    PointerType(Type *valueType) : Type(Type::PTR)
    {
        this->valueType = valueType;
    };
    std::string toStr();
    Type *getType() const { return valueType; };
};

class TypeSystem
{
private:
    static IntType commonInt;
    static IntType commonBool;
    static VoidType commonVoid;
    static IntType commonConstInt;

public:
    static Type *intType;
    static Type *voidType;
    static Type *boolType;
    static Type *constIntType;
};

#endif
