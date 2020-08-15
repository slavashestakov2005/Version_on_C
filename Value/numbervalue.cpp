#include <sstream>
#include "numbervalue.h"
#include <exception>

NumberValue* NumberValue::M_ONE = new NumberValue(-1);
NumberValue* NumberValue::ZERO = new NumberValue(0);
NumberValue* NumberValue::ONE = new NumberValue(1);

double NumberValue::asDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw std::logic_error("Bad Number class");
    }
}

std::string NumberValue::asString(){
    return value;
}

bool NumberValue::asBool(){
    return bool(value);
}

Bignum NumberValue::asBignum(){
    return value;
}

Values NumberValue::type() const{
    return Values::NUMBER;
}

NumberValue::operator std::string(){
    return asString();
};

bool operator==(NumberValue const& a, NumberValue const& b){
    return a.value == b.value;
}

bool operator!=(NumberValue const& a, NumberValue const& b){
    return a.value != b.value;
}

bool operator<(NumberValue const& a, NumberValue const& b){
    return a.value < b.value;
}

bool operator<=(NumberValue const& a, NumberValue const& b){
    return a.value <= b.value;
}

bool operator>(NumberValue const& a, NumberValue const& b){
    return a.value > b.value;
}

bool operator>=(NumberValue const& a, NumberValue const& b){
    return a.value >= b.value;
}
