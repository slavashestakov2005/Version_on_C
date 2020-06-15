#include "types.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/bignumbervalue.h"
#include "../Value/stringvalue.h"

namespace{
    std::string mas[] = {
        "Bool",
        "Number",
        "String",
        "Array",
        "Map",
        "Null",
        "Function",
        "Class"
    };

    class _Float : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            return new BigNumberValue(values[0] -> asBignum());
        }
    };

    class _Int : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            std::string str = std::string(BigNumberValue(values[0] -> asBignum())), cop;
            for(int i = 0; i < str.size(); ++i){
                if (str[i] == '.') break;
                else cop += str[i];
            }
            return new BigNumberValue(cop);
        }
    };

    class _String : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new StringValue(values[0] -> asString());
        }
    };

    class TypeToString : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new StringValue(mas[int(values[0] -> type())]);
        }
    };

    class Typeof : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new BigNumberValue(int(values[0] -> type()));
        }
    };
}

void Types::initConstants(){
    Variables::set("BOOL", new BigNumberValue(int(Values::BOOL)));
    Variables::set("NUMBER", new BigNumberValue(int(Values::NUMBER)));
    Variables::set("STRING", new BigNumberValue(int(Values::STRING)));
    Variables::set("ARRAY", new BigNumberValue(int(Values::ARRAY)));
    Variables::set("MAP", new BigNumberValue(int(Values::MAP)));
    Variables::set("NULL", new BigNumberValue(int(Values::NULL_)));
    Variables::set("FUNCTION", new BigNumberValue(int(Values::FUNCTION)));
    Variables::set("CLASS", new BigNumberValue(int(Values::CLASS)));
}

void Types::initFunctions(){
    Functions::set("float", new _Float());
    Functions::set("int", new _Int());
    Functions::set("string", new _String());
    Functions::set("type_to_string", new TypeToString());
    Functions::set("typeof", new Typeof());
}
