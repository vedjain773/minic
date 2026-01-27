#ifndef ERROR_H
#define ERROR_H

#include <string>

enum class ErrorType {
    UNEXPECTED_CHAR,
    NO_TERM_CHAR_MULT
};

class Error {
    private:
    ErrorType errorType;
    int line;
    int index;

    public:
    Error(ErrorType error_type, int line_num, int ind);

    void printErrorMsg(std::string source, std::string sourceContent);
};

#endif
