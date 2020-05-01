#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED

#include <string>
#include "bignumbers/bignum.h"

enum class Values{
    BOOL,
    NUMBER,
    STRING,
    ARRAY,
    MAP,
    NULL_,
    FUNCTION,
    CLASS,
};

class Value{
public:
    Values type;
    virtual double getDouble() = 0;
    virtual std::string getString() = 0;
    virtual bool getBool() = 0;
    virtual Bignum getBignum() = 0;
    virtual operator std::string() = 0;
    virtual ~Value(){}
    friend bool operator==(Value const& a, Value const& b);
    friend bool operator!=(Value const& a, Value const& b);
    friend bool operator<(Value const& a, Value const& b);
    friend bool operator<=(Value const& a, Value const& b);
    friend bool operator>(Value const& a, Value const& b);
    friend bool operator>=(Value const& a, Value const& b);
};

#endif // VALUE_H_INCLUDED
