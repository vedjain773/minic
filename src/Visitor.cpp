#include "Visitor.hpp"
#include "Expression.hpp"
#include <iostream>

void PrintVisitor::visitIntExpr(IntExpr& intexpr) {
    std::cout << base << "|-Int(" << intexpr.Val << ")\n";
    base = "";
}

void PrintVisitor::visitVarExpr(VarExpr& varexpr) {
    std::cout << base << "|-Var(" << varexpr.Name << ")\n";
    base = "";
}

void PrintVisitor::visitUnaryExpr(UnaryExpr& unaryexpr) {
    std::cout << base << "|-Unary(" << unaryexpr.Op << ")\n";
    base.append("  ");
}

void PrintVisitor::visitBinaryExpr(BinaryExpr& intexpr) {
    std::cout << "|-Int()\n";
}
