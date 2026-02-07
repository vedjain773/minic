#ifndef STATEMENT_H
#define STATEMENT_H

#include "Expression.hpp"
#include "StmtVisitor.hpp"

class Statement {
    public:
    virtual ~Statement() = default;
    virtual void accept(StmtVisitor& stmtVisitor) = 0;
};

class ExprStmt: public Statement {
    public:
    std::unique_ptr<Expression> expression;

    ExprStmt(std::unique_ptr<Expression> expr);
    void accept(StmtVisitor& stmtVisitor);
};

#endif
