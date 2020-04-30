#include "functionreferenceexpression.h"
#include "../Lib/functions.h"

FunctionValue* FunctionReferenceExpression::eval(){
    return new FunctionValue(Functions::get(name));
}

FunctionReferenceExpression::operator std::string(){
    return "::" + name;
}

void FunctionReferenceExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
