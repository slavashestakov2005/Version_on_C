#include "functionvalue.h"
#include "../Exception/typeexception.h"

double FunctionValue::getDouble(){
    throw new TypeException("Cannot cast function to number");
}

std::string FunctionValue::getString(){
    return std::string(*value);
}

bool FunctionValue::getBool(){
    throw new TypeException("Cannot cast function to bool");
}

Bignum FunctionValue::getBignum(){
    throw new TypeException("Cannot cast function to number");
}

Function* FunctionValue::getFunction(){
    return value;
}

FunctionValue::operator std::string(){
    return getString();
};

FunctionValue::~FunctionValue(){
    delete value;
}

bool operator==(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '==' cannot used for function and function");
}

bool operator!=(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '!=' cannot used for function and function");
}

bool operator<(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '<' cannot used for function and function");
}

bool operator<=(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '<=' cannot used for function and function");
}

bool operator>(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '>' cannot used for function and function");
}

bool operator>=(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '>=' cannot used for function and function");
}
