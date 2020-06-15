#ifndef NULLVALUE_H_INCLUDED
#define NULLVALUE_H_INCLUDED

#include "value.h"

class NullValue : public Value{
public:
    static NullValue* NULL_;
    NullValue(){}
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~NullValue(){}
    friend bool operator==(NullValue const& a, NullValue const& b);
    friend bool operator!=(NullValue const& a, NullValue const& b);
    friend bool operator<(NullValue const& a, NullValue const& b);
    friend bool operator<=(NullValue const& a, NullValue const& b);
    friend bool operator>(NullValue const& a, NullValue const& b);
    friend bool operator>=(NullValue const& a, NullValue const& b);
};

#endif // NULLVALUE_H_INCLUDED
