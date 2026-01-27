#include "Error.hpp"
#include <iostream>

Error::Error(ErrorType error_type, int line_num, int ind) {
    errorType = error_type;
    line = line_num;
    index = ind;
}

void Error::printErrorMsg(std::string source, std::string sourceContent) {
    switch (errorType) {
        case ErrorType::UNEXPECTED_CHAR: {
            std::cout << "Unexpected character: " << sourceContent[index] << "\n";
        }
        break;

        case ErrorType::NO_TERM_CHAR_MULT: {
            std::cout << "No matching */ found " << "\n";
        }
        break;
    }

    std::cout << "--> " << source << " " << line << ":" << index << "\n";
}
