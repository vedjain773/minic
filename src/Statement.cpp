#include "Statement.hpp"
#include "Visitor.hpp"

ExprStmt::ExprStmt(std::unique_ptr<Expression> expr) {
    expression = std::move(expr);
}

void ExprStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitExprStmt(*this);

    PrintVisitor printVis;

    printVis.depth += 1;
    std::unique_ptr<Expression> expr = std::move(this->expression);
    expr->accept(printVis);
    printVis.depth -= 1;

}
