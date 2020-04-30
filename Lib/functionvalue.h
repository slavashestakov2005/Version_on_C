#ifndef FUNCTIONVALUE_H_INCLUDED
#define FUNCTIONVALUE_H_INCLUDED

#include "value.h"
#include "function.h"
class FunctionValue : public Value{
private:
    Function* value;
public:
    FunctionValue(Function* value) : value(value) { type = Values::FUNCTION; }
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    Function* getFunction();
    operator std::string();
    ~FunctionValue();
    friend bool operator==(FunctionValue const& a, FunctionValue const& b);
    friend bool operator!=(FunctionValue const& a, FunctionValue const& b);
    friend bool operator<(FunctionValue const& a, FunctionValue const& b);
    friend bool operator<=(FunctionValue const& a, FunctionValue const& b);
    friend bool operator>(FunctionValue const& a, FunctionValue const& b);
    friend bool operator>=(FunctionValue const& a, FunctionValue const& b);
};

#endif // FUNCTIONVALUE_H_INCLUDED
