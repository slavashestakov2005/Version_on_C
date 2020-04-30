#ifndef USERDEFINEDFUNCTION_H_INCLUDED
#define USERDEFINEDFUNCTION_H_INCLUDED

#include "function.h"
#include "../Statement/statement.h"
#include "arguments.h"
class UserDefinedFunction : public Function{
protected:
    Statement* body;
public:
    Arguments arguments;
    UserDefinedFunction(Arguments arguments, Statement* body) : arguments(arguments), body(body) { type = true; }
    int getArgsCount();
    std::string getArgsName(int index);
    operator std::string();
    Value* execute(std::vector<Value*> values);
};

#endif // USERDEFINEDFUNCTION_H_INCLUDED
