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

class IfStmt: public Statement {
    public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;
    std::unique_ptr<Statement> elseStmt;

    IfStmt(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> ifbody, std::unique_ptr<Statement> elsestmt);
    void accept(StmtVisitor& stmtVisitor);
};

class ElseStmt: public Statement {
    public:
    std::unique_ptr<Statement> body;

    ElseStmt(std::unique_ptr<Statement> elsebody);
    void accept(StmtVisitor& stmtVisitor);
};

class WhileStmt: public Statement {
    public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;

    WhileStmt(std::unique_ptr<Expression> condn, std::unique_ptr<Statement> whilebody);
    void accept(StmtVisitor& stmtVisitor);
};

class ReturnStmt: public Statement {
    public:
    std::unique_ptr<Statement> retExpr;

    ReturnStmt(std::unique_ptr<Statement> retexpr);
    void accept(StmtVisitor& stmtVisitor);
};

#endif
