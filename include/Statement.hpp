#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>
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

class BlockStmt: public Statement {
    public:
    std::vector<std::unique_ptr<Statement>> statements;

    // BlockStmt(std::unique_ptr<Statement> stmt);
    void addStmt(std::unique_ptr<Statement> stmt);
    void accept(StmtVisitor& stmtvisistor);
};

#endif
