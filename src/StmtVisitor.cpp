#include "StmtVisitor.hpp"
#include "Statement.hpp"
#include <iostream>

void PrintStmtVisitor::visitExprStmt(ExprStmt& exprstmt) {
    std::cout << getIndent() << "|-Stmt(Expr)\n";
}

void PrintStmtVisitor::visitBlockStmt(BlockStmt& blockstmt) {
    std::cout << getIndent() << "|-Stmt(Block)\n";
}

void PrintStmtVisitor::visitIfStmt(IfStmt& ifstmt) {
    std::cout << getIndent() << "|-Stmt(If)\n";
}

void PrintStmtVisitor::visitElseStmt(ElseStmt& elsestmt) {
    std::cout << getIndent() << "|-Stmt(Else)\n";
}

void PrintStmtVisitor::visitWhileStmt(WhileStmt& whilestmt) {
    std::cout << getIndent() << "|-Stmt(While)\n";
}

void PrintStmtVisitor::visitReturnStmt(ReturnStmt& returnstmt) {
    std::cout << getIndent() << "|-Stmt(Return)\n";
}

std::string PrintStmtVisitor::getIndent() {
    std::string indent = "";

    for (int i = 0; i < depth; i++) {
        indent.append("  ");
    }

    return indent;
}
