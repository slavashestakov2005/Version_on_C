#ifndef EXPRSTATEMENT_H_INCLUDED
#define EXPRSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

class ExprStatement : public Statement{
    Expression* expression;
public:
    ExprStatement(Expression* expression) : expression(expression) {}
    Statements type(){ return Statements::ExprStatement; }
    void execute();
    operator std::string();
    ~ExprStatement();
    void accept(Visitor* visitor);
    friend Visitor;
};

#endif // EXPRSTATEMENT_H_INCLUDED
