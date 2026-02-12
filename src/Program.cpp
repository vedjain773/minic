#include "Program.hpp"
#include "StmtVisitor.hpp"

void Program::accept(ProgVisitor& progvisitor) {
    progvisitor.visitProgram(*this);
}

void Program::add(std::unique_ptr<Statement> stmt) {
    root.push_back(std::move(stmt));
}

void Program::printAST() {
    PrintStmtVisitor printSTMTvis;
    for (int i = 0; i < root.size(); i++) {
        Statement* stmt = (root[i]).get();
        stmt->accept(printSTMTvis);
    }
}
