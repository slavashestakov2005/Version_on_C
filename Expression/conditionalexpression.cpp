#include "conditionalexpression.h"
#include "../Lib/bool.h"
#include "../Lib/array.h"
#include "../Lib/functions.h"
#include "../Lib/classvalue.h"
#include "valueexpression.h"
#include "../Exception/operationIsnotsupportedexception.h"
#include "../Exception/typeexception.h"
#include <string>
#include <stdexcept>

namespace{
    std::string mas[] = {
        "==", "!=",
        "<", "<=", ">", ">=",
        "&&", "||"
    };

    bool operator_gtgt(Value const& a, Value const& b){
        if (a.type != b.type) return false;
        switch(a.type){
            case Values::ARRAY : return *(Array*)(&a) == *(Array*)(&b);
            case Values::BOOL : return *(Bool*)(&a) == *(Bool*)(&b);
            case Values::NUMBER : return *(BigNumber*)(&a) == *(BigNumber*)(&b);
            case Values::FUNCTION : return *(FunctionValue*)(&a) == *(FunctionValue*)(&b);
            case Values::MAP : return *(Map*)(&a) == *(Map*)(&b);
            case Values::STRING : return *(String*)(&a) == *(String*)(&b);
            case Values::NULL_ : return *(Null*)(&a) == *(Null*)(&b);
            case Values::CLASS : return *(ClassValue*)(&a) == *(ClassValue*)(&b);
        }
    }

    bool operator_lt(Value const& a, Value const& b){
        if (a.type != b.type) return int(a.type) < int(b.type);
        switch(a.type){
            case Values::ARRAY : return *(Array*)(&a) < *(Array*)(&b);
            case Values::BOOL : return *(Bool*)(&a) < *(Bool*)(&b);
            case Values::NUMBER : return *(BigNumber*)(&a) < *(BigNumber*)(&b);
            case Values::FUNCTION : return *(FunctionValue*)(&a) < *(FunctionValue*)(&b);
            case Values::MAP : return *(Map*)(&a) < *(Map*)(&b);
            case Values::STRING : return *(String*)(&a) < *(String*)(&b);
            case Values::NULL_ : return *(Null*)(&a) < *(Null*)(&b);
            case Values::CLASS : return *(ClassValue*)(&a) < *(ClassValue*)(&b);
        }
    }
}

Value* ConditionalExpression::calculate(ConditionalOperator operation, Value* left, Value* right){
    bool result;
    switch(operation){
        case ConditionalOperator::EQUALS : result = operator_gtgt(*left, *right); break;
        case ConditionalOperator::NOT_EQUALS : result = !operator_gtgt(*left, *right); break;
        case ConditionalOperator::LT : result = operator_lt(*left, *right); break;
        case ConditionalOperator::LTEQ : result = operator_lt(*left, *right) || operator_gtgt(*left, *right); break;
        case ConditionalOperator::GT : result = operator_lt(*right, *left); break;
        case ConditionalOperator::GTEQ : result = operator_lt(*right, *left) || operator_gtgt(*left, *right); break;
        case ConditionalOperator::AND : result = left -> getBool() && right -> getBool(); break;
        case ConditionalOperator::OR : result = left -> getBool() || right -> getBool(); break;
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
    return new Bool(result);
}

Value* ConditionalExpression::eval(){
    Value* value1 = expr1 -> eval();
    Value* value2 = expr2 -> eval();
    if (Functions::find(mas[(int) operation], 2)){
        std::vector<Value*> vec = { value1, value2 };
        return Functions::get(mas[(int) operation], 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

ConditionalExpression::operator std::string(){
    return "[ " + std::string(*expr1) + " " + mas[int(operation)] + " " + std::string(*expr2) + " ]";
}

ConditionalExpression::~ConditionalExpression(){
    delete expr1;
    expr1 = nullptr;
    delete expr2;
    expr2 = nullptr;
}

void ConditionalExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
