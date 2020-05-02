#include "global.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Lib/bool.h"
#include "../Lib/null.h"
#include "../Lib/string.h"
#include <iostream>

namespace{
    class Input : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            for(int i = 0; i < values.size(); ++i) std::cout << std::string(*(values[i]));
            std::string str;
            getline(std::cin, str);
            return new String(str);
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
}
