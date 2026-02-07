#ifndef STMT_VISITOR_H
#define STMT_VISITOR_H

#include "Visitor.hpp"

class ExprStmt;

class StmtVisitor {
    public:
    int depth = 0;

    virtual void visitExprStmt(ExprStmt& exprstmt) = 0;
};

class PrintStmtVisitor: public StmtVisitor {
    public:
    void visitExprStmt(ExprStmt& exprstmt);
};

#endif
