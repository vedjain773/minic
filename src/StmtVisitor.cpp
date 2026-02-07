#include "StmtVisitor.hpp"
#include "Statement.hpp"
#include <iostream>

void PrintStmtVisitor::visitExprStmt(ExprStmt& exprstmt) {
    std::cout << "|-Expr(Start)\n";
}
