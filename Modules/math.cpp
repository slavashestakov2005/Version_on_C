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
    class Abs : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(abs(values[0] -> getBignum()));
        }
    };

    class Acos : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(acos(values[0] -> getBignum()));
        }
    };

    class Asin : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(asin(values[0] -> getBignum()));
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

    class Cbrt : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(cbrt(values[0] -> getBignum()));
        }
    };

    class Ceil : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(ceil(values[0] -> getBignum()));
        }
    };

    class CopySign : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(copy_sign(values[0] -> getBignum(), values[1] -> getBignum()));
        }
    };

    class Cos : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(cos(values[0] -> getBignum()));
        }
    };

    class Cosh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(cosh(values[0] -> getBignum()));
        }
    };

    class Exp : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(exp(values[0] -> getBignum()));
        }
    };

    class Expm1 : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(expm1(values[0] -> getBignum()));
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

    class Floor : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(floor(values[0] -> getBignum()));
        }
    };

    class Hypot : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(hypot(values[0] -> getBignum(), values[1] -> getBignum()));
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

    class Log1p : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(log1p(values[0] -> getBignum()));
        }
    };

    class Pow : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
            else return new BigNumber(pow(values[0] -> getBignum(), values[1] -> getBignum()));
        }
    };

    class Round : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(round(values[0] -> getBignum()));
        }
    };

    class Signum : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            Bignum x = values[0] -> getBignum();
            if (x < 0) return new BigNumber(-1);
            else if (x > 0) return new BigNumber(1);
            else return new BigNumber(0);
        }
    };

    class Sin : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(sin(values[0] -> getBignum()));
        }
    };

    class Sinh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(sinh(values[0] -> getBignum()));
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

    class Tan : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(tan(values[0] -> getBignum()));
        }
    };

    class Tanh : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(tanh(values[0] -> getBignum()));
        }
    };

    class ToDegrees : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(to_degrees(values[0] -> getBignum()));
        }
    };

    class ToRadians : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
            else return new BigNumber(to_radians(values[0] -> getBignum()));
        }
    };
}

void Math::initConstants(){
    Variables::set("PI", new BigNumber(3.1415926535));
    Variables::set("E", new BigNumber(2.7182818284));
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
