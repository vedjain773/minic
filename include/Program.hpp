#ifndef PROGRAM_H
#define PROGRAM_H

#include "ProgVisitor.hpp"
#include "Statement.hpp"
#include <memory>
#include <vector>

class Program {
    public:
    std::vector<std::unique_ptr<Statement>> root;

    void accept(ProgVisitor& progvisitor);
    void add(std::unique_ptr<Statement> stmt);
    void printAST();
};

#endif
