#include "Statement.hpp"
#include "Visitor.hpp"

void EmptyStmt::accept(Visitor& visitor) {
    visitor.visitEmptyStmt(*this);
}

ExprStmt::ExprStmt(std::unique_ptr<Expression> expr) {
    expression = std::move(expr);
}

void ExprStmt::accept(Visitor& visitor) {
    visitor.visitExprStmt(*this);

    visitor.depth += 1;
    Expression* expr = (this->expression).get();
    expr->accept(visitor);
    visitor.depth -= 1;
}

void BlockStmt::addStmt(std::unique_ptr<Statement> stmt) {
    statements.push_back(std::move(stmt));
}

void BlockStmt::accept(Visitor& visitor) {
    visitor.visitBlockStmt(*this);

    visitor.depth += 1;
    for (int i = 0; i < statements.size(); i++) {
        Statement* stmt = (statements[i]).get();
        stmt->accept(visitor);
    }
    visitor.depth -= 1;
}

IfStmt::IfStmt(std::unique_ptr<Expression> condn, std::unique_ptr<Statement> ifbody, std::unique_ptr<Statement> elsestmt) {
    condition = std::move(condn);
    body = std::move(ifbody);
    elseStmt = std::move(elsestmt);
}

void IfStmt::accept(Visitor& visitor) {
    visitor.visitIfStmt(*this);

    Expression* condn = (this->condition).get();
    Statement* ifbody = (this->body).get();
    Statement* elsestmt = (this->elseStmt).get();

    visitor.depth += 1;

    condn->accept(visitor);
    ifbody->accept(visitor);

    if (elsestmt != nullptr) {
        elsestmt->accept(visitor);
    }

    visitor.depth -= 1;
}

ElseStmt::ElseStmt(std::unique_ptr<Statement> elsebody) {
    body = std::move(elsebody);
}

void ElseStmt::accept(Visitor& visitor) {
    visitor.visitElseStmt(*this);

    Statement* elsebody = (this->body).get();

    visitor.depth += 1;
    elsebody->accept(visitor);
    visitor.depth -= 1;
}

WhileStmt::WhileStmt(std::unique_ptr<Expression> condn, std::unique_ptr<Statement> whilebody) {
    condition = std::move(condn);
    body = std::move(whilebody);
}

void WhileStmt::accept(Visitor& visitor) {
    visitor.visitWhileStmt(*this);

    Expression* condn = (this->condition).get();
    Statement* elsebody = (this->body).get();

    visitor.depth += 1;

    condn->accept(visitor);
    elsebody->accept(visitor);

    visitor.depth -= 1;
}

ReturnStmt::ReturnStmt(std::unique_ptr<Statement> retexpr) {
    retExpr = std::move(retexpr);
}

void ReturnStmt::accept(Visitor& visitor) {
    visitor.visitReturnStmt(*this);

    Statement* retexpr = (this->retExpr).get();

    visitor.depth += 1;
    retexpr->accept(visitor);
    visitor.depth -= 1;
}

DeclStmt::DeclStmt(TokenType tokentype, std::string varname, std::unique_ptr<Expression> expr) {
    type = tokentype;
    name = varname;
    expression = std::move(expr);
}

void DeclStmt::accept(Visitor& visitor) {
    visitor.visitDeclStmt(*this);

    Expression* expr = (this->expression).get();

    visitor.depth += 1;

    if (expr != nullptr) {
        expr->accept(visitor);
    }

    visitor.depth -= 1;
}
