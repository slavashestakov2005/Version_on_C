#ifndef OBJECTCREATIONEXPRESSION_H_INCLUDED
#define OBJECTCREATIONEXPRESSION_H_INCLUDED

#include "expression.h"
#include <vector>
class ObjectCreationExpression : public Expression{
private:
    std::string name;
    std::vector<Expression*> constructorArguments;
public:
    ObjectCreationExpression(std::string name, std::vector<Expression*> constructorArguments) : name(name), constructorArguments(constructorArguments) {}
    Expressions type(){ return Expressions::ObjectCreationExpression; }
    Value* eval();
    operator std::string();
    ~ObjectCreationExpression();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // OBJECTCREATIONEXPRESSION_H_INCLUDED
