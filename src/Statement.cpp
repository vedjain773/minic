#include "Statement.hpp"
#include "Visitor.hpp"

ExprStmt::ExprStmt(std::unique_ptr<Expression> expr) {
    expression = std::move(expr);
}

void ExprStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitExprStmt(*this);

    PrintVisitor printVis;

    printVis.depth += 1;
    Expression* expr = (this->expression).get();
    expr->accept(printVis);
    printVis.depth -= 1;
}

BlockStmt::BlockStmt(std::unique_ptr<Statement> stmt) {
    statement = std::move(stmt);
}

void BlockStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitBlockStmt(*this);

    Statement* stmt = (this->statement).get();
    stmt->accept(stmtVisitor);
}
