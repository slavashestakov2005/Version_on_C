#include "exprtostat.h"

void ExprToStat::execute(){
    expression -> eval();
}

ExprToStat::operator std::string(){
    return std::string(*expression);
}

ExprToStat::~ExprToStat(){
    delete expression;
}

void ExprToStat::accept(Visitor* visitor){
    visitor -> visit(this);
}
