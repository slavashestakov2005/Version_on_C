#include "unaryexpression.h"
#include "../Lib/bignumber.h"
#include "../Lib/variables.h"
#include "../Lib/bool.h"
#include "../Lib/null.h"
#include "../Lib/functions.h"
#include "variableexpression.h"
#include "../Exception/typeexception.h"
#include "../Exception/operationIsnotsupportedexception.h"

namespace{
    std::string mas[] = {
        "+", "-", "!", "~", "++", "--"
    };
}

Value* UnaryExpression::calculate(UnaryOperator operation, Value* value){
    if (value -> type == Values::NULL_) return Null::NULL_;
    switch(operation){
        case UnaryOperator::PLUS : return new BigNumber(value -> getBignum());
        case UnaryOperator::NEGATIVE : return new BigNumber(-(value -> getBignum()));
        case UnaryOperator::NOT : return new Bool(!(value -> getBignum()));
        /// case UnaryOperator::COMPLEMENT : return new BigNumber(~(value -> getBignum()));
        case UnaryOperator::PLUSPLUS : return new BigNumber(++(value -> getBignum()));
        case UnaryOperator::MINUSMINUS : return new BigNumber(--(value -> getBignum()));
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
}

Value* UnaryExpression::eval(){
    Value* val = expr1 -> eval();
    if (Functions::find(mas[(int) operation], 1)){
        std::vector<Value*> value;
        value.push_back(val);
        return Functions::get(mas[(int) operation], 1) -> execute(value);
    }
    return calculate(operation, val);
}
UnaryExpression::operator std::string(){
    return mas[int(operation)] + " " + std::string(*expr1);
}
UnaryExpression::~UnaryExpression(){
    delete expr1;
    expr1 = nullptr;
}
void UnaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
