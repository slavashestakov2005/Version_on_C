#ifndef BOOL_H_INCLUDED
#define BOOL_H_INCLUDED

#include "value.h"
class Bool : public Value{
private:
    bool value;
public:
    static Bool* TRUE_, *FALSE_;
    Bool(bool value) : value(value) { type = Values::BOOL; }
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    operator std::string();
    ~Bool(){}
    friend bool operator==(Bool const& a, Bool const& b);
    friend bool operator!=(Bool const& a, Bool const& b);
    friend bool operator<(Bool const& a, Bool const& b);
    friend bool operator<=(Bool const& a, Bool const& b);
    friend bool operator>(Bool const& a, Bool const& b);
    friend bool operator>=(Bool const& a, Bool const& b);
};

#endif // BOOL_H_INCLUDED
