#ifndef UNARYEXPRESSION_H_INCLUDED
#define UNARYEXPRESSION_H_INCLUDED

#include "expression.h"
#include "unaryoperator.h"

class UnaryExpression : public Expression{
private:
    Expression* expr;
    UnaryOperator operation;
public:
    UnaryExpression(UnaryOperator operation, Expression* expr) : operation(operation), expr(expr) {}
    Expressions type(){ return Expressions::UnaryExpression; }
    /** @return  throw: OperationIsNotSupportedException*. */
    static Value* calculate(UnaryOperator operation, Value* value);
    Value* eval();
    operator std::string();
    ~UnaryExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // UNARYEXPRESSION_H_INCLUDED
