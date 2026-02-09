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

IfStmt::IfStmt(std::unique_ptr<Expression> condn, std::unique_ptr<Statement> ifbody) {
    condition = std::move(condn);
    body = std::move(ifbody);
}

void IfStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitIfStmt(*this);

    Expression* condn = (this->condition).get();
    Statement* ifbody = (this->body).get();

    PrintVisitor printVis;
    printVis.depth = stmtVisitor.depth;

    stmtVisitor.depth += 1;

    printVis.depth += 1;
    condn->accept(printVis);
    printVis.depth -= 1;

    ifbody->accept(stmtVisitor);
    stmtVisitor.depth -= 1;
}
