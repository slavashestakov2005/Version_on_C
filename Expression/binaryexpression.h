#ifndef BINARYEXPRESSION_H_INCLUDED
#define BINARYEXPRESSION_H_INCLUDED

#include "expression.h"
enum class BinaryOperator{
    ADD,        /// +
    SUBSTRACT,  /// -
    MULTIPLY,   /// *
    DIVIDE,     /// /
    REMAINDER,  /// %
    POWER,      /// **

    AND,        /// &
    OR,         /// |
    XOR,        /// ^
    LSHIFT,     /// <<
    RSHIFT      /// >>
};

class BinaryExpression : public Expression{
private:
    Expression* expr1, *expr2;
    BinaryOperator operation;
public:
    BinaryExpression(BinaryOperator operation) : operation(operation), expr1(nullptr), expr2(nullptr) {}
    BinaryExpression(BinaryOperator operation, Expression* expr1, Expression* expr2) : operation(operation), expr1(expr1), expr2(expr2) {}
    Expressions type(){ return Expressions::BinaryExpression; }
    static Value* calculate(BinaryOperator operation, Value* left, Value* right);
    Value* eval();
    Value* eval(Value* value1, Value* value2);
    operator std::string();
    ~BinaryExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // BINARYEXPRESSION_H_INCLUDED
