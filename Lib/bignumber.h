#ifndef BIGNUMBER_H_INCLUDED
#define BIGNUMBER_H_INCLUDED

#include "value.h"
#include "bignumbers/bignum.h"
class BigNumber : public Value{
private:
     Bignum value;
public:
    BigNumber(Bignum value) : value(value) { type = Values::NUMBER; }
    BigNumber(std::string value) : value(Bignum(value)) { type = Values::NUMBER; }
    BigNumber(int value) : value(Bignum(value)) { type = Values::NUMBER; }
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    operator std::string();
    ~BigNumber(){}
    friend bool operator==(BigNumber const& a, BigNumber const& b);
    friend bool operator!=(BigNumber const& a, BigNumber const& b);
    friend bool operator<(BigNumber const& a, BigNumber const& b);
    friend bool operator<=(BigNumber const& a, BigNumber const& b);
    friend bool operator>(BigNumber const& a, BigNumber const& b);
    friend bool operator>=(BigNumber const& a, BigNumber const& b);
};

#endif // BIGNUMBER_H_INCLUDED
