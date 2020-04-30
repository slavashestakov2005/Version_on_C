#ifndef NULL_H_INCLUDED
#define NULL_H_INCLUDED

#include "value.h"
class Null : public Value{
public:
    static Null* NULL_;
    Null(){ type = Values::NULL_; }
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    operator std::string();
    ~Null(){}
    friend bool operator==(Null const& a, Null const& b);
    friend bool operator!=(Null const& a, Null const& b);
    friend bool operator<(Null const& a, Null const& b);
    friend bool operator<=(Null const& a, Null const& b);
    friend bool operator>(Null const& a, Null const& b);
    friend bool operator>=(Null const& a, Null const& b);
};

#endif // NULL_H_INCLUDED
