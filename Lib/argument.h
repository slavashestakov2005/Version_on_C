#ifndef ARGUMENT_H_INCLUDED
#define ARGUMENT_H_INCLUDED

#include "../Expression/expression.h"
class Argument{
private:
    std::string name;
    Expression* expression = nullptr;
    bool arrayArgument = false;
public:
    Argument(std::string name) : name(name), expression(nullptr) {}
    Argument(std::string name, Expression* expression) : name(name), expression(expression) {}
    Argument(std::string name, bool array) : name(name), arrayArgument(array) {}
    std::string getName();
    Expression* getExpression();
    bool isArrayArgument();
    operator std::string();
};

#endif // ARGUMENT_H_INCLUDED
