#include "Expression.hpp"
#include <map>
#include <iostream>

std::map<Operators, std::string> enumToStr = {
    {Operators::BANG, "!"},
    {Operators::MINUS, "-"},
    {Operators::MODULUS, "%"},
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
    {"%", Operators::MODULUS},
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

IntExpr::IntExpr(int value, int tline, int tcol) {
    Val = value;
    line = tline;
    column = tcol;
}

CharExpr::CharExpr(char charac, int tline, int tcol) {
    character = charac;
    line = tline;
    column = tcol;
}

VarExpr::VarExpr(std::string name, int tline, int tcol) {
    Name = name;
    line = tline;
    column = tcol;
}

UnaryExpr::UnaryExpr(Operators op, std::unique_ptr<Expression> operand, int tline, int tcol) {
    Op = op;
    Operand = std::move(operand);
    line = tline;
    column = tcol;
}

BinaryExpr::BinaryExpr(Operators op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs, int tline, int tcol) {
    LHS = std::move(lhs);
    RHS = std::move(rhs);
    Op = op;
    line = tline;
    column = tcol;
}

AssignExpr::AssignExpr(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs, int tline, int tcol) {
    LHS = std::move(lhs);
    RHS = std::move(rhs);
    line = tline;
    column = tcol;
}

void EmptyExpr::accept(Visitor& visitor) {
    visitor.visitEmptyExpr(*this);
}

CallExpr::CallExpr(std::string callee_name, int tline, int tcol) {
    callee = callee_name;
    line = tline;
    column = tcol;
}

void CallExpr::add(std::unique_ptr<Expression> arg) {
    args.push_back(std::move(arg));
}

void IntExpr::accept(Visitor& visitor) {
    visitor.visitIntExpr(*this);
}

void CharExpr::accept(Visitor& visitor) {
    visitor.visitCharExpr(*this);
}

void VarExpr::accept(Visitor& visitor) {
    visitor.visitVarExpr(*this);
}

void UnaryExpr::accept(Visitor& visitor) {
    visitor.visitUnaryExpr(*this);
}

void BinaryExpr::accept(Visitor& visitor) {
    visitor.visitBinaryExpr(*this);
}

void AssignExpr::accept(Visitor& visitor) {
    visitor.visitAssignExpr(*this);
}

void CallExpr::accept(Visitor& visitor) {
    visitor.visitCallExpr(*this);
}
