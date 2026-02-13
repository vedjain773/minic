#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
    private:
    int line;
    int column;

    public:
    Error();
    Error(int line_num, int col_num);

    void printErrorMsg(std::string message);
};

#endif
