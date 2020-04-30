#include "conditionalexpression.h"
#include "../Lib/bool.h"
#include "../Lib/array.h"
#include "valueexpression.h"
#include "../Exception/operationIsnotsupportedexception.h"
#include <string>
#include <stdexcept>
namespace{
    std::string mas[] = {
        "==", "!=",
        "<", "<=", ">", ">=",
        "&&", "||"
    };
}
Value* ConditionalExpression::eval(){
    Value* value1 = expr1 -> eval();
    Value* value2 = expr2 -> eval();
    bool result;
    if (value1 -> type == Values::FUNCTION || value2 -> type == Values::FUNCTION) throw std::logic_error("Function not condition type");
    if (value1 -> type == Values::STRING){
        if (value2 -> type == Values::ARRAY) throw std::logic_error("String and array not equals type");
        if (value2 -> type == Values::BOOL) throw std::logic_error("String and boolean not equals type");
        if (value2 -> type == Values::NUMBER) throw std::logic_error("String and number not equals type");
        if (value2 -> type == Values::MAP) throw std::logic_error("String and map not equals type");
        std::string string1 = value1 -> getString();
        std::string string2 = value2 -> getString();
        switch(operation){
            case ConditionalOperator::LT: result = string1 < string2; break;
            case ConditionalOperator::LTEQ: result = string1 <= string2; break;
            case ConditionalOperator::GT: result = string1 > string2; break;
            case ConditionalOperator::GTEQ: result = string1 >= string2; break;
            case ConditionalOperator::EQUALS: result = string1 == string2; break;
            case ConditionalOperator::NOT_EQUALS: result = string1 != string2; break;
            default: throw new OperationIsNotSupportedException(mas[(int)operation]); break;
        }
    }
    else if (value1 -> type == Values::NUMBER || value1 -> type == Values::BOOL){
        if (value2 -> type == Values::ARRAY) throw std::logic_error("Double or boolean and array not equals type");
        if (value2 -> type == Values::MAP) throw std::logic_error("Double or boolean and map not equals type");
        if (value2 -> type == Values::STRING) throw std::logic_error("Double or boolean and string not equals type");
        Bignum num1 = (expr1 -> eval()) -> getBignum();
        Bignum num2 = (expr2 -> eval()) -> getBignum();
        switch(operation){
            case ConditionalOperator::LT: result = num1 < num2; break;
            case ConditionalOperator::LTEQ: result = num1 <= num2; break;
            case ConditionalOperator::GT: result = num1 > num2; break;
            case ConditionalOperator::GTEQ: result = num1 >= num2; break;
            case ConditionalOperator::EQUALS: result = num1 == num2; break;
            case ConditionalOperator::NOT_EQUALS: result = num1 != num2; break;
            case ConditionalOperator::AND: result = num1 && num2; break;
            case ConditionalOperator::OR: result = num1 || num2; break;
            default: throw new OperationIsNotSupportedException(mas[(int)operation]); break;
        }
    }
    else if (value1 -> type == Values::ARRAY){
        if (value2 -> type != Values::ARRAY) throw std::logic_error("Array and not array not equals type");
        if (operation == ConditionalOperator::AND) throw std::logic_error("Cannot using logic and for array");
        if (operation == ConditionalOperator::OR) throw std::logic_error("Cannot using logic or for array");
        Array* arr1 = (Array*)value1;
        Array* arr2 = (Array*)value2;
        switch(operation){
            case ConditionalOperator::LT: result = (*arr1) < (*arr2); break;
            case ConditionalOperator::LTEQ: result = (*arr1) <= (*arr2); break;
            case ConditionalOperator::GT: result = (*arr1) > (*arr2); break;
            case ConditionalOperator::GTEQ: result = (*arr1) >= (*arr2); break;
            case ConditionalOperator::EQUALS: result = (*arr1) == (*arr2); break;
            case ConditionalOperator::NOT_EQUALS: result = (*arr1) != (*arr2); break;
            default: throw new OperationIsNotSupportedException(mas[(int)operation]); break;
        }
    }
    else if (value1 -> type == Values::MAP){
        if (value2 -> type != Values::MAP) throw std::logic_error("Msp and not msp not equals type");
        if (operation == ConditionalOperator::AND) throw std::logic_error("Cannot using logic and for map");
        if (operation == ConditionalOperator::OR) throw std::logic_error("Cannot using logic or for map");
        Map* map1 = (Map*)value1;
        Map* map2 = (Map*)value2;
        switch(operation){
            case ConditionalOperator::LT: result = (*map1) < (*map2); break;
            case ConditionalOperator::LTEQ: result = (*map1) <= (*map2); break;
            case ConditionalOperator::GT: result = (*map1) > (*map2); break;
            case ConditionalOperator::GTEQ: result = (*map1) >= (*map2); break;
            case ConditionalOperator::EQUALS: result = (*map1) == (*map2); break;
            case ConditionalOperator::NOT_EQUALS: result = (*map1) != (*map2); break;
            default: throw new OperationIsNotSupportedException(mas[(int)operation]); break;
        }
    }
    return new Bool(result);
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
