#include "Expression.hpp"
#include <iostream>

IntExpr::IntExpr(int value) {
    Val = value;
}

VarExpr::VarExpr(std::string name) {
    Name = name;
}

UnaryExpr::UnaryExpr(char op, std::unique_ptr<Expression> operand) {
    Op = op;
    Operand = std::move(operand);
}

BinaryExpr::BinaryExpr(char op, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    LHS = std::move(lhs);
    RHS = std::move(rhs);
    Op = op;
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

    Operand->accept(visitor);
}

void BinaryExpr::accept(Visitor& visitor) {
    visitor.visitBinaryExpr(*this);

    std::unique_ptr<Expression> lExpr = std::move(this->LHS);
    std::unique_ptr<Expression> rExpr = std::move(this->RHS);

    lExpr->accept(visitor);
    rExpr->accept(visitor);
}
