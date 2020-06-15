#include "boolvalue.h"

BoolValue* BoolValue::TRUE_ = new BoolValue(true);
BoolValue* BoolValue::FALSE_ = new BoolValue(false);

double BoolValue::asDouble(){
    return (value ? 1 : 0);
}

std::string BoolValue::asString(){
    return (value ? "true" : "false");
}

bool BoolValue::asBool(){
    return value;
}

Bignum BoolValue::asBignum(){
    return Bignum(value);
}

Values BoolValue::type() const{
    return Values::BOOL;
}

BoolValue::operator std::string(){
    return asString();
}

bool operator==(BoolValue const& a, BoolValue const& b){
    return a.value == b.value;
}

bool operator!=(BoolValue const& a, BoolValue const& b){
    return a.value != b.value;
}

bool operator<(BoolValue const& a, BoolValue const& b){
    return a.value < b.value;
}

bool operator<=(BoolValue const& a, BoolValue const& b){
    return a.value <= b.value;
}

bool operator>(BoolValue const& a, BoolValue const& b){
    return a.value > b.value;
}

bool operator>=(BoolValue const& a, BoolValue const& b){
    return a.value >= b.value;
}
