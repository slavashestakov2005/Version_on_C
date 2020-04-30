#include "containerassignmentexpression.h"
#include "../Lib/variables.h"
#include <stdexcept>
#include "../Expression/binaryexpression.h"
#include "../Expression/unaryexpression.h"
#include "../Expression/valueexpression.h"
#include "../Exception/typeexception.h"

namespace {
    std::string mas[] = {
        "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "++_", "--_", "_++", "_--"
    };
}

Value* ContainerAssignmentExpression::eval(){
    Value* result = containerExpr -> getCopyElement();
    containerExpr -> set(AssignmentExpression::calculate(operation, containerExpr -> get(), expression -> eval()));
    if (operation != AssignmentOperator::_PLUSPLUS && operation != AssignmentOperator::_MINUSMINUS) result = containerExpr -> getContainer();
    return result;
}

ContainerAssignmentExpression::operator std::string(){
    return std::string(*containerExpr) + mas[int(operation)] + std::string(*expression);
}
ContainerAssignmentExpression::~ContainerAssignmentExpression(){
    delete expression;
    expression = nullptr;
}
void ContainerAssignmentExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
