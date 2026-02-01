#include "Scanner.hpp"
#include <iostream>
#include <fstream>

Scanner::Scanner(std::string source_arg) {
    source = source_arg;
}

void Scanner::scanFile() {
    std::ifstream file(source);

    std::string text;

    while (getline (file, text)) {
        sourceContent = sourceContent + text + '\n';
    }

    file.close();
}

void Scanner::scanToken() {
    // std::cout << current << "\n";
    char curr = sourceContent[current++];
    column++;
    switch (curr) {
        case '{': {
            addToken(TokenType::LEFT_CURLY);
        }
        break;

        case '}': {
            addToken(TokenType::RIGHT_CURLY);
        }
        break;

        case '(': {
            addToken(TokenType::LEFT_ROUND);
        }
        break;

        case ')': {
            addToken(TokenType::RIGHT_ROUND);
        }
        break;

        case '[': {
            addToken(TokenType::LEFT_SQUARE);
        }
        break;

        case ']': {
            addToken(TokenType::RIGHT_SQUARE);
        }
        break;

        case ',': {
            addToken(TokenType::COMMA);
        }
        break;

        case ';': {
            addToken(TokenType::SEMICOLON);
        }
        break;

        case '+': {
            addToken(TokenType::PLUS);
        }
        break;

        case '-': {
            addToken(TokenType::MINUS);
        }
        break;

        case '*': {
            addToken(TokenType::ASTERISK);
        }
        break;

        case '%': {
            addToken(TokenType::MODULUS);
        }
        break;

        case '=': {
            if (sourceContent[current] == '=') {
                addToken(TokenType::EQUALS_EQUALS);
                current++;
            } else {
                addToken(TokenType::EQUALS);
            }
        }
        break;

        case '<': {
            if (sourceContent[current] == '=') {
                current++;
                addToken(TokenType::LESS_EQUALS);
            } else {
                addToken(TokenType::LESS_THAN);
            }
        }
        break;

        case '>': {
            if (sourceContent[current] == '=') {
                current++;
                addToken(TokenType::GREATER_EQUALS);
            } else {
                addToken(TokenType::GREATER_THAN);
            }
        }
        break;

        case '!': {
            if (sourceContent[current] == '=') {
                current++;
                addToken(TokenType::BANG_EQUALS);
            } else {
                addToken(TokenType::BANG);
            }
        }
        break;

        case '&': {
            if (sourceContent[current] == '&') {
                current++;
                addToken(TokenType::AND);
            } else {
                addToken(TokenType::AMPERSAND);
            }
        }
        break;

        case '|': {
            if (sourceContent[current] == '|') {
                current++;
                addToken(TokenType::OR);
            } else {
                Error error(ErrorType::UNEXPECTED_CHAR, line, current, column);
                error.printErrorMsg(source, sourceContent);
            }
        }
        break;

        case '/': {
            if (sourceContent[current] == '/') {
                lookAhead('\n');
            } else if (sourceContent[current] == '*') {
                bool asterisk = lookAhead('*');

                if (!asterisk) {
                    Error error(ErrorType::NO_TERM_CHAR_MULT, line, current, column);
                    error.printErrorMsg(source, sourceContent);
                }

                if (sourceContent[current] == '/') {
                    current++;
                } else {
                    Error error(ErrorType::NO_TERM_CHAR_MULT, line, current, column);
                    error.printErrorMsg(source, sourceContent);
                }

            } else {
                addToken(TokenType::SLASH);
            }
        }
        break;

        case '"': {
            bool termInvComma = lookAhead('"');

            if (termInvComma) {
                addToken(TokenType::STRING);
            } else {
                Error error(ErrorType::UNEXPECTED_CHAR, line, current, column);
                error.printErrorMsg(source, sourceContent);
            }
        }

        case ' ': {
            //ignore
        }

        case '\r': {
            //ignore
        }

        case '\t': {
            //ignore
        }
        break;

        case '\n': {
            line++;
            column = 1;
        }
        break;

        default: {
            if (isDigit(curr)) {
                scanNumber();
            } else if (isAlpha(curr)) {
                scanWord();
            } else {
                Error error(ErrorType::UNEXPECTED_CHAR, line, current, column);
                error.printErrorMsg(source, sourceContent);
            }
        }
    }
}

void Scanner::scanProg() {
    while (current < sourceContent.size()) {
        start = current;
        scanToken();
    }

    Token token = Token(TokenType::END_OF_FILE, "", line);
    tokenList.push_back(token);
}

void Scanner::printTokens() {
    for (Token token: tokenList) {
        token.printToken();
        std::cout << "\n";
    }
}

void Scanner::addToken(TokenType tokenType) {
    std::string lex = sourceContent.substr(start, current - start);
    Token token = Token(tokenType, lex, line);
    tokenList.push_back(token);
}

bool Scanner::lookAhead(char expEnd) {
    bool isPresent = false;

    while (current < sourceContent.size()) {

        if (sourceContent[current] == '\n') {
            line++;
            column = 1;
        }

        ++current;
        if (sourceContent[current] == expEnd) {
            isPresent = true;
            current++;
            column++;
            break;
        }
    }

    return isPresent;
}

bool Scanner::isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    } else {
        return false;
    }
}

bool Scanner::isAlpha(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
        return true;
    } else {
        return false;
    }
}

void Scanner::scanNumber() {
    while(isDigit(sourceContent[current])) {
        current++;
    }

    addToken(TokenType::INTEGER);
}

void Scanner::scanWord() {
    while(isAlpha(sourceContent[current]) || isDigit(sourceContent[current])) {
        current++;
    }

    std::string sub = sourceContent.substr(start, current);

    auto it = keywords.find(sub);

    if (it != keywords.end()) {
        addToken(keywords[sub]);
    } else {
        addToken(TokenType::IDENTIFIER);
    }

}

std::vector<Token> Scanner::getTokenList() {
    return tokenList;
}
