#ifndef MAPEXPRESSION_H_INCLUDED
#define MAPEXPRESSION_H_INCLUDED

#include <map>
#include "expression.h"

class MapExpression : public Expression{
private:
    std::map<Expression*, Expression*> elements;
public:
    MapExpression(std::map<Expression*, Expression*> elements) : elements(elements) {}
    Expressions type(){ return Expressions::MapExpression; }
    Value* eval();
    operator std::string();
    ~MapExpression(){}
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // MAPEXPRESSION_H_INCLUDED
