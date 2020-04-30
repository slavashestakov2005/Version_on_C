#include "bool.h"

Bool* Bool::TRUE_ = new Bool(true);
Bool* Bool::FALSE_ = new Bool(false);

double Bool::getDouble(){
    return (value ? 1 : 0);
}

std::string Bool::getString(){
    return (value ? "true" : "false");
}

bool Bool::getBool(){
    return value;
}

Bignum Bool::getBignum(){
    return Bignum(value);
}

Bool::operator std::string(){
    return getString();
}

bool operator==(Bool const& a, Bool const& b){
    return a.value == b.value;
}

bool operator!=(Bool const& a, Bool const& b){
    return a.value != b.value;
}

bool operator<(Bool const& a, Bool const& b){
    return a.value < b.value;
}

bool operator<=(Bool const& a, Bool const& b){
    return a.value <= b.value;
}

bool operator>(Bool const& a, Bool const& b){
    return a.value > b.value;
}

bool operator>=(Bool const& a, Bool const& b){
    return a.value >= b.value;
}
