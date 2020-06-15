#ifndef MAPVALUE_H_INCLUDED
#define MAPVALUE_H_INCLUDED

#include <map>
#include "value.h"
#include "../Lib/function.h"

class Comparator{
public:
    bool operator()(Value* a, Value* b){
        return (*a) < (*b);
    }
};

class MapValue : public Value{
private:
    std::map<Value*, Value*, Comparator> map;
    bool thisMap = false;
public:
    MapValue(int size){}
    Value* get(Value* key);
    void set(Value* key, Value* value);
    void set(Value* key, Function* value);
    bool isThisMap();
    void setThisMap(bool thisMap);
    int getSize();
    bool containsKey(Value* key);
    MapValue* getCopyElement();
    static MapValue* add(MapValue* map1, MapValue* map2);
    std::map<Value*, Value*>::iterator iter();
    std::map<Value*, Value*>::iterator end();
    double asDouble();
    std::string asString();
    bool asBool();
    Bignum asBignum();
    Values type() const;
    operator std::string();
    ~MapValue(){}
    friend bool operator==(MapValue a, MapValue b);
    friend bool operator!=(MapValue a, MapValue b);
    friend bool operator<(MapValue a, MapValue b);
    friend bool operator<=(MapValue a, MapValue b);
    friend bool operator>(MapValue a, MapValue b);
    friend bool operator>=(MapValue a, MapValue b);
};

#endif // MAPVALUE_H_INCLUDED
