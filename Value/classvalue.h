#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "mapvalue.h"
#include "../Lib/classmethod.h"

class ClassValue : public Value{
private:
    std::string className;
    MapValue* thisMap = new MapValue(1);
    ClassMethod* constructor = nullptr;
public:
    ClassValue(std::string className);
    MapValue* getThisMap();
    void addField(std::string name, Value* value);
    void addMethod(std::string name, ClassMethod* method);
    void callConstructor(std::vector<Value*> values);
    Value* access(Value* value);
    void set(Value* key, Value* value);
    Value* get(Value* key);
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~ClassValue();
    friend bool operator==(ClassValue const& a, ClassValue const& b);
    friend bool operator!=(ClassValue const& a, ClassValue const& b);
    friend bool operator<(ClassValue const& a, ClassValue const& b);
    friend bool operator<=(ClassValue const& a, ClassValue const& b);
    friend bool operator>(ClassValue const& a, ClassValue const& b);
    friend bool operator>=(ClassValue const& a, ClassValue const& b);
};

#endif // CLASSVALUE_H_INCLUDED
