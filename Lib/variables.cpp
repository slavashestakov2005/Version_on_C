#include "variables.h"
#include "bignumber.h"
#include "bool.h"
#include "null.h"
#include "../Modules/global.h"
#include <iostream>
std::map<std::string, Value*> Variables::variables = {};

std::vector<std::map<std::string, Value*>*> Variables::vec = {};

void Variables::push(){
    std::map<std::string, Value*>* cop = new std::map<std::string, Value*>(variables);
    vec.push_back(cop);
}

void Variables::pop(){
    variables = *(vec.back());
    vec.pop_back();
}

void Variables::clear(){
    variables.clear();
    vec.clear();
}

void Variables::start(){
    variables.clear();
    vec.clear();
    Global::initVariables();
}

bool Variables::isExists(std::string key){
    return variables.find(key) != variables.cend();
}

Value* Variables::get(std::string key){
    std::cout << "Vars.get " << key << " is ? " << isExists(key) << std::endl;
    if (!isExists(key)) return new Null();
    else return variables[key];
}

void Variables::set(std::string key, Value* value){
    variables[key] = value;
}

void Variables::print(){
    for (auto now : variables) std::cout << now.first << "\t\t" << std::string(*now.second) << std::endl;
}
