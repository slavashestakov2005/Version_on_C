#include "bignum.h"
#include <cmath>
#include <iostream>
#include "../../Exception/mathexception.h"
namespace{
    Bignum tau("6.28318530717958647682");
    Bignum pi("3.14159265358979323846");
}
Bignum sin(const Bignum& x){
    return sin(double(x % tau));
}
Bignum cos(const Bignum& x){
    return cos(double(x % tau));
}
Bignum tan(const Bignum& x){
    return sin(x) / cos(x);
}
Bignum sinh(const Bignum& x){
    return sinh(double(x));
}
Bignum cosh(const Bignum& x){
    return cosh(double(x));
}
Bignum tanh(const Bignum& x){
    return sinh(x) / cosh(x);
}
Bignum asin(const Bignum& x){
    if (x < -1 || x > 1) throw MathException("For asin expected value in [-1; 1]");
    return asin(double(x));
}
Bignum acos(const Bignum& x){
    if (x < -1 || x > 1) throw MathException("For acos expected value in [-1; 1]");
    return acos(double(x));
}
Bignum atan(const Bignum& x){
    return atan(double(x));
}
Bignum atan2(const Bignum& x, const Bignum& y){
    return atan2(double(x), double(y));
}
Bignum exp(const Bignum& x){
    return exp(double(x));
}
Bignum log(const Bignum& x){
    return log(double(x));
}
Bignum log10(const Bignum& x){
    return log10(double(x));
}
Bignum pow(const Bignum& x, const Bignum& y){
    return pow(double(x), double(y));
}
Bignum sqrt(const Bignum& x){
    return sqrt(double(x));
}/*
Bignum exp(const Bignum& x){
    return exp(double(x));
}
Bignum exp(const Bignum& x){
    return exp(double(x));
}
Bignum exp(const Bignum& x){
    return exp(double(x));
}
*/
