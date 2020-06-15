#include "arrayvalue.h"
#include "boolvalue.h"
#include "classvalue.h"
#include "stringvalue.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Expression/valueexpression.h"

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Class"
    };

    class IsEmpty : public Function{
        public:
        Value* execute(std::vector<Value*> values){
             return new BoolValue(((ArrayValue*)values[0]) -> getSize() == 0);
        }
    };

    class Length : public Function{
        public:
        Value* execute(std::vector<Value*> values){
             return new BigNumberValue(((ArrayValue*)values[0]) -> getSize());
        }
    };
}

ArrayValue::ArrayValue(int size){
    elements = new std::vector<Value*>(size);
}

ArrayValue::ArrayValue(std::vector<Value*> elem){
    elements = new std::vector<Value*>(elem.size());
    for(int i = 0; i < elem.size(); ++i){
        (*elements)[i] = elem[i];
    }
}

ArrayValue::ArrayValue(const ArrayValue& arra){
    (*this) = ArrayValue(*arra.elements);
}

std::vector<Value*> ArrayValue::getCopyElement(){
    int size = elements -> size();
    std::vector<Value*> vec;
    for(int i = 0; i < size; ++i) vec.push_back(get(i));
    return vec;
}

Value* ArrayValue::get(int index) const{
    return (*elements)[index];
}

void ArrayValue::set(int index, Value* value){
    (*elements)[index] = value;
}

ArrayValue* ArrayValue::add(ArrayValue* array, Value* value){
    std::vector<Value*> vec;
    int size = array -> elements -> size() + 1;
    for(int i = 0; i < size - 1; ++i) vec.push_back(array -> get(i));
    vec.push_back(value);
    return new ArrayValue(vec);
}

ArrayValue* ArrayValue::add(ArrayValue* array1, ArrayValue* array2){
    std::vector<Value*> vec;
    int size = array1 -> elements -> size();
    for(int i = 0; i < size; ++i) vec.push_back(array1 -> get(i));
    size = array2 -> elements -> size();
    for(int i = 0; i < size; ++i) vec.push_back(array2 -> get(i));
    return new ArrayValue(vec);
}

int ArrayValue::getSize() const{
    return elements -> size();
}

Value* ArrayValue::accessDot(Value* property){
    std::string prop = property -> asString();
    if (prop == "length") return new FunctionValue(new Length());
    if (prop == "is_empty") return new FunctionValue(new IsEmpty());
    throw new UnknownPropertyException(prop);
}

Value* ArrayValue::accessBracket(Value* property){
    return get((int)property -> asDouble());
}

double ArrayValue::asDouble(){
    throw new TypeException("Cannot cast array to double");
}

std::string ArrayValue::asString(){
    std::string result = "[";
    for(unsigned i = 0; i < (*elements).size(); ++i){
        result += std::string(*(*elements)[i]);
        if (i < (*elements).size() - 1) result += ", ";
    }
    result += "]";
    return result;
}

bool ArrayValue::asBool(){
    throw new TypeException("Cannot cast array to bool");
}

Bignum ArrayValue::asBignum(){
    throw new TypeException("Cannot cast array to number");
}

Values ArrayValue::type() const{
    return Values::ARRAY;
}

ArrayValue::operator std::string(){
    return asString();
}

ArrayValue::~ArrayValue(){
    for(int i = 0; i < elements -> size(); ++i){
        delete (*elements)[i];
        (*elements)[i] = nullptr;
    }
    delete elements;
    elements = nullptr;
}

bool operator==(ArrayValue const& a, ArrayValue const& b){
    if (a.getSize() != b.getSize()) return false;
    for(int i = 0; i < a.getSize(); ++i){
        Value* val1 = a.get(i);
        Value* val2 = b.get(i);
        if (val1 -> type() != val2 -> type()) return false;
        if (*val1 != *val2) return false;
    }
    return true;
}

bool operator!=(ArrayValue const& a, ArrayValue const& b){
    return !(a == b);
}

bool operator<(ArrayValue const& a, ArrayValue const& b){
    if (a.getSize() > b.getSize()) return false;
    if (a.getSize() < b.getSize()) return true;
    for(int i = 0; i < a.getSize(); ++i){
        Value* val1 = a.get(i);
        Value* val2 = b.get(i);
        if (val1 -> type() != val2 -> type()) return (int) val1 -> type() < (int) val2 -> type();
        if (*val1 > *val2) return false;
        if (*val1 < *val2) return true;
    }
    return false;
}

bool operator<=(ArrayValue const& a, ArrayValue const& b){
    return !(a > b);
}

bool operator>(ArrayValue const& a, ArrayValue const& b){
    return b < a;
}

bool operator>=(ArrayValue const& a, ArrayValue const& b){
    return !(a < b);
}
