#ifndef FUNCTION_H
#define FUNCTION_H

#include "Scope.hpp"
#include "ExternalDecl.hpp"
#include "Statement.hpp"
#include "Token.hpp"
#include "Visitor.hpp"

class Parameter {
    public:
    TypeKind type;
    std::string name;

    Parameter(TokenType p_type, std::string p_name);
    void accept(Visitor& visitor);
};

class Prototype {
    public:
    TypeKind retType;
    std::string funcName;
    int line;
    int column;
    std::vector<std::unique_ptr<Parameter>> paramList;

    Prototype(TokenType ret_type, std::string func_name, int line, int column);
    void addParam(std::unique_ptr<Parameter> param);
    void accept(Visitor& visitor);
};

class FuncDef: public ExternalDecl {
    public:
    std::unique_ptr<Prototype> prototype;
    std::unique_ptr<Statement> funcBody;

    FuncDef(std::unique_ptr<Prototype> proto_type, std::unique_ptr<Statement> func_body);
    void accept(Visitor& visitor);
};

#endif
