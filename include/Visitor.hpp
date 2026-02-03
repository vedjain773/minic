#ifndef VISITOR_H
#define VISITOR_H

#include <string>

class IntExpr;
class VarExpr;
class UnaryExpr;
class BinaryExpr;

class Visitor {
    public:
    int depth = 0;

    virtual void visitIntExpr(IntExpr& intexpr) = 0;
    virtual void visitVarExpr(VarExpr& varexpr) = 0;
    virtual void visitUnaryExpr(UnaryExpr& unaryexpr) = 0;
    virtual void visitBinaryExpr(BinaryExpr& binaryexpr) = 0;
};

class PrintVisitor: public Visitor {
    public:
    void visitIntExpr(IntExpr& intexpr);
    void visitVarExpr(VarExpr& varexpr);
    void visitUnaryExpr(UnaryExpr& unaryexpr);
    void visitBinaryExpr(BinaryExpr& binaryexpr);

    std::string getIndent();
};

#endif
