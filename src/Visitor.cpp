#include "Visitor.hpp"
#include "Expression.hpp"
#include <iostream>

void PrintVisitor::visitIntExpr(IntExpr& intexpr) {
    std::cout << base << "|-Int(" << intexpr.Val << ")\n";
}

void PrintVisitor::visitVarExpr(VarExpr& varexpr) {
    std::cout << base << "|-Var(" << varexpr.Name << ")\n";
}

void PrintVisitor::visitUnaryExpr(UnaryExpr& unaryexpr) {
    std::cout << base << "|-Unary(" << unaryexpr.Op << ")\n";
}

void PrintVisitor::visitBinaryExpr(BinaryExpr& binexpr) {
    std::cout << base << "|-Oper(" << binexpr.Op << ")\n";
}

void PrintVisitor::incIndent() {
    base.append("  ");
}

void PrintVisitor::decIndent() {
    base.pop_back();
    base.pop_back();
}
