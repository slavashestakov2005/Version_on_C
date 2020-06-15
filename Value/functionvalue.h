#ifndef FUNCTIONVALUE_H_INCLUDED
#define FUNCTIONVALUE_H_INCLUDED

#include "value.h"
#include "../Lib/function.h"

class FunctionValue : public Value{
private:
    Function* value;
public:
    FunctionValue(Function* value) : value(value) {}
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
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
