#include "Program.hpp"
#include "Visitor.hpp"

void Program::accept(Visitor& visitor) {
    visitor.visitProgram(*this);

    for (int i = 0; i < root.size(); i++) {
        Statement* stmt = (root[i]).get();
        stmt->accept(visitor);
    }
}

void Program::add(std::unique_ptr<Statement> stmt) {
    root.push_back(std::move(stmt));
}

void Program::printAST() {
    PrintVisitor printvisitor;
    this->accept(printvisitor);
}
