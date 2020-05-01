#include "string.h"
#include <sstream>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Lib/array.h"
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
    class To_upper : public Function {
    private:
        std::string str;
    public:
        To_upper(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            for(char& x : str) x = toupper(x);
            return new String(str);
        }
    };
    class To_lower : public Function {
    private:
        std::string str;
    public:
        To_lower(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            for(char& x : str) x = tolower(x);
            return new String(str);
        }
    };
    class Chars : public Function {
    private:
        std::string str;
    public:
        Chars(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            std::vector<Value*> vec;
            for(auto x : str){
                std::string s;
                s += x;
                vec.push_back(new String(s));
            }
            return new Array(vec);
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
    if (prop == "to_upper") return new FunctionValue(new To_upper(value));
    if (prop == "to_lower") return new FunctionValue(new To_lower(value));
    if (prop == "chars") return new FunctionValue(new Chars(value));
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
