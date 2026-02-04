#include "Parser.hpp"
#include "Visitor.hpp"
#include <iostream>

Parser::Parser(std::vector<Token> tokenlist) {
    TokenList = tokenlist;
    current = 0;
}

Token Parser::getNextToken() {
    if (current < TokenList.size()) {
        return TokenList[current++];
    } else {
        return Token(TokenType::END_OF_FILE, "", 1);
    }
}

Token Parser::peekCurr() {
    return TokenList[current];
}

Token Parser::peekNext() {
    return TokenList[current+1];
}

std::unique_ptr<Expression> Parser::ParseIntExpr() {
    std::string NumStr = peekCurr().lexeme;
    int NumVal = std::stoi(NumStr);

    auto Result = std::make_unique<IntExpr>(NumVal);
    getNextToken();
    return std::move(Result);
}

std::unique_ptr<Expression> Parser::ParseVarExpr() {
    std::string Var = peekCurr().lexeme;

    auto Result = std::make_unique<VarExpr>(Var);
    getNextToken();
    return std::move(Result);
}

std::unique_ptr<Expression> Parser::ParseParenExpr() {
    getNextToken();

    auto Result = ParsePrimaryExpr();

    if (!Result) {
        return nullptr;
    }

    getNextToken();

    return Result;
}

std::unique_ptr<Expression> Parser::ParsePrimaryExpr() {
    switch(peekCurr().tokentype) {
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

std::unique_ptr<Expression> Parser::ParseUnaryExpr() {
    switch(peekCurr().tokentype) {
        case TokenType::BANG:
        case TokenType::MINUS: {
            Operators oper = getOp(peekCurr().lexeme);
            getNextToken();

            if (peekCurr().tokentype == TokenType::BANG || peekCurr().tokentype == TokenType::MINUS) {
                auto Result = std::make_unique<UnaryExpr>(oper, ParseUnaryExpr());
                return Result;
            } else {
                auto Result = std::make_unique<UnaryExpr>(oper, ParsePrimaryExpr());
                return Result;
            }
        }
        break;

        default: {
            return ParsePrimaryExpr();
        }
    }
}

std::unique_ptr<Expression> Parser::ParseFactorExpr() {
    auto lhs = std::move(ParseUnaryExpr());

    while (peekCurr().tokentype == TokenType::SLASH || peekCurr().tokentype == TokenType::ASTERISK) {
        Operators oper = getOp(peekCurr().lexeme);
        getNextToken();
        auto rhs = std::move(ParseUnaryExpr());
        lhs = std::make_unique<BinaryExpr>(oper, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Expression> Parser::ParseTermExpr() {
    auto lhs = std::move(ParseFactorExpr());

    while (peekCurr().tokentype == TokenType::MINUS || peekCurr().tokentype == TokenType::PLUS) {
        Operators oper = getOp(peekCurr().lexeme);
        getNextToken();
        auto rhs = std::move(ParseFactorExpr());
        lhs = std::make_unique<BinaryExpr>(oper, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Expression> Parser::ParseCompExpr() {
    auto lhs = std::move(ParseTermExpr());

    while (peekCurr().tokentype == TokenType::GREATER_THAN ||
            peekCurr().tokentype == TokenType::GREATER_EQUALS ||
            peekCurr().tokentype == TokenType::LESS_EQUALS ||
            peekCurr().tokentype == TokenType::LESS_THAN) {

        Operators oper = getOp(peekCurr().lexeme);
        getNextToken();
        auto rhs = std::move(ParseTermExpr());
        lhs = std::make_unique<BinaryExpr>(oper, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Expression> Parser::ParseEqualityExpr() {
    auto lhs = std::move(ParseCompExpr());

    while (peekCurr().tokentype == TokenType::BANG_EQUALS || peekCurr().tokentype == TokenType::EQUALS_EQUALS) {

        Operators oper = getOp(peekCurr().lexeme);
        getNextToken();
        auto rhs = std::move(ParseCompExpr());
        lhs = std::make_unique<BinaryExpr>(oper, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Expression> Parser::ParseLAndExpr() {
    auto lhs = std::move(ParseEqualityExpr());

    while (peekCurr().tokentype == TokenType::AND) {

        Operators oper = getOp(peekCurr().lexeme);
        getNextToken();
        auto rhs = std::move(ParseEqualityExpr());
        lhs = std::make_unique<BinaryExpr>(oper, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Expression> Parser::ParseLOrExpr() {
    auto lhs = std::move(ParseLAndExpr());

    while (peekCurr().tokentype == TokenType::OR) {
        Operators oper = getOp(peekCurr().lexeme);
        getNextToken();
        auto rhs = std::move(ParseLAndExpr());
        lhs = std::make_unique<BinaryExpr>(oper, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Expression> Parser::ParseAssignExpr() {
    auto lhs = std::move(ParseLOrExpr());


    if (peekCurr().tokentype == TokenType::EQUALS) {
        getNextToken();
        auto rhs = std::move(ParseAssignExpr());

        auto Result = std::make_unique<AssignExpr>(std::move(lhs), std::move(rhs));
        return Result;
    } else {
        return lhs;
    }
}


std::unique_ptr<Expression> Parser::ParseExpr() {
    return ParseAssignExpr();
}

void Parser::ParseProgram() {
    PrintVisitor printvisitor;
    while (true) {
        switch(peekCurr().tokentype) {
            case TokenType::SEMICOLON: {
                getNextToken();
            }
            break;

            case TokenType::END_OF_FILE: {
                return;
            }
            break;

            default: {
                std::unique_ptr<Expression> exp = std::move(ParseExpr());
                exp->accept(printvisitor);
            }
        }
    }
}
