#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <map>
#include <string>
#include "function.h"
/**
    @throw std::logic_error("Unknown function " + key)
**/
class Functions{
private:
    static std::map<std::string, Function*> functions;
public:
    static bool isExists(std::string key);
    static Function* get(std::string key);
    static void set(std::string key, Function* function);
    static void print();
    static void clear();
    static void start();
};

#endif // FUNCTIONS_H_INCLUDED
