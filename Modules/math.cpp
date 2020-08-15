#include "math.h"
#include <cmath>
#include "../Lib/function.h"
#include "../Value/numbervalue.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/mathexception.h"
#include "../Value/bignumbers/smath.h"

namespace{
    class Abs : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(abs(values[0] -> asBignum()));
        }
    };

    class Acos : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(acos(values[0] -> asBignum()));
        }
    };

    class Asin : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(asin(values[0] -> asBignum()));
        }
    };

    class Atan : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(atan(values[0] -> asBignum()));
        }
    };

    class Atan2 : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
            else return new NumberValue(atan2(values[0] -> asBignum(), values[1] -> asBignum()));
        }
    };

    class Cbrt : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(cbrt(values[0] -> asBignum()));
        }
    };

    class Ceil : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(ceil(values[0] -> asBignum()));
        }
    };

    class CopySign : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(copy_sign(values[0] -> asBignum(), values[1] -> asBignum()));
        }
    };

    class Cos : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(cos(values[0] -> asBignum()));
        }
    };

    class Cosh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(cosh(values[0] -> asBignum()));
        }
    };

    class Exp : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(exp(values[0] -> asBignum()));
        }
    };

    class Expm1 : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(expm1(values[0] -> asBignum()));
        }
    };

    class Factorial : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            if (values[0] -> asDouble() < 0) throw new MathException("Bad argument for factorial");
            Bignum result = 1;
            int n = values[0] -> asDouble();
            for(int i = 2; i <= n; ++i) result *= i;
            return new NumberValue(result);
        }
    };

    class Floor : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(floor(values[0] -> asBignum()));
        }
    };

    class Hypot : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(hypot(values[0] -> asBignum(), values[1] -> asBignum()));
        }
    };

    class Log : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(log(values[0] -> asBignum()));
        }
    };

    class Log10 : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(log10(values[0] -> asBignum()));
        }
    };

    class Log1p : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(log1p(values[0] -> asBignum()));
        }
    };

    class Pow : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
            else return new NumberValue(pow(values[0] -> asBignum(), values[1] -> asBignum()));
        }
    };

    class Round : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(round(values[0] -> asBignum()));
        }
    };

    class Signum : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            Bignum x = values[0] -> asBignum();
            if (x < 0) return new NumberValue(-1);
            else if (x > 0) return new NumberValue(1);
            else return new NumberValue(0);
        }
    };

    class Sin : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(sin(values[0] -> asBignum()));
        }
    };

    class Sinh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(sinh(values[0] -> asBignum()));
        }
    };

    class Sqrt : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else{
                if (values[0] -> asDouble() < 0) throw new MathException("Sqrt from negative argument");
                else return new NumberValue(sqrt(values[0] -> asBignum()));
            }
        }
    };

    class Tan : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(tan(values[0] -> asBignum()));
        }
    };

    class Tanh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(tanh(values[0] -> asBignum()));
        }
    };

    class ToDegrees : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(to_degrees(values[0] -> asBignum()));
        }
    };

    class ToRadians : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new NumberValue(to_radians(values[0] -> asBignum()));
        }
    };
}

void Math::initConstants(){
    Variables::set("PI", new NumberValue(3.1415926535));
    Variables::set("E", new NumberValue(2.7182818284));
}

void Math::initFunctions(){
    Functions::set("abs", new Abs());
    Functions::set("acos", new Acos());
    Functions::set("asin", new Asin());
    Functions::set("atan", new Atan());
    Functions::set("atan2", new Atan2());
    Functions::set("cbrt", new Cbrt());
    Functions::set("ceil", new Ceil());
    Functions::set("copy_sign", new CopySign());
    Functions::set("cos", new Cos());
    Functions::set("cosh", new Cosh());
    Functions::set("exp", new Exp());
    Functions::set("expm1", new Expm1());
    Functions::set("factorial", new Factorial());
    Functions::set("floor", new Floor());
    Functions::set("hypot", new Hypot());
    Functions::set("log", new Log());
    Functions::set("log10", new Log10());
    Functions::set("log1p", new Log1p());
    Functions::set("pow", new Pow());
    Functions::set("round", new Round());
    Functions::set("signum", new Signum());
    Functions::set("sin", new Sin());
    Functions::set("sinh", new Sinh());
    Functions::set("sqrt", new Sqrt());
    Functions::set("tan", new Tan());
    Functions::set("tanh", new Tanh());
    Functions::set("to_degrees", new ToDegrees());
    Functions::set("to_radians", new ToRadians());
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
