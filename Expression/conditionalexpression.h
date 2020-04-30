#ifndef CONDITIONALEXPRESSION_H_INCLUDED
#define CONDITIONALEXPRESSION_H_INCLUDED

#include "expression.h"
enum class ConditionalOperator{
    EQUALS,     /// ==
    NOT_EQUALS, /// !=

    LT,         /// <
    LTEQ,       /// <=
    GT,         /// >
    GTEQ,       /// >=

    AND,        /// &&
    OR          /// ||
};
class ConditionalExpression : public Expression{
private:
    Expression* expr1, *expr2;
    ConditionalOperator operation;
public:
    ConditionalExpression(ConditionalOperator operation, Expression* expr1, Expression* expr2) : operation(operation), expr1(expr1), expr2(expr2) {}
    Expressions type(){ return Expressions::ConditionalExpression; }
    Value* eval();
    operator std::string();
    ~ConditionalExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // CONDITIONALEXPRESSION_H_INCLUDED
