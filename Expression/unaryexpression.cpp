#include "unaryexpression.h"
#include "../Lib/bignumber.h"
#include "../Lib/variables.h"
#include "../Lib/bool.h"
#include "../Lib/null.h"
#include "variableexpression.h"
#include "../Exception/typeexception.h"
#include "../Exception/operationIsnotsupportedexception.h"

namespace{
    std::string mas[] = {
        "-", "!", "~", "++", "--"
    };
}

Value* UnaryExpression::eval(){
    Value* val = expr1 -> eval();
    if (val -> type == Values::NULL_) return new Null();
    if (val -> type != Values::NUMBER && val -> type != Values::BOOL) throw new TypeException("Bad argument for unary operation. Double or boolean excepted");
    switch(operation){
        case UnaryOperator::NEGATIVE : return new BigNumber(-(val -> getBignum()));
        case UnaryOperator::NOT : return new Bool(!(val -> getBignum()));
       /// case UnaryOperator::BIT_NOT : return new BigNumber(~(val -> getBignum()));
        case UnaryOperator::PLUSPLUS : return new BigNumber(++(val -> getBignum()));
        case UnaryOperator::MINUSMINUS : return new BigNumber(--(val -> getBignum()));
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
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
