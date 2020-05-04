#include "global.h"
#include "../Lib/array.h"
#include "../Lib/bignumber.h"
#include "../Lib/functions.h"
#include "../Lib/functionvalue.h"
#include "../Lib/classvalue.h"
#include "../Lib/map.h"
#include "../Lib/variables.h"
#include "../Lib/bool.h"
#include "../Lib/null.h"
#include "../Lib/string.h"
#include "../Exception/argumentsmismatchexception.h"
#include <iostream>

namespace{
    bool operator_lt(Value const& a, Value const& b){
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

    class Input : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            for(int i = 0; i < values.size(); ++i) std::cout << std::string(*(values[i]));
            std::string str;
            getline(std::cin, str);
            return new String(str);
        }
    };

    class Max : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() == 0) throw new ArgumentsMismatchException("One and least arguments expected");
            Value* ans = values[0];
            for(int i = 1; i < values.size(); ++i) ans = operator_lt(*ans, *values[i]) ? values[i] : ans;
            return ans;
        }
    };

    class Min : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() == 0) throw new ArgumentsMismatchException("One and least arguments expected");
            Value* ans = values[0];
            for(int i = 1; i < values.size(); ++i) ans = operator_lt(*ans, *values[i]) ? ans : values[i];
            return ans;
        }
    };
}

void Global::initConstants(){
    Variables::set("true", Bool::TRUE_);
    Variables::set("false", Bool::FALSE_);
    Variables::set("null", Null::NULL_);
}

void Global::initFunctions(){
    Functions::set("input", new Input());
    Functions::set("max", new Max());
    Functions::set("min", new Min());
}
