#include "StmtVisitor.hpp"
#include "Statement.hpp"
#include <iostream>

void PrintStmtVisitor::visitExprStmt(ExprStmt& exprstmt) {
    std::cout << "|-Stmt(Expr)\n";
}

void PrintStmtVisitor::visitBlockStmt(BlockStmt& blockstmt) {
    std::cout << "|-Stmt(Block)\n";
}
