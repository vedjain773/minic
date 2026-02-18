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

void Scope::addRow(std::string name, TokenType tokentype) {
    symTable.insert({name, TokToType(tokentype)});
}

bool Scope::search(std::string name) {
    return symTable.count(name);
}
