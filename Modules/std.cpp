#include "std.h"
#include "../Lib/function.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/arrayvalue.h"
#include "../Value/functionvalue.h"
#include "../Value/mapvalue.h"
#include "../Value/stringvalue.h"
#include "../Lib/userdefinedfunction.h"
#include "../Expression/valueexpression.h"
#include <iostream>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/mathexception.h"
#include "../Exception/typeexception.h"
#include "../path.h"
#include <ctime>
#include <sstream>
#include <algorithm>

namespace{
    std::vector<Value*> mas;
    Function* func;

    double modulo(double a, double b){
        if (a < 0) return std::max(b, -b) - modulo(-a, b);
        long long k = a / b;
        double res = a - k * b;
        return res;
    }

    bool comparator(Value* a, Value* b){
        return (*a) < (*b);
    }

    void qweek_sort(int l, int r){
        int i = l, j = r;
        std::vector<Value*> vec = { mas[(l + r) / 2] };
        Value* m = func -> execute(vec);
        while(i < j){
            vec = { mas[i] };
            while(comparator(func -> execute(vec), m)) { ++i; vec = { mas[i] }; }
            vec = { mas[j] };
            while(comparator(m, func -> execute(vec))) { --j; vec = { mas[j] }; }
            if (i <= j) std::swap(mas[i], mas[j]), ++i, --j;
        }
        if (i < r) qweek_sort(i, r);
        if (l < j) qweek_sort(l, j);
    }

    class ArrayCombine : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
            if (values[1] -> type() != Values::ARRAY) throw new TypeException("Array expected in second argument");
            ArrayValue* keys = (ArrayValue*)values[0], *value = (ArrayValue*)values[1];
            int len = std::min(keys -> getSize(), value -> getSize());
            MapValue* map = new MapValue(len);
            for(int i = 0; i < len; ++i) map -> set(keys -> get(i), value -> get(i));
            return map;
        }
    };

    class CharAt : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            std::string str = values[0] -> asString();
            int index = values[1] -> asDouble();
            str = str.at(index);
            return new StringValue(str);
        }
    };

    class Echo : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            for(unsigned i = 0; i < values.size(); ++i) std::cout << values[i] -> asString();
            std::cout << std::endl;
            return NullValue::NULL_;
        }
    };

    class Find : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> asString(), str2 = values[1] -> asString();
            int position = ((values.size() == 3) ? (int)values[2] -> asDouble() : 0);
            size_t x = str.find(str2, position);
            if (x == std::string::npos) return new BigNumberValue(-1);
            else return new BigNumberValue(x);
        }
    };

    class Join : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2) throw new ArgumentsMismatchException("At least two argument expected");
            if (values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
            std::string ans, delimiter = values[0] -> asString();
            if (values.size() == 2 && values[1] -> type() == Values::ARRAY){
                ArrayValue* arr = (ArrayValue*) values[1];
                for(int i = 0; i < arr -> getSize(); ++i){
                    ans += arr -> get(i) -> asString();
                    if (i < arr -> getSize() - 1) ans += delimiter;
                }
            }
            else{
                for(int i = 1; i < values.size(); ++i){
                    ans += values[i] -> asString();
                    if (i < values.size() - 1) ans += delimiter;
                }
            }
            return new StringValue(ans);
        }
    };

    class Len : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            int length;
            switch(values[0] -> type()){
                case Values::ARRAY : length = ((ArrayValue*)values[0]) -> getSize(); break;
                case Values::MAP : length = ((MapValue*)values[0]) -> getSize(); break;
                case Values::STRING : length = ((StringValue*)values[0]) -> getSize(); break;
                case Values::FUNCTION :{
                    if (((FunctionValue*)values[0]) -> getFunction() -> type) length = ((UserDefinedFunction*)(((FunctionValue*)values[0]) -> getFunction())) -> getArgsCount();
                    else length = 0;
                    break;
                }
                default : length = 0; break;
            }
            return new BigNumberValue(length);
        }
    };

    class MapKeyExists : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            if (values[0] -> type() != Values::MAP) throw new TypeException("Map expected in first argument");
            MapValue* map = (MapValue*)values[0];
            return new BoolValue(map -> containsKey(values[1]));
        }
    };

    class MapKeys : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            if (values[0] -> type() != Values::MAP) throw new TypeException("Map expected in first argument");
            MapValue* map = (MapValue*)values[0];
            std::vector<Value*> keys;
            int siz = map -> getSize();
            std::map<Value*, Value*>::iterator iter = map -> iter();
            for(int i = 0; i < siz; ++i, ++iter) keys.push_back(iter -> first);
            return new ArrayValue(keys);
        }
    };

    class MapValues : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            if (values[0] -> type() != Values::MAP) throw new TypeException("Map expected in first argument");
            MapValue* map = (MapValue*)values[0];
            std::vector<Value*> keys;
            int siz = map -> getSize();
            std::map<Value*, Value*>::iterator iter = map -> iter();
            for(int i = 0; i < siz; ++i, ++iter) keys.push_back(iter -> second);
            return new ArrayValue(keys);
        }
    };

    class NewArray : public Function{
    private:
        ArrayValue* createArray(std::vector<Value*> values, int index){
            int size = int(values[index] -> asDouble());
            int last = values.size() - 1;
            ArrayValue* arr = new ArrayValue(size);
            if (index == last){
                for(int i = 0; i < size; ++i){
                    arr -> set(i, NullValue::NULL_);
                }
            }
            else if(index < last){
                for(int i = 0; i < size; ++i){
                    arr -> set(i, createArray(values, index + 1));
                }
            }
            return arr;
        }
    public:
        Value* execute(std::vector<Value*> values){
            return createArray(values, 0);
        }
    };

    class ParseNumber : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
            int radix = values.size() == 2 ? values[1] -> asDouble() : 10;
            int power = 1;
            long long ans = 0;
            std::string parsed = values[0] -> asString();
            for(int i = parsed.size() - 1; i > -1; --i){
                int current;
                if (parsed[i] >= '0' && parsed[i] <= '9') current = parsed[i] - '0';
                else current = tolower(parsed[i]) - 'a';
                if (current < 0 || current >= radix) throw new MathException("Bad radix for parse string");
                ans += current * power;
                power *= radix;
            }
            return new BigNumberValue(ans);
        }
    };

    class Rand : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            int siz = values.size();
            double random = 1. * rand() / (RAND_MAX + 1), result;
            switch(siz){
                case (0) : result = random; break;
                case (1) : result = random * values[0] -> asDouble(); break;
                case (2) : {
                    double start = std::min(values[0] -> asDouble(), values[1] -> asDouble());
                    double finish = std::max(values[0] -> asDouble(), values[1] -> asDouble());
                    result = start + (finish - start) * random;
                    break;
                }
                default : throw new ArgumentsMismatchException("Fewer arguments expected");
            }
            std::ostringstream strs;
            strs << result;
            return new BigNumberValue(strs.str());
        }
    };

    class Replace : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            std::string str = values[0] -> asString(), start = values[1] -> asString(), finish = values[2] -> asString(), ans;
            for(int i = 0; i < str.size(); ++i){
                std::string temp = str.substr(i, start.size());
                if (temp == start) { i += start.size() - 1; ans += finish; }
                else ans += str[i];
            }
            return new StringValue(ans);
        }
    };

    class ReplaceFirst : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            std::string str = values[0] -> asString(), start = values[1] -> asString(), finish = values[2] -> asString(), ans;
            bool smena = false;
            for(int i = 0; i < str.size(); ++i){
                std::string temp;
                if (!smena) temp = str.substr(i, start.size());
                if (temp == start) { smena = true; i += start.size() - 1; ans += finish; }
                else ans += str[i];
            }
            return new StringValue(ans);
        }
    };

    class Rfind : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> asString(), str2 = values[1] -> asString();
            int position = ((values.size() == 3) ? (int)values[2] -> asDouble() : 0);
            size_t x = str.rfind(str2, position);
            if (x == std::string::npos) return new BigNumberValue(-1);
            else return new BigNumberValue(x);
        }
    };

    class Sleep : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            long long start = clock(), finish = clock();
            double tim = values[0] -> asDouble();
            while(finish - start < tim) finish = clock();
            return NullValue::NULL_;
        }
    };

    class Sort : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            mas.clear();
            if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
            if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
            ArrayValue* arr = (ArrayValue*)values[0];
            for(int i = 0; i < arr -> getSize(); ++i) mas.push_back(arr -> get(i));
            if (values.size() == 1) sort(mas.begin(), mas.end(), comparator);
            if (values.size() == 2){
                if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
                func = ((FunctionValue*)values[1]) -> getFunction();
                if (!mas.size()) return new ArrayValue(mas);
                qweek_sort(0, mas.size() - 1);
            }
            return new ArrayValue(mas);
        }
    };

    class Split : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> asString(), reg = values[1] -> asString();
            int limit = ((values.size() == 3) ? (int)values[2] -> asDouble() : -1);
            if (limit <= 0) limit = -1;
            std::vector<Value*> val;
            int pos = str.find(reg), last = 0;
            std::string t;
            while(pos != std::string::npos){
                std::string temp;
                for(int i = last; i < pos; ++i) temp += str[i];
                if (limit == -1 || val.size() < limit) val.push_back(new StringValue(temp));
                else break;
                last = pos + 1;
                pos = str.find(reg, last);
            }
            for(int i = last; i < str.size(); ++i) t += str[i];
            if (t != "") val.push_back(new StringValue(t));
            return new ArrayValue(val);
        }
    };

    class Substring : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> asString(), ans;
            int start = values[1] -> asDouble();
            if (values.size() == 2) ans = str.substr(start);
            else{
                int finish = values[2] -> asDouble();
                ans = str.substr(start, finish);
            }
            return new StringValue(ans);
        }
    };

    class Time : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
            return new BigNumberValue(clock());
        }
    };

    class ToChar : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            std::string str;
            str += char(values[0] -> asDouble());
            return new StringValue(str);
        }
    };

    class ToHexString : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            long long value = values[0] -> asDouble();
            std::string ans;
            while(value){
                int current = value % 16;
                ans += current < 10 ? '0' + current : 'a' + current - 10;
                value /= 16;
            }
            reverse(ans.begin(), ans.end());
            return new StringValue(ans);
        }
    };

    class ToLower : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            std::string str = values[0] -> asString();
            for(auto& x : str) x = tolower(x);
            return new StringValue(str);
        }
    };

    class ToUpper : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            std::string str = values[0] -> asString();
            for(auto& x : str) x = toupper(x);
            return new StringValue(str);
        }
    };

    class Trim : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            std::string ans, str = values[0] -> asString();
            for(int i = 0; i < str.size(); ++i){
                if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' || ans.size()) ans += str[i];
            }
            str = "";
            for(int i = ans.size() - 1; i > -1; --i){
                if (ans[i] != ' ' && ans[i] != '\t' && ans[i] != '\n' || str.size()) str += ans[i];
            }
            reverse(str.begin(), str.end());
            return new StringValue(str);
        }
    };
}

void Std::initConstants(){
    Variables::set("ARGS", Path::getCommandArguments());
}

void Std::initFunctions(){
    srand(time(0));
    Functions::set("array_combine", new ArrayCombine());
    Functions::set("char_at", new CharAt());
    Functions::set("echo", new Echo());
    Functions::set("find", new Find());
    Functions::set("join", new Join());
    Functions::set("len", new Len());
    Functions::set("map_key_exists", new MapKeyExists());
    Functions::set("map_keys", new MapKeys());
    Functions::set("map_values", new MapValues());
    Functions::set("new_array", new NewArray());
    Functions::set("parse_number", new ParseNumber());
    Functions::set("rand", new Rand());
    Functions::set("replace", new Replace());
    Functions::set("replace_first", new ReplaceFirst());
    Functions::set("rfind", new Rfind());
    Functions::set("sleep", new Sleep());
    Functions::set("sort", new Sort());
    Functions::set("split", new Split());
    Functions::set("substring", new Substring());
    Functions::set("time", new Time());
    Functions::set("to_char", new ToChar());
    Functions::set("to_hex_string", new ToHexString());
    Functions::set("to_lower", new ToLower());
    Functions::set("to_upper", new ToUpper());
    Functions::set("trim", new Trim());
}
