#ifndef __TYPE_H__
#define __TYPE_H__
#include <vector>
#include <string>

class Type
{
private:
    int kind;
    bool is_const;
protected:
    // enum {INT, FLOAT, CONST_INT, CONST_FLOAT, VOID, BOOL, FUNC, INT_ARRAY, FLOAT_ARRAY, CONST_INT_ARRAY, CONST_FLOAT_ARRAY, PTR};
    enum {INT, FLOAT, VOID, BOOL, FUNC, INT_ARRAY, FLOAT_ARRAY, CONST_INT_ARRAY, CONST_FLOAT_ARRAY, PTR};
public:
    Type(int kind, bool is_const = false) : kind(kind), is_const(is_const) {};
    virtual ~Type() {};
    virtual std::string toStr() = 0;
    bool isInt() const {return kind == INT;};
    bool isFloat() const {return kind == FLOAT;};
    // bool isConstInt() const {return kind == INT && is_const;}
    // bool isConstFloat() const {return kind == FLOAT && is_const;}
    bool isBool() const {return kind == BOOL;}
    bool isVoid() const {return kind == VOID;}
    bool isFunc() const {return kind == FUNC;}
    bool isIntArray() const {return kind == INT_ARRAY;}
    bool isFloatArray() const {return kind == FLOAT_ARRAY;}
    bool isConstIntArray() const {return kind == CONST_INT_ARRAY;}
    bool isConstFloatArray() const {return kind == CONST_FLOAT_ARRAY;}
    bool isArray() const {return kind == INT_ARRAY || kind == FLOAT_ARRAY || 
                            kind == CONST_FLOAT_ARRAY || kind == CONST_INT_ARRAY;}
    //ATTENTION: FUNC excluded
    // bool isAnyInt() const {return kind == INT || kind == CONST_INT || kind == INT_ARRAY || kind == CONST_INT_ARRAY;}
    bool isAnyInt() const {return kind == INT || kind == INT_ARRAY || kind == CONST_INT_ARRAY;}
    //ATTENTION: FUNC excluded
    // bool isAnyFloat() const {return kind == FLOAT || kind == FLOAT_ARRAY || kind == CONST_FLOAT || kind == CONST_FLOAT_ARRAY;}
    bool isAnyFloat() const {return kind == FLOAT || kind == FLOAT_ARRAY || kind == CONST_FLOAT_ARRAY;}
    bool calculatable() const {return isAnyInt()||isAnyFloat() || isBool();}//不是void其实就行
    bool isConst() const {return is_const || kind == CONST_INT_ARRAY || kind == CONST_FLOAT_ARRAY;}
};

class IntType : public Type
{
private:
    int size;
public:
    IntType(int size, bool is_const = false) : Type(Type::INT, is_const), size(size){};
    std::string toStr();
};

class FloatType : public Type
{
private:
    int size;
public:
    FloatType(int size, bool is_const = false) : Type(Type::FLOAT, is_const), size(size){};
    std::string toStr();
};

// class ConstIntType : public Type
// {
// private:
//     int size;
// public:
//     ConstIntType(int size) : Type(Type::CONST_INT), size(size){};
//     std::string toStr();
// };

// class ConstFloatType : public Type
// {
// private:
//     int size;
// public:
//     ConstFloatType(int size) : Type(Type::CONST_FLOAT), size(size){};
//     std::string toStr();
// };

class BoolType : public Type
{
private:
    int size;
public:
    BoolType(int size, bool is_const = false) : Type(Type::BOOL, is_const), size(size){};
    std::string toStr();
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
    Type *returnType;
    std::vector<Type*> paramsType;
public:
    FunctionType(Type* returnType, std::vector<Type*> paramsType) : 
    Type(Type::FUNC), returnType(returnType), paramsType(paramsType){};
    void setparamsType(std::vector<Type*>);
    Type* getRetType() {return returnType;};
    std::vector<Type*> getParamsType() {return this->paramsType;}
    std::string toStr();
};

class IntArrayType : public Type
{
private:
    std::vector<int> dimensions;
public:
    IntArrayType() : Type(Type::INT_ARRAY){};
    void pushBackDimension(int);
    std::vector<int> getDimensions();
    std::string toStr();
};

class FloatArrayType : public Type
{
private:
    std::vector<int> dimensions;
public:
    FloatArrayType() : Type(Type::FLOAT_ARRAY){};
    void pushBackDimension(int);
    std::vector<int> getDimensions();
    std::string toStr();
};

class ConstIntArrayType : public Type
{
private:
    std::vector<int> dimensions;
public:
    ConstIntArrayType() : Type(Type::CONST_INT_ARRAY){};
    void pushBackDimension(int);
    std::vector<int> getDimensions();
    std::string toStr();
};

class ConstFloatArrayType : public Type
{
private:
    std::vector<int> dimensions;
public:
    ConstFloatArrayType() : Type(Type::CONST_FLOAT_ARRAY){};
    void pushBackDimension(int);
    std::vector<int> getDimensions();
    std::string toStr();
};

class PointerType : public Type
{
private:
    Type *valueType;
public:
    PointerType(Type* valueType) : Type(Type::PTR) {this->valueType = valueType;};
    Type* getValueType() {return this->valueType;};
    std::string toStr();
};

class TypeSystem
{
private:
    static IntType commonInt;
    static IntType commonConstInt;
    static FloatType commonFloat;
    static FloatType commonConstFloat;
    static BoolType commonBool;
    static BoolType commonConstBool;
    static VoidType commonVoid;
public:
    static Type *intType;
    static Type *constIntType;
    static Type *floatType;
    static Type *constFloatType;
    static Type *boolType;
    static Type *constBoolType;
    static Type *voidType;
    static Type* getMaxType(Type* type1, Type* type2);
    static bool needCast(Type* type1, Type* type2);
};


#endif