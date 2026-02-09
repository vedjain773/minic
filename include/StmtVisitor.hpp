#ifndef STMT_VISITOR_H
#define STMT_VISITOR_H

#include "Visitor.hpp"

class ExprStmt;
class BlockStmt;
class IfStmt;
class ElseStmt;

class StmtVisitor {
    public:
    int depth = 0;

    virtual void visitExprStmt(ExprStmt& exprstmt) = 0;
    virtual void visitBlockStmt(BlockStmt& blockstmt) = 0;
    virtual void visitIfStmt(IfStmt& ifstmt) = 0;
    virtual void visitElseStmt(ElseStmt& elsestmt) = 0;
};

class PrintStmtVisitor: public StmtVisitor {
    public:
    void visitExprStmt(ExprStmt& exprstmt);
    void visitBlockStmt(BlockStmt& blockstmt);
    void visitIfStmt(IfStmt& ifstmt);
    void visitElseStmt(ElseStmt& elsestmt);

    std::string getIndent();
};

#endif
