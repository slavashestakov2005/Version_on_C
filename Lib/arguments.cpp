#include "arguments.h"

void Arguments::addRequired(std::string name){
    arguments.push_back(Argument(name));
    ++requiredCount;
}

void Arguments::addOptional(std::string name, Expression* expression){
    arguments.push_back(Argument(name, expression));
}

void Arguments::addArrayArgument(std::string name){
    arguments.push_back(Argument(name, true));
    ++arrayCount;
}

Argument Arguments::get(int index){
    return arguments[index];
}

int Arguments::getRequiredCounter(){
    return requiredCount;
}

int Arguments::getArrayCounter(){
    return arrayCount;
}

int Arguments::getSize(){
    return arguments.size();
}
Arguments::operator std::string(){
    std::string result = "(";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(arguments[i]);
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}
