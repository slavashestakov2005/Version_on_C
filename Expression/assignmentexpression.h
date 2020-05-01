#ifndef ASSIGNMENTEXPRESSION_H_INCLUDED
#define ASSIGNMENTEXPRESSION_H_INCLUDED

#include "expression.h"
#include "../Visitor/variableprinter.h"
#include "../Visitor/assignvalidator.h"

enum class AssignmentOperator{
    ASSIGN,
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,
    REMAINDER,
    POWER,

    AND,
    OR,
    XOR,
    LSHIFT,
    RSHIFT,

    PLUSPLUS_,
    MINUSMINUS_,
    _PLUSPLUS,
    _MINUSMINUS
};

class AssignmentExpression : public Expression{
private:
    AssignmentOperator operation;
    Expression* expression;
public:
    std::string variable;
    AssignmentExpression(AssignmentOperator operation, std::string variable, Expression* expression) : operation(operation), variable(variable), expression(expression) {}
    Expressions type(){ return Expressions::AssignmentExpression; }
    static Value* calculate(AssignmentOperator operation, Value* left, Value* right);
    Value* eval();
    operator std::string();
    ~AssignmentExpression();
    void accept(Visitor* visitor);
    friend Visitor;
    friend VariablePrinter;
    friend AssignValidator;
};

#endif // ASSIGNMENTEXPRESSION_H_INCLUDED
