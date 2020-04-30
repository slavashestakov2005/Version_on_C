#include "value.h"
#include "array.h"
#include "bool.h"
#include "bignumber.h"
#include "functionvalue.h"
#include "map.h"
#include "string.h"
#include "null.h"
#include "classvalue.h"

bool operator==(Value const& a, Value const& b){
    if (a.type != b.type) return false;
    switch(a.type){
        case Values::ARRAY : return *(Array*)(&a) == *(Array*)(&b);
        case Values::BOOL : return *(Bool*)(&a) == *(Bool*)(&b);
        case Values::NUMBER : return *(BigNumber*)(&a) == *(BigNumber*)(&b);
        case Values::FUNCTION : return *(FunctionValue*)(&a) == *(FunctionValue*)(&b);
        case Values::MAP : return *(Map*)(&a) == *(Map*)(&b);
        case Values::STRING : return *(String*)(&a) == *(String*)(&b);
        case Values::NULL_ : return *(Null*)(&a) == *(Null*)(&b);
        case Values::CLASS : return *(ClassValue*)(&a) == *(ClassValue*)(&b);
    }
}

bool operator!=(Value const& a, Value const& b){
    return !(a == b);
}

bool operator<(Value const& a, Value const& b){
    if (a.type != b.type) return int(a.type) < int(b.type);
    switch(a.type){
        case Values::ARRAY : return *(Array*)(&a) < *(Array*)(&b);
        case Values::BOOL : return *(Bool*)(&a) < *(Bool*)(&b);
        case Values::NUMBER : return *(BigNumber*)(&a) < *(BigNumber*)(&b);
        case Values::FUNCTION : return *(FunctionValue*)(&a) < *(FunctionValue*)(&b);
        case Values::MAP : return *(Map*)(&a) < *(Map*)(&b);
        case Values::STRING : return *(String*)(&a) < *(String*)(&b);
        case Values::NULL_ : return *(Null*)(&a) < *(Null*)(&b);
        case Values::CLASS : return *(ClassValue*)(&a) < *(ClassValue*)(&b);
    }
}

bool operator<=(Value const& a, Value const& b){
    return !(a > b);
}

bool operator>(Value const& a, Value const& b){
    return b < a;
}

bool operator>=(Value const& a, Value const& b){
    return !(a < b);
}
