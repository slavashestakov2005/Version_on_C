#include "string.h"
#include <sstream>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Lib/function.h"
#include "../Lib/bignumber.h"
#include "../Lib/functionvalue.h"

namespace{
    class Trim : public Function {
    private:
        std::string str;
    public:
        Trim(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            return new String("This is trimmed for : " + str + " : end");
        }
    };
}

int String::getSize(){
    return value.size();
}

Value* String::access(Value* property){
    std::string prop = property -> getString();
    if (prop == "length") return new BigNumber(getSize());
    if (prop == "trim") return new FunctionValue(new Trim(value));
    throw new UnknownPropertyException(prop);
}

double String::getDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw new TypeException("Cannot cast string to double");
    }
}

std::string String::getString(){
    return value;
}

bool String::getBool(){
    throw new TypeException("Cannot cast string to bool");
}

Bignum String::getBignum(){
    try{
        return Bignum(value);
    }catch(...){
        throw new TypeException("Cannot cast string to number");
    }
}

String::operator std::string(){
    return "'" + getString() + "'";
};

bool operator==(String const& a, String const& b){
    return a.value == b.value;
}

bool operator!=(String const& a, String const& b){
    return a.value != b.value;
}

bool operator<(String const& a, String const& b){
    return a.value < b.value;
}

bool operator<=(String const& a, String const& b){
    return a.value <= b.value;
}

bool operator>(String const& a, String const& b){
    return a.value > b.value;
}

bool operator>=(String const& a, String const& b){
    return a.value >= b.value;
}
