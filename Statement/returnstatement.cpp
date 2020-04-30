#include "returnstatement.h"

Value* ReturnStatement::getResult(){
    return result;
}

void ReturnStatement::execute(){
    result = expression -> eval();
    throw this;
}

ReturnStatement::operator std::string(){
    return "return " + std::string(*expression);
}

ReturnStatement::~ReturnStatement(){
    delete expression;
    expression = nullptr;
    delete result;
    result = nullptr;
}

void ReturnStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
