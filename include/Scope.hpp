#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>
#include "Token.hpp"

enum class TypeKind {
    //Types
    INT, CHAR, VOID
};

int getRank(TypeKind tk);
TypeKind TokToType(TokenType tk);

class Scope {
    public:
    std::map<std::string, TypeKind> symTable;

    void addRow(std::string name, TokenType tokentype);
    void addRow(std::string name, TypeKind type);
    bool search(std::string name);
};

#endif
