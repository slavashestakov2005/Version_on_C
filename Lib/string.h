#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include "value.h"
class String : public Value{
private:
    std::string value;
public:
    String(std::string value) : value(value) { type = Values::STRING; }
    int getSize();
    Value* access(Value* property);
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    operator std::string();
    ~String(){}
    friend bool operator==(String const& a, String const& b);
    friend bool operator!=(String const& a, String const& b);
    friend bool operator<(String const& a, String const& b);
    friend bool operator<=(String const& a, String const& b);
    friend bool operator>(String const& a, String const& b);
    friend bool operator>=(String const& a, String const& b);
};

#endif // STRING_H_INCLUDED
