#ifndef CONTAINERACCESSEXPRESSION_H_INCLUDED
#define CONTAINERACCESSEXPRESSION_H_INCLUDED

#include "expression.h"
#include <vector>
#include "../Lib/array.h"
#include "../Lib/map.h"
#include "containeracceselement.h"
class ContainerAccessExpression : public Expression{
private:
    Expression* root;
    bool rootVariable;
    std::vector<ContainerAccessElement> indices;
public:
    ContainerAccessExpression(std::string variable, std::vector<ContainerAccessElement> indices);
    ContainerAccessExpression(Expression* root, std::vector<ContainerAccessElement> indices);
    Expressions type(){ return Expressions::ContainerAccessExpression; }
    Value* eval();
    Value* get();
    Value* set(Value* value);
    Value* getContainer();
    Value* lastIndex();
    bool lastDot();
    Value* index(int index);
    bool isDot(int index);
    Value* getCopyElement();
    operator std::string();
    ~ContainerAccessExpression(){}
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // CONTAINERACCESSEXPRESSION_H_INCLUDED
