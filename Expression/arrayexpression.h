#ifndef ARRAYEXPRESSION_H_INCLUDED
#define ARRAYEXPRESSION_H_INCLUDED

#include <vector>
#include "expression.h"

class ArrayExpression : public Expression{
private:
    std::vector<Expression*> elements;
public:
    ArrayExpression(std::vector<Expression*> elements) : elements(elements) {}
    Expressions type(){ return Expressions::ArrayExpression; }
    Value* eval();
    operator std::string();
    ~ArrayExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // ARRAYEXPRESSION_H_INCLUDED
