#include "Visitor.hpp"
#include "Expression.hpp"
#include <iostream>

void PrintVisitor::visitIntExpr(IntExpr& intexpr) {
    std::cout << getIndent() << "|-Int(" << intexpr.Val << ")\n";
}

void PrintVisitor::visitVarExpr(VarExpr& varexpr) {
    std::cout << getIndent() << "|-Var(" << varexpr.Name << ")\n";
}

void PrintVisitor::visitUnaryExpr(UnaryExpr& unaryexpr) {
    std::cout << getIndent() << "|-Unary(" << getOpStr(unaryexpr.Op) << ")\n";
}

void PrintVisitor::visitBinaryExpr(BinaryExpr& binexpr) {
    std::cout << getIndent() << "|-Oper(" << getOpStr(binexpr.Op) << ")\n";
}

void PrintVisitor::visitAssignExpr(AssignExpr& assignexpr) {
    std::cout << getIndent() << "|-Assign(=)\n";
}

std::string PrintVisitor::getIndent() {
    std::string indent = "";

    for (int i = 0; i < depth; i++) {
        indent.append("  ");
    }

    return indent;
}
