#include "std.h"
#include "../Lib/function.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Lib/array.h"
#include "../Lib/functionvalue.h"
#include "../Lib/map.h"
#include "../Lib/string.h"
#include "../Lib/userdefinedfunction.h"
#include "../Expression/valueexpression.h"
#include <iostream>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../path.h"
#include <ctime>
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
    class Rand : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            int siz = values.size();
            switch(siz){
                case (0) : return new BigNumber(rand());
                case (1) : return new BigNumber(modulo(rand(), values[0] -> getDouble()));
                case (2) : {
                    double start = std::min(values[0] -> getDouble(), values[1] -> getDouble());
                    double finish = std::max(values[0] -> getDouble(), values[1] -> getDouble());
                    return new BigNumber(start + modulo(rand(), finish - start));
                }
            }
            throw new ArgumentsMismatchException("Fewer arguments expected");
        }
    };
    class Echo : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            for(unsigned i = 0; i < values.size(); ++i) std::cout << values[i] -> getString();
            std::cout << std::endl;
            return new BigNumber(0);
        }
    };
    class Sleep : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            long long start = clock(), finish = clock();
            double tim = values[0] -> getDouble();
            while(finish - start < tim) finish = clock();
            return new BigNumber(0);
        }
    };
    class NewArray : public Function{
    private:
        Array* createArray(std::vector<Value*> values, int index){
            int size = int(values[index] -> getDouble());
            int last = values.size() - 1;
            Array* arr = new Array(size);
            if (index == last){
                for(int i = 0; i < size; ++i){
                    arr -> set(i, new BigNumber(0));
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
    class Len : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            int length;
            switch(values[0] -> type){
                case Values::ARRAY : length = ((Array*)values[0]) -> getSize(); break;
                case Values::MAP : length = ((Map*)values[0]) -> getSize(); break;
                case Values::STRING : length = ((String*)values[0]) -> getSize(); break;
                case Values::FUNCTION :{
                    if (((FunctionValue*)values[0]) -> getFunction() -> type) length = ((UserDefinedFunction*)(((FunctionValue*)values[0]) -> getFunction())) -> getArgsCount();
                    else length = 0;
                    break;
                }
                default : throw new TypeException("Type cannot used for len function");
            }
            return new BigNumber(length);
        }
    };
    class Sort : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            mas.clear();
            if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
            if (values[0] -> type != Values::ARRAY) throw new TypeException("Array expected in first argument");
            Array* arr = (Array*)values[0];
            for(int i = 0; i < arr -> getSize(); ++i) mas.push_back(arr -> get(i));
            if (values.size() == 1) sort(mas.begin(), mas.end(), comparator);
            if (values.size() == 2){
                if (values[1] -> type != Values::FUNCTION) throw new TypeException("Function expected in second argument");
                func = ((FunctionValue*)values[1]) -> getFunction();
                if (!mas.size()) return new Array(mas);
                qweek_sort(0, mas.size() - 1);
            }
            return new Array(mas);
        }
    };
    class Split : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> getString(), reg = values[1] -> getString();
            int limit = ((values.size() == 3) ? (int)values[2] -> getDouble() : -1);
            if (limit < 0) limit = -1;
            std::vector<Value*> val;
            int pos = str.find(reg), last = 0;
            std::string t;
            while(pos != std::string::npos){
                std::string temp;
                for(int i = last; i < pos; ++i) temp += str[i];
                if (limit == -1 || val.size() < limit) val.push_back(new String(temp));
                else break;
                last = pos + 1;
                pos = str.find(reg, last);
            }
            for(int i = last; i < str.size(); ++i) t += str[i];
            if (t != "") val.push_back(new String(t));
            return new Array(val);
        }
    };
    class Join : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2) throw new ArgumentsMismatchException("At least two argument expected");
            if (values[0] -> type != Values::STRING) throw new TypeException("String expected in first argument");
            std::string ans, delimiter = values[0] -> getString();
            if (values.size() == 2 && values[1] -> type == Values::ARRAY){
                Array* arr = (Array*) values[1];
                for(int i = 0; i < arr -> getSize(); ++i){
                    ans += arr -> get(i) -> getString();
                    if (i < arr -> getSize() - 1) ans += delimiter;
                }
            }
            else{
                for(int i = 1; i < values.size(); ++i){
                    ans += values[i] -> getString();
                    if (i < values.size() - 1) ans += delimiter;
                }
            }
            return new String(ans);
        }
    };
    class Find : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> getString(), str2 = values[1] -> getString();
            int position = ((values.size() == 3) ? (int)values[2] -> getDouble() : 0);
            size_t x = str.find(str2, position);
            if (x == std::string::npos) return new BigNumber(-1);
            else return new BigNumber(x);
        }
    };
    class Rfind : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> getString(), str2 = values[1] -> getString();
            int position = ((values.size() == 3) ? (int)values[2] -> getDouble() : 0);
            std::cout << str << " " << str2 << " " << position << std::endl;
            size_t x = str.rfind(str2, position);
            if (x == std::string::npos) return new BigNumber(-1);
            else return new BigNumber(x);
        }
    };
    class CharAt : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            std::string str = values[0] -> getString();
            int index = values[1] -> getDouble();
            str = str.at(index);
            return new String(str);
        }
    };
    class ToChar : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            std::string str;
            str += char(values[0] -> getDouble());
            return new String(str);
        }
    };
    class Substring : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments expected");
            std::string str = values[0] -> getString(), ans;
            int start = values[1] -> getDouble();
            if (values.size() == 2) ans = str.substr(start);
            else{
                int finish = values[2] -> getDouble();
                ans = str.substr(start, finish);
            }
            return new String(ans);
        }
    };
    class ToLower : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            std::string ans, str = values[0] -> getString();
            for(int i = 0; i < str.size(); ++i) ans += tolower(str[i]);
            return new String(ans);
        }
    };
    class ToUpper : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            std::string ans, str = values[0] -> getString();
            for(int i = 0; i < str.size(); ++i) ans += toupper(str[i]);
            return new String(ans);
        }
    };
    class Trim : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            std::string ans, str = values[0] -> getString();
            for(int i = 0; i < str.size(); ++i){
                if (str[i] !=  ' ' || ans.size()) ans += str[i];
            }
            str = "";
            for(int i = ans.size() - 1; i > -1; --i){
                if (ans[i] != ' ' || str.size()) str += ans[i];
            }
            reverse(str.begin(), str.end());
            return new String(str);
        }
    };
    class Replace : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            std::string str = values[0] -> getString(), start = values[1] -> getString(), finish = values[2] -> getString(), ans;
            for(int i = 0; i < str.size(); ++i){
                std::string temp = str.substr(i, start.size());
                if (temp == start) { i += start.size() - 1; ans += finish; }
                else ans += str[i];
            }
            return new String(ans);
        }
    };
    class ReplaceFirst : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            std::string str = values[0] -> getString(), start = values[1] -> getString(), finish = values[2] -> getString(), ans;
            bool smena = false;
            for(int i = 0; i < str.size(); ++i){
                std::string temp;
                if (!smena) temp = str.substr(i, start.size());
                if (temp == start) { smena = true; i += start.size() - 1; ans += finish; }
                else ans += str[i];
            }
            return new String(ans);
        }
    };
    class Time : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
            return new BigNumber(clock());
        }
    };
    class ArrayCombine : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            if (values[0] -> type != Values::ARRAY) throw new TypeException("Array expected in first argument");
            if (values[1] -> type != Values::ARRAY) throw new TypeException("Array expected in second argument");
            Array* keys = (Array*)values[0], *value = (Array*)values[1];
            int len = std::min(keys -> getSize(), value -> getSize());
            Map* map = new Map(len);
            for(int i = 0; i < len; ++i) map -> set(keys -> get(i), value -> get(i));
            return map;
        }
    };
    class MapKeyExists : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            if (values[0] -> type != Values::MAP) throw new TypeException("Map expected in first argument");
            Map* map = (Map*)values[0];
            return new Bool(map -> containsKey(values[1]));
        }
    };
    class MapKeys : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            if (values[0] -> type != Values::MAP) throw new TypeException("Map expected in first argument");
            Map* map = (Map*)values[0];
            std::vector<Value*> keys;
            int siz = map -> getSize();
            std::map<Value*, Value*>::iterator iter = map -> iter();
            for(int i = 0; i < siz; ++i, ++iter) keys.push_back(iter -> first);
            return new Array(keys);
        }
    };
    class MapValues : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
            if (values[0] -> type != Values::MAP) throw new TypeException("Map expected in first argument");
            Map* map = (Map*)values[0];
            std::vector<Value*> keys;
            int siz = map -> getSize();
            std::map<Value*, Value*>::iterator iter = map -> iter();
            for(int i = 0; i < siz; ++i, ++iter) keys.push_back(iter -> second);
            return new Array(keys);
        }
    };
}
void Std::init(){
    srand(time(0));
    Variables::set("ARGS", Path::getCommandArguments());
    Functions::set("echo", new Echo());
    Functions::set("rand", new Rand());
    Functions::set("sleep", new Sleep());
    Functions::set("len", new Len());
    Functions::set("time", new Time());

    Functions::set("split", new Split());
    Functions::set("join", new Join());
    Functions::set("find", new Find());
    Functions::set("rfind", new Rfind());
    Functions::set("charat", new CharAt());
    Functions::set("tochar", new ToChar());
    Functions::set("substring", new Substring());
    Functions::set("tolower", new ToLower());
    Functions::set("toupper", new ToUpper());
    Functions::set("trim", new Trim());
    Functions::set("replace", new Replace());
    Functions::set("replacefirst", new ReplaceFirst());

    Functions::set("new_array", new NewArray());
    Functions::set("sort", new Sort());
    Functions::set("arraycombine", new ArrayCombine());
    Functions::set("mapkeyexist", new MapKeyExists());
    Functions::set("mapkeys", new MapKeys());
    Functions::set("mapvalues", new MapValues());
}
