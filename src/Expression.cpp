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
