#ifndef STRINGVALUE_H_INCLUDED
#define STRINGVALUE_H_INCLUDED

#include "container.h"
#include "value.h"

class StringValue : public Value, Container{
private:
    std::string value;
public:
    StringValue(std::string value) : value(value) {}
    int getSize();
    void set(int index, Value* val);
    Value* accessDot(Value* property);
    Value* accessBracket(Value* property);
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~StringValue(){}
    friend bool operator==(StringValue const& a, StringValue const& b);
    friend bool operator!=(StringValue const& a, StringValue const& b);
    friend bool operator<(StringValue const& a, StringValue const& b);
    friend bool operator<=(StringValue const& a, StringValue const& b);
    friend bool operator>(StringValue const& a, StringValue const& b);
    friend bool operator>=(StringValue const& a, StringValue const& b);
};

#endif // STRINGVALUE_H_INCLUDED
