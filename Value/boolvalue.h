#ifndef BOOLVALUE_H_INCLUDED
#define BOOLVALUE_H_INCLUDED

#include "value.h"

class BoolValue : public Value{
private:
    bool value;
public:
    static BoolValue *TRUE_, *FALSE_;
    BoolValue(bool value) : value(value) {}
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~BoolValue(){}
    friend bool operator==(BoolValue const& a, BoolValue const& b);
    friend bool operator!=(BoolValue const& a, BoolValue const& b);
    friend bool operator<(BoolValue const& a, BoolValue const& b);
    friend bool operator<=(BoolValue const& a, BoolValue const& b);
    friend bool operator>(BoolValue const& a, BoolValue const& b);
    friend bool operator>=(BoolValue const& a, BoolValue const& b);
};

#endif // BOOLVALUE_H_INCLUDED
