#include "types.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"

namespace{
    class Float_ : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            return new NumberValue(values[0] -> asBignum());
        }
    };

    class Int_ : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            std::string str = std::string(NumberValue(values[0] -> asBignum())), cop;
            for(int i = 0; i < str.size(); ++i){
                if (str[i] == '.') break;
                else cop += str[i];
            }
            return new NumberValue(cop);
        }
    };

    class String_ : public Function{
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
            else return new StringValue(getValueName(values[0] -> type()));
        }
    };

    class Typeof : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new NumberValue(int(values[0] -> type()));
        }
    };
}

void Types::initConstants(){
    Variables::set("BOOL", new NumberValue(int(Values::BOOL)));
    Variables::set("NUMBER", new NumberValue(int(Values::NUMBER)));
    Variables::set("STRING", new NumberValue(int(Values::STRING)));
    Variables::set("ARRAY", new NumberValue(int(Values::ARRAY)));
    Variables::set("MAP", new NumberValue(int(Values::MAP)));
    Variables::set("NULL", new NumberValue(int(Values::NULL_)));
    Variables::set("FUNCTION", new NumberValue(int(Values::FUNCTION)));
    Variables::set("CLASS", new NumberValue(int(Values::CLASS)));
}

void Types::initFunctions(){
    Functions::set("float", new Float_());
    Functions::set("int", new Int_());
    Functions::set("string", new String_());
    Functions::set("type_to_string", new TypeToString());
    Functions::set("typeof", new Typeof());
}
