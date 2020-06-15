#ifndef FUNCTIONREFERENCEEXPRESSION_H_INCLUDED
#define FUNCTIONREFERENCEEXPRESSION_H_INCLUDED

#include "expression.h"
#include "../Value/functionvalue.h"

class FunctionReferenceExpression : public Expression{
private:
    std::string name;
public:
    FunctionReferenceExpression(std::string name) : name(name) {}
    Expressions type(){ return Expressions::FunctionalReferenceExpression; }
    FunctionValue* eval();
    operator std::string();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // FUNCTIONREFERENCEEXPRESSION_H_INCLUDED
