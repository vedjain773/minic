#include "Statement.hpp"
#include "Visitor.hpp"

ExprStmt::ExprStmt(std::unique_ptr<Expression> expr) {
    expression = std::move(expr);
}

void ExprStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitExprStmt(*this);

    PrintVisitor printVis;
    printVis.depth = stmtVisitor.depth;

    printVis.depth += 1;
    Expression* expr = (this->expression).get();
    expr->accept(printVis);
    printVis.depth -= 1;
}

// BlockStmt::BlockStmt(std::unique_ptr<Statement> stmt) {
//     statement = std::move(stmt);
// }

void BlockStmt::addStmt(std::unique_ptr<Statement> stmt) {
    statements.push_back(std::move(stmt));
}

void BlockStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitBlockStmt(*this);

    stmtVisitor.depth += 1;
    for (int i = 0; i < statements.size(); i++) {
        Statement* stmt = (statements[i]).get();
        stmt->accept(stmtVisitor);
    }
    stmtVisitor.depth -= 1;
}
