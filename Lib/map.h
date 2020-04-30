#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "value.h"
#include "function.h"
#include <map>
class Comparator{
public:
    bool operator()(Value* a, Value* b){
        return (*a) < (*b);
    }
};

class Map : public Value{
private:
    std::map<Value*, Value*, Comparator> map;
    bool thisMap = false;
public:
    Map(int size){ type = Values::MAP; }
    Value* get(Value* key);
    void set(Value* key, Value* value);
    void set(Value* key, Function* value);
    bool isThisMap();
    void setThisMap(bool thisMap);
    int getSize();
    bool containsKey(Value* key);
    Map* getCopyElement();
    static Map* add(Map* map1, Map* map2);
    std::map<Value*, Value*>::iterator iter();
    std::map<Value*, Value*>::iterator end();
    double getDouble();
    std::string getString();
    bool getBool();
    Bignum getBignum();
    operator std::string();
    ~Map(){}
    friend bool operator==(Map a, Map b);
    friend bool operator!=(Map a, Map b);
    friend bool operator<(Map a, Map b);
    friend bool operator<=(Map a, Map b);
    friend bool operator>(Map a, Map b);
    friend bool operator>=(Map a, Map b);
};

#endif // MAP_H_INCLUDED
