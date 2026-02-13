#include "Scope.hpp"

void Scope::addRow(std::string name, TokenType tokentype) {
    switch(tokentype) {
        case TokenType::INT: {
            symTable.insert({name, TypeKind::INT});
        }
        break;

        case TokenType::CHAR: {
            symTable.insert({name, TypeKind::CHAR});
        }
        break;
    }
}

bool Scope::search(std::string name) {
    return symTable.count(name);
}
