#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <memory>

class Expression {
    public:
    virtual ~Expression() = default;
};

class IntExpr: public Expression {
    public:
    int Val;

    IntExpr(int value);
};

class VarExpr: public Expression {
    public:
    std::string Name;

    VarExpr(std::string name);
};

class BinaryExpr: public Expression {
    public:
    char Op;
    std::unique_ptr<Expression> LHS;
    std::unique_ptr<Expression> RHS;

    BinaryExpr(char op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
};

#endif
