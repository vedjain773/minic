#include "Expression.hpp"
#include <iostream>

IntExpr::IntExpr(int value) {
    Val = value;
}

VarExpr::VarExpr(std::string name) {
    Name = name;
}

BinaryExpr::BinaryExpr(char op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    LHS = std::move(lhs);
    RHS = std::move(rhs);
    Op = op;
}
