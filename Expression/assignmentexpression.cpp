#include "assignmentexpression.h"
#include "../Lib/variables.h"
#include "../Expression/binaryexpression.h"
#include "../Expression/valueexpression.h"
#include "../Exception/operationIsnotsupportedexception.h"

namespace {
    std::string mas[] = {
        "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "++_", "--_", "_++", "_--"
    };
}

Value* AssignmentExpression::calculate(AssignmentOperator operation, Value* left, Value* right){
    Value* result;
    switch(operation){
        case (AssignmentOperator::ASSIGN) : result = right; break;
        case (AssignmentOperator::ADD) : result = BinaryExpression::calculate(BinaryOperator::ADD, left, right); break;
        case (AssignmentOperator::SUBSTRACT) : result = BinaryExpression::calculate(BinaryOperator::SUBSTRACT , left, right); break;
        case (AssignmentOperator::MULTIPLY) : result = BinaryExpression::calculate(BinaryOperator::MULTIPLY, left, right); break;
        case (AssignmentOperator::DIVIDE) : result = BinaryExpression::calculate(BinaryOperator::DIVIDE, left, right); break;
        case (AssignmentOperator::REMAINDER) : result = BinaryExpression::calculate(BinaryOperator::REMAINDER, left, right); break;
        case (AssignmentOperator::AND) : result = BinaryExpression::calculate(BinaryOperator::AND, left, right); break;
        case (AssignmentOperator::OR) : result = BinaryExpression::calculate(BinaryOperator::OR, left, right); break;
        case (AssignmentOperator::XOR) : result = BinaryExpression::calculate(BinaryOperator::XOR, left, right); break;
        case (AssignmentOperator::LSHIFT) : result = BinaryExpression::calculate(BinaryOperator::LSHIFT, left, right); break;
        case (AssignmentOperator::RSHIFT) : result = BinaryExpression::calculate(BinaryOperator::RSHIFT, left, right); break;
        case (AssignmentOperator::_PLUSPLUS) : result = BinaryExpression::calculate(BinaryOperator::ADD, left, new BigNumber(1)); break;
        case (AssignmentOperator::PLUSPLUS_) : result = BinaryExpression::calculate(BinaryOperator::ADD, left, new BigNumber(1)); break;
        case (AssignmentOperator::_MINUSMINUS) : result = BinaryExpression::calculate(BinaryOperator::SUBSTRACT, left, new BigNumber(1)); break;
        case (AssignmentOperator::MINUSMINUS_) : result = BinaryExpression::calculate(BinaryOperator::SUBSTRACT, left, new BigNumber(1)); break;
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
    return result;
}

#include <iostream>
Value* AssignmentExpression::eval(){
    Value* left = Variables::get(variable);
    Value* right = expression == nullptr ? nullptr : expression -> eval();
    Value* result = calculate(operation, left, right);
    Variables::set(variable, result);
    if (operation == AssignmentOperator::_PLUSPLUS || operation == AssignmentOperator::_MINUSMINUS) result = left;
    return result;
}
AssignmentExpression::operator std::string(){
    return variable + " " + mas[int(operation)] + " " + std::string(*expression);
}
AssignmentExpression::~AssignmentExpression(){
    std::cout << "delete Assignment expession\n";
    delete expression;
    expression = nullptr;
}
void AssignmentExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
