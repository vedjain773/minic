#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>

enum class TypeKind {
    INT, CHAR
};

class Scope {
    public:
    std::map<std::string, TypeKind> symTable;

    void addRow(std::string name, TypeKind typekind);
};

#endif
