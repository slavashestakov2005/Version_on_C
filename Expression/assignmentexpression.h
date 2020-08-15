#ifndef ASSIGNMENTEXPRESSION_H_INCLUDED
#define ASSIGNMENTEXPRESSION_H_INCLUDED

#include "assignmentoperator.h"
#include "expression.h"
#include "../Visitor/assignvalidator.h"
#include "../Visitor/variableprinter.h"

class AssignmentExpression : public Expression{
private:
    AssignmentOperator operation;
    Expression* expression;
public:
    std::string variable;
    AssignmentExpression(AssignmentOperator operation, std::string variable, Expression* expression) : operation(operation), variable(variable), expression(expression) {}
    Expressions type(){ return Expressions::AssignmentExpression; }
    /** @return  throw: OperationIsNotSupportedException*. */
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
