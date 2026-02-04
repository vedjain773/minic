#include "Expression.hpp"
#include <map>
#include <iostream>

std::map<Operators, std::string> enumToStr = {
    {Operators::BANG, "!"},
    {Operators::MINUS, "-"},
    {Operators::DIVIDE, "/"},
    {Operators::MULT, "*"},
    {Operators::PLUS, "+"},
    {Operators::GREATER, ">"},
    {Operators::GREATER_EQUALS, ">="},
    {Operators::LESS, "<"},
    {Operators::LESS_EQUALS, "<="},
    {Operators::EQUALS, "=="},
    {Operators::NOT_EQUALS, "!="},
    {Operators::AND, "&&"},
    {Operators::OR, "||"},
};

std::map<std::string, Operators> strToEnum = {
    {"!", Operators::BANG},
    {"-", Operators::MINUS},
    {"/", Operators::DIVIDE},
    {"*", Operators::MULT},
    {"+", Operators::PLUS},
    {">", Operators::GREATER},
    {">=", Operators::GREATER_EQUALS},
    {"<", Operators::LESS,},
    {"<=", Operators::LESS_EQUALS},
    {"==", Operators::EQUALS},
    {"!=", Operators::NOT_EQUALS},
    {"&&", Operators::AND},
    {"||", Operators::OR},
};

std::string getOpStr(Operators op) {
    return enumToStr[op];
}

Operators getOp(std::string opStr) {
    return strToEnum[opStr];
}

IntExpr::IntExpr(int value) {
    Val = value;
}

VarExpr::VarExpr(std::string name) {
    Name = name;
}

UnaryExpr::UnaryExpr(Operators op, std::unique_ptr<Expression> operand) {
    Op = op;
    Operand = std::move(operand);
}

BinaryExpr::BinaryExpr(Operators op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    LHS = std::move(lhs);
    RHS = std::move(rhs);
    Op = op;
}

AssignExpr::AssignExpr(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    LHS = std::move(lhs);
    RHS = std::move(rhs);
}

void IntExpr::accept(Visitor& visitor) {
    visitor.visitIntExpr(*this);
}

void VarExpr::accept(Visitor& visitor) {
    visitor.visitVarExpr(*this);
}

void UnaryExpr::accept(Visitor& visitor) {
    visitor.visitUnaryExpr(*this);

    std::unique_ptr<Expression> Operand = std::move(this->Operand);

    visitor.depth += 1;
    Operand->accept(visitor);
    visitor.depth -= 1;
}

void BinaryExpr::accept(Visitor& visitor) {
    visitor.visitBinaryExpr(*this);

    std::unique_ptr<Expression> lExpr = std::move(this->LHS);
    std::unique_ptr<Expression> rExpr = std::move(this->RHS);

    visitor.depth += 1;
    lExpr->accept(visitor);
    visitor.depth -= 1;

    visitor.depth += 1;
    rExpr->accept(visitor);
    visitor.depth -= 1;
}

void AssignExpr::accept(Visitor& visitor) {
    visitor.visitAssignExpr(*this);

    std::unique_ptr<Expression> lExpr = std::move(this->LHS);
    std::unique_ptr<Expression> rExpr = std::move(this->RHS);

    visitor.depth += 1;
    lExpr->accept(visitor);
    visitor.depth -= 1;

    visitor.depth += 1;
    rExpr->accept(visitor);
    visitor.depth -= 1;
}
