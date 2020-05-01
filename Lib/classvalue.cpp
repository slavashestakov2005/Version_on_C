#include "classvalue.h"
#include "string.h"
#include "../Exception/typeexception.h"

ClassValue::ClassValue(std::string className) : className(className){
    type = Values::CLASS;
    thisMap -> setThisMap(true);
};

Map* ClassValue::getThisMap(){
    return thisMap;
}

void ClassValue::addField(std::string name, Value* value){
    thisMap -> set(new String(name), value);
}

void ClassValue::addMethod(std::string name, ClassMethod* method){
    thisMap -> set(new String(name), method);
    if (name == className) constructor = method;
}

void ClassValue::callConstructor(std::vector<Value*> values){
    if (constructor != nullptr) constructor -> execute(values);
}

Value* ClassValue::access(Value* value){
    return thisMap -> get(value);
}

void ClassValue::set(Value* key, Value* value){
    if (!thisMap -> containsKey(key)) throw new std::logic_error("Unable to add new field " + key -> getString() + " to class " + className);
    thisMap -> set(key, value);
}

Value* ClassValue::get(Value* key){
    if (!thisMap -> containsKey(key)){
        std::string s = "Field " + std::string(*key) + " undefined in " + className;
        throw new std::logic_error(s.c_str());
    }
    return thisMap -> get(key);
}

double ClassValue::getDouble(){
    throw new TypeException("Cannot cast class to double");
}

std::string ClassValue::getString(){
    return "class " + className + "@" + std::string(*thisMap);
}

bool ClassValue::getBool(){
    throw new TypeException("Cannot cast class to bool");
}

Bignum ClassValue::getBignum(){
    throw new TypeException("Cannot cast class to number");
}

ClassValue::operator std::string(){
    return getString();
}

ClassValue::~ClassValue(){
    delete thisMap;
    thisMap = nullptr;
    delete constructor;
    constructor = nullptr;
}

bool operator==(ClassValue const& a, ClassValue const& b){
    return a.className == b.className;
}

bool operator!=(ClassValue const& a, ClassValue const& b){
    return a.className != b.className;
}

bool operator<(ClassValue const& a, ClassValue const& b){
    return a.className < b.className;
}

bool operator<=(ClassValue const& a, ClassValue const& b){
    return a.className <= b.className;
}

bool operator>(ClassValue const& a, ClassValue const& b){
    return a.className > b.className;
}

bool operator>=(ClassValue const& a, ClassValue const& b){
    return a.className >= b.className;
}
