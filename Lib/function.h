#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <vector>
#include "../Value/value.h"

class Function{
public:
    bool type = false;
    virtual Value* execute(std::vector<Value*>) = 0;
    virtual operator std::string(){ return "Function from module\n"; }
};

#endif // FUNCTION_H_INCLUDED
