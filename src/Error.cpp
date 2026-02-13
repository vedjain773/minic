#include "Error.hpp"
#include <iostream>

Error::Error() {
    line = 0;
    column = 0;
}

Error::Error(int line_num, int col_num) {
    line = line_num;
    column = col_num;
}

void Error::printErrorMsg(std::string message) {
    std::cout << message << "\n";
    std::cout << "--> " << line << ":" << column << "\n";
}
