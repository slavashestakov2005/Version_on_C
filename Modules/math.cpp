#include "math.h"
#include <cmath>
#include "../Lib/function.h"
#include "../Lib/bignumber.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/mathexception.h"
#include "../Lib/bignumbers/smath.h"
namespace{
    Bignum absolute(Bignum a){
        return a < 0 ? -a : a;
    }
    class Sin : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(sin(values[0] -> getBignum()));
        }
    };
    class Cos : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(cos(values[0] -> getBignum()));
        }
    };
    class Tan : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(tan(values[0] -> getBignum()));
        }
    };
    class Sinh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(sinh(values[0] -> getBignum()));
        }
    };
    class Cosh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(cosh(values[0] -> getBignum()));
        }
    };
    class Tanh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(tanh(values[0] -> getBignum()));
        }
    };
    class Asin : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(asin(values[0] -> getBignum()));
        }
    };
    class Acos : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(acos(values[0] -> getBignum()));
        }
    };
    class Atan : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(atan(values[0] -> getBignum()));
        }
    };
    class Atan2 : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
            else return new BigNumber(atan2(values[0] -> getBignum(), values[1] -> getBignum()));
        }
    };
    class Exp : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(exp(values[0] -> getBignum()));
        }
    };
    class Log : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(log(values[0] -> getBignum()));
        }
    };
    class Log10 : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(log10(values[0] -> getBignum()));
        }
    };
    class Pow : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
            else return new BigNumber(pow(values[0] -> getBignum(), values[1] -> getBignum()));
        }
    };
    class Sqrt : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else{
                if (values[0] -> getDouble() < 0) throw new MathException("Sqrt from negative argument");
                else return new BigNumber(sqrt(values[0] -> getBignum()));
            }
        }
    };
    class Abs : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(absolute(values[0] -> getBignum()));
        }
    };
    class Factorial : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            if (values[0] -> getDouble() < 0) throw new MathException("Bad argument for factorial");
            Bignum result = 1;
            int n = values[0] -> getDouble();
            for(int i = 2; i <= n; ++i) result *= i;
            return new BigNumber(result);
        }
    };
}

void Math::initConstants(){
    Variables::set("Pi", new BigNumber(3.1415926535));
    Variables::set("Пи", new BigNumber(3.1415926535));
    Variables::set("E", new BigNumber(2.7182818284));
    Variables::set("GOLDEN_RATIO", new BigNumber(1.6180339887));
}

void Math::initFunctions(){
    Functions::set("sin", new Sin());
    Functions::set("cos", new Cos());
    Functions::set("tan", new Tan());
    Functions::set("sinh", new Sinh());
    Functions::set("cosh", new Cosh());
    Functions::set("tanh", new Tanh());
    Functions::set("asin", new Asin());
    Functions::set("acos", new Acos());
    Functions::set("atan", new Atan());
    Functions::set("atan2", new Atan2());
    Functions::set("exp", new Exp());
    Functions::set("log", new Log());
    Functions::set("log10", new Log10());
    Functions::set("pow", new Pow());
    Functions::set("sqrt", new Sqrt());
    Functions::set("abs", new Abs());
    Functions::set("factorial", new Factorial());
}

/*
_CRTIMP double __cdecl ceil (double);
_CRTIMP double __cdecl floor (double);
_CRTIMP double __cdecl fabs (double);

_CRTIMP double __cdecl ldexp (double, int);
_CRTIMP double __cdecl frexp (double, int*);
_CRTIMP double __cdecl modf (double, double*);
_CRTIMP double __cdecl fmod (double, double);
*/
