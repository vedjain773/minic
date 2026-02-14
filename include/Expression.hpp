#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <memory>
#include "Scope.hpp"
#include "Visitor.hpp"

enum class Operators {
    //Unary
    BANG, MINUS,

    //Binary
    DIVIDE, MULT, PLUS,

    //Comparison
    GREATER, GREATER_EQUALS, LESS, LESS_EQUALS,

    //Equality
    EQUALS, NOT_EQUALS,

    //Logical
    AND, OR,
};

std::string getOpStr(Operators op);
Operators getOp(std::string op_str);

class Expression {
    public:
    virtual ~Expression() = default;
    virtual void accept(Visitor& visitor) = 0;
    TypeKind infType;
};

class IntExpr: public Expression {
    public:
    int Val;

    IntExpr(int value);
    void accept(Visitor& visitor);
};

class CharExpr: public Expression {
    public:
    char character;

    CharExpr(char charac);
    void accept(Visitor& visitor);
};

class VarExpr: public Expression {
    public:
    std::string Name;

    VarExpr(std::string name);
    void accept(Visitor& visitor);
};

class UnaryExpr: public Expression {
    public:
    Operators Op;
    std::unique_ptr<Expression> Operand;

    UnaryExpr(Operators op, std::unique_ptr<Expression> operand);
    void accept(Visitor& visitor);
};

class BinaryExpr: public Expression {
    public:
    Operators Op;
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    BinaryExpr(Operators op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    void accept(Visitor& visitor);
};

class AssignExpr: public Expression {
    public:
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    AssignExpr(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    void accept(Visitor& visitor);
};

#endif
