#ifndef UNARYEXPRESSION_H_INCLUDED
#define UNARYEXPRESSION_H_INCLUDED

#include "expression.h"

enum class UnaryOperator{
    PLUS,           /// +
    NEGATIVE,       /// -
    NOT,            /// !
    COMPLEMENT,     /// ~
    PLUSPLUS,       /// ++
    MINUSMINUS,     /// --
};

class UnaryExpression : public Expression{
private:
    Expression* expr1;
    UnaryOperator operation;
public:
    UnaryExpression(UnaryOperator operation, Expression* expr1) : operation(operation), expr1(expr1) {}
    Expressions type(){ return Expressions::UnaryExpression; }
    static Value* calculate(UnaryOperator operation, Value* value);
    Value* eval();
    operator std::string();
    ~UnaryExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // UNARYEXPRESSION_H_INCLUDED
