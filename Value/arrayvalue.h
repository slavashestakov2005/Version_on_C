#ifndef ARRAYVALUE_H_INCLUDED
#define ARRAYVALUE_H_INCLUDED

#include <vector>
#include "container.h"
#include "value.h"

class ArrayValue : public Value, Container{
private:
    std::vector<Value*>* elements;
public:
    ArrayValue(int size);
    ArrayValue(std::vector<Value*> elem);
    ArrayValue(const ArrayValue& arra);
    std::vector<Value*> getCopyElement();
    Value* get(int index) const;
    void set(int index, Value* value);
    static ArrayValue* add(ArrayValue* array, Value* value);
    static ArrayValue* add(ArrayValue* array1, ArrayValue* array2);
    int getSize() const;
    Value* accessDot(Value* property);
    Value* accessBracket(Value* property);
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~ArrayValue();
    friend bool operator==(ArrayValue const& a, ArrayValue const& b);
    friend bool operator!=(ArrayValue const& a, ArrayValue const& b);
    friend bool operator<(ArrayValue const& a, ArrayValue const& b);
    friend bool operator<=(ArrayValue const& a, ArrayValue const& b);
    friend bool operator>(ArrayValue const& a, ArrayValue const& b);
    friend bool operator>=(ArrayValue const& a, ArrayValue const& b);
};

#endif // ARRAYVALUE_H_INCLUDED
