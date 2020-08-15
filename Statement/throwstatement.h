#ifndef THROWSTATEMENT_H_INCLUDED
#define THROWSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Value/value.h"

class ThrowStatement : public Statement{
private:
    Expression* expression;
    Value* result;
public:
    ThrowStatement(Expression* expression) : expression(expression) {}
    Statements type(){ return Statements::ThrowStatement; }
    Value* getResult();
    /** @return  throw: ThrowStatement*. */
    void execute();
    operator std::string();
    ~ThrowStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // THROWSTATEMENT_H_INCLUDED
