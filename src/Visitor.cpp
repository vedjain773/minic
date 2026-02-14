#include "Visitor.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "Program.hpp"
#include "Error.hpp"
#include <iostream>

void PrintVisitor::visitIntExpr(IntExpr& intexpr) {
    std::cout << getIndent() << "|-Int(" << intexpr.Val << ")\n";
}

void PrintVisitor::visitCharExpr(CharExpr& charexpr) {
    std::cout << getIndent() << "|-Char(" << charexpr.character << ")\n";
}

void PrintVisitor::visitVarExpr(VarExpr& varexpr) {
    std::cout << getIndent() << "|-Var(" << varexpr.Name << ")\n";
}

void PrintVisitor::visitUnaryExpr(UnaryExpr& unaryexpr) {
    std::cout << getIndent() << "|-Unary(" << getOpStr(unaryexpr.Op) << ")\n";

    Expression* Operand = (unaryexpr.Operand).get();

    depth += 1;
    Operand->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitBinaryExpr(BinaryExpr& binexpr) {
    std::cout << getIndent() << "|-Oper(" << getOpStr(binexpr.Op) << ")\n";

    Expression* lExpr = (binexpr.LHS).get();
    Expression* rExpr = (binexpr.RHS).get();

    depth += 1;
    lExpr->accept(*this);
    depth -= 1;

    depth += 1;
    rExpr->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitAssignExpr(AssignExpr& assignexpr) {
    std::cout << getIndent() << "|-Assign(=)\n";

    Expression* lExpr = (assignexpr.LHS).get();
    Expression* rExpr = (assignexpr.RHS).get();

    depth += 1;
    lExpr->accept(*this);
    depth -= 1;

    depth += 1;
    rExpr->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitExprStmt(ExprStmt& exprstmt) {
    std::cout << getIndent() << "|-Stmt(Expr)\n";

    Expression* expr = (exprstmt.expression).get();

    depth += 1;
    expr->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitBlockStmt(BlockStmt& blockstmt) {
    std::cout << getIndent() << "|-Stmt(Block)\n";

    depth += 1;
    for (int i = 0; i < blockstmt.statements.size(); i++) {
        Statement* stmt = (blockstmt.statements[i]).get();
        stmt->accept(*this);
    }
    depth -= 1;
}

void PrintVisitor::visitIfStmt(IfStmt& ifstmt) {
    std::cout << getIndent() << "|-Stmt(If)\n";

    Expression* condn = (ifstmt.condition).get();
    Statement* ifbody = (ifstmt.body).get();
    Statement* elsestmt = (ifstmt.elseStmt).get();

    depth += 1;

    condn->accept(*this);
    ifbody->accept(*this);

    if (elsestmt != nullptr) {
        elsestmt->accept(*this);
    }

    depth -= 1;
}

void PrintVisitor::visitElseStmt(ElseStmt& elsestmt) {
    std::cout << getIndent() << "|-Stmt(Else)\n";

    Statement* elsebody = (elsestmt.body).get();

    depth += 1;
    elsebody->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitWhileStmt(WhileStmt& whilestmt) {
    std::cout << getIndent() << "|-Stmt(While)\n";

    Expression* condn = (whilestmt.condition).get();
    Statement* elsebody = (whilestmt.body).get();

    depth += 1;
    condn->accept(*this);
    elsebody->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitReturnStmt(ReturnStmt& returnstmt) {
    std::cout << getIndent() << "|-Stmt(Return)\n";

    Statement* retexpr = (returnstmt.retExpr).get();

    depth += 1;
    retexpr->accept(*this);
    depth -= 1;
}

void PrintVisitor::visitDeclStmt(DeclStmt& declstmt) {
    std::cout << getIndent() << "|-Stmt(Declare)\n";
    std::cout << getIndent() << "  |-Var(" + declstmt.name + ")\n";

    Expression* expr = (declstmt.expression).get();

    depth += 1;

    if (expr != nullptr) {
        expr->accept(*this);
    }

    depth -= 1;
}

void PrintVisitor::visitEmptyStmt(EmptyStmt& emptystmt) {
    std::cout << getIndent() << "\n";
}

void PrintVisitor::visitProgram(Program& program) {
    std::cout << getIndent() << "\n";

    for (int i = 0; i < program.root.size(); i++) {
        Statement* stmt = (program.root[i]).get();
        stmt->accept(*this);
    }
}

std::string PrintVisitor::getIndent() {
    std::string indent = "";

    for (int i = 0; i < depth; i++) {
        indent.append("  ");
    }

    return indent;
}

void SemanticVisitor::visitProgram(Program& program) {
    Scope globalScope;
    scopeVec.push_back(globalScope);

    for (int i = 0; i < program.root.size(); i++) {
        Statement* stmt = (program.root[i]).get();
        stmt->accept(*this);
    }

    scopeVec.pop_back();
}

void SemanticVisitor::visitEmptyStmt(EmptyStmt& emptystmt) {
    //dosomething
}

void SemanticVisitor::visitBlockStmt(BlockStmt& blockstmt) {
    Scope locScope;
    scopeVec.push_back(locScope);

    for (int i = 0; i < blockstmt.statements.size(); i++) {
        Statement* stmt = (blockstmt.statements[i]).get();
        stmt->accept(*this);
    }

    scopeVec.pop_back();
}

void SemanticVisitor::visitDeclStmt(DeclStmt& declstmt) {
    if (scopeVec[scopeVec.size() - 1].search(declstmt.name)) {
        Error error;
        error.printErrorMsg(declstmt.name + " is already declared");
    } else {
        scopeVec[scopeVec.size() - 1].addRow(declstmt.name, declstmt.type);
    }

    Expression* expr = (declstmt.expression).get();

    if (expr != nullptr) {
        expr->accept(*this);
    }
}

void SemanticVisitor::visitIfStmt(IfStmt& ifstmt) {
    Expression* condn = (ifstmt.condition).get();
    Statement* ifbody = (ifstmt.body).get();
    Statement* elsestmt = (ifstmt.elseStmt).get();

    condn->accept(*this);
    ifbody->accept(*this);

    if (elsestmt != nullptr) {
        elsestmt->accept(*this);
    }
}

void SemanticVisitor::visitElseStmt(ElseStmt& elsestmt) {
    Statement* elsebody = (elsestmt.body).get();

    elsebody->accept(*this);
}

void SemanticVisitor::visitWhileStmt(WhileStmt& whilestmt) {
    Expression* condn = (whilestmt.condition).get();
    Statement* elsebody = (whilestmt.body).get();

    condn->accept(*this);
    elsebody->accept(*this);
}

void SemanticVisitor::visitReturnStmt(ReturnStmt& returnstmt) {
    Statement* retexpr = (returnstmt.retExpr).get();

    retexpr->accept(*this);
}

void SemanticVisitor::visitExprStmt(ExprStmt& exprstmt) {
    Expression* expr = (exprstmt.expression).get();

    expr->accept(*this);
}

void SemanticVisitor::visitAssignExpr(AssignExpr& assignexpr) {
    Expression* lExpr = (assignexpr.LHS).get();
    Expression* rExpr = (assignexpr.RHS).get();

    lExpr->accept(*this);

    rExpr->accept(*this);
}

void SemanticVisitor::visitBinaryExpr(BinaryExpr& binexpr) {
    Expression* lExpr = (binexpr.LHS).get();
    Expression* rExpr = (binexpr.RHS).get();

    lExpr->accept(*this);

    rExpr->accept(*this);
}

void SemanticVisitor::visitUnaryExpr(UnaryExpr& unaryexpr) {
    Expression* Operand = (unaryexpr.Operand).get();

    Operand->accept(*this);
}

void SemanticVisitor::visitVarExpr(VarExpr& varexpr) {
    bool flag = false;

    for (int i = scopeVec.size() - 1; i >= 0; i--) {
        if (scopeVec[i].search(varexpr.Name)) {
            flag = true;
            break;
        }
    }

    if (!flag) {
        Error error;
        error.printErrorMsg("Undeclared variable: " + varexpr.Name);
    }
}

void SemanticVisitor::visitCharExpr(CharExpr& charexpr) {
    //dosomething
}

void SemanticVisitor::visitIntExpr(IntExpr& intexpr) {
    //dosomething
}
