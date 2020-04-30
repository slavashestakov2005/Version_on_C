#include "functions.h"
#include "function.h"
#include "../Exception/unknownfunctionexception.h"
#include "string.h"
#include "../Modules/global.h"
#include <iostream>

std::map<std::string, Function*> Functions::functions = {};

bool Functions::isExists(std::string key){
    return functions.find(key) != functions.cend();
}

Function* Functions::get(std::string key){
    if (!isExists(key)) throw new UnknownFunctionException(key);
    else return functions[key];
}

void Functions::set(std::string key, Function* function){
    functions[key] = function;
}

void Functions::print(){
    for (auto now : functions) std::cout << now.first << "\t\t" << now.second -> type << std::endl;
}

void Functions::clear(){
    functions.clear();
}

void Functions::start(){
    functions.clear();
    Global::initFunction();
}
