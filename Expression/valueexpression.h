#ifndef VALUEEXPRESSION_H_INCLUDED
#define VALUEEXPRESSION_H_INCLUDED

#include "expression.h"
#include "../Lib/string.h"
#include "../Lib/array.h"
#include "../Lib/bool.h"
#include "../Lib/functionvalue.h"
#include "../Lib/map.h"
#include "../Lib/bignumber.h"
#include "../Lib/null.h"
class ValueExpression : public Expression{
public:
    Value* value;
    ValueExpression(std::string val){ value = new String(val); }
    ValueExpression(Array val){ value = new Array(val); }
    ValueExpression(bool val){ value = new Bool(val); }
    ValueExpression(Function* val){ value = new FunctionValue(val); }
    ValueExpression(Map val){ value = new Map(val); }
    ValueExpression(Bignum val){ value = new BigNumber(val); }
    ValueExpression(Null null){ value = new Null(); }
    ValueExpression(Value* val);
    Expressions type(){ return Expressions::ValueExpression; }
    Value* eval();
    operator std::string();
    ~ValueExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // VALUEEXPRESSION_H_INCLUDED
