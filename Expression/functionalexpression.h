#ifndef FUNCTIONALEXPRESSION_H_INCLUDED
#define FUNCTIONALEXPRESSION_H_INCLUDED

#include <vector>
#include "expression.h"
#include "../Lib/function.h"

class FunctionalExpression : public Expression{
private:
    Expression* functionExpr;
    std::vector<Expression*> arguments;
    Function* getFunction(std::string name);
    Function* consumeFunction(Expression* expr);
public:
    FunctionalExpression(Expression* functionExpr) : functionExpr(functionExpr) {}
    Expressions type(){ return Expressions::FunctionalExpression; }
    void addArguments(Expression* argument);
    Value* eval();
    operator std::string();
    ~FunctionalExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // FUNCTIONALEXPRESSION_H_INCLUDED
