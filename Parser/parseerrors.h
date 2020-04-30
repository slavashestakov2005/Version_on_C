#ifndef PARSEERRORS_H_INCLUDED
#define PARSEERRORS_H_INCLUDED

#include "parseerror.h"
#include <vector>
class ParseErrors{
private:
    std::vector<ParseError*> errors;
public:
    ParseErrors(){}
    void clear();
    void add(std::exception* ex, int line);
    bool hasError();
    operator std::string();
};

#endif // PARSEERRORS_H_INCLUDED
