#ifndef RETURNSTATEMENT_H_INCLUDED
#define RETURNSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Value/value.h"

class ReturnStatement : public Statement{
private:
    Expression* expression;
    Value* result;
public:
    ReturnStatement(Expression* expression) : expression(expression) {}
    Statements type(){ return Statements::ReturnStatement; }
    Value* getResult();
    void execute();
    operator std::string();
    ~ReturnStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // RETURNSTATEMENT_H_INCLUDED
