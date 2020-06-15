#ifndef ARGUMENTS_H_INCLUDED
#define ARGUMENTS_H_INCLUDED

#include <vector>
#include "argument.h"

class Arguments{
private:
    std::vector<Argument> arguments;
    int requiredCount = 0;
    int arrayCount = 0;
public:
    Arguments(){}
    void addRequired(std::string name);
    void addOptional(std::string name, Expression* expression);
    void addArrayArgument(std::string name);
    Argument get(int index);
    int getRequiredCounter();
    int getArrayCounter();
    int getSize();
    operator std::string();
};

#endif // ARGUMENTS_H_INCLUDED
