#include "Scope.hpp"

int getRank(TypeKind tk)  {
    switch (tk) {
        case TypeKind::INT: {
            return 2;
        }
        break;

        case TypeKind::CHAR: {
            return 1;
        }
        break;

        default: {
            return 0;
        }
    }
}

TypeKind TokToType(TokenType tk) {
    switch (tk) {
        case TokenType::INT: {
            return TypeKind::INT;
        }
        break;

        case TokenType::CHAR: {
            return TypeKind::CHAR;
        }
        break;

        default: {
            return TypeKind::VOID;
        }
    }
}

void Scope::addRow(std::string name, TokenType tokentype, SymbolKind symKind) {
    Symbol symbol;
    symbol.type = TokToType(tokentype);
    symbol.kind = symKind;

    symTable.insert({name, symbol});
}

void Scope::addRow(std::string name, TypeKind type, SymbolKind symKind) {
    Symbol symbol;
    symbol.type = type;
    symbol.kind = symKind;

    symTable.insert({name, symbol});
}

bool Scope::search(std::string name) {
    return symTable.count(name);
}
