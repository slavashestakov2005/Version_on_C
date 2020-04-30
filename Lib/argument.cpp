#include "argument.h"

std::string Argument::getName(){
    return name;
}

Expression* Argument::getExpression(){
    return expression;
}

bool Argument::isArrayArgument(){
    return arrayArgument;
}

Argument::operator std::string(){
    return (arrayArgument ? "*" : "") + name + (expression == nullptr ? "" : " = " + std::string(*expression));
}
