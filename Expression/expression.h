#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <string>
#include "../Value/value.h"
#include "../Visitor/node.h"

enum class Expressions{
    ArrayExpression,
    AssignmentExpression,
    BinaryExpression,
    ConditionalExpression,
    ContainerAccessExpression,
    ContainerAssignmentExpression,
    FunctionalExpression,
    FunctionalReferenceExpression,
    MapExpression,
    ObjectCreationExpression,
    TernaryExpression,
    UnaryExpression,
    ValueExpression,
    VariableExpression
};

class Expression : public Node{
public:
    virtual Value* eval() = 0;
    virtual operator std::string() = 0;
    virtual ~Expression(){}
    virtual Expressions type() = 0;
};

#endif // EXPRESSION_H_INCLUDED
