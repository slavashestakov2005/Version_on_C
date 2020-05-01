#include "array.h"
#include "bool.h"
#include "string.h"
#include "../Exception/typeexception.h"
#include "../Expression/valueexpression.h"

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Class"
    };

    class IsEmpty : public Function{
        public:
        Value* execute(std::vector<Value*> values){
             return new Bool(((Array*)values[0]) -> getSize() == 0);
        }
    };
    class Length : public Function{
        public:
        Value* execute(std::vector<Value*> values){
             return new BigNumber(((Array*)values[0]) -> getSize());
        }
    };
}

Array::Array(int size){
    type = Values::ARRAY;
    elements = new std::vector<Value*>(size);
}

Array::Array(std::vector<Value*> elem){
    type = Values::ARRAY;
    elements = new std::vector<Value*>(elem.size());
    for(unsigned i = 0; i < elem.size(); ++i){
        (*elements)[i] = elem[i];
    }
}

Array::Array(const Array& arra){
    type = Values::ARRAY;
    (*this) = Array(*arra.elements);
}

std::vector<Value*> Array::getCopyElement(){
    int size = elements -> size();
    std::vector<Value*> vec;
    for(int i = 0; i < size; ++i) vec.push_back(get(i));
    return vec;
}

Value* Array::get(int index) const{
    return (*elements)[index];
}

void Array::set(int index, Value* value){
    (*elements)[index] = value;
}

Array* Array::add(Array* array, Value* value){
    std::vector<Value*> vec;
    int size = array -> elements -> size() + 1;
    for(int i = 0; i < size - 1; ++i) vec.push_back(array -> get(i));
    vec.push_back(value);
    return new Array(vec);
}

Array* Array::add(Array* array1, Array* array2){
    std::vector<Value*> vec;
    int size = array1 -> elements -> size();
    for(int i = 0; i < size; ++i) vec.push_back(array1 -> get(i));
    size = array2 -> elements -> size();
    for(int i = 0; i < size; ++i) vec.push_back(array2 -> get(i));
    return new Array(vec);
}

int Array::getSize() const{
    return elements -> size();
}

Value* Array::access(Value* property){
    std::string prop = property -> getString();
    if (prop == "length") return new FunctionValue(new Length());
    if (prop == "is_empty") return new FunctionValue(new IsEmpty());
    return get((int)property -> getDouble());
}

double Array::getDouble(){
    throw new TypeException("Cannot cast array to number");
}

std::string Array::getString(){
    std::string result = "[";
    for(unsigned i = 0; i < (*elements).size(); ++i){
        result += std::string(*(*elements)[i]);
        if (i < (*elements).size() - 1) result += ", ";
    }
    result += "]";
    return result;
}

bool Array::getBool(){
    throw new TypeException("Cannot cast array to bool");
}

Bignum Array::getBignum(){
    throw new TypeException("Cannot cast array to number");
}

Array::operator std::string(){
    return getString();
}

Array::~Array(){
    for(unsigned i = 0; i < elements -> size(); ++i){
        delete (*elements)[i];
        (*elements)[i] = nullptr;
    }
    delete elements;
    elements = nullptr;
}

bool operator==(Array const& a, Array const& b){
    if (a.getSize() != b.getSize()) return false;
    for(int i = 0; i < a.getSize(); ++i){
        Value* val1 = a.get(i);
        Value* val2 = b.get(i);
        if (val1 -> type != val2 -> type) return false;
        switch(val1 -> type){
            case (Values::ARRAY):{
                if(*(Array*)(val1) != *(Array*)(val2)) return false;
                break;
            }
            case (Values::BOOL):{
                if(*(Bool*)(val1) != *(Bool*)(val2)) return false;
                break;
            }
            case (Values::NUMBER):{
                if(*(BigNumber*)(val1) != *(BigNumber*)(val2)) return false;
                break;
            }
            case (Values::STRING):{
                if(*(String*)(val1) != *(String*)(val2)) return false;
                break;
            }
        }
    }
    return true;
}

bool operator!=(Array const& a, Array const& b){
    return !(a == b);
}

bool operator<(Array const& a, Array const& b){
    for(int i = 0; i < a.getSize(); ++i){
        if (i > b.getSize()) return false;
        Value* val1 = a.get(i);
        Value* val2 = b.get(i);
        if (val1 -> type == Values::BOOL) val1 = new BigNumber(val1 -> getBool());
        if (val2 -> type == Values::BOOL) val2 = new BigNumber(val2 -> getBool());
        if (val1 -> type != val2 -> type){
            std::string t1 = mas[int(val1 -> type)], t2 = mas[int(val2 -> type)];
            throw TypeException(t1 + " and " + t2 + " cannot used for conditional operation");
        }
        switch(val1 -> type){
            case (Values::ARRAY):{
                if(*(Array*)(val1) > *(Array*)(val2)) return false;
                if(*(Array*)(val1) < *(Array*)(val2)) return true;
                break;
            }
            case (Values::NUMBER):{
                if(*(BigNumber*)(val1) > *(BigNumber*)(val2)) return false;
                if(*(BigNumber*)(val1) < *(BigNumber*)(val2)) return true;
                break;
            }
            case (Values::STRING):{
                if(*(String*)(val1) > *(String*)(val2)) return false;
                if(*(String*)(val1) < *(String*)(val2)) return true;
                break;
            }
        }
    }
    if (a.getSize() > b.getSize()) return false;
    if (a.getSize() < b.getSize()) return true;
    return false;
}

bool operator<=(Array const& a, Array const& b){
    return !(a > b);
}

bool operator>(Array const& a, Array const& b){
    return b < a;
}

bool operator>=(Array const& a, Array const& b){
    return !(a < b);
}
