#include "mapvalue.h"
#include "../Exception/typeexception.h"
#include "../Expression/valueexpression.h"

Value* MapValue::get(Value* key){
    if (containsKey(key)) return map[key];
    else return NullValue::NULL_;
}

void MapValue::set(Value* key, Value* value){
    map[key] = value;
}

void MapValue::set(Value* key, Function* value){
    map[key] = new FunctionValue(value);
}

bool MapValue::isThisMap(){
    return thisMap;
}

void MapValue::setThisMap(bool thisMap){
    this -> thisMap = thisMap;
}

int MapValue::getSize(){
    return map.size();
}

bool MapValue::containsKey(Value* key){
    return map.find(key) != map.cend();
}

MapValue* MapValue::getCopyElement(){
    MapValue* newMap = new MapValue(1);
    for(auto now : map){
        newMap -> set(now.first, now.second);
    }
    return newMap;
}

MapValue* MapValue::add(MapValue* map1, MapValue* map2){
    MapValue* result = new MapValue(1);
    for(auto now : map1 -> map) result -> set(now.first, now.second);
    for(auto now : map2 -> map) result -> set(now.first, now.second);
    return result;
}


std::map<Value*, Value*>::iterator MapValue::iter(){
    return map.begin();
}

std::map<Value*, Value*>::iterator MapValue::end(){
    return map.end();
}

double MapValue::asDouble(){
    throw new TypeException("Cannot cast map to number");
}

std::string MapValue::asString(){
    std::string result = "{";
    int siz = map.size(), i = 0;
    for(auto now : map){
        bool str = now.first -> type() == Values::STRING;
        result += std::string(*now.first);
        result += ": ";
        str = now.second -> type() == Values::STRING;
        result += std::string(*now.second);
        if (i < siz - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

bool MapValue::asBool(){
    throw new TypeException("Cannot cast map to bool");
}

Bignum MapValue::asBignum(){
    throw new TypeException("Cannot cast map to number");
}

Values MapValue::type() const{
    return Values::MAP;
}

MapValue::operator std::string(){
    return asString();
}

bool operator==(MapValue a, MapValue b){
    if (a.getSize() != b.getSize()) return false;
    auto nowa = a.map.begin();
    auto nowb = b.map.begin();
    while(nowa != a.map.end()){
        if (nowa -> first -> type() != nowb -> first -> type()) return false;
        if (nowa -> second -> type() != nowb -> second -> type()) return false;
        if (*(nowa -> first) != *(nowb -> first)) return false;
        if (*(nowa -> second) != *(nowb -> second)) return false;
        ++nowa;
        ++nowb;
    }
    return true;
}

bool operator!=(MapValue a, MapValue b){
    return !(a == b);
}

bool operator<(MapValue a, MapValue b){
    auto nowa = a.map.begin();
    auto nowb = b.map.begin();
    while(nowa != a.map.end()){
        if (nowb == b.map.end()) return false;
        if (nowa -> first -> type() < nowb -> first -> type()) return true;
        if (nowa -> first -> type() > nowb -> first -> type()) return false;
        if (*(nowa -> first) < *(nowb -> first)) return true;
        if (*(nowa -> first) > *(nowb -> first)) return false;
        if (nowa -> second -> type() < nowb -> second -> type()) return true;
        if (nowa -> second -> type() > nowb -> second -> type()) return false;
        if (*(nowa -> second) < *(nowb -> second)) return true;
        if (*(nowa -> second) > *(nowb -> second)) return false;
        ++nowa;
        ++nowb;
    }
    if (nowb != b.map.end()) return true;
    return false;
}

bool operator<=(MapValue a, MapValue b){
    return !(a > b);
}

bool operator>(MapValue a, MapValue b){
    return b < a;
}

bool operator>=(MapValue a, MapValue b){
    return !(a < b);
}
