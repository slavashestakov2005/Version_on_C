#ifndef CONTAINERASSIGNMENTSTATEMENT_H_INCLUDED
#define CONTAINERASSIGNMENTSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "../Expression/containeraccessexpression.h"
#include "../Expression/assignmentexpression.h"
#include "../Visitor/assignvalidator.h"

class ContainerAssignmentExpression : public Expression{
private:
    AssignmentOperator operation;
    ContainerAccessExpression* containerExpr;
    Expression* expression;
public:
    ContainerAssignmentExpression(AssignmentOperator operation, ContainerAccessExpression* containerExpr, Expression* expression) : operation(operation), containerExpr(containerExpr), expression(expression) {}
    Expressions type(){ return Expressions::ContainerAssignmentExpression; }
    Value* eval();
    operator std::string();
    ~ContainerAssignmentExpression();
    void accept(Visitor* visitor);
    friend Visitor;
    friend AssignValidator;
};

#endif // CONTAINERASSIGNMENTSTATEMENT_H_INCLUDED
