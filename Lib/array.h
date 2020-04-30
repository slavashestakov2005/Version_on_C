#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "value.h"
#include <vector>
/**
    @throw std::logic_error("Cannot cast array to number")
**/
class Array : public Value{
private:
    std::vector<Value*>* elements;
public:
    Array(int size);
    Array(std::vector<Value*> elem);
    Array(const Array& arra);
    std::vector<Value*> getCopyElement();
    Value* get(int index) const;
    void set(int index, Value* value);
    static Array* add(Array* array, Value* value);
    static Array* add(Array* array1, Array* array2);
    int getSize() const;
    Value* access(Value* property);
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    operator std::string();
    ~Array();
    friend bool operator==(Array const& a, Array const& b);
    friend bool operator!=(Array const& a, Array const& b);
    friend bool operator<(Array const& a, Array const& b);
    friend bool operator<=(Array const& a, Array const& b);
    friend bool operator>(Array const& a, Array const& b);
    friend bool operator>=(Array const& a, Array const& b);
};

#endif // ARRAY_H_INCLUDED
