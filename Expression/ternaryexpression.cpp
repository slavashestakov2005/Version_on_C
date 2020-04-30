#include "ternaryexpression.h"

Value* TernaryExpression::eval(){
    if (condition -> eval() -> getDouble()) return trueExpr -> eval();
    else return falseExpr -> eval();
}

TernaryExpression::operator std::string(){
    return std::string(*condition) + " ? " + std::string(*trueExpr) + " : " + std::string(*falseExpr);
}

TernaryExpression::~TernaryExpression(){
    delete condition;
    condition = nullptr;
    delete trueExpr;
    trueExpr = nullptr;
    delete falseExpr;
    falseExpr = nullptr;
}

void TernaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
