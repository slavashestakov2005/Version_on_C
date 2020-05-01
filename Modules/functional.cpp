#include "functional.h"
#include "../Lib/functions.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Lib/functionvalue.h"
#include "../Lib/array.h"
#include "../Lib/map.h"
#include "../Lib/bignumber.h"
namespace{
    std::vector<Value*> mas;
    Function* func;
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
    Value* filterArray(Array* arr, Function* consumer){
        int size = arr -> getSize();
        std::vector<Value*> value;
        for(int i = 0; i < size; ++i){
            std::vector<Value*> temp;
            temp.push_back(arr -> get(i));
            if (consumer -> execute(temp) -> getBool()) value.push_back(arr -> get(i));
        }
        return new Array(value);
    }
    Value* filterMap(Map* map, Function* consumer){
        int i = 0;
        Map* value;
        std::map<Value*, Value*>::iterator iter = map -> iter();
        while (i < map -> getSize()){
            std::vector<Value*> args = { iter -> first, iter -> second };
            if (consumer -> execute(args)) value -> set(iter -> first, iter -> second);
            ++iter;
            ++i;
        }
        return value;
    }
    class Filter : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
            if (values[1] -> type != Values::FUNCTION) throw new TypeException("Function expected in second argument");
            Value* container = values[0];
            Function* consumer = ((FunctionValue*) values[1]) -> getFunction();
            if (container -> type == Values::ARRAY) return filterArray((Array*) container, consumer);
            if (container -> type == Values::MAP) return filterMap((Map*) container, consumer);
            throw new TypeException("Invalid first argument. Array or map expected");
        }
    };
    Value* mapArray(Array* arr, Function* consumer){
        int size = arr -> getSize();
        std::vector<Value*> value;
        for(int i = 0; i < size; ++i){
            std::vector<Value*> temp;
            temp.push_back(arr -> get(i));
            value.push_back(consumer -> execute(temp));
        }
        return new Array(value);
    }
    Value* mapMap(Map* map, Function* consumer, Function* consumer2){
        int i = 0;
        Map* value;
        std::map<Value*, Value*>::iterator iter = map -> iter();
        while (i < map -> getSize()){
            std::vector<Value*> args1 = { iter -> first};
            std::vector<Value*> args2 = { iter -> second};
            value -> set(consumer -> execute(args1), consumer2 -> execute(args2));
            ++iter;
            ++i;
        }
        return value;
    }
    class _Map : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("At least two arguments excepted");
            if (values[1] -> type != Values::FUNCTION) throw new TypeException("Function expected in second argument");
            Value* container = values[0];
            Function* consumer = ((FunctionValue*) values[1]) -> getFunction();
            if (container -> type == Values::ARRAY) return mapArray((Array*) container, consumer);
            if (container -> type == Values::MAP){
                if (values.size() < 3) throw new ArgumentsMismatchException("Three arguments excepted for map function for map type");
                if (values[2] -> type != Values::FUNCTION) throw new TypeException("Function expected in third argument");
                Function* consumer2 = ((FunctionValue*) values[1]) -> getFunction();
                return mapMap((Map*) container, consumer, consumer2);
            }
            throw new TypeException("Invalid first argument. Array or map expected");
        }
    };
    class Foreach : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
            if (values[1] -> type != Values::FUNCTION) throw new TypeException("Function expected at second argument");
            Function* function = ((FunctionValue*) values[1]) -> getFunction();
            Value* container = values[0];
            if (container -> type == Values::ARRAY){
                Array* arr = (Array*)container;
                for(int i = 0; i < arr -> getSize(); ++i){
                    std::vector<Value*> args = {arr -> get(i)};
                    function -> execute(args);
                }
            }
            else if (container -> type == Values::MAP){
                Map map = *(Map*)container;
                int i = 0;
                std::map<Value*, Value*>::iterator iter = map.iter();
                while (i < map.getSize()){
                    std::vector<Value*> args = { iter -> first, iter -> second };
                    function -> execute(args);
                    ++iter;
                    ++i;
                }
            }
            else throw new TypeException("Invalid first argument. Array or map expected");
            return new BigNumber(0);
        }
    };
    class Reduce : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
            if (values[2] -> type != Values::FUNCTION) throw new TypeException("Function expected in third argument");
            Value* container = values[0], *identy = values[1];
            Function* accumulator = ((FunctionValue*) values[2]) -> getFunction();
            if (container -> type == Values::ARRAY){
                Value* result = identy;
                Array* arr = (Array*) container;
                for(int i = 0; i < arr -> getSize(); ++i){
                    std::vector<Value*> args = {result, arr -> get(i)};
                    result = accumulator -> execute(args);
                }
                return result;
            }
            if (container -> type == Values::MAP){
                Value* result = identy;
                Map map = *(Map*)container;
                int i = 0;
                std::map<Value*, Value*>::iterator iter = map.iter();
                while (i < map.getSize()){
                    std::vector<Value*> args = { result, iter -> first, iter -> second };
                    result = accumulator -> execute(args);
                    ++iter;
                    ++i;
                }
                return result;
            }
            throw new TypeException("Invalid first argument. Array or map expected");
        }
    };
    Value* FlatmapArray(Array* arr, Function* mapper){
        int siz = arr -> getSize();
        std::vector<Value*> values;
        for(int i = 0; i < siz; ++i){
            std::vector<Value*> temp = { arr -> get(i) };
            Value* inner = mapper -> execute(temp);
            if (inner -> type != Values::ARRAY) throw new TypeException("Array expected " + std::string(*inner));
            Array* valArr = (Array*) inner;
            for(int i = 0; i < valArr -> getSize(); ++i){
                values.push_back(valArr -> get(i));
            }
        }
        return new Array(values);
    }
    class Flatmap : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 2) throw new ArgumentsMismatchException("At least arguments excepted");
            if (values[0] -> type != Values::ARRAY) throw new TypeException("Array expected at first argument");
            if (values[1] -> type != Values::FUNCTION) throw new TypeException("Function expected at second arguments");
            return FlatmapArray((Array*)values[0], ((FunctionValue*)values[1]) -> getFunction());
        }
    };
    class Sortby : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            mas.clear();
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
            if (values[0] -> type != Values::ARRAY) throw new TypeException("Array expected in first argument");
            if (values[1] -> type != Values::FUNCTION) throw new TypeException("Function expected in second argument");
            Array* arr = (Array*)values[0];
            for(int i = 0; i < arr -> getSize(); ++i) mas.push_back(arr -> get(i));
            func = ((FunctionValue*)values[1]) -> getFunction();
            if (!mas.size()) return new Array(mas);
            qweek_sort(0, mas.size() - 1);
            return new Array(mas);
        }
    };
    class Chain : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() < 3) throw new ArgumentsMismatchException("3 and least arguments expected");
            Value* result = values[0];
            for(int i = 1; i < values.size(); i += 2){
                if (values[i] -> type != Values::FUNCTION) throw new TypeException(std::string(*values[i]) + " is not a function");
                Function* function = ((FunctionValue*)values[i]) -> getFunction();
                result = function -> execute({result, values[i + 1]});
            }
            return result;
        }
    };
}
void Functional::init(){
    Functions::set("foreach", new Foreach());
    Functions::set("filter", new Filter());
    Functions::set("map", new _Map());
    Functions::set("reduce", new Reduce());
    Functions::set("flat_map", new Flatmap());
    Functions::set("sortby", new Sortby());
    Functions::set("chain", new Chain());
    /// combine
    /// take_while
    /// drop_while
}
