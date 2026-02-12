#include "Program.hpp"
#include "Visitor.hpp"

void Program::accept(Visitor& visitor) {
    visitor.visitProgram(*this);
}

void Program::add(std::unique_ptr<Statement> stmt) {
    root.push_back(std::move(stmt));
}

void Program::printAST() {
    PrintVisitor printvisitor;
    this->accept(printvisitor);
}
