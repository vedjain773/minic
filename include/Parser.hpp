#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.hpp"
#include "Expression.hpp"

class Parser {
    public:
    std::vector<Token> TokenList;
    int current;

    Parser(std::vector<Token> tokenlist);
    Token getNextToken();
    Token peekCurr();
    Token peekNext();

    std::unique_ptr<Expression> ParsePrimaryExpr();
    std::unique_ptr<Expression> ParseIntExpr();
    std::unique_ptr<Expression> ParseVarExpr();
    std::unique_ptr<Expression> ParseParenExpr();

    std::unique_ptr<Expression> ParseUnaryExpr();

    std::unique_ptr<Expression> ParseFactorExpr();

    std::unique_ptr<Expression> ParseTermExpr();

    std::unique_ptr<Expression> ParseCompExpr();

    std::unique_ptr<Expression> ParseExpr();

    void ParseProgram();
};

#endif
