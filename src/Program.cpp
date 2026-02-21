#include "Program.hpp"
#include "Visitor.hpp"

void Program::accept(Visitor& visitor) {
    visitor.visitProgram(*this);
}

void Program::add(std::unique_ptr<ExternalDecl> edecl) {
    root.push_back(std::move(edecl));
}

void Program::printAST() {
    PrintVisitor printvisitor;
    this->accept(printvisitor);
}

void Program::semAnalyse() {
    SemanticVisitor semvisitor;
    this->accept(semvisitor);
}
