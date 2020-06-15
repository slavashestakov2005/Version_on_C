#include "unaryexpression.h"
#include "../Value/bignumbervalue.h"
#include "../Lib/variables.h"
#include "../Value/boolvalue.h"
#include "../Value/nullvalue.h"
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
    if (value -> type() == Values::NULL_) return NullValue::NULL_;
    switch(operation){
        case UnaryOperator::PLUS : return new BigNumberValue(value -> asBignum());
        case UnaryOperator::NEGATIVE : return new BigNumberValue(-(value -> asBignum()));
        case UnaryOperator::NOT : return new BoolValue(!(value -> asBignum()));
        /// case UnaryOperator::COMPLEMENT : return new BigNumber(~(value -> asBignum()));
        case UnaryOperator::PLUSPLUS : return new BigNumberValue(++(value -> asBignum()));
        case UnaryOperator::MINUSMINUS : return new BigNumberValue(--(value -> asBignum()));
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
    return "[" + mas[int(operation)] + " " + std::string(*expr1) + "]";
}
UnaryExpression::~UnaryExpression(){
    delete expr1;
    expr1 = nullptr;
}
void UnaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
