#include "Scope.hpp"

void Scope::addRow(std::string name, TypeKind typekind) {
    symTable.insert({name, typekind});
}
