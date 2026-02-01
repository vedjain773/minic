#include "Scanner.hpp"
#include "Parser.hpp"
#include "Visitor.hpp"

int main() {
    Scanner scanner("test/sample.c");
    scanner.scanFile();
    scanner.scanProg();

    std::vector <Token> tokenlist = scanner.getTokenList();
    Parser parser(tokenlist);

    std::unique_ptr<Expression> root = parser.ParseProgram();

    PrintVisitor printvisitor;
    root->accept(printvisitor);

    return 0;
}
