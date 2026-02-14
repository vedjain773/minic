#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>
#include "Token.hpp"

enum class TypeKind {
    //Types
    INT, CHAR, VOID
};

class Scope {
    public:
    std::map<std::string, TypeKind> symTable;

    void addRow(std::string name, TokenType tokentype);
    bool search(std::string name);
};

#endif
