#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "value.h"

class Variables{
private:
    static std::map<std::string, Value*> variables;
    static std::vector<std::map<std::string, Value*>*> vec;
public:
    static void push();
    static void pop();
    static void clear();
    static void start();
    static bool isExists(std::string key);
    static Value* get(std::string key);
    static void set(std::string key, Value* value);
    static void print();
};

#endif // VARIABLES_H_INCLUDED
