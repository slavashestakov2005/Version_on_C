#ifndef BIGNUMBERVALUE_H_INCLUDED
#define BIGNUMBERVALUE_H_INCLUDED

#include "value.h"
#include "bignumbers/bignum.h"

class BigNumberValue : public Value{
private:
     Bignum value;
public:
    BigNumberValue(Bignum value) : value(value) {}
    BigNumberValue(std::string value) : value(Bignum(value)) {}
    BigNumberValue(int value) : value(Bignum(value)) {}
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~BigNumberValue(){}
    friend bool operator==(BigNumberValue const& a, BigNumberValue const& b);
    friend bool operator!=(BigNumberValue const& a, BigNumberValue const& b);
    friend bool operator<(BigNumberValue const& a, BigNumberValue const& b);
    friend bool operator<=(BigNumberValue const& a, BigNumberValue const& b);
    friend bool operator>(BigNumberValue const& a, BigNumberValue const& b);
    friend bool operator>=(BigNumberValue const& a, BigNumberValue const& b);
};

#endif // BIGNUMBERVALUE_H_INCLUDED
