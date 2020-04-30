#include "types.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Lib/bignumber.h"
#include "../Lib/string.h"
namespace{
    std::string mas[] = {
        "Bool",
        "String",
        "Array",
        "Map",
        "Function",
        "Number"
    };
    class Typeof : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new BigNumber(int(values[0] -> type));
        }
    };
    class TypeToString : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new String(mas[int(values[0] -> type)]);
        }
    };
    class _String : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            else return new String(values[0] -> getString());
        }
    };
    class _Int : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            std::string str = std::string(BigNumber(values[0] -> getBignum())), cop;
            for(int i = 0; i < str.size(); ++i){
                if (str[i] == '.') break;
                else cop += str[i];
            }
            return new BigNumber(cop);
        }
    };
    class _Float : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw std::logic_error("One argument expected");
            return new BigNumber(values[0] -> getBignum());
        }
    };

}
void Types::init(){
    Functions::set("typeof", new Typeof());
    Functions::set("typeToString", new TypeToString());
    Functions::set("string", new _String());
    Functions::set("int", new _Int());
    Functions::set("float", new _Float());
    Variables::set("BOOLEAN", new BigNumber(int(Values::BOOL)));
    Variables::set("NUMBER", new BigNumber(int(Values::NUMBER)));
    Variables::set("STRING", new BigNumber(int(Values::STRING)));
    Variables::set("ARRAY", new BigNumber(int(Values::ARRAY)));
    Variables::set("MAP", new BigNumber(int(Values::MAP)));
    Variables::set("FUNCTION", new BigNumber(int(Values::FUNCTION)));
}
