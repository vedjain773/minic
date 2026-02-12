#ifndef PROGRAM_H
#define PROGRAM_H

#include "Statement.hpp"
#include <memory>
#include <vector>

class Program {
    public:
    std::vector<std::unique_ptr<Statement>> root;

    void add(std::unique_ptr<Statement> stmt);
    void printAST();
};

#endif
