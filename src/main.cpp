#include "Scanner.hpp"
#include "Parser.hpp"

int main() {
    Scanner scanner("test/sample.c");
    scanner.scanFile();
    scanner.scanProg();
    scanner.printTokens();

    std::vector <Token> tokenlist = scanner.getTokenList();
    Parser parser(tokenlist);

    parser.ParsePrimaryExpr();
    return 0;
}
