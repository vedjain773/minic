#include "Token.hpp"
#include <iostream>

std::unordered_map<std::string, TokenType> keywords = {
    {"int", TokenType::INT},
    {"char", TokenType::CHAR},
    {"void", TokenType::VOID},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"return", TokenType::RETURN},
    {"struct", TokenType::STRUCT}
};

Token::Token(TokenType token_type, std::string lex, int line_num) {
    tokentype = token_type;
    lexeme = lex;
    line = line_num;
}

void Token::printToken() {
    std::cout << "Token: " << lexeme;
}
