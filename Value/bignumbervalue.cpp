#include <sstream>
#include "bignumbervalue.h"
#include "../Exception/typeexception.h"

double BigNumberValue::asDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw new TypeException("Cannot cast number to double");
    }
}

std::string BigNumberValue::asString(){
    return value;
}

bool BigNumberValue::asBool(){
    return bool(value);
}

Bignum BigNumberValue::asBignum(){
    return value;
}

Values BigNumberValue::type() const{
    return Values::NUMBER;
}

BigNumberValue::operator std::string(){
    return asString();
};

bool operator==(BigNumberValue const& a, BigNumberValue const& b){
    return a.value == b.value;
}

bool operator!=(BigNumberValue const& a, BigNumberValue const& b){
    return a.value != b.value;
}

bool operator<(BigNumberValue const& a, BigNumberValue const& b){
    return a.value < b.value;
}

bool operator<=(BigNumberValue const& a, BigNumberValue const& b){
    return a.value <= b.value;
}

bool operator>(BigNumberValue const& a, BigNumberValue const& b){
    return a.value > b.value;
}

bool operator>=(BigNumberValue const& a, BigNumberValue const& b){
    return a.value >= b.value;
}
