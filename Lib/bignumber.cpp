#include "bignumber.h"
#include <sstream>
#include "../Exception/typeexception.h"

double BigNumber::getDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw new TypeException("Cannot cast number to double");
    }
}

std::string BigNumber::getString(){
    return value;
}

bool BigNumber::getBool(){
    return bool(value);
}

Bignum BigNumber::getBignum(){
    return value;
}

BigNumber::operator std::string(){
    return getString();
};

bool operator==(BigNumber const& a, BigNumber const& b){
    return a.value == b.value;
}

bool operator!=(BigNumber const& a, BigNumber const& b){
    return a.value != b.value;
}

bool operator<(BigNumber const& a, BigNumber const& b){
    return a.value < b.value;
}

bool operator<=(BigNumber const& a, BigNumber const& b){
    return a.value <= b.value;
}

bool operator>(BigNumber const& a, BigNumber const& b){
    return a.value > b.value;
}

bool operator>=(BigNumber const& a, BigNumber const& b){
    return a.value >= b.value;
}
