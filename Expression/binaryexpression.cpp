#include "binaryexpression.h"
#include "../Lib/bignumber.h"
#include "../Lib/string.h"
#include "../Lib/array.h"
#include "valueexpression.h"
#include "../Exception/typeexception.h"
#include "../Exception/mathexception.h"
#include "../Exception/operationIsnotsupportedexception.h"
#include "../Lib/functions.h"
#include "../Lib/null.h"
#include "../Lib/bignumbers/smath.h"
#include <vector>

namespace{
    std::string mas[] = {
        "+", "-", "*", "/", "%", "**",
        "&", "|", "^", "<<", ">>"
    };
}

Value* BinaryExpression::calculate(BinaryOperator operation, Value* left, Value* right){
    if (left -> type == Values::CLASS || right -> type == Values::CLASS) throw new TypeException("Cannot used binary operation for class");
    if (left -> type == Values::FUNCTION || right -> type == Values::FUNCTION) throw new TypeException("Cannot used binary operation for function");
    if (left -> type == Values::NULL_ || right -> type == Values::NULL_) return new Null();
    if (left -> type == Values::MAP && right -> type != Values::MAP && right -> type != Values::STRING) throw new TypeException("Cannot used binary operation for map and not map and not string");
    if (right -> type == Values::MAP && left -> type != Values::MAP && left -> type != Values::STRING) throw new TypeException("Cannot used binary operation for not map and not string and array");
    if (left -> type == Values::ARRAY && right -> type == Values::ARRAY){
        if (operation != BinaryOperator::ADD) throw new TypeException("Cannot used array and array for not plus operation");
        return Array::add((Array*) left, (Array*) right);
    }
    if (left -> type == Values::MAP && right -> type == Values::MAP){
        if (operation != BinaryOperator::ADD) throw new TypeException("Cannot used map and map for not plus operation");
        return Map::add((Map*) left, (Map*) right);
    }
    if (left -> type == Values::ARRAY){
        if (operation != BinaryOperator::ADD) throw new TypeException("Cannot used not plus binary operation for array");
        return Array::add((Array*) left, right);
    }
    if (right -> type == Values::ARRAY && left -> type != Values::STRING){
        throw new TypeException("Cannot used binary plus for not string, not array and array");
    }
    if (left -> type == Values::STRING || right -> type == Values::STRING){
        std::string string1 = left -> getString();
        std::string string2 = right -> getString();
        switch(operation){
            case BinaryOperator::ADD : return new String(string1 + string2);
            case BinaryOperator::MULTIPLY : {
                if (right -> type != Values::NUMBER) throw new TypeException("Unknown multiply for not number and not number");
                int iterations = right -> getDouble();
                std::string result;
                for(int i = 0; i < iterations; ++i) result += string1;
                return new String(result);
            }
            default: throw new OperationIsNotSupportedException(mas[(int)operation], "for string");
        }
    }
    Bignum num1 = left -> getBignum();
    Bignum num2 = right -> getBignum();
    Bignum result;
    ///long long lon1 = num1, lon2 = num2;
    switch(operation){
        case BinaryOperator::ADD : result = BigNumber(num1 + num2); break;
        case BinaryOperator::SUBSTRACT : result = BigNumber(num1 - num2); break;
        case BinaryOperator::MULTIPLY : result = BigNumber(num1 * num2); break;
        case BinaryOperator::DIVIDE : result = BigNumber(num1 / num2); break;
        case BinaryOperator::REMAINDER : result = BigNumber(num1 % num2); break;
        case BinaryOperator::POWER : result = pow(num1, num2); break;
///        case BinaryOperator::AND: return new BigNumber(lon1 & lon2);
///        case BinaryOperator::OR: return new BigNumber(lon1 | lon2);
///        case BinaryOperator::XOR: return new BigNumber(lon1 ^ lon2);
///        case BinaryOperator::LSHIFT: return new BigNumber(lon1 << lon2);
///        case BinaryOperator::RSHIFT: return new BigNumber(lon1 >> lon2);
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
    return new BigNumber(result);
}

Value* BinaryExpression::eval(){
    Value* value1 = expr1 -> eval();
    Value* value2 = expr2 -> eval();
    if (Functions::find(mas[int(operation)], 2)){
        std::vector<Value*> vec = {value1, value2};
        return Functions::get(mas[int(operation)], 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

BinaryExpression::operator std::string(){
    return "[" + std::string(*expr1) + " " + mas[int(operation)] + " " + std::string(*expr2) + "]";
}

void BinaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

BinaryExpression::~BinaryExpression(){
    delete expr1;
    expr1 = nullptr;
    delete expr2;
    expr2 = nullptr;
}
