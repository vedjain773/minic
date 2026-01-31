#include "Parser.hpp"
#include <iostream>

Parser::Parser(std::vector<Token> tokenlist) {
    TokenList = tokenlist;
    current = 0;
}

Token Parser::getNextToken() {
    if (current < TokenList.size()) {
        return TokenList[current++];
    } else {
        return TokenList[current];
    }
}

std::unique_ptr<Expression> Parser::ParseIntExpr() {
    std::cout << "Parsed an integer primary expression\n";
    std::string NumStr = TokenList[current].lexeme;
    int NumVal = std::stoi(NumStr);

    auto Result = std::make_unique<IntExpr>(NumVal);
    getNextToken();
    return std::move(Result);
}

std::unique_ptr<Expression> Parser::ParseVarExpr() {
    std::cout << "Parsed an identifier primary expression\n";
    std::string Var = TokenList[current].lexeme;

    auto Result = std::make_unique<VarExpr>(Var);
    getNextToken();
    return std::move(Result);
}

std::unique_ptr<Expression> Parser::ParseParenExpr() {
    std::cout << "Parsed an primary expression\n";
    getNextToken();

    auto Result = ParsePrimaryExpr();

    if (!Result) {
        return nullptr;
    }

    getNextToken();

    return Result;
}

std::unique_ptr<Expression> Parser::ParsePrimaryExpr() {
    switch(TokenList[current].tokentype) {
        case TokenType::INTEGER: {
            return ParseIntExpr();
        }
        break;

        case TokenType::IDENTIFIER: {
            return ParseVarExpr();
        }
        break;

        case TokenType::LEFT_ROUND: {
            return ParseParenExpr();
        }
        break;

        default: {
            return nullptr;
        }
    }
}
