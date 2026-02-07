#include "StmtVisitor.hpp"
#include "Statement.hpp"
#include <iostream>

void PrintStmtVisitor::visitExprStmt(ExprStmt& exprstmt) {
    std::cout << getIndent() << "|-Stmt(Expr)\n";
}

void PrintStmtVisitor::visitBlockStmt(BlockStmt& blockstmt) {
    std::cout << getIndent() << "|-Stmt(Block)\n";
}

std::string PrintStmtVisitor::getIndent() {
    std::string indent = "";

    for (int i = 0; i < depth; i++) {
        indent.append("  ");
    }

    return indent;
}
