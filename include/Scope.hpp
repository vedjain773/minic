#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>
#include <vector>
#include "Token.hpp"

enum class SymbolKind {
    VARIABLE,
    FUNCTION
};

enum class TypeKind {
    //Types
    INT, CHAR, VOID
};

struct Symbol {
    SymbolKind kind;
    TypeKind type;

    std::vector<TypeKind> params;
};

int getRank(TypeKind tk);
TypeKind TokToType(TokenType tk);

class Scope {
    public:
    std::map<std::string, Symbol> symTable;

    void addRow(std::string name, TokenType tokentype, SymbolKind symKind);
    void addRow(std::string name, TypeKind type, SymbolKind symKind);
    bool search(std::string name);
};

#endif
