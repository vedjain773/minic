#ifndef PROGRAM_H
#define PROGRAM_H

#include "Visitor.hpp"
#include "Statement.hpp"
#include <memory>
#include <vector>

class Program {
    public:
    std::vector<std::unique_ptr<Statement>> root;

    void accept(Visitor& visitor);
    void add(std::unique_ptr<Statement> stmt);
    void printAST();
    void semAnalyse();
};

#endif
