#ifndef FUNCTIONSTATEMENT_H_INCLUDED
#define FUNCTIONSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/functionalexpression.h"

class FunctionStatement : public Statement{
private:
    FunctionalExpression* function;
public:
    FunctionStatement(FunctionalExpression* function) : function(function) {}
    Statements type(){ return Statements::FunctionStatement; }
    void execute();
    operator std::string();
    ~FunctionStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // FUNCTIONSTATEMENT_H_INCLUDED
