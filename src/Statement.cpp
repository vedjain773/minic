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

IfStmt::IfStmt(std::unique_ptr<Expression> condn, std::unique_ptr<Statement> ifbody, std::unique_ptr<Statement> elsestmt) {
    condition = std::move(condn);
    body = std::move(ifbody);
    elseStmt = std::move(elsestmt);
}

void IfStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitIfStmt(*this);

    Expression* condn = (this->condition).get();
    Statement* ifbody = (this->body).get();
    Statement* elsestmt = (this->elseStmt).get();

    PrintVisitor printVis;
    printVis.depth = stmtVisitor.depth;

    stmtVisitor.depth += 1;

    printVis.depth += 1;
    condn->accept(printVis);
    printVis.depth -= 1;

    ifbody->accept(stmtVisitor);

    if (elsestmt != nullptr) {
        elsestmt->accept(stmtVisitor);
    }

    stmtVisitor.depth -= 1;
}

ElseStmt::ElseStmt(std::unique_ptr<Statement> elsebody) {
    body = std::move(elsebody);
}

void ElseStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitElseStmt(*this);

    Statement* elsebody = (this->body).get();

    stmtVisitor.depth += 1;
    elsebody->accept(stmtVisitor);
    stmtVisitor.depth -= 1;
}

WhileStmt::WhileStmt(std::unique_ptr<Expression> condn, std::unique_ptr<Statement> whilebody) {
    condition = std::move(condn);
    body = std::move(whilebody);
}

void WhileStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitWhileStmt(*this);

    Expression* condn = (this->condition).get();
    Statement* elsebody = (this->body).get();

    PrintVisitor printVis;
    printVis.depth = stmtVisitor.depth;

    stmtVisitor.depth += 1;

    printVis.depth += 1;
    condn->accept(printVis);
    printVis.depth -= 1;

    elsebody->accept(stmtVisitor);
    stmtVisitor.depth -= 1;
}

ReturnStmt::ReturnStmt(std::unique_ptr<Statement> retexpr) {
    retExpr = std::move(retexpr);
}

void ReturnStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitReturnStmt(*this);

    Statement* retexpr = (this->retExpr).get();

    stmtVisitor.depth += 1;
    retexpr->accept(stmtVisitor);
    stmtVisitor.depth -= 1;
}

DeclStmt::DeclStmt(TokenType tokentype, std::string varname, std::unique_ptr<Expression> expr) {
    type = tokentype;
    name = varname;
    expression = std::move(expr);
}

void DeclStmt::accept(StmtVisitor& stmtVisitor) {
    stmtVisitor.visitDeclStmt(*this);

    Expression* expr = (this->expression).get();

    PrintVisitor printVis;
    printVis.depth = stmtVisitor.depth;

    stmtVisitor.depth += 1;
    printVis.depth += 1;

    if (expr != nullptr) {
        expr->accept(printVis);
    }

    printVis.depth -= 1;
    stmtVisitor.depth -= 1;
}
