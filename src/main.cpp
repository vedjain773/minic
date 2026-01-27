#include "Scanner.hpp"

int main() {
    Scanner scanner("test/sample.c");
    scanner.scanFile();
    scanner.scanProg();
    scanner.printTokens();
    return 0;
}
