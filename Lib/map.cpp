#include "map.h"
#include "../Exception/typeexception.h"
#include "../Expression/valueexpression.h"

Value* Map::get(Value* key){
    if (containsKey(key)) return map[key];
    else return Null::NULL_;
}

void Map::set(Value* key, Value* value){
    map[key] = value;
}

void Map::set(Value* key, Function* value){
    map[key] = new FunctionValue(value);
}

bool Map::isThisMap(){
    return thisMap;
}

void Map::setThisMap(bool thisMap){
    this -> thisMap = thisMap;
}

int Map::getSize(){
    return map.size();
}

bool Map::containsKey(Value* key){
    return map.find(key) != map.cend();
}

Map* Map::getCopyElement(){
    Map* newMap = new Map(1);
    for(auto now : map){
        newMap -> set(now.first, now.second);
    }
    return newMap;
}

Map* Map::add(Map* map1, Map* map2){
    Map* result = new Map(1);
    for(auto now : map1 -> map) result -> set(now.first, now.second);
    for(auto now : map2 -> map) result -> set(now.first, now.second);
    return result;
}


std::map<Value*, Value*>::iterator Map::iter(){
    return map.begin();
}

std::map<Value*, Value*>::iterator Map::end(){
    return map.end();
}

double Map::getDouble(){
    throw new TypeException("Cannot cast map to number");
}

std::string Map::getString(){
    std::string result = "{";
    int siz = map.size(), i = 0;
    for(auto now : map){
        bool str = now.first -> type == Values::STRING;
        result += std::string(*now.first);
        result += ": ";
        str = now.second -> type == Values::STRING;
        result += std::string(*now.second);
        if (i < siz - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

bool Map::getBool(){
    throw new TypeException("Cannot cast map to bool");
}

Bignum Map::getBignum(){
    throw new TypeException("Cannot cast map to number");
}

Map::operator std::string(){
    return getString();
}

bool operator==(Map a, Map b){
    if (a.getSize() != b.getSize()) return false;
    auto nowa = a.map.begin();
    auto nowb = b.map.begin();
    while(nowa != a.map.end()){
        if (nowa -> first -> type != nowb -> first -> type) return false;
        if (nowa -> second -> type != nowb -> second -> type) return false;
        if (*(nowa -> first) != *(nowb -> first)) return false;
        if (*(nowa -> second) != *(nowb -> second)) return false;
        ++nowa;
        ++nowb;
    }
    return true;
}

bool operator!=(Map a, Map b){
    return !(a == b);
}

bool operator<(Map a, Map b){
    auto nowa = a.map.begin();
    auto nowb = b.map.begin();
    while(nowa != a.map.end()){
        if (nowb == b.map.end()) return false;
        if (nowa -> first -> type < nowb -> first -> type) return true;
        if (nowa -> first -> type > nowb -> first -> type) return false;
        if (*(nowa -> first) < *(nowb -> first)) return true;
        if (*(nowa -> first) > *(nowb -> first)) return false;
        if (nowa -> second -> type < nowb -> second -> type) return true;
        if (nowa -> second -> type > nowb -> second -> type) return false;
        if (*(nowa -> second) < *(nowb -> second)) return true;
        if (*(nowa -> second) > *(nowb -> second)) return false;
        ++nowa;
        ++nowb;
    }
    if (nowb != b.map.end()) return true;
    return false;
}

bool operator<=(Map a, Map b){
    return !(a > b);
}

bool operator>(Map a, Map b){
    return b < a;
}

bool operator>=(Map a, Map b){
    return !(a < b);
}
