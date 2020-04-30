#include "null.h"
#include "../Exception/typeexception.h"

Null* Null::NULL_ = new Null();

double Null::getDouble(){
    throw new TypeException("Cannot cast null to double");
}

std::string Null::getString(){
    throw new TypeException("Cannot cast null to string");
}

bool Null::getBool(){
    throw new TypeException("Cannot cast null to bool");
}

Bignum Null::getBignum(){
    throw new TypeException("Cannot cast null to number");
}

Null::operator std::string(){
    return "null";
}

bool operator==(Null const& a, Null const& b){
    return true;
}

bool operator!=(Null const& a, Null const& b){
    return false;
}

bool operator<(Null const& a, Null const& b){
    return false;
}

bool operator<=(Null const& a, Null const& b){
    return true;
}

bool operator>(Null const& a, Null const& b){
    return false;
}

bool operator>=(Null const& a, Null const& b){
    return true;
}
