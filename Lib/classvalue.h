#include "classmethod.h"
#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "map.h"
class ClassValue : public Value{
private:
    std::string className;
    Map* thisMap = new Map(1);
    ClassMethod* constructor = nullptr;
public:
    ClassValue(std::string className) : className(className) { type = Values::CLASS; };
    Map* getThisMap();
    void addField(std::string name, Value* value);
    void addMethod(std::string name, ClassMethod* method);
    void callConstructor(std::vector<Value*> values);
    Value* access(Value* value);
    void set(Value* key, Value* value);
    Value* get(Value* key);
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
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
