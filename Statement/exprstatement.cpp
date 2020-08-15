#include "exprstatement.h"

void ExprStatement::execute(){
    expression -> eval();
}

ExprStatement::operator std::string(){
    return std::string(*expression);
}

ExprStatement::~ExprStatement(){
    delete expression;
}

void ExprStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
